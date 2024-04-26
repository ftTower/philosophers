/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:22:50 by tauer             #+#    #+#             */
/*   Updated: 2024/04/26 02:23:15 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

bool	ft_atoi(const char *str, long *out_value)
{
	int	sign;
	int	value;
	int	i;

	value = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (false);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if (value > (__INT_MAX__ - str[i] + '0') / 10)
			return (false);
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (true);
	*out_value = value * sign;
	return (true);
}

bool	set_param(t_data *data, char **argv)
{
	if (ft_atoi(argv[1], &data->param.number_philo) && ft_atoi(argv[2],
			&data->param.time_to_die) && ft_atoi(argv[3],
			&data->param.time_to_eat) && ft_atoi(argv[4],
			&data->param.time_to_sleep))
		return (ft_atoi(argv[5], &data->param.number_eat),
			true);
	return (false);
}