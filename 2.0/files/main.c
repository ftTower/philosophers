/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:06:31 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 22:27:21 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	*monitor_routine(void *in_data)
{
	t_data	*data;
	long	index;

	index = -1;
	data = (t_data *)in_data;
	// data->b_end = false;
	while (!all_threads_running(data))
		;
	while (!end(data))
	{
		while (++index < data->n_philo)
		{
			if (philo_died(&data->philo[index]))
			{
				set_bool(data, &data->table, &data->b_end,
					true);
				print_statut(DEAD, data, &data->philo[index],
					false);
			}
		}
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	long	index;

	printf("Starting simulation...\n");
	if (!data->philo)
		s_exit(data, EXIT_FAILURE);
	else if (data->n_philo == 1)
		thread_handler(data, &data->philo[0], NULL, T_CREATE);
	else
	{
		index = -1;
		while (++index < data->n_philo)
			thread_handler(data, &data->philo[index], NULL, T_CREATE);
		thread_handler(data, NULL, &data->monitor, T_MONITOR_CREATE);
		data->t_simulation = get_time(data, MILLISECOND);	
		set_bool(data, &data->table, &data->b_ready, true);
		index = -1;
		while (++index < data->n_philo)
			thread_handler(data, &data->philo[index], NULL, T_JOIN);
		thread_handler(data, NULL, &data->monitor, T_JOIN);
	}
	printf("\n\nSimulation completed.\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 4 || argc > 6 || setup(&data, argv + 1))
		return (1);
	return (simulation(&data), printf("\n\nCHILL IT IS\n\n"), s_exit(&data,
			EXIT_SUCCESS), 0);
}
