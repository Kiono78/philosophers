/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:50:50 by bterral           #+#    #+#             */
/*   Updated: 2022/03/09 10:49:59 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo			*philo;

	philo = (t_philo *)param;
	if ((philo->id % 2) == 0)
	{
		print_action(philo, THINKING);
		usleep(philo->data->time_to_eat * 1000);
	}
	picking_up(philo);
	return (NULL);
}

int	manage_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		init_philo(&data->philo[i], data, i);
		if (pthread_create(&data->philo[i].thread, NULL,
				&routine, &data->philo[i]) != 0)
			return (free_and_error(data));
		i++;
	}
	if (data->nb_philo != 0)
		someone_died(data);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (free_and_error(data));
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->switch_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	t_data					data;

	if (parsing_error(ac, av))
		return (1);
	if (retrieve_data(&data, av))
		return (1);
	if (!data.philo)
		return (1);
	if (manage_thread(&data))
		return (1);
	free_structures(&data);
	return (0);
}
