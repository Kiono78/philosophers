/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:20:00 by bterral           #+#    #+#             */
/*   Updated: 2022/03/09 13:27:23 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*output;

	output = (void *)malloc(nmemb * size);
	if (output == NULL)
		return (NULL);
	ft_bzero(output, nmemb * size);
	return (output);
}

int	free_and_error(t_data *data)
{
	if (data->nb_philo)
	{
		if (data->philo)
			free(data->philo);
		if (data->fork)
			free(data->fork);
		if (data->meal_mutex)
			free(data->meal_mutex);
		if (data->feast_mutex)
			free(data->feast_mutex);
	}
	return (1);
}

void	free_structures(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->meal_mutex[i]);
		pthread_mutex_destroy(&data->feast_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->switch_mutex);
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
	if (data->meal_mutex)
		free(data->meal_mutex);
	if (data->feast_mutex)
		free(data->feast_mutex);
}
