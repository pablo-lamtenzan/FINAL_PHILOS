/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:35:20 by pablo             #+#    #+#             */
/*   Updated: 2020/12/16 22:55:54 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

#include <stdlib.h>

bool			destroy_mutexes(t_shared *const sh)
{
	uint32_t	i;

	if (sh->philosophers)
	{
		i = 0;
		while (i < sh->nb)
		{
			pthread_mutex_destroy(&sh->philosophers[i].mutex);
			pthread_mutex_destroy(&sh->philosophers[i++].eating_done);
		}
		free(sh->philosophers);
	}
	if (sh->forks)
	{
		i = 0;
		while (i < sh->nb)
			pthread_mutex_destroy(&sh->forks[i++]);
		free(sh->forks);
	}
	pthread_mutex_destroy(&sh->output);
	pthread_mutex_destroy(&sh->end);
	return (true);
}
