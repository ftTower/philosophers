/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:41:09 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 00:30:47 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	is_ready_to_eat(t_data *data, long index, long next_pos, long prev_pos)
{
	if ((get_long(&data->philos[next_pos].info.mutex,
				&data->philos[next_pos].info.n_meal) \
				< get_long(&data->philos[index].info.mutex,
				&data->philos[index].info.n_meal)
			|| (get_long(&data->philos[next_pos].info.mutex,
					&data->philos[next_pos].info.t_lastmeal) \
					< get_long(&data->philos[index].info.mutex,
					&data->philos[index].info.t_lastmeal)))
		|| get_long(&data->philos[prev_pos].info.mutex,
			&data->philos[prev_pos].info.n_meal) \
			< get_long(&data->philos[index].info.mutex,
			&data->philos[index].info.n_meal)
		|| get_long(&data->philos[prev_pos].info.mutex,
			&data->philos[prev_pos].info.t_lastmeal) \
			< get_long(&data->philos[index].info.mutex,
			&data->philos[index].info.t_lastmeal))
		return ;
	else if (get_statut(&data->philos[index]) != EAT
		&& !get_bool(&data->philos[next_pos].info.mutex,
			&data->philos[next_pos].info.rdy_to_eat)
		&& !get_bool(&data->philos[prev_pos].info.mutex,
			&data->philos[prev_pos].info.rdy_to_eat))
		set_bool(&data->philos[index].info.mutex,
			&data->philos[index].info.rdy_to_eat, true);
	return (true);
}

void	monitor_process(t_data *data, bool display)
{
	long	index;
	long	min_meals;
	long	comp;

	set_bool(&data->sync.mutex, &data->sync.monitor_ready, true);
	set_long(&data->sync.mutex, &data->sync.t_start, get_time(MILLISECOND));
	while (!get_bool(&data->sync.mutex, &data->sync.end))
	{
		if (display && (get_time(MILLISECOND) - data->sync.t_start) % 5 == 0)
			monitor_print(&data->monitor, false);
		min_meals = __LONG_MAX__;
		index = -1;
		comp = -1;
		while (++index < data->monitor.param.n_philo && !is_dead(data, index) \
		&& !is_end(data, index) && min_meal(data, index, &min_meals, comp) && \
		is_ready_to_eat(data, index, data->philos[index].utils.next_pos, \
		data->philos[index].utils.prev_pos))
			data->monitor.all_status[index] = get_statut(&data->philos[index]);
		if (data->monitor.param.max_meal > -1
			&& min_meals >= data->monitor.param.max_meal)
			set_bool(&data->sync.mutex, &data->sync.end, true);
		usleep(10);
	}
	if (display)
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
	monitor_process(data, DEBUG_MODE);
	return (NULL);
}
