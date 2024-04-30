/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:03:59 by tauer             #+#    #+#             */
/*   Updated: 2024/05/01 00:36:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

// pthread_create();
// pthread_join();

void	error_handler(t_data *data, int error_code, t_philo *philo)
{
	if (!error_code)
		return ;
	else if (error_code == EAGAIN)
		return (tprint("Insufficient resources to create another thread. philo->pos = ",
				philo->pos, true, RE_WH));
	
	texit(data, EXIT_FAILURE);
}

void	thread_manager(t_data *data, t_philo *philo, void *(*foo)(void *),
		t_cmd code)
{
	int	error_code;

	error_code = 0;
	if (code == CREATE)
		error_code = pthread_create(&philo->id, NULL, foo, NULL);
	else if (code == DESTROY)
		pthread_exit(&philo->id);
	else if (code == JOIN)
		pthread_join(philo->id, NULL);
	error_handler(data, error_code, philo);
}

void	thread_handler(t_data *data, long pos, void *(*foo)(void *), t_cmd code)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->pos == pos)
			break ;
		philo = philo->next;
	}
	if (philo)
		thread_manager(data, philo, foo, code);
}
