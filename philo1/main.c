/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:30:42 by pablo             #+#    #+#             */
/*   Updated: 2020/12/16 23:22:50 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo1.h"

// heap used after free: ./philo_one 10 800 200 100 1 (this cmd x2)
// happends in all the cases
// i ve freed the philos and then a thread use philosopers
// happends en both case: philo starved and philo max eat

// old has segfualt 1 time (can't reproduce) ./philo_one 10 800 200 100 1

// test the share->end

int				main(int ac, const char **av)
{
	t_shared	sh;
	static const char err_args_nb[] = "Error: Bad number of arguments\n";
	static const char err_args_val[] = \
		"Error: Invalid: input or memory block allocated\n";

	// TO DO: Last arg == 1
	if (ac < 5 || ac > 6)
		return (write(STDERR_FILENO, err_args_nb, sizeof(err_args_nb)));
	if (!parse(&sh, ac, av) || !engine(&sh))
		return (destroy_mutexes(&sh) && write(STDERR_FILENO, \
			err_args_val, sizeof(err_args_val)));
	// TO DO: Correct this stuff
	pthread_mutex_lock(&sh.end);
	//pthread_mutex_unlock(&sh.end);
	destroy_mutexes(&sh);
	return (0);
}