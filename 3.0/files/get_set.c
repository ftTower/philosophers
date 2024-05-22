/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:19:48 by tauer             #+#    #+#             */
/*   Updated: 2024/05/22 01:40:16 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	set_bool(pthread_mutex_t mutex, bool *value, bool to_set)
{
	pthread_mutex_lock(&mutex);
	*value = to_set;
	pthread_mutex_unlock(&mutex); 
}

bool	get_bool(pthread_mutex_t mutex, bool to_get)
{
	bool ret;
	
	pthread_mutex_lock(&mutex);
	ret = to_get;
	pthread_mutex_unlock(&mutex);
	return (ret); 
}

void	increase_long(pthread_mutex_t mutex, long *to_set)
{
	pthread_mutex_lock(&mutex);
	(*to_set)++;
	pthread_mutex_unlock(&mutex); 
}
