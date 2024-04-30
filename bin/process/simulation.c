/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:34:50 by tauer             #+#    #+#             */
/*   Updated: 2024/04/30 02:33:19 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	simulation(t_data *data)
{
	print_philo(data, true, true, PRINT_SIMULATION);
	// print_data(data);
	philo_statut_setter(data, 10, SLEEPING);
	print_philo(data, true, true, PRINT_SIMULATION);
	(void)data;
}
