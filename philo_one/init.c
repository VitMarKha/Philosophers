#include "philo_one.h"

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

static	int	checking_arguments(char **argv, int argc)
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

static	void	init_philo(t_data *data, int argc)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = ft_calloc(data->count_philo, sizeof(pthread_mutex_t));
	while (++i < data->count_philo)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&data->chat, NULL);
	i = -1;
	while (++i < data->count_philo)
	{
		data->array_philo[i].chat = &data->chat;
		data->array_philo[i].num = i;
		data->array_philo[i].lfork = &forks[i];
		data->array_philo[i].rfork = &forks[(i + 1) % data->count_philo];
		data->array_philo[i].time_to_die = data->time_to_die;
		data->array_philo[i].time_to_eat = data->time_to_eat;
		data->array_philo[i].time_to_sleep = data->time_to_sleep;
		if (argc == 6)
			data->array_philo[i].must_eat = data->must_eat;
		else
			data->array_philo[i].must_eat = -1;
		data->array_philo[i].begin_time = data->begin_time;
		data->array_philo[i].begin_life = data->begin_time;
	}
}

int	init_data(char **argv, int argc, t_data *data)
{
	if (checking_arguments(argv, argc))
		return (1);
	data->begin_time = get_time(0);
	data->count_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = 0;
	data->array_philo = ft_calloc(data->count_philo, sizeof(t_philo *));
	init_philo(data, argc);
	return (0);
}
