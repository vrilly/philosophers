#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef struct s_args
{
	int	num_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_args;

typedef struct s_chopstick
{
	int				reserved;
	pthread_mutex_t	*mutex;
}	t_chopstick;

typedef struct s_philosopher
{
	int				philosopher_number;
	struct timeval	*start_time;
	struct timeval	s_last_feeding;
	pthread_t		thread;
	t_args			*args;
	pthread_mutex_t	*cs_state;
	t_chopstick		*cs_left;
	t_chopstick		*cs_right;
}	t_philosopher;

typedef struct s_philosophers
{
	pthread_mutex_t	*cs_state;
	t_chopstick		**chopsticks;
	t_philosopher	**entities;
	t_args			args;
	struct timeval	start_time;
}	t_philosophers;

typedef void*	(*t_start_routine)(void *);

void	get_args(t_args *args, char *input);
void	spawn_chopsticks(t_philosophers *philosophers);
void	spawn_philosophers(t_philosophers *philosophers);
void	*philosopher(t_philosopher *data);
int		ms_between_timestamps(struct timeval *a, struct timeval *b);
int		try_lock_cs(t_philosopher *data);
void	unlock_cs(t_philosopher *data);

#endif