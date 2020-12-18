/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:36:01 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 03:07:24 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo3.h"

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
			if (sem_wait(sh->philosophers[y++].eating_done))
				return (NULL);
		}
	}
	if (sh->exited == true)
			return (arg);
	sh->exited = true;
	if (!msg(&sh->philosophers[0], MSG_OVEREAT) || sem_post(sh->end))
		return (NULL);
	return (arg);
}

static void		*starved_persistent_checker(void *arg)
{
	t_philo *const	p = (t_philo*const)arg;
	t_shared *const	sh = p->shared;
	bool			died;

	died = false;
	while (died == false)
	{
		if (sh->exited == false && sem_wait(p->mutex))
			return (NULL);
		if (sh->exited == true)
			return ((void*)(int64_t)sem_post(p->mutex));
		died = philo_is_starved(p);
		if (sh->exited == false && sem_post(p->mutex))
			return (NULL);
		died == false ? usleep(1000) : 0;
	}
	sh->exited = true;
	if (!msg(p, MSG_DIE) || sem_post(p->shared->end))
		return (NULL);
	return (arg);
}

static void		*philo_routine(void *arg)
{
	pthread_t			tid;
	uint8_t				i;
	t_philo	*const		p = (t_philo*const)arg;
	static bool			(*const actions[])(t_philo *const) = {
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
		if (!actions[i++ - 1](p))
			return (NULL);
	return (arg);
}

bool			engine(t_shared *sh)
{
	pthread_t	tid;
	uint32_t	i;

	sh->born_date = get_time();
	if (ft_thread_detacher(&tid, &overeat_persistent_checker, (void*)sh))
		return (false);
	i = 0;
	while (i < sh->nb)
	{
		if (!(sh->philosophers[i].pid = fork()))
		{
			philo_routine((void*)&sh->philosophers[i]);
			exit(EXIT_SUCCESS);
		}
		else if (sh->philosophers[i].pid < 0)
			return (false);
		i++;
		usleep(100);
	}
	return (true);
}