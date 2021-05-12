#include "philo_three.h"

static	void	*monitoring_die(void *philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	while (1)
	{
		if (philo->time_to_die < get_time(philo->begin_life))
		{
			sem_wait(philo->chat);
			printf("\x1b[31m%zu %d died\n",
				get_time(philo->begin_time), philo->num + 1);
			kill(*philo->pid, 2);
			return (NULL);
		}
	}
	return (NULL);
}

static	void	*monitoring_eat(void *data_tmp)
{
	int		i;
	t_data	*data;

	data = (t_data *)data_tmp;
	i = -1;
	while (++i < data->count_philo)
		sem_wait(data->array_philo[i].eat);
	sem_wait(data->chat);
	kill_all(data);
	return (NULL);
}

static	void	start_process(t_data *data, int i, int argc)
{
	usleep(300);
	init_philo(data, argc, i);
	pthread_create(&data->array_philo[i].thread, NULL, philo,
		(void *)&data->array_philo[i]);
	pthread_create(&data->monitoring_die, NULL, monitoring_die,
		(void *)&data->array_philo[i]);
	pthread_join(data->monitoring_eat, NULL);
	pthread_join(data->monitoring_die, NULL);
	kill_all(data);
}

static	void	start_philo(t_data *data, int argc)
{
	int	i;

	i = -1;
	while (++i < data->count_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return ;
		if (data->pids[i] > 0)
		{
			if (argc == 6)
				pthread_create(&data->monitoring_eat, NULL,
					monitoring_eat, (void *)data);
		}
		if (data->pids[i] == 0)
			start_process(data, i, argc);
	}
	i = -1;
	while (++i < data->count_philo)
		waitpid(data->pids[i], &data->status_pid, 0);
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
	start_philo(&data, argc);
	return (0);
}
