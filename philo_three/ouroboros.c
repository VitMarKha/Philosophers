#include "philo_three.h"

void	take_fork(t_philo *philo, int number)
{
	sem_wait(philo->waiter_stop);
	sem_wait(philo->bunch_forks);
	sem_wait(philo->chat);
	printf("%zu %d has taken a fork\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	sem_wait(philo->bunch_forks);
	sem_wait(philo->chat);
	printf("%zu %d has taken a fork\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	sem_post(philo->waiter_stop);
}

void	put_fork(t_philo *philo, int number)
{
	(void)number;
	sem_post(philo->bunch_forks);
	sem_post(philo->bunch_forks);
}

void	eating(t_philo *philo, int number)
{
	sem_wait(philo->chat);
	printf("%zu %d is eating\n",
		get_time(philo->begin_time), number + 1);
	philo->begin_life = get_time(0);
	sem_post(philo->chat);
	my_usleep(philo->time_to_eat);
}

void	sleeping_thinking(t_philo *philo, int number)
{
	sem_wait(philo->chat);
	printf("%zu %d is sleeping\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	my_usleep(philo->time_to_sleep);
	sem_wait(philo->chat);
	printf("%zu %d is thinking\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
}
