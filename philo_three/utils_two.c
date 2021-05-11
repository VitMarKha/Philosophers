#include "philo_three.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

static	void	ft_itoa_while(int *nbr, int *sign, char **str)
{
	while (*nbr)
	{
		if (*sign)
			*sign = -1;
		else
			*sign = 1;
		**str-- = (*nbr % 10) * *sign + '0';
		*nbr /= 10;
	}
}

char	*ft_itoa(int nbr)
{
	int		temp;
	int		size;
	int		sign;
	char	*str;

	temp = nbr;
	size = 1;
	sign = nbr < 0;
	temp /= 10;
	while (temp)
		size++;
	str = malloc(sizeof(char) * (size + 1 + sign));
	if (!str)
		return (NULL);
	if (sign)
		*str++ = '-';
	str += size;
	*str-- = '\0';
	if (nbr == 0)
		*str-- = '0';
	ft_itoa_while(&nbr, &sign, &str);
	return (str + 1 - sign);
}

void	kill_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count_philo)
		kill(data->pids[i], 9);
	free(data->pids);
}
