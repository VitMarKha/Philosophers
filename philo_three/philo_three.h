#ifndef PHILO_TWO_H

# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philo
{
	int				num;
	int				argc;
	int				how_many_us;
	int				i_ate;
	pthread_t		thread;
	pid_t			*pid;

	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			must_eat;
	ssize_t			begin_time;
	ssize_t			begin_life;

	sem_t			*chat;
	sem_t			*bunch_forks;
	sem_t			*waiter_stop;
	sem_t			*eat;
}					t_philo;

typedef struct s_data
{
	int				pos_philo;
	int				status;
	int				count_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			must_eat;
	sem_t			*chat;
	sem_t			*bunch_forks;
	sem_t			*waiter_stop;
	sem_t			*eat;
	pid_t			*pids;
	pthread_t		monitoring_die;
	pthread_t		monitoring_eat;

	t_philo			*array_philo;
	ssize_t			begin_time;
}				t_data;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

void	init_data(char **argv, int argc, t_data *data);

ssize_t	get_time(ssize_t begin_time);

void	my_usleep(ssize_t time);

void	take_fork(t_philo *philo, int number);

void	put_fork(t_philo *philo);

void	eating(t_philo *philo, int number);

void	sleeping_thinking(t_philo *philo, int number);

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

#endif
