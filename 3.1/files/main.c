/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/05/28 02:09:00 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int	main(int argc, char **argv)
{
	t_data	data;
	long	index;

	if (argc < 5 || argc > 6 || init_data(&data, argv + 1))
		return (printf("failure\n"), EXIT_FAILURE);
	index = -1;
	// data.sync.t_start = get_time(MILLISECOND);
	pthread_create(&data.monitor.thread, NULL, monitor_life, &data.monitor);
	while (++index < data.philos[0].param.n_philo)
		pthread_create(&data.philos[index].utils.thread, NULL, philo_life,
			&data.philos[index]);
	// usleep(500);
	set_long(data.sync.mutex, &data.sync.t_start, get_time(MILLISECOND));
	set_bool(data.sync.mutex, &data.sync.all_ready, true);
	index = -1;
	pthread_join(data.monitor.thread, NULL);
	while (++index < data.philos[0].param.n_philo)
		pthread_join(data.philos[index].utils.thread, NULL);
	for (index = 0; index < data.philos[0].param.n_philo; index++)
		pthread_mutex_destroy(&data.philos[index].utils.mutex);
	pthread_mutex_destroy(&data.sync.mutex);
	return (debug_philos(data.philos, data.philos[0].param.n_philo), free(data.philos),free(data.monitor.all_status),
		EXIT_SUCCESS);
}
