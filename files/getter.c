/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:08:29 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 01:13:28 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	get_bool(t_sync *sync, pthread_mutex_t *mutex, bool *src)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	ret = *src;
	if (pthread_mutex_unlock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	return (ret);
}

t_statut	get_statut(t_philo *philo)
{
	t_statut	statut;

	statut = UNSET;
	if (pthread_mutex_lock(&philo->utils.mutex))
		set_bool(philo->sync, &philo->sync->mutex, &philo->sync->end, true);
	statut = philo->utils.statut;
	if (pthread_mutex_unlock(&philo->utils.mutex))
		set_bool(philo->sync, &philo->sync->mutex, &philo->sync->end, true);
	return (statut);
}

long	get_long(t_sync *sync, pthread_mutex_t *mutex, long *src)
{
	long	value;

	value = 0;
	if (pthread_mutex_lock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	value = *src;
	if (pthread_mutex_unlock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	return (value);
}
