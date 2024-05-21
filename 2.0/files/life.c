/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:15:07 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 22:57:51 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork.fork);
	print_statut(L_FORK, philo->data, philo, true);
	pthread_mutex_lock(&philo->r_fork->fork);
	print_statut(R_FORK, philo->data, philo, true);
	print_statut(EAT, philo->data, philo, true);
	t_usleep(philo->data->t_eat, philo->data);
	// usleep(philo->data->t_eat);
	// printf("{%ld}\n", philo->data->t_eat);
	// increase_long(philo->data, &philo->philo, &philo->n_meal);
	philo->n_meal++;
	if (philo->data->n_meal > 0 && philo->n_meal == philo->data->n_meal)
		set_bool(philo->data, &philo->philo, &philo->dead, true);
	pthread_mutex_unlock(&philo->l_fork.fork);
	pthread_mutex_unlock(&philo->r_fork->fork);

}

void	thinking(t_philo *philo)
{
	(void)philo;
	print_statut(THINK, philo->data, philo, true);
	// printf("thinking\n");
}

void	*routine(void *in_data)
{
	t_philo	*philo;

	philo = (t_philo *)in_data;
	wait_threads(philo->data);
	increase_long(philo->data, &philo->data->table, &philo->data->n_threads);
	set_long(philo->data, &philo->philo, &philo->t_meal, get_time(philo->data,
			MILLISECOND));
	while (!end(philo->data))
	{
		//! eat
		eat(philo);
		//! sleep
		// printf("sleep\n");
		// usleep(philo->data->t_sleep);
		print_statut(SLEEP, philo->data, philo, true);
		t_usleep(philo->data->t_sleep, philo->data);
		// usleep(philo->data->t_sleep);
		//! thinkin
		thinking(philo);
	}
	return (NULL);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(philo->data, &philo->philo, &philo->dead))
		return (false);
	elapsed = get_time(philo->data, MILLISECOND) - get_long(philo->data,
			&philo->philo, &philo->t_meal);
	t_to_die = philo->data->t_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}
