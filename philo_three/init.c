#include "philo_three.h"

static	void	init_philo(t_data *data, int argc)
{
	int	i;

	data->bunch_forks = sem_open("bunch_forks", O_CREAT, 0777,
			data->count_philo);
	sem_unlink("bunch_forks");
	data->waiter_stop = sem_open("waiter_stop", O_CREAT, 0777, 1);
	sem_unlink("waiter_stop");
	data->chat = sem_open("chat", O_CREAT, 0777, 1);
	sem_unlink("chat");
	data->forks = ft_calloc(data->count_philo, sizeof(pid_t));
	i = -1;
	while (++i < data->count_philo)
	{
		data->array_philo[i].num = i;
		data->array_philo[i].time_to_die = data->time_to_die;
		data->array_philo[i].time_to_eat = data->time_to_eat;
		data->array_philo[i].time_to_sleep = data->time_to_sleep;
		if (argc == 6)
			data->array_philo[i].must_eat = data->must_eat;
		else
			data->array_philo[i].must_eat = -1;
		data->array_philo[i].begin_time = data->begin_time;
		data->array_philo[i].begin_life = data->begin_time;
		data->array_philo[i].chat = data->chat;
		data->array_philo[i].bunch_forks = data->bunch_forks;
		data->array_philo[i].waiter_stop = data->waiter_stop;
	}
}

void	init_data(char **argv, int argc, t_data *data)
{
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
	data->pos_philo = 0;
	init_philo(data, argc);
}
