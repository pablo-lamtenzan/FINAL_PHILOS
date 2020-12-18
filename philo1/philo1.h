/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:21:42 by pablo             #+#    #+#             */
/*   Updated: 2020/12/18 02:00:30 by pablo            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO1_H
# define PHILO1_H

# include <pthread.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_EATING		1
# define MSG_SPLEEPING	2
# define MSG_THINKING	4
# define MSG_FORK		8
# define MSG_DIE		16
# define MSG_OVEREAT	32

# define MAX_PHILO_NB	42u
# define MIN_PHILO_NB	2u
# define ARGS_LIMIT		100ul

/*
** This is the structure for each philosopher
**
** index				-> philosophers index
** left_fork			-> philosopher's left fork index
** right_fork			-> philosopher's right fork index
** remaining_time		-> time remaining before die
** eate_time			-> last time the philosopher eate
** is_eating			-> if currently the philosopher is eating
** times_eaten			-> time the philosopher has eat // not used
** shared				-> shared ressources
** mutex				-> philosopher own mutex
** eating_done			-> asyncronous meal count
*/

typedef struct	s_philo
{
	uint32_t			index;
	uint32_t			left_fork;
	uint32_t			right_fork;
	uint64_t			remaining_time;
	uint64_t			eate_time;
	bool				is_eating;
	struct s_shared		*shared;
	pthread_mutex_t		mutex;
	pthread_mutex_t		eating_done;
}				t_philo;

/*
** This are the shared ressources structure:
**
** nb				-> number of philosophers
** born_date		-> the date when the program starts
** time_to_die		-> maximum time a philosopher is alive without eating
** time_to_eat		-> time a philosopher needs to eat
** time_to_sleep	-> time a philosopher needs to sleep
** max_meals		-> maximum meals any philosopher is allowed to have
** forks			-> shared forks used to eat
** output			-> shared stdout
** end				-> program termination
** philosophers		-> all the running philosophers
*/

typedef struct	s_shared
{
	uint32_t			nb;
	uint64_t			born_date;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int32_t				max_meals;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output;
	pthread_mutex_t		end;
	bool				exited;
	t_philo				*philosophers;
}				t_shared;

/*
** Main fuctions
*/
bool			parse(t_shared *const sh, int ac, const char **av);
bool			engine(t_shared *const sh);
void			msg(t_philo *const p, uint8_t code);
bool			destroy_mutexes(t_shared *const sh);

/*
** Actions
*/
void			ph_take_forks(t_philo *const p);
void			ph_drop_forks(t_philo *const p);
void			ph_eat(t_philo *const p);
void			ph_think(t_philo *const p);
void			ph_sleep(t_philo *const p);

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

#endif
