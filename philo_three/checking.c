#include "philo_three.h"

static	int	checking_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid arguments\n");
			return (1);
		}
	}
	return (0);
}

int	checking_arguments(char **argv, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (checking_arg(argv[i]))
			return (1);
	}
	return (0);
}
