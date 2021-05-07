#include "philo_two.h"

void	take_fork(t_data *data, int number)
{
	sem_wait(data->waiter_stop);
	sem_wait(data->bunch_forks);
	sem_wait(data->chat);
	printf("%zu %d has taken a fork\n",
		get_time(data->array_philo[number].begin_time), data->array_philo[number].num + 1);
	sem_post(data->chat);
	sem_wait(data->bunch_forks);
	sem_wait(data->chat);
	printf("%zu %d has taken a fork\n",
		get_time(data->array_philo[number].begin_time), data->array_philo[number].num + 1);
	sem_post(data->chat);
	sem_post(data->waiter_stop);
}

void	put_fork(t_data *data, int number)
{
	(void)number;
	sem_post(data->bunch_forks);
	sem_post(data->bunch_forks);
}

void	eating(t_data *data, int number)
{
	sem_wait(data->chat);
	printf("%zu %d is eating\n", get_time(data->array_philo[number].begin_time), data->array_philo[number].num + 1);
	data->array_philo[number].begin_life = get_time(0);
	sem_post(data->chat);
	my_usleep(data->time_to_eat);
}

void	sleeping_thinking(t_data *data, int number)
{
	sem_wait(data->chat);
	printf("%zu %d is sleeping\n", get_time(data->array_philo[number].begin_time), data->array_philo[number].num + 1);
	sem_post(data->chat);
	my_usleep(data->time_to_sleep);
	sem_wait(data->chat);
	printf("%zu %d is thinking\n", get_time(data->array_philo[number].begin_time), data->array_philo[number].num + 1);
	sem_post(data->chat);
}
