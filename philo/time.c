/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:03:33 by bterral           #+#    #+#             */
/*   Updated: 2022/03/10 14:01:51 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	custom_usleep(uint64_t input_time, t_philo *philo)
{
	uint64_t	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < input_time)
	{
		if (philo->data->nb_philo > 100)
			usleep(1000);
		else
			usleep(100);
	}
}

void	populate_last_feast(t_philo *philo)
{
	pthread_mutex_lock(philo->feast_mutex);
	philo->last_feast = get_time();
	pthread_mutex_unlock(philo->feast_mutex);
}
