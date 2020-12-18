/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:30:42 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 01:58:01 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo1.h"

int				main(int ac, const char **av)
{
	t_shared	sh;
	static const char err_args_nb[] = "Error: Bad number of arguments\n";
	static const char err_args_val[] = \
		"Error: Invalid: input or memory block allocated\n";

	if (ac < 5 || ac > 6)
		return (write(STDERR_FILENO, err_args_nb, sizeof(err_args_nb)));
	if (!parse(&sh, ac, av) || !engine(&sh))
		return (destroy_mutexes(&sh) && write(STDERR_FILENO, \
			err_args_val, sizeof(err_args_val)));
	pthread_mutex_lock(&sh.end);
	destroy_mutexes(&sh);
	return (0);
}