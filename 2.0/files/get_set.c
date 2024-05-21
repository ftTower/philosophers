/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:16:45 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 00:18:17 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	set_bool(t_data *data, mtx *mutex, bool *dest, bool value)
{
	mutex_handler(data, mutex, M_LOCK);
	*dest = value;
	mutex_handler(data, mutex, M_UNLOCK);
}

bool	get_bool(t_data *data, mtx *mutex, bool *value)
{
	bool	ret;

	mutex_handler(data, mutex, M_LOCK);
	ret = *value;
	mutex_handler(data, mutex, M_UNLOCK);
	return (ret);
}

void	set_long(t_data *data, mtx *mutex, long *dest, long value)
{
	mutex_handler(data, mutex, M_LOCK);
	*dest = value;
	mutex_handler(data, mutex, M_UNLOCK);
}

bool	get_long(t_data *data, mtx *mutex, long *value)
{
	bool	ret;

	mutex_handler(data, mutex, M_LOCK);
	ret = *value;
	mutex_handler(data, mutex, M_UNLOCK);
	return (ret);
}

void	increase_long(t_data *data, mtx *mutex, long *value)
{
	mutex_handler(data, mutex, M_LOCK);
	(*value)++;
	mutex_handler(data, mutex, M_UNLOCK);
}


