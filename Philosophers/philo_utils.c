/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:18:18 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 20:59:46 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	sign;
	int	res;

	x = 0;
	res = 0;
	sign = 1;
	while (str[x] == 32 || (str[x] >= 9 && str[x] <= 13))
		x++;
	if (str[x] == '-')
	{
		sign = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] != '\0' && str[x] >= '0' && str[x] <= '9')
	{
		res *= 10;
		res += str[x] - 48;
		x++;
	}
	return (res * sign);
}

int	has_any_philosopher_died(t_philosopher *philo, int num)
{
	int	i;
	int	last_meal;

	i = 0;
	while (i < num)
	{
		pthread_mutex_lock(&philo[i].mutex_last_meal);
		last_meal = get_the_time(philo[i].last_meal);
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		if (philo[i].duration < last_meal)
		{
			pthread_mutex_lock(philo[i].write);
			printf("%lld ms philosopher %d died\n",
				get_the_time(philo[i].start),
				philo[i].philo_id + (1));
			return (1);
		}
		i++;
	}
	return (0);
}
