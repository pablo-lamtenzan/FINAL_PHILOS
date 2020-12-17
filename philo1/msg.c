/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:01:08 by pablo             #+#    #+#             */
/*   Updated: 2020/12/16 23:45:10 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

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

void				msg(t_philo *const p, uint8_t code)
{
	static bool		all_are_alive = true;

	pthread_mutex_lock(&p->shared->output);
	if (all_are_alive)
	{
		print_time(p);
		if (code & (MSG_DIE | MSG_OVEREAT))
			all_are_alive = false;
		if (!(code & MSG_OVEREAT))
			ft_putnbr_fd((uint64_t)(p->index + 1), STDOUT_FILENO);
		write(STDOUT_FILENO, output(code), ft_strlen(output(code)));
	}
	pthread_mutex_unlock(&p->shared->output);
}
