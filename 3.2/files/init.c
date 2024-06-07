/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:38:46 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 19:27:16 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	init_mutex(t_table *table, t_error *error_code)
{
	int		mutex_code;
	long	index;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->arg.nb_philos);
	if (!table->forks)
		return (*error_code = MALLOC_FORK, true);
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
			return (*error_code = error_mutex(table, mutex_code, index, 2),
				true);
		mutex_code = pthread_mutex_init(&table->forks[index], NULL);
		if (mutex_code != 0)
			return (*error_code = error_mutex(table, mutex_code, index, 3),
				true);
	}
	return (false);
}

bool	init_philosophers(t_table *table, t_error *error_code)
{
	long	index;

	table->philos = malloc(sizeof(t_philosopher) * table->arg.nb_philos);
	if (!table->philos)
		return (*error_code = MALLOC_PHILO, true);
	index = -1;
	while (++index < table->arg.nb_philos)
	{
		table->philos[index].table = table;
		table->philos[index].id = index;
		table->philos[index].left_fork = index;
		if (index == 0)
			table->philos[index].right_fork = table->arg.nb_philos - 1;
		else
			table->philos[index].right_fork = index - 1;
	}
	return (false);
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
	return (ft_atoi(argv[4], &table->arg.max_meals, false),
		table->everyone_ready = false, false);
}

bool	init_table(t_table *table, t_error *error_code, int argc, char **argv)
{
	*error_code = SUCCES;
	if (init_param(table, error_code, argc, argv))
		return (true);
	else if (init_philosophers(table, error_code))
		return (true);
	else if (init_mutex(table, error_code))
		return (true);
	return (false);
}
