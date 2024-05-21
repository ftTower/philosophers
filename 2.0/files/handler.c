/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:13:30 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 02:12:18 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	s_exit(t_data *data, int exit_statut)
{
	long	index;

	index = -1;
	while (++index < data->n_philo)
	{
		if (pthread_mutex_destroy(&data->philo[index].philo) != 0)
			fprintf(stderr, "Failed to destroy philo mutex\n");
		if (pthread_mutex_destroy(&data->philo[index].l_fork.fork) != 0)
			fprintf(stderr, "Failed to destroy left fork mutex\n");
	}
	if (pthread_mutex_destroy(&data->table) != 0)
		fprintf(stderr, "Failed to destroy table mutex\n");
	if (pthread_mutex_destroy(&data->write) != 0)
		fprintf(stderr, "Failed to destroy write mutex\n");
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	exit(exit_statut);
}

void	*s_malloc(t_data *data, size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		s_exit(data, EXIT_FAILURE);
	return (ret);
}

void	thread_handler(t_data *data, t_philo *philo, pthread_t *monitor_thread,
		t_thread code)
{
	long	ret_check;

	ret_check = 1;
	if (philo && !monitor_thread)
	{
		if (code == T_CREATE)
			ret_check = pthread_create(&philo->thread, NULL, routine, &data->philo[philo->id]);
		else if (code == T_JOIN)
			ret_check = pthread_join(philo->thread, NULL);
		else
			ret_check = printf("wrong code for handling threads [philo threads] ");
	}
	else if (monitor_thread && !philo)
	{
		if (code == T_MONITOR_CREATE)
			ret_check = pthread_create(&data->monitor, NULL, monitor_routine,
					data);
		else if (code == T_JOIN)
			ret_check = pthread_join(data->monitor, NULL);
		else
			ret_check = printf("wrong code for handling threads [monitor] ");
	}
	if (ret_check != 0)
	{
		printf("[return (code : %ld]\n", ret_check);
		s_exit(data, EXIT_FAILURE);
	}
}

void	mutex_handler(t_data *data, mtx *mutex, t_thread code)
{
	int	ret_check;

	ret_check = -1;
	if (code == M_INIT)
	{
		// *mutex = (mtx)PTHREAD_MUTEX_INITIALIZER;
		ret_check = pthread_mutex_init(mutex, NULL);
	}
	else if (code == M_LOCK)
	{
		ret_check = pthread_mutex_lock(mutex);
		// printf("MLOCK\n");
	}
	else if (code == M_UNLOCK)
	{
		ret_check = pthread_mutex_unlock(mutex);
		// printf("MUNLOCK\n");
	}
	else if (code == M_DESTROY)
	{
		printf("Attempting to destroy mutex at address: %p\n", (void *)mutex);
		ret_check = pthread_mutex_destroy(mutex);
	}
	else
		ret_check = printf("wrong code for handling mutex\n");
	if (ret_check != 0)
	{
		printf("[%d] Mutex operation failed at %p\n", ret_check, (void *)mutex);
		s_exit(data, EXIT_FAILURE); // Ensure to handle cleanup gracefully
	}
}