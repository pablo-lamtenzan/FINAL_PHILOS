/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 23:29:02 by plamtenz          #+#    #+#             */
/*   Updated: 2020/12/17 02:01:26 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

static const char	*output(uint8_t code)
{
	uint64_t			i;
	uint8_t				tmp;
	static const char	*messages[] = {
		" is eating\n",
		" is sleeping\n",
		" is thinking\n",
		" has taken a fork\n",
		" has died\n",
		"MAX EAT TIMES ALLOWED REACHED\n"
	};

	i = 0;
	tmp = 1;
	while (!(tmp & code) && (++i))
		tmp = tmp << 1;
	return (i < sizeof(messages) / sizeof(*messages) ? messages[i] : NULL);
}

static void			print_time(t_philo *p)
{
	static const char ms[] = "ms\t";

	ft_putnbr_fd(get_time() - p->shared->born_date, STDOUT_FILENO);
	write(STDOUT_FILENO, ms, sizeof(ms));
}

bool				msg(t_philo *const p, uint8_t code)
{
	static bool		all_are_alive = true;

	if (sem_wait(p->shared->output))
		return (false);
	if (all_are_alive)
	{
		print_time(p);
		if (code & (MSG_DIE | MSG_OVEREAT))
			all_are_alive = false;
		if (!(code & MSG_OVEREAT))
			ft_putnbr_fd((uint64_t)(p->index + 1), STDOUT_FILENO);
		write(STDOUT_FILENO, output(code), ft_strlen(output(code)));
	}
	return (!sem_post(p->shared->output));
}
