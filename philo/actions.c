/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:38:32 by bterral           #+#    #+#             */
/*   Updated: 2022/03/08 16:22:45 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	philo->time = get_time();
	if (print_action(philo, SLEEPING))
		return ;
	custom_usleep(philo->data->time_to_sleep, philo);
	thinking(philo);
}

void	picking_up(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo->time = get_time();
	if (print_action(philo, TAKING_FORK))
		return ;
	if (philo->data->nb_philo == 1)
		return ;
	pthread_mutex_lock(philo->left_fork);
	philo->time = get_time();
	print_action(philo, TAKING_FORK);
	eating(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	sleeping(philo);
}

void	thinking(t_philo *philo)
{
	philo->time = get_time();
	if (print_action(philo, THINKING))
		return ;
	picking_up(philo);
}

void	eating(t_philo *philo)
{
	philo->last_feast = get_time();
	if (print_action(philo, EATING))
		return ;
	philo->nb_of_meals++;
	custom_usleep(philo->data->time_to_eat, philo);
}

int	print_action(t_philo *philo, int action)
{
	if (thread_end(philo))
		return (1);
	if (action == SLEEPING)
		printf("%llu %d is sleeping\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == TAKING_FORK)
		printf("%llu %d has taken a fork\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == EATING)
		printf("%llu %d is eating\n",
			philo->last_feast - philo->data->start_ms, philo->id);
	else if (action == THINKING)
		printf("%llu %d is thinking\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == DIED)
	{
		philo->time = get_time();
		printf("%llu %d died\n",
			philo->time - philo->data->start_ms, philo->id);
	}
	return (0);
}
