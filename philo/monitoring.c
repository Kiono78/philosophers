/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:39:16 by bterral           #+#    #+#             */
/*   Updated: 2022/03/08 16:26:53 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->switch_mutex);
	if (philo->data->kill_switch)
	{
		pthread_mutex_unlock(&philo->data->switch_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->switch_mutex);
	return (0);
}

void	activate_kill_switch(t_data *data)
{
	pthread_mutex_lock(&data->switch_mutex);
	data->kill_switch = 1;
	pthread_mutex_unlock(&data->switch_mutex);
}

int	someone_died(t_data *data)
{
	int	i;

	while (data->kill_switch == 0)
	{
		data->full_philo = 0;
		i = -1;
		while (++i < data->nb_philo)
		{
			if (data->philo[i].nb_of_meals >= data->nb_meals
				&& data->nb_meals != 0)
				data->full_philo++;
			if (data->full_philo == data->nb_philo)
			{
				activate_kill_switch(data);
				break ;
			}
			if (get_time() > (data->philo[i].last_feast + data->time_to_die))
			{
				print_action(&data->philo[i], DIED);
				activate_kill_switch(data);
				break ;
			}
		}
	}
	return (0);
}
