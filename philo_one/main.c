#include "philo_one.h"

//после размышлений он ест
//после еды он спит
//после сна он размышляет
//pthread_create - создает поток
//pthread_detach - очищает поток
//pthread_join - ждет завершения потока
//pthread_mutex_init - мютекс

// usleep(1000000);

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
	usleep(1000000);
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		printf(" %d has taken a fork\n", philo->num);
		pthread_mutex_lock(philo->rfork);
		printf(" %d is eating\n", philo->num);
		usleep(1000000);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		printf(" %d is sleeping\n", philo->num);
		usleep(1000000);
		printf(" %d is thinking\n", philo->num);
		printf(" %d died\n", philo->num);
	}
	return (NULL);
}

void	start_philo(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->count_philo)
		pthread_create(&data->array_philo[i].thread, NULL, philo, (void *)&data->array_philo[i]);
	i = -1;
	while (++i < data->count_philo)
		pthread_join(data->array_philo[i].thread, NULL);
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
