/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:19:48 by tauer             #+#    #+#             */
/*   Updated: 2024/05/26 01:31:14 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

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

bool	get_bool(pthread_mutex_t mutex, bool src)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&mutex);
	ret = src;
	pthread_mutex_unlock(&mutex);
	return (ret);
}

void	set_bool(pthread_mutex_t mutex, bool *dst, bool src)
{
	pthread_mutex_lock(&mutex);
	*dst = src;
	pthread_mutex_unlock(&mutex);
}
