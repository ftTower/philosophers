/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:47:19 by tauer             #+#    #+#             */
/*   Updated: 2024/05/21 03:00:51 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	loading(bool *ready, long size)
{
	long index;

	index = -1;
	printf("\033c");
	if (!ready)
		return ;
	while(++index < size)
	{
		if (index % 10 == 0)
			printf("\n");
		if (ready[index])
			printf("\033[48;5;46m   \033[0m");
		else
			printf("\033[48;5;255m   \033[0m");
	}
	printf("\n");
}

void	terror(const char *which_function, const char *error_msg)
{
	printf("[in %s] : %s...\n", which_function, error_msg);
}

void	p_lifetime(t_lifetime lifetime)
{
	if (!DEBUG_MODE)
		return ;
	printf("\033c\nn_phi : %ld\n", lifetime.n_philo);
	printf("t_die : %ld\n", lifetime.t_die);
	printf("t_eat : %ld\n", lifetime.t_eat);
	printf("t_sle : %ld\n", lifetime.t_sleep);
	if (lifetime.max_meal != -1)
		printf("m_mea : %ld\n", lifetime.max_meal);
}

void	p_philos(t_philo *philo)
{
	long index;
	t_philo phi;

	if (!DEBUG_MODE)
		return ;
	index = -1;
	while (++index < philo->lifetime.n_philo)
	{
		phi = philo[index];
		printf("=======[%ld]=====================================\n", phi.id);
		printf("lifetime : [%ld|%ld] : [%ldms|%ldms|%ldms]\n",
			phi.lifetime.n_philo, phi.lifetime.max_meal, phi.lifetime.t_die,
			phi.lifetime.t_eat, phi.lifetime.t_sleep);
		printf("syncro   : [%ld]\n", phi.sync->n_threads);
		printf("forks    : [first fork %ld] - [second fork %ld]\n",
			phi.first_fork.id, phi.second_fork.id);
		if (phi.statut.statut == UNASSIGNED)
			printf("UNASSIGNED\n");
		else
			printf("ASSIGNED\n");
	}
}