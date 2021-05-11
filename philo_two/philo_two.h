#ifndef PHILO_TWO_H

# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num;

	pthread_t		thread;

	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			must_eat;
	ssize_t			begin_time;
	ssize_t			begin_life;
}					t_philo;

typedef struct s_data
{
	int				pos_philo;
	int				count_philo;

	ssize_t			begin_time;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			must_eat;

	sem_t			*chat;
	sem_t			*bunch_forks;
	sem_t			*waiter_stop;
	sem_t			*security;

	t_philo			*array_philo;
}				t_data;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

void	init_data(char **argv, int argc, t_data *data);

ssize_t	get_time(ssize_t begin_time);

void	my_usleep(ssize_t time);

void	take_fork(t_data *data, int number);

void	put_fork(t_data *data, int number);

void	eating(t_data *data, int number);

void	sleeping_thinking(t_data *data, int number);

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

#endif
