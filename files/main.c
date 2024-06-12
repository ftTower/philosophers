/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 01:13:03 by tauer            ###   ########.fr       */
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
	pthread_create(&data.monitor.thread, NULL, monitor_life, &data);
	while (++index < data.philos[0].param.n_philo)
		pthread_create(&data.philos[index].utils.thread, NULL, philo_life,
			&data.philos[index]);
	set_bool(&data.sync, &data.sync.mutex, &data.sync.all_ready, true);
	index = -1;
	pthread_join(data.monitor.thread, NULL);
	while (++index < data.philos[0].param.n_philo)
		pthread_join(data.philos[index].utils.thread, NULL);
	return (mutex_destroy(&data), debug_philos(data.philos,
			data.philos[0].param.n_philo), free(data.philos),
		free(data.monitor.all_status), EXIT_SUCCESS);
}
