/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:36:18 by plamtenz          #+#    #+#             */
/*   Updated: 2020/12/17 02:00:01 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

uint64_t		u64_atoi(const char **av, size_t index)
{
	const int			tmp = ft_atoi(av[index]);

	return (tmp < 0 ? 0 : (uint64_t)tmp);
}

int				main(int ac, const char **argv)
{
	t_shared			sh;
	static const char	err_args_nb[] = "Error: Bad number of arguments\n";
	static const char	err_args_val[] = \

	"Error: Invalid: input or memory block allocated\n";
	if (ac < 5 || ac > 6)
		return (write(STDERR_FILENO, err_args_nb, sizeof(err_args_nb)));
	if (!parse(&sh, ac, argv) || !engine(&sh))
	{
		destroy_semaphores(&sh);
		return (write(STDERR_FILENO, err_args_val, sizeof(err_args_val)));
	}
	sem_wait(sh.end);
	destroy_semaphores(&sh);
	return (0);
}
