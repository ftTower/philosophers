/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/05/26 02:00:54 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

// void	life(t_philo *philo)
// {
// 	if (get_bool(philo->utils.mutex, philo->info.rdy_to_eat))
// 		printf("EAT\n");
// }

void	*philo_life(void *in_philo)
{
	t_philo	*philo;

	philo = (t_philo *)in_philo;
	while (!get_bool(philo->sync->mutex, philo->sync->all_ready))
		;
	philo->info.t_spawn = get_time(MILLISECOND);
	// while (!get_bool(philo->sync->mutex, philo->sync->end))
	// 	life(philo);
	return (NULL);
}

void	*monitor_life(void *in_monitor)
{
	t_monitor	*monitor;
	long		index;

	monitor = (t_monitor *)in_monitor;
	while (!get_bool(monitor->sync->mutex, monitor->sync->all_ready))
		;
	while (!get_bool(monitor->sync->mutex, monitor->sync->end))
	{
		index = -1;
		while (++index < monitor->param.n_philo)
		{
			// printf("%ld\n", monitor->philos[index].id);
			if (get_statut(&monitor->philos[monitor->philos[index].utils.next_pos]) != EAT
				&& !get_bool(monitor->philos[monitor->philos[index].utils.next_pos].utils.mutex,
					monitor->philos[monitor->philos[index].utils.next_pos].info.rdy_to_eat)
				&& get_statut(&monitor->philos[monitor->philos[index].utils.prev_pos]) != EAT
				&& !get_bool(monitor->philos[monitor->philos[index].utils.prev_pos].utils.mutex,
					monitor->philos[monitor->philos[index].utils.prev_pos].info.rdy_to_eat))
				set_statut(&monitor->philos[index], EAT);
			if (get_time(MILLISECOND) - monitor->sync->t_start > 100)
				set_bool(monitor->sync->mutex, &monitor->sync->end, true);
		}
	}
	printf("monitor ok\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	long	index;

	if (argc < 4 || argc > 6 || init_data(&data, argv + 1))
		return (printf("failure\n"), EXIT_FAILURE);
	index = -1;
	while (++index < data.philos[0].param.n_philo)
		pthread_create(&data.philos[index].utils.thread, NULL, philo_life,
			&data.philos[index]);
	pthread_create(&data.monitor.thread, NULL, monitor_life, &data.monitor);
	set_bool(data.sync.mutex, &data.sync.all_ready, true);
	data.sync.t_start = get_time(MILLISECOND);
	index = -1;
	while (++index < data.philos[0].param.n_philo)
		pthread_join(data.philos[index].utils.thread, NULL);
	pthread_join(data.monitor.thread, NULL);
	return (debug_philos(data.philos, data.philos[0].param.n_philo),
		EXIT_SUCCESS);
}
