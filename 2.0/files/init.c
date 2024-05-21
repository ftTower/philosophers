/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:16:05 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 22:41:01 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	init_data(t_data *data)
{
	data->n_threads = 0;
	data->b_ready = false;
	data->b_end = false;
	
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->fork = malloc(sizeof(t_fork) * data->n_philo);

	pthread_mutex_init(&data->table, NULL);
	pthread_mutex_init(&data->write, NULL);

	long index = -1;
	while(++index < data->n_philo)
	{
		data->philo[index].id = index;
		data->philo[index].t_meal = 0;
		data->philo[index].n_meal = 0;
		data->philo[index].dead = false;
		data->philo[index].data = data;
		pthread_mutex_init(&data->philo[index].philo, NULL);
		pthread_mutex_init(&data->fork[index].fork, NULL);
		data->fork[index].id = index;
	}
	index = -1;
	while (++index < data->n_philo)
	{
		if (index % 2 != 0)
		{
			data->philo[index].l_fork = data->fork[index];
			data->philo[index].r_fork = &data->fork[(index + 1)
			% data->n_philo];		
		}
		else
		{
			data->philo[index].r_fork = &data->fork[index];
			data->philo[index].l_fork = data->fork[(index + 1)
			% data->n_philo];			
		}
	}
}

bool	setup(t_data *data, char **argv)
{
	if (ft_atoi(argv[0], &data->n_philo) && ft_atoi(argv[1], &data->t_die)
		&& ft_atoi(argv[2], &data->t_eat) && ft_atoi(argv[3], &data->t_sleep))
		return (data->t_die *= 1e3, data->t_eat *= 1e3, data->t_sleep *= 1e3,
			ft_atoi(argv[4], &data->n_meal), init_data(data), print_data(data),
			(data->t_die < 6e3 && data->t_eat < 6e3 && data->t_sleep < 6e3));
	return (true);
}