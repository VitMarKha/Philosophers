#include "philo_three.h"

static	size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

static	char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		++i;
		++j;
	}
	p[i] = '\0';
	return (p);
}

static	char	*ft_itoa(int nbr)
{
	int		temp;
	int		size;
	int		sign;
	char	*str;

	temp = nbr;
	size = 1;
	sign = nbr < 0;
	while (temp /= 10)
		size++;
	if (!(str = malloc(sizeof(char) * (size + 1 + sign))))
		return (NULL);
	if (sign)
		*str++ = '-';
	str += size;
	*str-- = '\0';
	if (nbr == 0)
		*str-- = '0';
	while (nbr)
	{
		*str-- = (nbr % 10) * (sign ? -1 : 1) + '0';
		nbr /= 10;
	}
	return (str + 1 - sign);
}

static	void	init_semaphore(t_data *data, int argc)
{
	int		i;
	char	*str;
	char	*num;

	data->bunch_forks = sem_open("bunch_forks", O_CREAT, 0777,
			data->count_philo);
	sem_unlink("bunch_forks");
	data->waiter_stop = sem_open("waiter_stop", O_CREAT, 0777, 1);
	sem_unlink("waiter_stop");
	data->chat = sem_open("chat", O_CREAT, 0777, 1);
	sem_unlink("chat");
	if (argc == 6)
	{
		data->eat = ft_calloc(data->count_philo, sizeof(sem_t *));
		i = -1;
		while (++i < data->count_philo)
		{
			num = ft_itoa(i);
			str = ft_strjoin("eat", num);
			data->array_philo[i].eat = sem_open(str, O_CREAT, 0777, 1);
			sem_unlink(str);
			free(str);
			free(num);
			sem_wait(data->array_philo[i].eat);
		}
	}
}

void	init_data(char **argv, int argc, t_data *data)
{
	data->begin_time = get_time(0);
	data->count_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->array_philo = ft_calloc(data->count_philo, sizeof(t_philo *));
	data->pids = ft_calloc(data->count_philo, sizeof(pid_t));
	init_semaphore(data, argc);
}
