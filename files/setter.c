/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:19:48 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 16:46:12 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	increase_long(pthread_mutex_t *mutex, long *src)
{
	pthread_mutex_lock(mutex);
	(*src)++;
	pthread_mutex_unlock(mutex);
}

void	set_long(pthread_mutex_t *mutex, long *dst, long src)
{
	pthread_mutex_lock(mutex);
	*dst = src;
	pthread_mutex_unlock(mutex);
}

void	set_statut(t_philo *philo, t_statut src)
{
	pthread_mutex_lock(&philo->utils.mutex);
	philo->utils.statut = src;
	pthread_mutex_unlock(&philo->utils.mutex);
}

void	set_bool(pthread_mutex_t *mutex, bool *dst, bool src)
{
	pthread_mutex_lock(mutex);
	*dst = src;
	pthread_mutex_unlock(mutex);
}
