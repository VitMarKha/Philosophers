#include "philo_one.h"

//после размышлений он ест
//после еды он спит
//после сна он размышляет
//pthread_create - создает поток
//pthread_detach - очищает поток
//pthread_join - ждет завершения потока
//pthread_mutex_init - мютекс

void	*philo(void	*philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	// while (1)
	// {
	// 	printf("Expectation\n");
	// 	if (philo->count_philo == philo->num)
	// 		break ;
	// }
	// usleep(1000000);
	// gettimeofday(&philo->tv1, &philo->tz);
	philo->begin_life = get_time(0);
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num);
		pthread_mutex_unlock(philo->chat);
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num);
		pthread_mutex_unlock(philo->chat);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d is eating\n", get_time(philo->begin_time), philo->num);
		philo->begin_life = get_time(0);
		pthread_mutex_unlock(philo->chat);
		my_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		// if (philo->must_eat != -1)
		// {
		// 	--philo->must_eat;
		// 	if (philo->must_eat == 0)
		// 		return (NULL);
		// }
		pthread_mutex_lock(philo->chat);
		printf("%zu %d is sleeping\n", get_time(philo->begin_time), philo->num);
		pthread_mutex_unlock(philo->chat);

		my_usleep(philo->time_to_sleep);

		pthread_mutex_lock(philo->chat);
		printf("%zu %d is thinking\n", get_time(philo->begin_time), philo->num);
		pthread_mutex_unlock(philo->chat);
	}
	return (NULL);
}

void	*count_to_die(void *date_tmp)
{
	int		i;
	t_data	*data;

	data = date_tmp;
	while (1)
	{
		i = -1;
		while (++i < data->count_philo)
		{
			if (data->time_to_die < get_time(data->array_philo[i].begin_life) && data->array_philo[i].begin_life != 0)
			{
				pthread_mutex_lock(&data->chat);
				printf("%zu %d died\n", get_time(data->array_philo[i].begin_time), i + 1);
				return (NULL);
			}
		}
	}
	return (NULL);
}

// void *waiter_watching(void *data_tmp)
// {
// 	int		i;
// 	t_data	*data;

// 	data = data_tmp;
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < data->count_philo)
// 		{
// 			if (data->array_philo[i].i_ate == 1)

// 		}
// 	}
// }

void	start_philo(t_data *data)
{
	int				i;
	pthread_t		cracken;
	// pthread_t		waiter;

	i = -1;
	pthread_create(&cracken, NULL, count_to_die, (void *)data);
	// pthread_create(&waiter, NULL, waiter_watching, (void *)data);
	while (++i < data->count_philo)
		pthread_create(&data->array_philo[i].thread, NULL, philo, (void *)&data->array_philo[i]);
	i = -1;
	pthread_join(cracken, NULL);
	pthread_mutex_destroy(&data->chat);
	// while (++i < data->count_philo)
	// 	pthread_join(data->array_philo[i].thread, NULL);
	// Destroy and free
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
