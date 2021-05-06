#include "philo_one.h"

void    take_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num + 1);
		pthread_mutex_unlock(philo->chat);
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num + 1);
		pthread_mutex_unlock(philo->chat);
	}
	else
	{
		pthread_mutex_lock(philo->lfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num + 1);
		pthread_mutex_unlock(philo->chat);
		pthread_mutex_lock(philo->rfork);
		pthread_mutex_lock(philo->chat);
		printf("%zu %d has taken a fork\n", get_time(philo->begin_time), philo->num + 1);
		pthread_mutex_unlock(philo->chat);
	}
}

void	put_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
	}
	else
	{
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->chat);
	printf("%zu %d is eating\n", get_time(philo->begin_time), philo->num + 1);
	philo->begin_life = get_time(0);
	pthread_mutex_unlock(philo->chat);
	my_usleep(philo->time_to_eat);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->chat);
	printf("%zu %d is sleeping\n", get_time(philo->begin_time), philo->num + 1);
	pthread_mutex_unlock(philo->chat);
	my_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->chat);
	printf("%zu %d is thinking\n", get_time(philo->begin_time), philo->num + 1);
	pthread_mutex_unlock(philo->chat);
}
