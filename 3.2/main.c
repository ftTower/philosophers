/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:18:43 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 02:10:51 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum e_error
{
	SUCCES,
	NB_ARGC,
	ERR_ARGV,
	MUTEX_EAGAIN,
	MUTEX_EBUSY,
	MUTEX_EINVAL,
	MUTEX_EFAULT,
}					t_error;

typedef struct s_arg
{
	long			time_eat;
	long			time_die;
	long			time_sleep;
	long			nb_philos;
	long			max_meals;
}					t_arg;

typedef struct s_philosopher
{
	long			id;
	long			left_fork;
	long			right_fork;
	pthread_mutex_t	mutex;
}					t_philosopher;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philosopher	*philos;
	t_arg			arg;
	pthread_mutex_t	mutex_sync;
	pthread_mutex_t	mutex_write;
}					t_table;

bool	ft_atoi(const char *str, long *out_value, bool is_time)
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
	while (str[i])
	{
		if (value > (__INT_MAX__ - str[i] + '0') / 10 || str[i] > '9'
			|| str[i] < '0')
			return (*out_value = -1, false);
		value = (value * 10) + (str[i++] - '0');
	}
	if (is_time)
		return (*out_value = (value * sign) * 1e3, true);
	return (*out_value = (value * sign), true);
}

void	error_catcher(t_error error_code)
{
	if (error_code == SUCCES)
		return ;
	else if (error_code == NB_ARGC || error_code == ERR_ARGV)
		printf("[nb_philosophers] [time_eat] [time_die] [time_sleep] {max_meals}\n");
	else if (error_code == MUTEX_EINVAL)
		printf("[EINVAL] : Invalid argument\n");
	else if (error_code == MUTEX_EBUSY)
		printf("[EBUSY] : Device or resource busy\n");
	else if (error_code == MUTEX_EAGAIN)
		printf("[EAGAIN] : Resource temporarily unavailable\n");
	else if (error_code == MUTEX_EFAULT)
		printf("[EFAULT] : Bad adress\n");
	exit(EXIT_FAILURE);
}

t_error	error_mutex(t_table *table,int mutex_error_code, long comp_index, long statut)
{
	t_error error_code;
	long index;

	if (mutex_error_code == EAGAIN)
		error_code = MUTEX_EAGAIN;
	else if (mutex_error_code == EBUSY)
		error_code = MUTEX_EBUSY;
	else if (mutex_error_code == EINVAL)
		error_code = MUTEX_EINVAL;
	else if (mutex_error_code == EFAULT)
		error_code = MUTEX_EFAULT;
	if (statut == 1 || statut == 2 || statut == 3)
		pthread_mutex_destroy(&table->mutex_sync);
	else if (statut == 2 || statut == 3)
	{
		pthread_mutex_destroy(&table->mutex_write);
		index = -1;
		while(++index < comp_index)
		{
			pthread_mutex_destroy(&table->philos[index].mutex);
			if ((statut != 2 && index < comp_index - 1) || statut == 3)
				pthread_mutex_destroy(&table->forks[index]);
		}
	}
}

bool	init_mutex(t_table *table, t_error *error_code)
{
	int		mutex_code;
	long	index;

	mutex_code = pthread_mutex_init(&table->mutex_sync, NULL);
	if (mutex_code != 0)
		return (*error_code = error_mutex(table, mutex_code, 0, 0), true);
	mutex_code = pthread_mutex_init(&table->mutex_write, NULL);
	if (mutex_code != 0)
		return (*error_code = error_mutex(table, mutex_code, 0, 1), true);
	index = -1;
	while (++index < table->arg.nb_philos)
	{
		mutex_code = pthread_mutex_init(&table->philos[index].mutex, NULL);
		if (mutex_code != 0)
			return (*error_code = error_mutex(table, mutex_code, index, 2), true);
		mutex_code = pthread_mutex_init(&table->forks[index], NULL);
		if (mutex_code != 0)
			return (*error_code = error_mutex(table, mutex_code, index, 3), true);
	}
	return (false);
}

bool	init_philosophers(t_table *table, t_error *error_code)
{

}

bool	init_param(t_table *table, t_error *error_code, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (*error_code = NB_ARGC, true);
	else if (!ft_atoi(argv[0], &table->arg.nb_philos, false)
		|| !ft_atoi(argv[1], &table->arg.time_eat, true) || !ft_atoi(argv[2],
			&table->arg.time_die, true) || !ft_atoi(argv[3],
			&table->arg.time_sleep, true))
		return (*error_code = ERR_ARGV, true);
	return (ft_atoi(argv[4], &table->arg.max_meals, false), false);
}

bool	init_table(t_table *table, t_error *error_code, int argc, char **argv)
{
	*error_code = SUCCES;
	if (init_param(table, error_code, argc, argv))
		return (true);
	else if (init_mutex(table, error_code))
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_error	error_code;

	if (init_table(&table, &error_code, argc, argv + 1))
		error_catcher(error_code);
	return (EXIT_SUCCESS);
}
