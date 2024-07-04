/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:08:29 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 17:04:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	get_bool(pthread_mutex_t *mutex, bool *src)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *src;
	pthread_mutex_unlock(mutex);
	return (ret);
}

t_statut	get_statut(t_philo *philo)
{
	t_statut	statut;

	statut = UNSET;
	pthread_mutex_lock(&philo->utils.mutex);
	statut = philo->utils.statut;
	pthread_mutex_unlock(&philo->utils.mutex);
	return (statut);
}

long	get_long(pthread_mutex_t *mutex, long *src)
{
	long	value;

	value = 0;
	pthread_mutex_lock(mutex);
	value = *src;
	pthread_mutex_unlock(mutex);
	return (value);
}
