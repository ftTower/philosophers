/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/05/21 02:57:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	*philo_life(void *in_philo)
{
	t_philo *philo;

	philo = (t_philo *)in_philo;
	philo->sync->n_threads++;
	philo->sync->ready[philo->id] = true;
	return (NULL);
}

bool	simulation(t_data *data)
{
	long index;

	index = -1;
	while(++index < data->lifetime.n_philo)
	{
		if (pthread_create(&data->philos[index].thread, NULL, philo_life, &data->philos[index]) != 0)
			return (true);
		loading(data->sync.ready, data->lifetime.n_philo);
	}
	

			
	index = -1;
	while(++index < data->lifetime.n_philo)
		if (pthread_join(data->philos[index].thread, NULL) != 0)
			return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (data_init(&data, argc, argv + 1))
		return (EXIT_FAILURE);
	if (simulation(&data))
		return (EXIT_FAILURE);
	return (p_lifetime(data.lifetime),p_philos(data.philos),data_free(&data),EXIT_SUCCESS);
}
