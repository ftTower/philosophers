/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:12:34 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 15:56:30 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	null_data(t_data *data)
{
	data->param.number_eat = -1;
	data->param.number_philo = 0;
	data->param.time_to_die = 0;
	data->param.time_to_eat = 0;
	data->param.time_to_sleep = 0;
	data->stat.memory_allocated = 0;
}
