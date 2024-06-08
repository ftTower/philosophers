/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/06/08 01:48:29 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_debug(t_philo *phi, char *msg)
{
	printf("%ld : [%ld] %s (%ld | %ld)\n", get_time(MILLISECOND)
		- phi->sync->t_simulation, phi->id, msg, phi->first_fork.id,
		phi->second_fork->id);
}

void	print_lock(pthread_mutex_t mutex, t_philo *phi, t_statut_code code)
{
	pthread_mutex_lock(&mutex);
	if (code == L_FORK || code == R_FORK)
		printf("%-6ld  %ld has taken a fork\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	else if (code == EAT)
		printf("%-6ld  %ld is eating\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	else if (code == SLEEP)
		printf("%-6ld  %ld is sleeping\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	else if (code == THINK)
		printf("%-6ld  %ld is thinking\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	else if (code == DEAD)
		printf("%-6ld  %ld is dead\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	else if (code == UNASSIGNED)
		printf("%-6ld  %ld his unassigned\n", get_time(MILLISECOND)
			- phi->sync->t_simulation, phi->id + 1);
	pthread_mutex_unlock(&mutex);
}

void	eat(t_philo *philo)
{
    pthread_mutex_t *first_fork_mutex;
    pthread_mutex_t *second_fork_mutex;

    if (philo->id % 2 == 0) {
        first_fork_mutex = &philo->first_fork.mutex;
        second_fork_mutex = &philo->second_fork->mutex;
    } else {
        first_fork_mutex = &philo->second_fork->mutex;
        second_fork_mutex = &philo->first_fork.mutex;
    }
    // Verrouiller les fourchettes dans le bon ordre
    pthread_mutex_lock(first_fork_mutex);
    print_lock(philo->sync->write_mutex, philo, L_FORK);
    pthread_mutex_lock(second_fork_mutex);
    print_lock(philo->sync->write_mutex, philo, R_FORK);
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo->first_fork.mutex);
	// 	print_lock(philo->sync->write_mutex, philo, L_FORK);
	// 	pthread_mutex_lock(&philo->second_fork->mutex);
	// 	print_lock(philo->sync->write_mutex, philo, R_FORK);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo->second_fork->mutex);
	// 	print_lock(philo->sync->write_mutex, philo, R_FORK);		
	// 	pthread_mutex_lock(&philo->first_fork.mutex);
	// 	print_lock(philo->sync->write_mutex, philo, L_FORK);
	// }
	print_lock(philo->sync->write_mutex, philo, EAT);
	usleep(philo->lifetime.t_eat);
	pthread_mutex_unlock(&philo->first_fork.mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
}

void	life(t_philo *philo)
{
	print_lock(philo->sync->write_mutex, philo, THINK);
	eat(philo);
	print_lock(philo->sync->write_mutex, philo, SLEEP);
	usleep(philo->lifetime.t_sleep);
}

void	*philo_life(void *in_philo)
{
	t_philo	*philo;

	philo = (t_philo *)in_philo;
	increase_long(philo->sync->mutex, &philo->sync->n_threads);
	set_bool(philo->sync->mutex, &philo->sync->ready[philo->id], true);
	while (!get_bool(philo->sync->mutex, &philo->sync->all_ready))
		;
	philo->statut.t_spawn = get_time(MILLISECOND);
	if (philo->id % 2 == 0)
		usleep(philo->lifetime.t_eat);
	while (!get_bool(philo->sync->mutex, &philo->sync->end))
		life(philo);
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
		// loading(data->sync.ready, data->lifetime.n_philo);
	}
	data->sync.t_simulation = get_time(MILLISECOND);
	set_bool(data->sync.mutex, &data->sync.all_ready, true);
	index = -1;
	while (++index < data->lifetime.n_philo)
		if (pthread_join(data->philos[index].thread, NULL) != 0)
			return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_data	data;
	long index = -1;

	if (data_init(&data, argc, argv + 1))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data.sync.write_mutex, NULL) != 0)
		return (data_free(&data), terror("data_memory",
				"error initing sync write mutex"), true);
	if (pthread_mutex_init(&data.sync.mutex, NULL) != 0)
		return (data_free(&data), terror("data_memory",
				"error initing sync mutex"), true);
	while (++index < data.lifetime.n_philo)
	{
		data.forks[index].id = index;
		data.philos[index].id = index;
		if (pthread_mutex_init(&data.philos[index].mutex, NULL) == -1)
			return (terror("data_memory", "error initing a philo mutex"),
				data_free(&data), true);
		else if (pthread_mutex_init(&data.philos[index].statut.mutex, NULL) ==
			-1)
			return (terror("data_memory", "error initing a philo.statut mutex"),
				data_free(&data), true);
		else if (pthread_mutex_init(&data.forks[index].mutex, NULL) == -1)
			return (terror("data_memory", "error initing a fork mutex"),
				data_free(&data), true);
	}
	if (simulation(&data))
		return (EXIT_FAILURE);
	return (p_lifetime(data.lifetime), p_philos(data.philos), data_free(&data),
		EXIT_SUCCESS);
}
