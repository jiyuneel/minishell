#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		if (sign == 1 && res > 9223372036854775807)
			return (-1);
		else if (res > 0 && sign == -1 && res - 1 > 9223372036854775807)
			return (0);
	}
	return (sign * res);
}

// int	check_overflow(int sign)

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	printf("%s: %d\n", av[1], ft_atoi(av[1]));
	printf("atoi: %d\n", atoi(av[1]));
	return (0);
}
