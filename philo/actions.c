/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:38:32 by bterral           #+#    #+#             */
/*   Updated: 2022/03/04 14:44:58 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	philo->time = get_time();
	print_action(philo, SLEEPING);
	custom_usleep(philo->data->time_to_sleep);
	thinking(philo);
}

void	picking_up(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo->time = get_time();
	print_action(philo, TAKING_FORK);
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
	print_action(philo, THINKING);
	picking_up(philo);
}

void	eating(t_philo *philo)
{
	philo->time = get_time();
	print_action(philo, EATING);
	philo->time_last_feast = philo->time;
	philo->nb_of_meals++;
	custom_usleep(philo->data->time_to_sleep);
}

void	print_action(t_philo *philo, int action)
{
	if (philo->data->kill_switch)
		return ;
	if (action == SLEEPING)
		printf("%llu philo %d is sleeping\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == TAKING_FORK)
		printf("%llu philo %d has taken a fork\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == EATING)
		printf("%llu philo %d is eating\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == THINKING)
		printf("%llu philo %d is thinking\n",
			philo->time - philo->data->start_ms, philo->id);
	else if (action == DIED)
	{
		philo->time = get_time();
		printf("%llu philo %d died\n",
			philo->time - philo->data->start_ms, philo->id);
	}
}
