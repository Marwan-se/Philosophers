/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kurapika <kurapika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:00:49 by msekhsou          #+#    #+#             */
/*   Updated: 2023/04/21 01:20:42 by kurapika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_philosopher	*info;
	
	info = malloc(sizeof(t_philosopher));
	if ((ac != 5 && ac != 6) || check_for_char(ac, av))
		return(printf("args error"), 1);
	args_infos(info, ac, av);
}