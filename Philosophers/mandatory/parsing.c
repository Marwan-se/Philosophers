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
