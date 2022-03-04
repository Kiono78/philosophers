/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:09:30 by bterral           #+#    #+#             */
/*   Updated: 2022/02/24 13:56:29 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

long	ft_atol(const char *str)
{
	long	res;
	long	sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

int	error_figures(char **nbs)
{
	int	i;
	int	j;

	i = 1;
	while (nbs[i])
	{
		if (!nbs[i][0])
			return (1);
		if (ft_atol(nbs[i]) > INT_MAX || ft_strlen(nbs[i]) > 11)
			return (1);
		j = 0;
		if (nbs[i][j] == '-')
			return (1);
		while (nbs[i][j])
		{
			if (nbs[i][j] < '0' || nbs[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int parsing_error(int ac, char **av)
{
	//nb philo > 1 smtg else to add ?
	if (ac != 5 && ac != 6)
	{
		printf("5 or 6 arguments needed !\n");
		return (1);
	}
	if (error_figures(av))
	{
		printf("Arguments are not valid !\n");
		return (1);
	}
	return (0);
}