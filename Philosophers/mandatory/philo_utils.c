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
