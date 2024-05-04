/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:22:50 by tauer             #+#    #+#             */
/*   Updated: 2024/05/03 02:23:08 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>



bool	set_param(t_data *data, char **argv)
{
	if (ft_atoi(argv[1], &data->param.number_philo) && ft_atoi(argv[2],
			&data->param.time_to_die) && ft_atoi(argv[3],
			&data->param.time_to_eat) && ft_atoi(argv[4],
			&data->param.time_to_sleep))
		return (data->param.time_to_die *= 1e3, data->param.time_to_eat *= 1e3,
			data->param.time_to_sleep *= 1e3, ft_atoi(argv[5],
				&data->param.number_eat), (data->param.time_to_die > 6e3
				&& data->param.time_to_eat > 6e3
				&& data->param.time_to_sleep > 6e3));
	return (false);
}
