/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:50 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 01:13:22 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	is_end(t_data *data, long index)
{
	if (get_bool(&data->sync, &data->philos[index].info.mutex,
			&data->philos[index].info.dead) == true)
		return (set_bool(&data->sync, &data->sync.mutex, &data->sync.end, true),
			true);
	return (false);
}

bool	min_meal(t_data *data, long index, long *min_meal, long comp)
{
	comp = get_long(&data->sync, &data->philos[index].info.mutex,
			&data->philos[index].info.n_meal);
	if (comp < *min_meal)
		*min_meal = comp;
	return (true);
}

bool	is_dead(t_data *data, long index)
{
	long		comp;
	long		time;
	t_statut	statut;

	time = get_time(MILLISECOND);
	comp = get_long(&data->sync, &data->philos[index].info.mutex,
			&data->philos[index].info.t_lastmeal);
	statut = get_statut(&data->philos[index]);
	if (comp == 0)
		return (false);
	if ((time - comp) > data->monitor.biggest_starvation)
		data->monitor.biggest_starvation = (time - comp);
	if ((time - comp) > data->monitor.param.t_die / 1e3 && (statut != EAT))
		return (print_statut_lock(DEAD, &data->philos[index], true, false),
			set_statut(&data->philos[index], DEAD), set_bool(&data->sync,
				&data->sync.mutex, &data->sync.end, true), set_bool(&data->sync,
				&data->philos[index].info.mutex, &data->philos[index].info.dead,
				true), true);
	return (false);
}
