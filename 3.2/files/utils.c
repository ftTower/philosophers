/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:38:02 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 18:43:33 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	ft_atoi(const char *str, long *out_value, bool is_time)
{
	int	sign;
	int	value;
	int	i;

	value = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (*out_value = -1, false);
	while (str[i] && (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i])
	{
		if (value > (__INT_MAX__ - str[i] + '0') / 10 || str[i] > '9'
			|| str[i] < '0')
			return (*out_value = -1, false);
		value = (value * 10) + (str[i++] - '0');
	}
	if (is_time)
		return (*out_value = (value * sign) * 1e3, true);
	return (*out_value = (value * sign), true);
}

void	final_table(t_table *table)
{
	long index;

	index = -1;
	while (++index < table->arg.nb_philos)
	{
		printf("+================%ld==================\n",
			table->philos[index].id);
		printf("|  LEFT FORK %-6ld RIGHT FORK %-6ld \n",
			table->philos[index].left_fork, table->philos[index].right_fork);
		if (table->everyone_ready)
			printf("| has started\n");
		else
			printf("| waiting\n");
	}
}