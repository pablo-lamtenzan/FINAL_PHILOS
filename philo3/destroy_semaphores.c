/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_semaphores.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:30:06 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 18:48:26 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo3.h"

bool			destroy_semaphores(t_shared *const sh)
{
	uint32_t	i;
	char		*sname;

	i = -1;
	while (++i < sh->nb)
	{
		sem_unlink(sname = sem_name(SEM_PHILO, i));
		free(sname);
		sem_unlink(sname = sem_name(SEM_EAT, i));
		free(sname);
	}
	free(sh->philosophers);
	return (sem_unlink(SEM_FORK)
		&& sem_unlink(SEM_OUTPUT)
		&& sem_unlink(SEM_DEAD));
}
