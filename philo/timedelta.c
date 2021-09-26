#include "philosophers.h"

int	ms_between_timestamps(struct timeval *a, struct timeval *b)
{
	int	sec_delta;
	int	ms_delta;

	sec_delta = b->tv_sec - a->tv_sec;
	ms_delta = (b->tv_usec - a->tv_usec) / 1000;
	ms_delta += sec_delta * 1000;
	return (ms_delta);
}
