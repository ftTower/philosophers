/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:53 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 01:05:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	init_fork(t_data *data)
{
	data->fork = malloc(sizeof(t_fork));
	if (!data->fork)
		return (false);
	return (data->fork->pos = 0, true);
}

bool	add_fork(t_data *data, long index)
{
	t_fork	*list;
	t_fork	*new_fork;

	list = NULL;
	if (index != 0)
		list = data->fork;
	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		return (true);
	else if (!list)
	{
		free(data->fork);
		data->fork = NULL;
	}
	return (new_fork->next = list, new_fork->pos = index, data->fork = new_fork,
		false);
}

bool	fork_maker(t_data *data)
{
	long	index;

	index = 0;
	init_fork(data);
	while (index < data->param.number_philo)
		if (add_fork(data, index++))
			return (print_sclr("", CLEAR, false),
				print_sclr("failed to make a fork", RED_, true), false);
	return (true);
}
