/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:41:09 by tauer             #+#    #+#             */
/*   Updated: 2024/05/27 02:51:03 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	all_statut_printer(t_monitor *monitor)
{
	long	index;

	index = -1;
	// printf("\033c");
	t_putnbr(MAGENTA, get_time(MILLISECOND)- monitor->sync->t_start,false);
	t_putstr(MAGENTA, " |", false);
	while (++index < monitor->param.n_philo)
	{
		if (monitor->all_status[index] == EAT)
			t_putstr(BG_GREEN, " ", false);
		else if (monitor->all_status[index] == THINK)
			t_putstr(BG_WHITE, " ", false);
		else if (monitor->all_status[index] == SLEEP)
			t_putstr(BG_RED, " ", false);
		else if (monitor->all_status[index] == UNSET)
			t_putstr(RED, "XX", false);
	}
	t_putstr(MAGENTA, "|", true);
}

void	*monitor_life(void *in_monitor)
{
	t_monitor	*monitor;
	long		index;

	monitor = (t_monitor *)in_monitor;
	while (!get_bool(monitor->sync->mutex, monitor->sync->all_ready))
		;
	while (!get_bool(monitor->sync->mutex, monitor->sync->end))
	{
		index = -1;
		while (++index < monitor->param.n_philo)
		{
			if (!get_bool(monitor->philos[index].utils.mutex,
					monitor->philos[index].info.rdy_to_eat)
				&& get_statut(&monitor->philos[monitor->philos[index].utils.next_pos]) != EAT
				&& !get_bool(monitor->philos[monitor->philos[index].utils.next_pos].utils.mutex,
					monitor->philos[monitor->philos[index].utils.next_pos].info.rdy_to_eat)
				&& get_statut(&monitor->philos[monitor->philos[index].utils.prev_pos]) != EAT
				&& !get_bool(monitor->philos[monitor->philos[index].utils.prev_pos].utils.mutex,
					monitor->philos[monitor->philos[index].utils.prev_pos].info.rdy_to_eat))
			{
				set_bool(monitor->philos[index].utils.mutex,
					&monitor->philos[index].info.rdy_to_eat, true);
			}
			monitor->all_status[index] = get_statut(&monitor->philos[index]);
			if (get_time(MILLISECOND) - monitor->sync->t_start > 3000)
				set_bool(monitor->sync->mutex, &monitor->sync->end, true);
		}
		if ((get_time(MILLISECOND) - monitor->sync->t_start) % 30 == 0)
			all_statut_printer(monitor);
		usleep(100);
	}
	printf("monitor finished with %ld for median\n", monitor->median_meal);
	return (NULL);
}
