/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:19:48 by tauer             #+#    #+#             */
/*   Updated: 2024/06/13 01:02:18 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	increase_long(t_sync *sync, pthread_mutex_t *mutex, long *src)
{
	if (pthread_mutex_lock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	(*src)++;
	if (pthread_mutex_unlock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
}

void	set_long(t_sync *sync, pthread_mutex_t *mutex, long *dst, long src)
{
	if (pthread_mutex_lock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	*dst = src;
	if (pthread_mutex_unlock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
}

void	set_statut(t_philo *philo, t_statut src)
{
	if (pthread_mutex_lock(&philo->utils.mutex) != 0)
		set_bool(philo->sync, &philo->sync->mutex, &philo->sync->end, true);
	philo->utils.statut = src;
	if (pthread_mutex_unlock(&philo->utils.mutex) != 0)
		set_bool(philo->sync, &philo->sync->mutex, &philo->sync->end, true);
}

void	set_bool(t_sync *sync, pthread_mutex_t *mutex, bool *dst, bool src)
{
	if (pthread_mutex_lock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
	*dst = src;
	if (pthread_mutex_unlock(mutex) != 0)
		set_bool(sync, &sync->mutex, &sync->end, true);
}
