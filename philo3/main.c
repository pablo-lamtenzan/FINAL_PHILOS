/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:47:28 by pablo             #+#    #+#             */
/*   Updated: 2020/12/17 02:34:28 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo3.h"
# include <sys/wait.h>
# include <signal.h>

void			zombies_killer(t_shared sh)
{
	uint32_t	nb;
	uint32_t	i;

	i = 0;
	while (i < sh.nb)
		kill(sh.philosophers[i++].pid, SIGTERM);
	nb = sh.nb;
	while (nb)
	{
		if (waitpid(0, NULL, WNOHANG) > 0)
			nb--;
	}
}

uint64_t				u64_atoi(const char **av, size_t index)
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
	zombies_killer(sh);
	destroy_semaphores(&sh);
	return (0);
}