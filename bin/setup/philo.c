/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:06 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 17:09:20 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	init_philo(t_data *data)
{
	data->philo = malloc(sizeof(t_philo));
	if (!data->philo)
		return (false);
	return (data->philo->is_full = false, data->philo->last_meal = 0,
		data->philo->left_fork = -1, data->philo->right_fork = -1,
		data->philo->next = NULL, data->philo->pos = 0, true);
}

bool	add_philo(t_data *data, long index)
{
	t_philo	*list;
	t_philo	*new_philo;

	list = NULL;
	if (index != 1)
		list = data->philo;
	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (true);
	data->stat.memory_allocated += (sizeof(t_philo));
	if (!list)
	{
		free(data->philo);
		data->philo = NULL;
	}
	return (new_philo->is_full = false, new_philo->right_fork = index - 1,
		new_philo->left_fork = index % data->param.number_philo,
		new_philo->last_meal = -1, new_philo->next = list,
		new_philo->pos = index,data->philo = new_philo, false);
}

bool	philo_maker(t_data *data)
{
	long	index;

	index = 1;
	init_philo(data);
	while (index <= data->param.number_philo)
		if (add_philo(data, index++))
			return (print_sclr("", CLEAR, false),
				print_sclr("failed to make a philo", RED_, true), false);
	return (true);
}

void	thread_maker(t_data *data)
{
	long index;

	index = 1;
	while(index <= data->param.number_philo)
		thread_handler(data, index++, routine, CREATE);
}
