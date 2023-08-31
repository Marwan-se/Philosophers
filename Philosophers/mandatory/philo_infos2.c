/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_infos2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:38:23 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 16:29:47 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) philo;
	if (philosopher->philo_id % 2)
		usleep(1000);
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	pthread_mutex_unlock(philosopher->write);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(philosopher->write);
	printf("%lld ms philosopher %d has taken a fork\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	printf("%lld ms philosopher %d is eating\n",
		get_the_time(philosopher->start), philosopher->philo_id);
	pthread_mutex_unlock(philosopher->write);
	ft_usleep_test(philosopher->time_to_eat);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->mutex_last_meal);
	philosopher->last_meal = get_the_time(0);
	pthread_mutex_unlock(&philosopher->mutex_last_meal);	
	if (philosopher->have_time_to_eat)
		philosopher->num_of_time_to_eat--;
	ft_sleep(philosopher);
	return (NULL);
}

void	ft_usleep_test(int time)
{
	long long	t;

	t = get_the_time(0);
	while (get_the_time(0) - t < time)
		usleep(1);
}

void	*ft_sleep(void *philo)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *) philo;
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is sleeping\n",
		get_the_time(philosophers->start), philosophers->philo_id);
	pthread_mutex_unlock(philosophers->write);
	usleep(philosophers->time_to_sleep * 1000);
	pthread_mutex_lock(philosophers->write);
	printf("%lld ms philosopher %d is thinking\n",
		get_the_time(philosophers->start), philosophers->philo_id);
	pthread_mutex_unlock(philosophers->write);
	routine(philosophers);
	return (NULL);
}

long long	get_the_time(long long beginning_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - beginning_time);
}

int	is_death(t_philosopher *philo, int num)
{
	int	i;
	int	var;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&philo[i % num].mutex_last_meal);
			var = get_the_time(philo[i % num].last_meal);
			pthread_mutex_unlock(&philo[i % num].mutex_last_meal);
			if (philo[i % num].duration
				< var)
			{
				pthread_mutex_lock(philo[i].write);
				printf("%lld ms philosopher %d died\n", 
					get_the_time(philo[i % num].start), 
					philo[i % num].philo_id);
				return (1);
			}
			i++;
		}
		if (philo->have_time_to_eat && philo->num_of_time_to_eat < 0)
			return (1);
	}
	return (0);
}
