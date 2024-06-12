/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:54:36 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 00:22:04 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	mutex_destroy(t_data *data)
{
	long	index;

	index = -1;
	while (++index < data->monitor.param.n_philo)
		pthread_mutex_destroy(&data->philos[index].utils.mutex);
	pthread_mutex_destroy(&data->sync.mutex);
}

void	mutex_init(t_data *data)
{
	long	index;

	index = -1;
	pthread_mutex_init(&data->sync.mutex, NULL);
	pthread_mutex_init(&data->sync.write_mutex, NULL);
	while (++index < data->monitor.param.n_philo)
	{
		pthread_mutex_init(&data->philos[index].utils.mutex, NULL);
		pthread_mutex_init(&data->philos[index].info.mutex, NULL);
	}
}
