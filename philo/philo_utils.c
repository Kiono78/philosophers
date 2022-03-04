/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:03:33 by bterral           #+#    #+#             */
/*   Updated: 2022/03/04 13:25:00 by bterral          ###   ########.fr       */
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

int	free_and_error(t_data *data, t_philo *philo)
{
	if (philo)
		free(philo);
	if (data)
		free(data);
	return (1);
}

uint64_t get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	custom_usleep(int input_time)
{
	uint64_t start_time;
	uint64_t target_time;

	start_time = get_time();
	target_time = (u_int64_t)input_time;
	while ((get_time() - start_time) < target_time)
		usleep(100);
}
