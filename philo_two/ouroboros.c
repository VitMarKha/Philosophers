#include "philo_two.h"

// static	void	take_fork_odd(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->lfork);
// 	pthread_mutex_lock(philo->chat);
// 	printf("%zu %d has taken a fork\n",
// 		get_time(philo->begin_time), philo->num + 1);
// 	pthread_mutex_unlock(philo->chat);
// 	pthread_mutex_lock(philo->rfork);
// 	pthread_mutex_lock(philo->chat);
// 	printf("%zu %d has taken a fork\n",
// 		get_time(philo->begin_time), philo->num + 1);
// 	pthread_mutex_unlock(philo->chat);
// }

void	take_fork(t_philo *philo)
{
	// if (philo->num % 2 == 0)
	// {
		sem_wait(philo->bunch_forks);
		sem_wait(philo->chat);
		printf("%zu %d has taken a fork\n",
			get_time(philo->begin_time), philo->num + 1);
		sem_post(philo->chat);
		sem_wait(philo->bunch_forks);
		sem_wait(philo->chat);
		printf("%zu %d has taken a fork\n",
			get_time(philo->begin_time), philo->num + 1);
		sem_post(philo->chat);
	// }
	// else
	// 	take_fork_odd(philo);
}

void	put_fork(t_philo *philo)
{
	// if (philo->num % 2 == 0)
	// {
		sem_post(philo->bunch_forks);
		sem_post(philo->bunch_forks);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(philo->lfork);
	// 	pthread_mutex_unlock(philo->rfork);
	// }
}

void	eating(t_philo *philo)
{
	sem_wait(philo->chat);
	printf("%zu %d is eating\n", get_time(philo->begin_time), philo->num + 1);
	philo->begin_life = get_time(0);
	sem_post(philo->chat);
	my_usleep(philo->time_to_eat);
}

void	sleeping_thinking(t_philo *philo)
{
	sem_wait(philo->chat);
	printf("%zu %d is sleeping\n", get_time(philo->begin_time), philo->num + 1);
	sem_post(philo->chat);
	my_usleep(philo->time_to_sleep);
	sem_wait(philo->chat);
	printf("%zu %d is thinking\n", get_time(philo->begin_time), philo->num + 1);
	sem_post(philo->chat);
}
