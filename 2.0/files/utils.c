/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:13:10 by tauer             #+#    #+#             */
/*   Updated: 2024/05/21 22:09:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	ft_atoi(const char *str, long *out_value)
{
	int	sign;
	int	value;
	int	i;

	value = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (*out_value = -1, false);
	while (str[i] && (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if (value > (__INT_MAX__ - str[i] + '0') / 10)
			return (*out_value = -1, false);
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (true);
	return (*out_value = value * sign, true);
}



#include <unistd.h>

void	t_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rest;

	start = get_time(data, MICROSECOND);
	while (get_time(data, MICROSECOND) - start < usec)
	{
		if (end(data))
			break ;
		elapsed = get_time(data, MICROSECOND) - start;
		rest = usec - elapsed;
		if (rest > 1e3)
			usleep(rest / 2);
		else
			while (get_time(data, MICROSECOND) - start < usec)
				;
	}
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	set_long(philo->data, &philo->philo, &philo->t_meal, get_time(philo->data,
			MILLISECOND));
	increase_long(philo->data, &philo->data->table, &philo->data->n_threads);
	print_statut(L_FORK, philo->data, philo, false);
	while (!end(philo->data))
		t_usleep(200, philo->data);
	return (NULL);
}