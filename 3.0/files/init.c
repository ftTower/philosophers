/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:24:47 by tauer             #+#    #+#             */
/*   Updated: 2024/05/29 00:01:23 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	data_null(t_data *data)
{
	data->lifetime.max_meal = 0;
	data->lifetime.t_die = 0;
	data->lifetime.t_eat = 0;
	data->lifetime.t_sleep = 0;
	data->sync.t_simulation = 0;
	data->sync.n_threads = 0;
	data->sync.end = false;
	data->sync.all_ready = false;
	data->forks = NULL;
	data->philos = NULL;
}

void	data_free(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->sync.ready)
		free(data->sync.ready);
}

void	data_link(t_data *data)
{
	long	index;

	index = -1;
	while (++index < data->lifetime.n_philo)
	{
		data->philos[index].first_fork = data->forks[index];
		data->philos[index].second_fork = &data->forks[(index + 1)
			% data->lifetime.n_philo];
		// if (index % 2 == 0)
		// {
		// 	data->philos[index].first_fork = data->forks[(index + 1)
		// 		% data->lifetime.n_philo];
		// 	data->philos[index].second_fork = &data->forks[index];
		// }
		data->philos[index].lifetime = data->lifetime;
		data->sync.ready[index] = false;
		data->philos[index].sync = &data->sync;
		data->philos[index].statut.n_meal = 0;
		data->philos[index].statut.t_meal = 0;
		data->philos[index].statut.statut = UNASSIGNED;
	}
}

bool	data_memory(t_data *data)
{
	long	index;

	data->philos = malloc(sizeof(t_philo) * data->lifetime.n_philo);
	data->forks = malloc(sizeof(t_fork) * data->lifetime.n_philo);
	data->sync.ready = malloc(sizeof(bool) * data->lifetime.n_philo);
	if (!data->philos || !data->forks || !data->sync.ready)
		return (data_free(data), terror("data_memory", "malloc failed"), true);
	index = -1;
	
	return (data_link(data), false);
}

bool	data_lifetime(t_data *data, char **argv)
{
	if (!ft_atoi(argv[0], &data->lifetime.n_philo, false) || !ft_atoi(argv[1],
			&data->lifetime.t_die, true) || !ft_atoi(argv[2],
			&data->lifetime.t_eat, true) || !ft_atoi(argv[3],
			&data->lifetime.t_sleep, true))
		return (terror("data_lifetime", "failed to atoi args"), true);
	else if (data->lifetime.t_die < 6e3 || data->lifetime.t_eat < 6e3
		|| data->lifetime.t_sleep < 6e3)
		return (terror("data_lifetime", "args need to be > 6000ms"), true);
	return (ft_atoi(argv[4], &data->lifetime.max_meal, false), false);
}

bool	data_init(t_data *data, int argc, char **argv)
{
	if (!argv[0] || argc <= 4 || argc > 6)
		return (terror("data_init", "invalid args"), true);
	return (data_null(data), data_lifetime(data, argv) || data_memory(data));
}
