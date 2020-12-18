/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:35:20 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 01:16:29 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

#include <stdlib.h>

bool			destroy_mutexes(t_shared *const sh)
{
	uint32_t	i;

	if (sh->philosophers)
	{
		i = -1;
		while (++i < sh->nb)
		{
			pthread_mutex_lock(&sh->philosophers[i].mutex);
			pthread_mutex_unlock(&sh->philosophers[i].mutex);
			pthread_mutex_destroy(&sh->philosophers[i].mutex);
			pthread_mutex_destroy(&sh->philosophers[i].eating_done);
		}
		free(sh->philosophers);
	}
	if (sh->forks)
	{
		i = -1;
		while (++i < sh->nb)
			pthread_mutex_destroy(&sh->forks[i]);
		free(sh->forks);
	}
	pthread_mutex_destroy(&sh->output);
	pthread_mutex_destroy(&sh->end);
	return (true);
}
