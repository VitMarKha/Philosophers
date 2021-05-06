#include "philo_one.h"

static  int ft_isdigit(int c)
{
	return (((c >= 48) && (c <= 57)) ? 1 : 0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;
	int			sign;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		++i;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i] - '0');
		if ((n > 2147483647 && sign == 1) ||
			(n < -2147483647 && sign == -1))
			return ((sign == 1) ? -1 : 0);
		i++;
	}
	return (sign * n);
}

static	void	ft_bzero(void *s, size_t n)
{
	char *tmp;

	if (n == 0)
		return ;
	tmp = s;
	while (n-- != 0)
		*tmp++ = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
