#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>

typedef enum e_printer_msg
{
	CUSTOM,
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	DONE
}	t_printer_msg;

typedef struct s_args
{
	int	num_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
}	t_args;

typedef struct s_chopstick
{
	int				reserved;
	pthread_mutex_t	*mutex;
}	t_chopstick;

typedef struct s_global_vars
{
	t_args			args;
	struct timeval	start_time;
	pthread_mutex_t	state_lock;
	int				dead;
	int				done;
}	t_global_vars;

typedef struct s_philosopher
{
	int				philosopher_number;
	int				times_eaten;
	struct timeval	s_last_feeding;
	pthread_t		thread;
	t_chopstick		*cs_left;
	t_chopstick		*cs_right;

	t_global_vars	*globals;
}	t_philosopher;

typedef struct s_philosophers
{
	t_global_vars	globals;
	t_chopstick		**chopsticks;
	t_philosopher	**entities;
	pthread_t		watchdog;
}	t_philosophers;

typedef void*	(*t_start_routine)(void *);

int				get_args(t_args *args, int argc, char **argv);
void			spawn_chopsticks(t_philosophers *philosophers);
void			spawn_philosophers(t_philosophers *philosophers);
void			*philosopher(t_philosopher *data);
int				ms_between_timestamps(struct timeval *a, struct timeval *b);
void			usleep_wrap(unsigned int n);
void			printer(t_philosopher *data, t_printer_msg msg, char *custom_msg);
void			*watchdog(t_philosophers *philos);

#endif
