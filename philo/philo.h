/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:27 by bterral           #+#    #+#             */
/*   Updated: 2022/03/10 13:33:41 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SLEEPING 0
# define TAKING_FORK 1
# define EATING 2
# define THINKING 3
# define DIED 4

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_of_meals;
	uint64_t		last_feast;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	uint64_t		time;
	int				full;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*feast_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	int				nb_meals;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	uint64_t		start_ms;
	int				full_philo;
	int				kill_switch;
	pthread_mutex_t	switch_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*feast_mutex;
}	t_data;

//// PHILO ////

void		*routine(void *param);
int			manage_thread(t_data *data);

//// PARSING ////

int			ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
long		ft_atol(const char *str);
int			error_figures(char **nbs);
int			parsing_error(int ac, char **av);

//// INIT ////

int			initialize_mutex(t_data *data);
int			retrieve_data(t_data *data, char **av);
void		init_philo(t_philo *philo, t_data *data, int i);

//// TIME ////

uint64_t	get_time(void);
void		custom_usleep(uint64_t input_time, t_philo *philo);
void		populate_last_feast(t_philo *philo);

//// ACTIONS ////

void		sleeping(t_philo *philo);
void		picking_up(t_philo *philo);
void		eating(t_philo *philo);
int			print_action(t_philo *philo, int action);
void		thinking(t_philo *philo);

//// MONITORING ////

int			someone_died(t_data *data);
int			thread_end(t_philo *philo);
void		activate_kill_switch(t_data *data);

//// HEAP ////

void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			free_and_error(t_data *data);
void		free_structures(t_data *data);

#endif