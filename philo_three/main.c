#include "philo_three.h"

static	void	*philo(void	*philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	pthread_detach(philo->thread);
	while (1)
	{
		take_fork(philo, philo->num);
		eating(philo, philo->num);
		put_fork(philo, philo->num);
		if (philo->must_eat != -1)
		{
			if (philo->must_eat != 0)
				--philo->must_eat;
		}
		sleeping_thinking(philo, philo->num);
	}
	return (NULL);
}

static	void	kill_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count_philo)
		kill(data->forks[i], 2);
}

static	void	*monitoring(void *philo_tmp)
{
	t_philo	*philo;

	philo = philo_tmp;
	while (1)
	{
		if (philo->time_to_die < get_time(philo->begin_life))
		{
			sem_wait(philo->chat);
			printf("%zu %d died\n",
				get_time(philo->begin_time), philo->num + 1);
			return (NULL);
		}
		if (philo->must_eat == 0)
		{
			printf("I AM HERE\n");
			sem_wait(philo->chat);
			sem_wait(philo->waiter_stop);
			return (NULL);
		}
	}
	return (NULL);
}

static	void	start_philo(t_data *data, int argc)
{
	int	i;

	i = -1;
	while (++i < data->count_philo)
	{
		if ((data->forks[i] = fork()) == -1)
			return ;
		else if (data->forks[i] == 0)
		{
			usleep(300);
			data->array_philo[i].num = i;
			data->array_philo[i].time_to_die = data->time_to_die;
			data->array_philo[i].time_to_eat = data->time_to_eat;
			data->array_philo[i].time_to_sleep = data->time_to_sleep;
			if (argc == 6)
				data->array_philo[i].must_eat = data->must_eat;
			else
				data->array_philo[i].must_eat = -1;
			data->array_philo[i].chat = data->chat;
			data->array_philo[i].bunch_forks = data->bunch_forks;
			data->array_philo[i].waiter_stop = data->waiter_stop;
			data->pos_philo = i;
			data->array_philo[i].begin_time = get_time(0);
			data->array_philo[i].begin_life = get_time(0);
			pthread_create(&data->cracken, NULL, monitoring, (void *)&data->array_philo[i]);
			pthread_create(&data->array_philo[i].thread, NULL, philo, (void *)&data->array_philo[i]);
			pthread_join(data->cracken, NULL);
			kill_all(data);
		}
	}
	i = -1;
	while (++i < data->count_philo)
		waitpid(data->forks[i], &data->status, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 6 && argc != 5)
		return (1);
	else
		init_data(argv, argc, &data);
	start_philo(&data, argc);
	return (0);
}
