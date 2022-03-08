/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 11:46:36 by bterral           #+#    #+#             */
/*   Updated: 2022/03/08 16:19:43 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	retrieve_data(t_data *data, char **av)
{
	int	i;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = 0;
	data->philo = ft_calloc(data->nb_philo, sizeof(t_philo));
	data->fork = ft_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	if (!data->philo || !data->fork)
		return (free_and_error(data));
	i = 0;
	while (i++ < data->nb_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	data->start_ms = get_time();
	data->kill_switch = 0;
	pthread_mutex_init(&data->switch_mutex, NULL);
	return (0);
}

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->nb_of_meals = 0;
	philo->last_feast = get_time();
	philo->right_fork = &data->fork[i];
	philo->left_fork = &data->fork[philo->id % data->nb_philo];
	philo->data = data;
}
