/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:18:27 by msekhsou          #+#    #+#             */
/*   Updated: 2023/08/31 16:20:43 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_infos
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_time_to_eat;
}	t_infos;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t mutex_last_meal;
	long long		start;
	int				have_time_to_eat;
	int				num_of_time_to_eat;
	pthread_t		philo_thread;
	long long		last_meal;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		duration;
	long long		remaining_time;
}	t_philosopher;

int			check_for_char(int ac, char **av);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
size_t		ft_strlen(char *s);
void		args_infos(t_infos *info, int ac, char **av);
int			init_infos(t_philosopher *philo, t_infos arg, int ac);
void		philo_routine(t_philosopher *philo, int number);
void		start_the_routine(t_philosopher *philo, int number);
long long	get_the_time(long long beginning_time);
void		*routine(void *arg);
void		*ft_sleep(void *philo);
int			is_eating(t_philosopher *philo, int number);
void		mutex_destroy(pthread_mutex_t *fork, int number);
int			is_death(t_philosopher *philo, int number);
void		ft_usleep_test(int time);
int			check_0(t_infos *arg);

#endif