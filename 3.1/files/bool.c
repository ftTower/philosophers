/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:50 by tauer             #+#    #+#             */
/*   Updated: 2024/06/11 02:54:03 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool is_end(t_data *data, long index)
{
	if (get_bool(&data->philos[index].info.mutex,
				 &data->philos[index].info.dead) == true)
		return (set_bool(&data->sync.mutex, &data->sync.end, true), true);
	return (false);
}

bool min_meal(t_data *data, long index, long *min_meal, long comp)
{
	comp = get_long(&data->philos[index].info.mutex,
					&data->philos[index].info.n_meal);
	if (comp < *min_meal)
		*min_meal = comp;
	return (true);
}

bool is_dead(t_data *data, long index)
{
	long comp;
	long time;

	time = get_time(MILLISECOND);
	comp = get_long(&data->philos[index].info.mutex,
					&data->philos[index].info.t_lastmeal);
	if (comp == 0)
		return (false);
	if ((time - comp) > data->monitor.biggest_starvation)
		data->monitor.biggest_starvation = (time - comp);
	if ((time - comp) * 1000 >= data->monitor.param.t_die)
		return (set_bool(&data->sync.mutex,
						 &data->sync.end, true),
				set_bool(&data->philos[index].info.mutex,
						 &data->philos[index].info.dead, true),
				print_statut_lock(DEAD,
								  &data->philos[index], true, false),
				true);
	return (false);
}
