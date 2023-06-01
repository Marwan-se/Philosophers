/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:18:27 by msekhsou          #+#    #+#             */
/*   Updated: 2023/05/23 19:21:48 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_infos
{
	int philo_nbr;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_time_to_eat;
} t_infos;

typedef	struct s_philosopher
{
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	pthread_t		philo_thread;
	long long 		last_meal;
	long long		time_to_eat;
	long long 		meals_eaten;
	long long		time_to_sleep;
	long long 		duration;
	long long		remaining_time;
	long long		start;
	int				have_time_to_eat;
	int				num_of_time_to_eat;
} t_philosopher;


int		check_for_char(int ac, char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(char *s);
void	args_infos(t_infos *info, int ac, char **av);
void	init_infos(t_philosopher *philo, t_infos arg, int ac);

#endif