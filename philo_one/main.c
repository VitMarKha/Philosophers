#include "philo_one.h"

//после размышлений он ест
//после еды он спит
//после сна он размышляет
//pthread_create - создает поток
//pthread_detach - очищает поток
//pthread_join - ждет завершения потока
//pthread_mutex_init - мютекс

// usleep(1000000);

struct timeval tv1,tv2,dtv;

struct timezone tz;

void time_start(void)
{
	gettimeofday(&tv1, &tz);
}

long time_stop(void)
{
	gettimeofday(&tv2, &tz);
	dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
	dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;
	if(dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

void	*philo(void	*data_tmp)
{
	int		my_num;
	t_data	*data;

	data = data_tmp;
	my_num = data->array_philo[data->count_philo].num;
	while (1)
	{
		printf("Hello\n");
		if (data->count_philo == 0)
			break ;
	}
	while (1)
	{
		pthread_mutex_lock(&data->array_philo[my_num].mutex);
		printf(" %d has taken a fork\n", my_num);
		pthread_mutex_unlock(&data->array_philo[my_num].mutex);
		printf(" %d is eating\n", my_num);
		printf(" %d is sleeping\n", my_num);
		printf(" %d is thinking\n", my_num);
		printf(" %d died\n", my_num);
	}
	pthread_mutex_destroy(&data->array_philo[my_num].mutex);
	return (NULL);
}

void	readiness_philo(t_data *data)
{
	++data->count_philo;
	while (--data->count_philo)
		pthread_create(&data->array_philo[data->count_philo].thread, NULL, philo, (void *)data);
	time_start();
}

void	init_philo(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->count_philo)
	{
		data->array_philo[i].num = i;
		data->array_philo[i].lfork = i;
		data->array_philo[i].rfork = (i + 1) % data->count_philo;
	}
	pthread_mutex_init(&data->array_philo[i].mutex, NULL);
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

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 6 && argc != 5)
		return (1);
	else
		init_data(argv, argc, &data);
	readiness_philo(&data);
	while(1)
		;
	printf("Time: %ld\n", time_stop());
	return (0);
}
