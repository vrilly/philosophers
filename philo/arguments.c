#include "philo.h"

static int	fatoi(char *str)
{
	long	result;
	int		negative;

	result = 0;
	while ((*str == ' ' || *str == '\t' || *str == '\r'
			|| *str == '\n' || *str == '\v' || *str == '\f') && *str)
		str++;
	negative = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		result *= 10;
		result += (int)*str - '0';
		str++;
	}
	if (negative)
		return (result * -1);
	return (result);
}

static int	parse_arg(char *arg, int *dst, char *param)
{
	int	i;

	if (!arg)
	{
		printf("Argument %s is missing.\n", param);
		return (1);
	}
	i = fatoi(arg);
	if (i <= 0)
	{
		printf("Argument %s is out of range.\n", param);
		return (1);
	}
	*dst = i;
	return (0);
}

int	get_args(t_args *args, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 2)
		parse_arg(NULL, NULL, "number_of_philosophers");
	if (argc < 3)
		parse_arg(NULL, NULL, "time_to_die");
	if (argc < 4)
		parse_arg(NULL, NULL, "time_to_eat");
	if (argc < 5)
		parse_arg(NULL, NULL, "time_to_sleep");
	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 6)
		i += parse_arg(argv[5], &args->times_to_eat,
			"number_of_times_each_philosopher_must_eat");
	else
		args->times_to_eat = -1;
	i += parse_arg(argv[1], &args->num_of_philosophers,
			"number_of_philosophers");
	i += parse_arg(argv[2], &args->time_to_die, "time_to_die");
	i += parse_arg(argv[3], &args->time_to_eat, "time_to_eat");
	i += parse_arg(argv[4], &args->time_to_sleep, "time_to_sleep");
	return (i);
}
