/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:50:50 by bterral           #+#    #+#             */
/*   Updated: 2022/03/04 15:04:01 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void*	routine(void *param)
{
	t_philo			*philo;
	
	philo = (t_philo *)param;
	if ((philo->id % 2) == 0)
		sleeping(philo);
	if ((philo->id % 2) == 1)
		picking_up(philo);
	return (NULL);
}

int	retrieve_data(t_data *data, char **av)
{
	int i;

	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = 0;
	data->philo = ft_calloc(data->nb_philo, sizeof(t_philo));
	data->fork = ft_calloc(data->nb_philo, sizeof(pthread_mutex_t));
	if (!data->philo || !data->fork)
		return (free_and_error(data, NULL));
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	data->start_ms = get_time();
	data->kill_switch = 0;
	return (0);
}

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->nb_of_meals = 0;
	philo->time_last_feast = get_time();
	philo->right_fork = &data->fork[i];
	philo->left_fork = &data->fork[philo->id % data->nb_philo];
	philo->data = data;
}

int	main(int ac, char **av)
{
	t_data					data;
	int						i;
	
	if (parsing_error(ac, av))
		return (1);
	if (retrieve_data(&data, av))
		return (1);
	if (!data.philo)
		return (1);
	i = 0;
	while (i < data.nb_philo)
	{
		init_philo(&data.philo[i], &data, i);
		if (pthread_create(&data.philo[i].thread, NULL, &routine, &data.philo[i]) != 0)
			return (free_and_error(&data, data.philo));
		i++;
	}
	someone_died(&data);
	i = 0;
	while (i < data.nb_philo)
	{
		if (pthread_join(data.philo[i].thread, NULL) != 0)
			return (free_and_error(&data, data.philo));
		pthread_mutex_destroy(&data.fork[i]);
		i++;
	}
	return (0);
}
