/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:41:09 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 00:11:37 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void meal_statut_printer(t_monitor *monitor)
{
    for (long i = 0; i < monitor->param.n_philo; ++i)
    {
        pthread_mutex_lock(&monitor->philos[i].info.mutex);
        printf("\033c");
        printf("Philo %ld: Meals %ld, Last Meal %ld, Ready to Eat %d, Status %d\n",
               i, monitor->philos[i].info.n_meal, monitor->philos[i].info.t_lastmeal,
               (int)monitor->philos[i].info.rdy_to_eat, monitor->philos[i].utils.statut);
        pthread_mutex_unlock(&monitor->philos[i].info.mutex);
    }
}


// void	meal_statut_printer(t_monitor *monitor)
// {
// 	long	index;
// 	long	n_meal;

// 	index = -1;
// 	// printf("\033c");
// 	t_putnbr(MAGENTA, get_time(MILLISECOND) - get_long(&monitor->sync->mutex, monitor->sync->t_start), false, true);
// 	t_putstr(MAGENTA, " |", false);
// 	while (++index < monitor->param.n_philo)
// 	{
// 		n_meal = get_long(&monitor->philos[index].utils.mutex,
// 				monitor->philos[index].info.n_meal);
// 		if (monitor->philos[index].info.dead)
// 			t_putstr(BG_RED, "   ", false);
// 		else if (monitor->all_status[index] == EAT)
// 			t_putnbr(BG_GREEN, n_meal, false, false);
// 		else if (monitor->all_status[index] == THINK)
// 			t_putnbr(BG_WHITE, n_meal, false, false);
// 		else if (monitor->all_status[index] == SLEEP)
// 			t_putnbr(BG_RED, n_meal, false, false);
// 		else if (monitor->all_status[index] == UNSET)
// 			t_putnbr(RED, n_meal, false, false);
// 	}
// 	t_putstr(MAGENTA, "|", true);
// }

void	all_statut_printer(t_monitor *monitor)
{
	long	index;

	index = -1;
	// printf("\033c");
	t_putnbr(MAGENTA, get_time(MILLISECOND) - monitor->sync->t_start, false,
		true);
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
			t_putstr(RED, "  ", false);
	}
	t_putstr(MAGENTA, "|", true);
}

void	*monitor_life(void *in_data)
{
	t_data *data;
	long		index;

	data = (t_data *)in_data;

	// while(!get_bool(&monitor->sync->mutex, monitor->sync->all_ready))
	// 	write(1, "", 0);
	while (!get_bool(&data->monitor.sync->mutex, data->monitor.sync->end))
	{
		index = -1;
		while (++index < data->monitor.param.n_philo)
		{
			if (get_bool(&data->philos[index].info.mutex, data->philos[index].info.dead) == true)
				set_bool(&data->sync.mutex, &data->sync.end, true);
			if ((get_long(&data->philos[data->philos[index].utils.next_pos].info.mutex,
						data->philos[data->philos[index].utils.next_pos].info.n_meal) < get_long(&data->philos[index].info.mutex,
						data->philos[index].info.n_meal)
					|| get_long(&data->philos[data->philos[index].utils.prev_pos].info.mutex,
						data->philos[data->philos[index].utils.prev_pos].info.n_meal) < get_long(&data->philos[index].info.mutex,
						data->philos[index].info.n_meal)))
					write(1, "", 0);
			else if (!get_bool(&data->philos[index].info.mutex,
					data->philos[index].info.rdy_to_eat)
				&& get_statut(&data->philos[data->philos[index].utils.next_pos]) != EAT
				&& !get_bool(&data->philos[data->philos[index].utils.next_pos].info.mutex,
					data->philos[data->philos[index].utils.next_pos].info.rdy_to_eat)
				&& get_statut(&data->philos[data->philos[index].utils.prev_pos]) != EAT
				&& !get_bool(&data->philos[data->philos[index].utils.prev_pos].info.mutex,
					data->philos[data->philos[index].utils.prev_pos].info.rdy_to_eat))
			{
				set_bool(&data->philos[index].info.mutex,
					&data->philos[index].info.rdy_to_eat, true);
			}
			data->monitor.all_status[index] = get_statut(&data->philos[index]);
			// printf("%u", monitor->all_status[index]);
		}
		// if ((get_time(MILLISECOND) - monitor->sync->t_start) % 50 == 0)
			// meal_statut_printer(monitor);
		// all_statut_printer(monitor);
		usleep(200);
			// printf("\n");
	}
	printf("monitor finished after %-6ld ms [%ld]\n", get_time(MILLISECOND)- data->sync.t_start, data->monitor.param.max_meal);
	return (NULL);
}


