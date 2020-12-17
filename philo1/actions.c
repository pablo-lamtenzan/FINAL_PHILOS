/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:34:00 by pablo             #+#    #+#             */
/*   Updated: 2020/12/16 22:55:05 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void		ph_take_forks(t_philo *const p)
{
	pthread_mutex_lock(&p->shared->forks[p->left_fork]);
	msg(p, MSG_FORK);
	pthread_mutex_lock(&p->shared->forks[p->right_fork]);
	msg(p, MSG_FORK);
}

void		ph_drop_forks(t_philo *const p)
{
	pthread_mutex_unlock(&p->shared->forks[p->left_fork]);
	pthread_mutex_unlock(&p->shared->forks[p->right_fork]);
}

void		ph_eat(t_philo *const p)
{
	pthread_mutex_lock(&p->mutex);
	p->is_eating = true;
	p->eate_time = get_time();
	p->remaining_time = p->eate_time + p->shared->time_to_die;
	msg(p, MSG_EATING);
	usleep(p->shared->time_to_eat * 1000ul);
	p->is_eating = false;
	pthread_mutex_unlock(&p->mutex);
	pthread_mutex_unlock(&p->eating_done);
}

void		ph_think(t_philo *const p)
{
	msg(p, MSG_THINKING);
}

void		ph_sleep(t_philo *const p)
{
	msg(p, MSG_SPLEEPING);
	usleep(p->shared->time_to_sleep * 1000ul);
}
