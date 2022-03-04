/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:27 by bterral           #+#    #+#             */
/*   Updated: 2022/03/04 14:48:51 by bterral          ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				nb_of_meals;
	int				time_last_feast;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	uint64_t		time;
	int 			full;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	uint64_t 		time_to_sleep;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	int				nb_meals;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	uint64_t		start_ms;
	int				full_philo;
	int				kill_switch;
}	t_data;

int		retrieve_data(t_data *data, char **av);
void*	routine();
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
long	ft_atol(const char *str);
int		error_figures(char **nbs);
int 	parsing_error(int ac, char **av);

////PHILO UTILS////

void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		free_and_error(t_data *data, t_philo *philo);
uint64_t get_time();
void	custom_usleep(int input_time);

////ACTIONS////

void	sleeping(t_philo *philo);
void	picking_up(t_philo *philo);
void	eating(t_philo *philo);
void	print_action(t_philo *philo, int action);
void	thinking(t_philo *philo);

////MONITORING////

int someone_died(t_data *data);

#endif