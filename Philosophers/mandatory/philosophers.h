/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kurapika <kurapika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:59:50 by msekhsou          #+#    #+#             */
/*   Updated: 2023/04/21 00:39:59 by kurapika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher
{
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_time_to_eat;
    int meals_eaten;
    unsigned long long last_meal;
    bool is_dead;
} t_philosopher;

int     check_for_char(int ac, char **av);
int     ft_isdigit(int c);
int     ft_atoi(const char *str);
size_t  ft_strlen(char *s);
void	args_infos(t_philosopher *info, int ac, char **av);

#endif