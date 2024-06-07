/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:19:48 by tauer             #+#    #+#             */
/*   Updated: 2024/06/08 00:21:40 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	increase_long(pthread_mutex_t *mutex, long *src)
{
	pthread_mutex_lock(mutex);
	(*src)++;
	pthread_mutex_unlock(mutex);
}

long	get_long(pthread_mutex_t *mutex, long *src)
{
	long value;

	value = 0;
	pthread_mutex_lock(mutex);
	value = *src;
	pthread_mutex_unlock(mutex);
	return (value);
}
void	set_long(pthread_mutex_t *mutex, long *dst, long src)
{
	pthread_mutex_lock(mutex);
	*dst = src;
	pthread_mutex_unlock(mutex);
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

void	set_statut(t_philo *philo, t_statut src)
{
	pthread_mutex_lock(&philo->utils.mutex);
	philo->utils.statut = src;
	pthread_mutex_unlock(&philo->utils.mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *src)
{
	bool	ret;

	ret = false;
	if (pthread_mutex_lock(mutex) != 0)
		return (ret);
	ret = *src;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_bool(pthread_mutex_t *mutex, bool *dst, bool src)
{
	pthread_mutex_lock(mutex);
	*dst = src;
	pthread_mutex_unlock(mutex);
}
