/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:18:03 by msekhsou          #+#    #+#             */
/*   Updated: 2023/05/09 11:18:06 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_for_char(int ac, char **av)
{
    int i;

	i = 1;
    while (i < ac)
	{
        int j = 0;
        while (av[i][j] != '\0')
		{
            if (!ft_isdigit(av[i][j]))
                return 1;
            j++;
        }
        i++;
    }
    return (0);
}
