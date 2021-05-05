#ifndef PHILO_ONE_H

# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct timeval timing;

typedef struct s_philo
{
	int				num;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_t		thread;

	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	must_eat;
	ssize_t begin_time;
	ssize_t begin_life;

	// struct timeval tv1;
	// struct timeval tv2;
	// struct timeval dtv;
	// struct timezone tz;
}				t_philo;

typedef struct s_data
{
	int		count_philo;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	must_eat;

	t_philo	*array_philo;
	ssize_t begin_time;
}				t_data;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

void	init_data(char **argv, int argc, t_data *data);

// long	time_stop(void);

ssize_t get_time(ssize_t begin_time);

#endif
