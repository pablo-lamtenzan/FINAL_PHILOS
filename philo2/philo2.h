/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:18:35 by plamtenz          #+#    #+#             */
/*   Updated: 2020/12/18 02:58:03 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO2_H
# define PHILO2_H

# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>

# define SEM_FORK		"Fork"
# define SEM_OUTPUT		"Output"
# define SEM_DEAD		"Dead"
# define SEM_PHILO		"Philo"
# define SEM_EAT		"Eat"

# define MSG_EATING		1
# define MSG_SPLEEPING	2
# define MSG_THINKING	4
# define MSG_FORK		8
# define MSG_DIE		16
# define MSG_OVEREAT	32

# define MAX_PHILO_NB	42u
# define MIN_PHILO_NB	2u
# define ARGS_LIMIT		100ul

typedef struct	s_philo
{
	pid_t				pid;
	uint32_t			index;
	uint32_t			left_fork;
	uint32_t			right_fork;
	uint64_t			remaining_time;
	uint64_t			eate_time;
	bool				is_eating;
	struct s_shared		*shared;
	sem_t				*mutex;
	sem_t				*eating_done;
}				t_philo;

typedef struct	s_shared
{
	uint32_t			nb;
	uint64_t			born_date;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int32_t				max_meals;
	sem_t				*forks;
	sem_t				*output;
	sem_t				*end;
	bool				exited;
	t_philo				*philosophers;
}				t_shared;

/*
** Main fuctions
*/
bool			parse(t_shared *const sh, int ac, const char **av);
bool			engine(t_shared *const sh);
bool			msg(t_philo *const p, uint8_t code);
bool			destroy_semaphores(t_shared *const sh);

/*
** Actions
*/
bool			ph_take_forks(t_philo *const p);
bool			ph_drop_forks(t_philo *const p);
bool			ph_eat(t_philo *const p);
bool			ph_think(t_philo *const p);
bool			ph_sleep(t_philo *const p);

/*
** Helper
*/
int				ft_thread_detacher(pthread_t *const tid,
	void *(*start_routine)(void*), void *arg);
bool			philo_is_starved(t_philo *const p);
uint64_t		get_time();
void			ft_putnbr_fd(uint64_t n, int fd);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
char			*sem_name(const char *name, int index);
uint64_t		u64_atoi(const char **av, size_t index);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
