#include "philosophers.h"

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

int	ft_init(int ag, char **av, t_m_data *m_data)
{
	if (ag >= 5 && ag <= 6)
	{
		if (!ft_atoi(av[1], &m_data->n_philo))
			return (0);
		if (!ft_atoi(av[2], &m_data->t_to_die))
			return (0);
		if (!ft_atoi(av[3], &m_data->t_to_eat))
			return (0);
		if (!ft_atoi(av[4], &m_data->t_to_sleep))
			return (0);
	}
	else
		return (print_error(3));
	m_data->n_eat = -1;
	if (ag == 6)
	{
		if (!ft_atoi(av[5], &m_data->n_eat))
			return (0);
	}
	if (m_data->n_philo == 0)
		return (print_error(4));
	return (1);
}

int is_died(t_m_data *m_date)
{
	int 			i;
	long int		time;
	struct timeval	tmp;

	i = 0;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		while (i < m_date->n_philo)
		{
			time = (tmp.tv_sec - m_date->philo[i].t_eat.tv_sec) * 1000 + \
				(tmp.tv_usec - m_date->philo[i].t_eat.tv_usec) / 1000;
			if (time > m_date->t_to_die)
			{
//				pthread_mutex_lock(&m_date->std_out);
				return (print_status(&(m_date->philo[i]), 4));
			}
			if (m_date->philo[i].n_eat == 0) {
//				pthread_mutex_lock(&m_date->std_out);
				return (print_status(&(m_date->philo[i]), 5));
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (5);
}

int main(int ag, char **av)
{
	t_m_data m_date;

	if (!ft_init(ag, av, &m_date))
		return (0);
	if (!ph_mutex_tread_all(&m_date))
		return (0);
	usleep (1000);
	is_died(&m_date);
    return 0;
}
