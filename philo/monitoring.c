/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:39:16 by bterral           #+#    #+#             */
/*   Updated: 2022/03/04 15:01:18 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int someone_died(t_data *data)
{
	int i;

	while (1)
	{
		data->full_philo = 0;
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->philo[i].nb_of_meals == data->nb_meals && data->nb_meals != 0)
				data->full_philo++;
			if (data->full_philo == data->nb_philo)
			{
				data->kill_switch = 1;
				break;
			}
			if (get_time() > (data->philo[i].time_last_feast + data->time_to_die))
			{
				print_action(&data->philo[i], DIED);
				// printf("%lld    %lld     %lld\n", get_time(), (data->philo[i].time_last_feast + data->time_to_die), get_time() - (data->philo[i].time_last_feast + data->time_to_die));
				data->kill_switch = 1;
				break;
			}
			i++;
		}
		if (data->kill_switch)
			break;
	}
	return (0);
}