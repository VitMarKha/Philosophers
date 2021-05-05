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

void	*philo(void	*philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	// while (1)
	// {
	// 	printf("Hello\n");
	// 	if (data->count_philo == 0)
	// 		break ;
	// }
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
	int i = -1;

	while (++i < data->count_philo)
		pthread_create(&data->array_philo[i].thread, NULL, philo, (void *)&data->array_philo[i]);
	i = -1;
	while (++i < data->count_philo)
		pthread_join(data->array_philo[i].thread, NULL);
	// Destroy
	// time_start();
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 6 && argc != 5)
		return (1);
	else
		init_data(argv, argc, &data);
	start_philo(&data);
	while(1)
		;
	printf("Time: %ld\n", time_stop());
	return (0);
}
