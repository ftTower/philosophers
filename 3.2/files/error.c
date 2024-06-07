/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:39:27 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 18:40:16 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

t_error	error_mutex(t_table *table, int mutex_error_code, long comp_index,
		long statut)
{
	t_error	error_code;
	long	index;

	if (mutex_error_code == EAGAIN)
		error_code = MUTEX_EAGAIN;
	else if (mutex_error_code == EBUSY)
		error_code = MUTEX_EBUSY;
	else if (mutex_error_code == EINVAL)
		error_code = MUTEX_EINVAL;
	else if (mutex_error_code == EFAULT)
		error_code = MUTEX_EFAULT;
	if (statut == 1 || statut == 2 || statut == 3)
		pthread_mutex_destroy(&table->mutex_sync);
	else if (statut == 2 || statut == 3)
	{
		pthread_mutex_destroy(&table->mutex_write);
		index = -1;
		while (++index < comp_index)
		{
			pthread_mutex_destroy(&table->philos[index].mutex);
			if ((statut != 2 && index < comp_index - 1) || statut == 3)
				pthread_mutex_destroy(&table->forks[index]);
		}
	}
	return (error_code);
}

void	error_catcher(t_error error_code)
{
	if (error_code == SUCCES)
		return ;
	else if (error_code == NB_ARGC || error_code == ERR_ARGV)
		printf("[nb_philosophers] [time_eat] [time_die] [time_sleep] {max_meals}\n");
	else if (error_code == MALLOC_PHILO)
		printf("[MALLOC_PHILO] : malloc returned null\n");
	else if (error_code == MUTEX_EINVAL)
		printf("[EINVAL] : Invalid argument\n");
	else if (error_code == MUTEX_EBUSY)
		printf("[EBUSY] : Device or resource busy\n");
	else if (error_code == MUTEX_EAGAIN)
		printf("[EAGAIN] : Resource temporarily unavailable\n");
	else if (error_code == MUTEX_EFAULT)
		printf("[EFAULT] : Bad adress\n");
	exit(EXIT_FAILURE);
}
