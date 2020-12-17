/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:11:35 by pablo             #+#    #+#             */
/*   Updated: 2020/12/17 00:26:03 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"
#include <stdlib.h>

static bool			init_all(t_shared *const sh)
{
	uint32_t		i;

	if (!(sh->forks = malloc(sizeof(pthread_mutex_t) * sh->nb)))
		return (false);
	i = 0;
	while (i < sh->nb)
	{
		sh->philosophers[i].index = i;
		sh->philosophers[i].left_fork = i;
		sh->philosophers[i].right_fork = (i + 1u) % sh->nb;
		sh->philosophers[i].is_eating = false;
		sh->philosophers[i].shared = sh;
		if (pthread_mutex_init(&sh->philosophers[i].mutex, NULL)
				|| pthread_mutex_init(&sh->philosophers[i].eating_done, NULL))
			return (false);
		pthread_mutex_lock(&sh->philosophers[i++].eating_done);
	}
	if (!(i = 0) && (pthread_mutex_init(&sh->output, NULL)
			|| pthread_mutex_init(&sh->end, NULL)))
		return (false);
	pthread_mutex_lock(&sh->end);
	while (i < sh->nb)
		if (pthread_mutex_init(&sh->forks[i++], NULL))
			return (false);
	return (true);
}

static uint32_t		u32_atoi(const char **av, size_t index)
{
	const int		tmp = ft_atoi(av[index]);

	return (tmp < 0 ? 0 : (uint32_t)tmp);
}

static uint64_t		u64_atoi(const char **av, size_t index)
{
	const int		tmp = ft_atoi(av[index]);

	return (tmp < 0 ? 0 : (uint64_t)tmp);
}

bool				parse(t_shared *const sh, int ac, const char **av)
{
	sh->philosophers = NULL;
	sh->forks = NULL;
	if (((sh->nb = u32_atoi(av, 1ul)) > MAX_PHILO_NB || sh->nb < MIN_PHILO_NB)
	|| (sh->time_to_die = u64_atoi(av, 2ul)) < ARGS_LIMIT
	|| (sh->time_to_eat = u64_atoi(av, 3ul)) < ARGS_LIMIT
	|| (sh->time_to_sleep = u64_atoi(av, 4ul)) < ARGS_LIMIT
	|| (sh->max_meals = ac == 6 ? ft_atoi(av[5]) : 0) < 0
	|| !(sh->philosophers = malloc(sizeof(t_philo) * sh->nb)))
		return (false);
	sh->max_meals = sh->max_meals == 0 ? -1 : sh->max_meals;
	return (init_all(sh));
}
