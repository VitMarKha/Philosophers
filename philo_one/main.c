#include "philo_one.h"

void	*philo(void	*philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	philo->begin_life = get_time(0);
	while (1)
	{
		take_fork(philo);
		eating(philo);
		put_fork(philo);
		if (philo->must_eat != -1)
		{
			if (philo->must_eat != 0)
				--philo->must_eat;
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*count_to_die(void *date_tmp)
{
	int		i;
	int		did_everyone_eat;
	t_data	*data;

	data = date_tmp;
	while (1)
	{
		i = -1;
		did_everyone_eat = data->count_philo;
		while (++i < data->count_philo)
		{
			if (data->time_to_die < get_time(data->array_philo[i].begin_life))
			{
				pthread_mutex_lock(&data->chat);
				printf("%zu %d died\n", get_time(data->array_philo[i].begin_time), i + 1);
				return (NULL);
			}
			if (data->array_philo[i].must_eat == 0)
				--did_everyone_eat;
		}
		if (did_everyone_eat == 0)
		{
			pthread_mutex_lock(&data->chat);
			return (NULL);
		}
	}
	return (NULL);
}

void	start_philo(t_data *data)
{
	int				i;
	pthread_t		cracken;

	i = -1;
	pthread_create(&cracken, NULL, count_to_die, (void *)data);
	while (++i < data->count_philo)
		pthread_create(&data->array_philo[i].thread, NULL, philo, (void *)&data->array_philo[i]);
	pthread_join(cracken, NULL);
	pthread_mutex_destroy(&data->chat);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 6 && argc != 5)
		return (1);
	else
		init_data(argv, argc, &data);
	start_philo(&data);
	return (0);
}
