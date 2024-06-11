/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:41:09 by tauer             #+#    #+#             */
/*   Updated: 2024/06/11 02:17:19 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	is_ready_to_eat(t_data *data, long index)
{
	if ((get_long(&data->philos[data->philos[index].utils.next_pos].info.mutex,
				&data->philos[data->philos[index].utils.next_pos].info.n_meal)
			< get_long(&data->philos[index].info.mutex,
				&data->philos[index].info.n_meal)
			|| get_long(&data->philos[data->philos[index].utils.prev_pos].info.mutex,
				&data->philos[data->philos[index].utils.prev_pos].info.n_meal) < get_long(&data->philos[index].info.mutex,
				&data->philos[index].info.n_meal)))
		write(1, "", 0);
	else if (!get_bool(&data->philos[index].info.mutex,
			&data->philos[index].info.rdy_to_eat)
		&& get_statut(&data->philos[data->philos[index].utils.next_pos]) != EAT
		&& !get_bool(&data->philos[data->philos[index].utils.next_pos].info.mutex,
			&data->philos[data->philos[index].utils.next_pos].info.rdy_to_eat)
		&& get_statut(&data->philos[data->philos[index].utils.prev_pos]) != EAT
		&& !get_bool(&data->philos[data->philos[index].utils.prev_pos].info.mutex,
			&data->philos[data->philos[index].utils.prev_pos].info.rdy_to_eat))
	{
		set_bool(&data->philos[index].info.mutex,
			&data->philos[index].info.rdy_to_eat, true);
	}
}

void	monitor_process(t_data *data, bool display)
{
	long	index;
	long	min_meals;
	long	comp;

	set_long(&data->sync.mutex, &data->sync.t_start, get_time(MILLISECOND));
	while (!get_bool(&data->sync.mutex, &data->sync.end))
	{
		if (display && (get_time(MILLISECOND) - data->sync.t_start) % 10 == 0)
			monitor_print(&data->monitor, false);
		min_meals = __LONG_MAX__;
		index = -1;
		comp = -1;
		while (++index < data->monitor.param.n_philo && !is_dead(data, index) &&!is_end(data, index) && min_meal(data, index, &min_meals, comp))
		{
			is_ready_to_eat(data, index);
			data->monitor.all_status[index] = get_statut(&data->philos[index]);
		}
		if (data->monitor.param.max_meal > -1 && min_meals >= data->monitor.param.max_meal)
			set_bool(&data->sync.mutex, &data->sync.end, true);
		usleep(1);
	}
	monitor_print(&data->monitor, true);
}

void	*monitor_life(void *in_data)
{
	t_data	*data;
	long	index;

	data = (t_data *)in_data;
	index = -1;
	while (!get_bool(&data->sync.mutex, &data->sync.all_ready))
		write(1, "", 0);
	while (++index < data->monitor.param.n_philo)
		is_ready_to_eat(data, index);
	set_bool(&data->sync.mutex, &data->sync.monitor_ready, true);
	monitor_process(data, false);
	return (NULL);
}
