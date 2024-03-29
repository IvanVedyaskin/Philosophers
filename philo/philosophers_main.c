/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:20:24 by mmeredit          #+#    #+#             */
/*   Updated: 2022/05/01 16:20:26 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_error(int flag)
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

static int	ft_atoi(char *str, int *ag_philo)
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

static int	ft_init(int ag, char **av, t_m_data *m_data)
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

static int	is_died(t_m_data *m_data)
{
	int				i;
	struct timeval	tmp;

	i = -1;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		while (++i < m_data->n_philo)
		{
			pthread_mutex_lock(&m_data->philo[i].time);
			if (time_count(&tmp, &m_data->philo[i].t_eat) > m_data->t_to_die)
			{
				pthread_mutex_unlock(&m_data->philo[i].time);
				pthread_mutex_lock(&m_data->std_out);
				if (check_eat(m_data))
					return (pthread_mutex_unlock(&m_data->std_out));
				else
					return (print_status(&(m_data->philo[i]), 4));
			}
			pthread_mutex_unlock(&m_data->philo[i].time);
		}
		i = -1;
		usleep(1000);
	}
	return (5);
}

int	main(int ag, char **av)
{
	t_m_data	m_data;

	if (!ft_init(ag, av, &m_data))
		return (write(1, "Error!\n", 7));
	if (!ph_mutex_tread_all(&m_data))
		return (write(1, "Error!\n", 7));
	if (is_died(&m_data) == 5)
	{
		if (!all_destroy(&m_data))
			return (write(1, "Error!\n", 7));
	}
	return (0);
}
