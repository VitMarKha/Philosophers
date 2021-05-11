#include "philo_three.h"

static	void	checking_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid arguments\n");
			exit(0);
		}
	}
}

void	checking_arguments(char **argv, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
		checking_arg(argv[i]);
}
