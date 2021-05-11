#include "philo_three.h"

static	void	take_fork(t_philo *philo, int number)
{
	sem_wait(philo->waiter_stop);
	sem_wait(philo->bunch_forks);
	sem_wait(philo->chat);
	printf("\x1b[33m%zu %d has taken a fork\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	sem_wait(philo->bunch_forks);
	sem_wait(philo->chat);
	printf("\x1b[33m%zu %d has taken a fork\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	sem_post(philo->waiter_stop);
}

static	void	put_fork(t_philo *philo)
{
	sem_post(philo->bunch_forks);
	sem_post(philo->bunch_forks);
}

static	void	eating(t_philo *philo, int number)
{
	sem_wait(philo->chat);
	printf("\x1b[32m%zu %d is eating\n",
		get_time(philo->begin_time), number + 1);
	philo->begin_life = get_time(0);
	sem_post(philo->chat);
	my_usleep(philo->time_to_eat);
}

static	void	sleeping_thinking(t_philo *philo, int number)
{
	sem_wait(philo->chat);
	printf("\x1b[34m%zu %d is sleeping\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
	my_usleep(philo->time_to_sleep);
	sem_wait(philo->chat);
	printf("\x1b[35m%zu %d is thinking\n",
		get_time(philo->begin_time), number + 1);
	sem_post(philo->chat);
}

void	*philo(void	*philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	pthread_detach(philo->thread);
	while (1)
	{
		take_fork(philo, philo->num);
		eating(philo, philo->num);
		put_fork(philo);
		if (philo->must_eat != -1)
		{
			--philo->must_eat;
			if (philo->must_eat == 0)
			{
				sem_post(philo->eat);
				exit(0);
			}
		}
		sleeping_thinking(philo, philo->num);
	}
	return (NULL);
}
