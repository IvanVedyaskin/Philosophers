#include "philo.h"


int	print_error(int flag)
{
	if (flag == 1)
		printf ("The argument is greater than an integer!\n");
	else if (flag == 2)
		printf ("The argument cannot be a negative number!\n");
	else if (flag == 3)
		printf ("Invalid number of arguments!\n");
	else
		printf ("Enter at least one philosopher!\n");
	return (0);
}

int	ft_atoi(char *str, int *ag_philo)
{
	int						i;
	int						negative;
	unsigned long long int	num;

	num = 0;
	negative = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (print_error(1));
		i++;
	}
	if (negative < 0)
		return (print_error(2));
	*ag_philo = (int) num;
	return (1);
}

int	ft_init(int ag, char **av, t_main_philo *philo)
{
	if (ag >= 5 && ag <= 6)
	{
		if (!ft_atoi(av[1], &philo->num_of_philo))
			return (0);
		if (!ft_atoi(av[2], &philo->time_to_die))
			return (0);
		if (!ft_atoi(av[3], &philo->time_to_eat))
			return (0);
		if (!ft_atoi(av[4], &philo->time_to_sleep))
			return (0);
	}
	else
		return (print_error(3));
	if (ag == 6)
	{
		if (!ft_atoi(av[5], &philo->num_must_eat))
			return (0);
	}
	if (philo->num_of_philo == 0)
		return (print_error(4));
	return (1);
}

int	main(int ag, char **av)
{
    t_main_philo	philo;
	// struct timeval	start;

	// gettimeofday(&start, 0);
	// philo.start_time = &start;
	if (!ft_init(ag, av, &philo))
		return (0);
	if (!philo_create(&philo))
        return (0);
}