/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 00:17:30 by pablo             #+#    #+#             */
/*   Updated: 2020/12/17 00:17:31 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo2.h"

int			ft_thread_detacher(pthread_t *const tid,
	void *(*start_routine)(void*), void *arg)
{
	const int	ret = pthread_create(tid, NULL, start_routine, arg);

	return (!ret && pthread_detach(*tid));
}

bool		philo_is_starved(t_philo *const p)
{
	return (!p->is_eating && get_time() > p->remaining_time);
}
