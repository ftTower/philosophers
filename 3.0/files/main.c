/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/05/22 02:32:20 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_lock(pthread_mutex_t mutex, t_philo *phi, char *msg)
{
	pthread_mutex_lock(&mutex);
	printf("[%ld] %s (%ld | %ld)\n", phi->id, msg, phi->first_fork.id,
		phi->second_fork->id);
	pthread_mutex_unlock(&mutex);
}

void	*philo_life(void *in_philo)
{
	t_philo	*philo;

	philo = (t_philo *)in_philo;
	
	increase_long(philo->sync->mutex, &philo->sync->n_threads);
	set_bool(philo->sync->mutex, &philo->sync->ready[philo->id], true);
	
	while(!get_bool(philo->sync->mutex, philo->sync->all_ready))
		;
	
	philo->statut.t_spawn = get_time(MILLISECOND);
	while (!get_bool(philo->sync->mutex, philo->sync->end))
	{
		pthread_mutex_lock(&philo->first_fork.mutex);
		print_lock(philo->statut.mutex, philo, "take 1 fork");
		pthread_mutex_lock(&philo->second_fork->mutex);
		print_lock(philo->statut.mutex, philo, "take 2 fork");
		print_lock(philo->statut.mutex, philo, "eat");
		usleep(philo->lifetime.t_eat);
		pthread_mutex_unlock(&philo->second_fork->mutex);
		pthread_mutex_unlock(&philo->first_fork.mutex);
		print_lock(philo->statut.mutex, philo, "free");
		// if (get_time(MILLISECOND) - philo->sync->t_simulation == 5000)	
		// 	set_bool(philo->sync->mutex, &philo->sync->end, true);
	}
	return (NULL);
}

bool	simulation(t_data *data)
{
	long	index;

	index = -1;
	while (++index < data->lifetime.n_philo)
	{
		if (pthread_create(&data->philos[index].thread, NULL, philo_life,
				&data->philos[index]) != 0)
			return (true);
		loading(data->sync.ready, data->lifetime.n_philo);
	}
	set_bool(data->sync.mutex, &data->sync.all_ready, true);
	data->sync.t_simulation = get_time(MILLISECOND);
	index = -1;
	while (++index < data->lifetime.n_philo)
		if (pthread_join(data->philos[index].thread, NULL) != 0)
			return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (data_init(&data, argc, argv + 1))
		return (EXIT_FAILURE);
	if (simulation(&data))
		return (EXIT_FAILURE);
	return (p_lifetime(data.lifetime), p_philos(data.philos), data_free(&data),
		EXIT_SUCCESS);
}
