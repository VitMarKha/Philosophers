#include "philo_one.h"

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
