/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:23:54 by tauer             #+#    #+#             */
/*   Updated: 2024/04/26 02:24:22 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (0);
	while (str[size])
		size++;
	return (size);
}

void	print_data(t_data *data)
{
	printf("\n\nnum_philo :[%ld] num_eat :[%ld] time_die :[%ld] time_eat :[%ld] time_sleep :[%ld]\n\n\n",
		data->param.number_philo, data->param.number_eat,
		data->param.time_to_die, data->param.time_to_eat,
		data->param.time_to_sleep);
}
