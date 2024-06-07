/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/06/07 18:31:52 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int	main(int argc, char **argv)
{
	t_data	data;
	long	index;

	//!init

	if (argc < 5 || argc > 6 || init_data(&data, argv + 1))
		return (printf("failure\n"), EXIT_FAILURE);
	// data.sync.t_start = get_time(MILLISECOND);
	
	//! mutexs
	
	pthread_mutex_init(&data.sync.mutex, NULL);
	pthread_mutex_init(&data.sync.write_mutex, NULL);
	for (index = 0; index < data.philos[0].param.n_philo; index++)
	{
		pthread_mutex_init(&data.philos[index].utils.mutex, NULL);
		pthread_mutex_init(&data.philos[index].info.mutex, NULL);	
	}

	//! threads
	
	index = -1;
	pthread_create(&data.monitor.thread, NULL, monitor_life, &data);
	while (++index < data.philos[0].param.n_philo)
	{
		pthread_create(&data.philos[index].utils.thread, NULL, philo_life,
			&data.philos[index]);
		// usleep(1);
	}

	//! start

	set_bool(&data.sync.mutex, &data.sync.all_ready, true);
	set_long(&data.sync.mutex, &data.sync.t_start,
		get_time(MILLISECOND));
	// set_long(&monitor->philos[0].sync->mutex,
		// &monitor->philos->sync->t_start, get_time(MILLISECOND));
	// usleep(500);

	//!finish
	
	
	pthread_join(data.monitor.thread, NULL);
	index = -1;
	while (++index < data.philos[0].param.n_philo)
		pthread_join(data.philos[index].utils.thread, NULL);
	
	for (index = 0; index < data.philos[0].param.n_philo; index++)
		pthread_mutex_destroy(&data.philos[index].utils.mutex);
	pthread_mutex_destroy(&data.sync.mutex);
	
	return (debug_philos(data.philos, data.philos[0].param.n_philo),
		free(data.philos), free(data.monitor.all_status), EXIT_SUCCESS);
}
