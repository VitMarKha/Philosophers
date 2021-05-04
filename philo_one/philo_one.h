#ifndef PHILO_ONE_H

# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>



typedef struct s_philo
{
	int num;
	pthread_t thread;
	pthread_mutex_t mutex;
}				t_philo;

typedef struct s_data
{
	int		number_of_philosophers;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	number_of_times_each_philosopher_must_eat;
	t_philo	*array;
}				t_data;

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t size);

#endif
