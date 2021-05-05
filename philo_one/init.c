#include "philo_one.h"

static  void	init_philo(t_data *data)
{
	int i;
	pthread_mutex_t *forks;

	i = -1;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->count_philo);
	while (++i < data->count_philo)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data->count_philo)
	{
		data->array_philo[i].num = i + 1;
		data->array_philo[i].lfork = &forks[i + 1];
		data->array_philo[i].rfork = &forks[(i + 2) % data->count_philo];
	}
}

void	init_data(char **argv, int argc, t_data *data)
{
	data->count_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = 0;
	data->array_philo = ft_calloc(data->count_philo, sizeof(t_philo *));
	init_philo(data);
}
