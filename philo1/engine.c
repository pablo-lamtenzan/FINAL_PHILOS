/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:21:06 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 01:25:41 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

#include <stdio.h>

/*
** All the "eating done" mutexes are locked in the init.
** Trying to lock locked mutexes "locks" the thread until
** the mutex is locked, if the mutex is unlocked the thread can
** proceed.
** Each time a philo eats a mutex will be unlocked. If the philos
** unlock more mutextes than they are allowed the program ends.
*/

static void		*overeat_persistent_checker(void *arg)
{
	t_shared *const	sh = (t_shared*const)arg;
	int32_t			i;
	uint32_t		y;

	if (sh->max_meals <= 0)
		return (arg);
	i = -1;
	while (++i < sh->max_meals && !(y = 0))
	{
		while (y < sh->nb)
		{
			if (sh->exited == true)
				return (arg);
			pthread_mutex_lock(&sh->philosophers[y++].eating_done);
		}
	}
	if (sh->exited == true)
		return (arg);
	sh->exited = true;
	msg(&sh->philosophers[0], MSG_OVEREAT);
	pthread_mutex_unlock(&sh->end);
	return (arg);
}

/*
** This function is a used like a deamon for each philosopher.
** It will perform a persistent check the remaining time each
** philosopher has before die in case it doesn't eat enought
** frequently.
*/

static void		*starved_persistent_checker(void *arg)
{
	t_philo *const	p = (t_philo*const)arg;
	t_shared *const	sh = p->shared;
	bool			died;

	died = false;
	while (died == false)
	{
		pthread_mutex_lock(&p->mutex);
		if (sh->exited == true)
			return ((void*)(int64_t)pthread_mutex_unlock(&p->mutex));
		died = philo_is_starved(p);
		pthread_mutex_unlock(&p->mutex);
		died == false ? usleep(1000) : 0;
	}
	sh->exited = true;
	msg(p, MSG_DIE);
	pthread_mutex_unlock(&p->shared->end);
	return (arg);
}

/*
** This is the routine made by each philosopher. Each philosopher
** will run it own straved persistent checker.
*/

static void		*philo_routine(void *arg)
{
	pthread_t			tid;
	uint8_t				i;
	t_philo	*const		p = (t_philo*const)arg;
	static void			(*const actions[])(t_philo *const) = {
		&ph_take_forks,
		&ph_eat,
		&ph_drop_forks,
		&ph_sleep,
		&ph_think
	};

	i = 1;
	p->eate_time = get_time();
	p->remaining_time = p->eate_time + p->shared->time_to_die;
	if (ft_thread_detacher(&tid, &starved_persistent_checker, arg))
		return (NULL);
	while (i % ((sizeof(actions) / sizeof(*actions)) + 1ul) || (i = 1))
		actions[i++ - 1](p);
	return (arg);
}

/*
** Main engine fucntion: will run a global overeat persistent checker and
** all the required philosophers with their starved persistent checkers.
*/

bool			engine(t_shared *const sh)
{
	pthread_t	tid;
	uint32_t	i;

	sh->born_date = get_time();
	if (ft_thread_detacher(&tid, &overeat_persistent_checker, (void*)sh))
		return (false);
	i = 0;
	while (i < sh->nb)
	{
		if (ft_thread_detacher(&tid, &philo_routine, \
				(void*)&sh->philosophers[i++]))
			return (false);
		usleep(100);
	}
	return (true);
}
