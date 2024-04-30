/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:34:50 by tauer             #+#    #+#             */
/*   Updated: 2024/05/01 00:53:56 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

// void	task_assigner(t_data *data, t_philo *philo)
// {
	
// }

bool	check_end_simulation(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo)
	{
		if (philo->is_full || philo->last_meal >= data->param.time_to_die)
			return (false);
		philo = philo->next;
	}
	return (true);
}



void	simulation(t_data *data)
{
	// print_data(data);
	while(check_end_simulation(data))
	{
		
		print_philo(data, true, true, PRINT_SIMULATION);
	}
}
