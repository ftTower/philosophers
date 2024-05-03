/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:29:34 by tauer             #+#    #+#             */
/*   Updated: 2024/05/01 18:28:59 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	philo_bool_setter(t_data *data, long pos, t_set which_code, bool to_set)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->pos == pos && which_code == FULL)
			return (mutex_handler(data, &philo->mutex, LOCK),philo->is_full = to_set, false);
		philo = philo->next;
	}
	return (tprint("failed on setting bool | philo->pos = ", pos, true, RE_WH),
		texit(data, EXIT_FAILURE), true);
}

bool	philo_statut_setter(t_data *data, long pos, t_statut statut)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->pos == pos && statut == EATING)
			return (philo->statut = EATING, false);
		else if (philo->pos == pos && statut == THINKIN)
			return (philo->statut = THINKIN, false);
		else if (philo->pos == pos && statut == SLEEPING)
			return (philo->statut = SLEEPING, false);
		else if (philo->pos == pos && statut == UNASIGNED)
			return (philo->statut = UNASIGNED, false);
		philo = philo->next;
	}
	return (tprint("failed on setting statut | philo->pos = ", pos, true,
			RE_WH), texit(data, EXIT_FAILURE), true);
}

bool	philo_long_setter(t_data *data, long pos, t_set which_code, long to_set)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->pos == pos && which_code == POS)
			return (philo->is_full = to_set, false);
		else if (philo->pos == pos && which_code == LAST_MEAL)
			return (philo->last_meal = to_set, false);
		else if (philo->pos == pos && which_code == LEFT_FORK)
			return (philo->left_fork = to_set, false);
		else if (philo->pos == pos && which_code == RIGHT_FORK)
			return (philo->right_fork = to_set, false);
		philo = philo->next;
	}
	return (tprint("failed on setting long | philo->pos = ", pos, true, RE_WH),
		texit(data, EXIT_FAILURE), true);
}

bool	fork_long_setter(t_data *data, long pos, t_set which_code, long to_set)
{
	t_fork	*fork;

	fork = data->fork;
	while (fork)
	{
		if (fork->pos == pos && which_code == POS)
			return (fork->pos = to_set, false);
		fork = fork->next;
	}
	return (tprint("failed on setting long | fork->pos = ", pos, true, RE_WH),
		texit(data, EXIT_FAILURE), true);
}

// bool	fork_bool_setter(t_data *data, long pos, t_set which_code, bool to_set)
// {
// 	t_fork *fork;

// 	fork = data->fork;
// 	while(fork)
// 	{
// 		if (fork->pos == pos && which_code == POS)
// 			return (false);
// 		fork = fork->next;
// 	}
// 	return (true);
// }
