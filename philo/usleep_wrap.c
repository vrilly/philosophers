#include "philosophers.h"

void	usleep_wrap(unsigned int n)
{
	struct timeval	begin;
	struct timeval	temp;

	gettimeofday(&begin, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
		if ((size_t)(((size_t)(temp.tv_sec - begin.tv_sec)) * 1000000 +
				((size_t)(temp.tv_usec - begin.tv_usec))) > n)
			break ;
	}
}
