#include "philo_two.h"

static	void	*philo(void	*data_tmp)
{
	int		number;
	t_data	*data;

	data = (t_data *)data_tmp;
	sem_wait(data->security);
	number = data->pos_philo;
	sem_post(data->security);
	while (1)
	{
		take_fork(data, number);
		eating(data, number);
		put_fork(data, number);
		if (data->array_philo[number].must_eat != -1)
		{
			if (data->array_philo[number].must_eat != 0)
				--data->array_philo[number].must_eat;
		}
		sleeping_thinking(data, number);
	}
	return (NULL);
}

static	int	check_for_death(t_data *data, int *did_everyone_eat, int *i)
{
	if (data->time_to_die < get_time(data->array_philo[*i].begin_life))
	{
		sem_wait(data->chat);
		printf("\x1b[31m%zu %d died\n",
			get_time(data->array_philo[*i].begin_time), *i + 1);
		return (1);
	}
	if (data->array_philo[*i].must_eat == 0)
		--*did_everyone_eat;
	return (0);
}

static	void	*monitoring(void *date_tmp)
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
			if (check_for_death(data, &did_everyone_eat, &i))
				return (NULL);
		}
		if (did_everyone_eat == 0)
		{
			sem_wait(data->chat);
			return (NULL);
		}
	}
	return (NULL);
}

static	void	start_philo(t_data *data)
{
	int				i;
	pthread_t		cracken;

	i = -1;
	pthread_create(&cracken, NULL, monitoring, (void *)data);
	while (++i < data->count_philo)
	{
		data->pos_philo = i;
		pthread_create(&data->array_philo[i].thread,
			NULL, philo, (void *)data);
		usleep(100);
	}
	pthread_join(cracken, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 6 && argc != 5)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	else
	{
		if (init_data(argv, argc, &data))
			return (1);
	}
	start_philo(&data);
	return (0);
}
