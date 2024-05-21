/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:14:18 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 22:47:12 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	wait_threads(t_data *data)
{
	while (!get_bool(data, &data->table, &data->b_ready))
		;
}

bool	all_threads_running(t_data *data)
{
	bool	ret;

	ret = false;
	mutex_handler(data, &data->table, M_LOCK);
	// printf("%ld -> %ld\n", data->n_threads, data->n_philo);
	if (data->n_threads == data->n_philo)
		ret = true;
	mutex_handler(data, &data->table, M_UNLOCK);
	return (ret);
}

bool	end(t_data *data)
{
	return (get_bool(data, &data->table, &data->b_end));
}