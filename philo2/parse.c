/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:42:18 by plamtenz          #+#    #+#             */
/*   Updated: 2020/12/19 20:04:07 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

#include <fcntl.h>

char				*sem_name(const char *name, int index)
{
	int				i;
	char			*dest;

	if (!(dest = malloc(sizeof(char) * UINT8_MAX)))
		return (NULL);
	i = ft_strlcpy(dest, name, ft_strlen(name));
	while (index > 0)
	{
		dest[i++] = (index % 10) + '0';
		index /= 10;
	}
	dest[i] = 0;
	return (dest);
}

static sem_t		*new_sem(char *name, size_t nb)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 420, nb));
}

static bool			init_all(t_shared *const sh)
{
	uint32_t		i;
	char			*name;

	i = -1;
	while (++i < sh->nb)
	{
		sh->philosophers[i].index = i;
		sh->philosophers[i].left_fork = i;
		sh->philosophers[i].right_fork = (i + 1) % sh->nb;
		sh->philosophers[i].is_eating = false;
		sh->philosophers[i].shared = sh;
		if (!(sh->philosophers[i].mutex = \
				new_sem(name = sem_name(SEM_PHILO, i), 1)))
		{
			free(name);
			return (false);
		}
		free(name);
		if (!(sh->philosophers[i].eating_done = \
				new_sem(name = sem_name(SEM_EAT, i), 0)))
		{
			free(name);
			return (false);
		}
		free(name);
	}
	if (!(sh->forks = new_sem(SEM_FORK, sh->nb)) \
			|| !(sh->output = new_sem(SEM_OUTPUT, 1)) \
			|| !(sh->end = new_sem(SEM_DEAD, 0)))
		return (false);
	return (true);
}

static uint32_t		u32_atoi(const char **av, size_t index)
{
	const int		tmp = ft_atoi(av[index]);

	return (tmp < 0 ? 0 : (uint32_t)tmp);
}

bool				parse(t_shared *const sh, int ac, const char **av)
{
	sh->philosophers = NULL;
	sh->forks = NULL;
	sh->exited = false;
	if (((sh->nb = u32_atoi(av, 1ul)) > MAX_PHILO_NB || sh->nb < MIN_PHILO_NB) \
		|| (sh->time_to_die = u64_atoi(av, 2ul)) < ARGS_LIMIT \
		|| (sh->time_to_eat = u64_atoi(av, 3ul)) < ARGS_LIMIT \
		|| (sh->time_to_sleep = u64_atoi(av, 4ul)) < ARGS_LIMIT \
		|| (sh->max_meals = ac == 6 ? ft_atoi(av[5]) : 0) < 0 \
		|| !(sh->philosophers = malloc(sizeof(t_philo) * sh->nb)))
		return (false);
	sh->max_meals = sh->max_meals == 0 ? -1 : sh->max_meals;
	return (init_all(sh));
}
