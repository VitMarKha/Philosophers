#ifndef PHILO_THREE_H

# define PHILO_THREE_H

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

	pthread_t		thread;
	pid_t			*pid;

	ssize_t			begin_time;
	ssize_t			begin_life;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			must_eat;

	sem_t			*chat;
	sem_t			*bunch_forks;
	sem_t			*waiter_stop;
	sem_t			*eat;
}					t_philo;

typedef struct s_data
{
	int				status_pid;
	int				count_philo;

	ssize_t			begin_time;
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
}				t_data;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

void	init_data(char **argv, int argc, t_data *data);

void	init_philo(t_data *data, int argc, int i);

ssize_t	get_time(ssize_t begin_time);

void	my_usleep(ssize_t time);

void	*philo(void	*philo_tmp);

void	kill_all(t_data *data);

void	checking_arguments(char **argv, int argc);

size_t	ft_strlen(const char *s);

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_itoa(int nbr);

#endif
