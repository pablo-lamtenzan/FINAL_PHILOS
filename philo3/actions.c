/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:11:21 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 18:48:41 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

bool			ph_take_forks(t_philo *const p)
{
	return (!sem_wait(p->shared->forks)
		&& msg(p, MSG_FORK)
		&& !sem_wait(p->shared->forks)
		&& msg(p, MSG_FORK));
}

bool			ph_drop_forks(t_philo *const p)
{
	return (!sem_post(p->shared->forks)
	&& !sem_post(p->shared->forks));
}

bool			ph_eat(t_philo *const p)
{
	if (sem_wait(p->mutex))
		return (false);
	p->is_eating = true;
	p->eate_time = get_time();
	p->remaining_time = p->eate_time + p->shared->time_to_die;
	if (!msg(p, MSG_EATING))
		return (false);
	usleep(p->shared->time_to_eat * 1000ul);
	p->is_eating = false;
	return (!sem_post(p->mutex) && !sem_post(p->eating_done));
}

bool			ph_think(t_philo *const p)
{
	return (msg(p, MSG_THINKING));
}

bool			ph_sleep(t_philo *const p)
{
	return (msg(p, MSG_SPLEEPING)
		&& !usleep(p->shared->time_to_sleep * 1000ul));
}
