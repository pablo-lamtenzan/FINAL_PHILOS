/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:26:11 by pablo             #+#    #+#             */
/*   Updated: 2020/12/17 20:18:13 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo3.h"

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
	if (sem_wait(p->shared->output) || sem_wait(p->shared->nobody_dead))
		return (false);
	print_time(p);
	if (!(code & (MSG_DIE | MSG_OVEREAT)) && sem_post(p->shared->nobody_dead))
		return (false);
	if (!(code & MSG_OVEREAT))
		ft_putnbr_fd((uint64_t)(p->index + 1), STDOUT_FILENO);
	write(STDOUT_FILENO, output(code), ft_strlen(output(code)));
	return (!sem_post(p->shared->output));
}