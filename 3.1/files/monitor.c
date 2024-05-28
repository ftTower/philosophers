/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:41:09 by tauer             #+#    #+#             */
/*   Updated: 2024/05/28 02:09:59 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void meal_statut_printer(t_monitor *monitor)
{
    for (long i = 0; i < monitor->param.n_philo; ++i)
    {
        pthread_mutex_lock(&monitor->philos[i].utils.mutex);
        printf("Philo %ld: Meals %ld, Last Meal %ld, Ready to Eat %d, Status %d\n",
               i, monitor->philos[i].info.n_meal, monitor->philos[i].info.t_lastmeal,
               (int)monitor->philos[i].info.rdy_to_eat, monitor->philos[i].utils.statut);
        pthread_mutex_unlock(&monitor->philos[i].utils.mutex);
    }
}


// void	meal_statut_printer(t_monitor *monitor)
// {
// 	long	index;
// 	long	n_meal;

// 	index = -1;
// 	// printf("\033c");
// 	t_putnbr(MAGENTA, get_time(MILLISECOND) - monitor->sync->t_start, false,
// 		true);
// 	t_putstr(MAGENTA, " |", false);
// 	while (++index < monitor->param.n_philo)
// 	{
// 		n_meal = get_long(monitor->philos[index].utils.mutex,
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

// void	*monitor_life(void *in_monitor)
// {
// 	t_monitor	*monitor;
// 	long		index;

// 	monitor = (t_monitor *)in_monitor;
// 	while (!get_bool(monitor->sync->mutex, monitor->sync->end))
// 	{
// 		index = -1;
// 		while (++index < monitor->param.n_philo)
// 		{
// 			if (get_bool(monitor->philos[index].utils.mutex, monitor->philos[index].info.dead) == true)
// 				set_bool(monitor->sync->mutex, &monitor->sync->end, true);
// 			if ((get_long(monitor->philos[monitor->philos[index].utils.next_pos].utils.mutex,
// 						monitor->philos[monitor->philos[index].utils.next_pos].info.n_meal) < get_long(monitor->philos[index].utils.mutex,
// 						monitor->philos[index].info.n_meal)
// 					|| get_long(monitor->philos[monitor->philos[index].utils.prev_pos].utils.mutex,
// 						monitor->philos[monitor->philos[index].utils.prev_pos].info.n_meal) < get_long(monitor->philos[index].utils.mutex,
// 						monitor->philos[index].info.n_meal)))
// 				index = index + 0;
// 			else if (!get_bool(monitor->philos[index].utils.mutex,
// 					monitor->philos[index].info.rdy_to_eat)
// 				&& get_statut(&monitor->philos[monitor->philos[index].utils.next_pos]) != EAT
// 				&& !get_bool(monitor->philos[monitor->philos[index].utils.next_pos].utils.mutex,
// 					monitor->philos[monitor->philos[index].utils.next_pos].info.rdy_to_eat)
// 				&& get_statut(&monitor->philos[monitor->philos[index].utils.prev_pos]) != EAT
// 				&& !get_bool(monitor->philos[monitor->philos[index].utils.prev_pos].utils.mutex,
// 					monitor->philos[monitor->philos[index].utils.prev_pos].info.rdy_to_eat))
// 			{
// 				set_bool(monitor->philos[index].utils.mutex,
// 					&monitor->philos[index].info.rdy_to_eat, true);
// 			}
// 			// monitor->all_status[index] = get_statut(&monitor->philos[index]);
// 		}
// 		if ((get_time(MILLISECOND) - monitor->sync->t_start) % 50 == 0)
// 			meal_statut_printer(monitor);
// 		// all_statut_printer(monitor);
// 		usleep(1000);
// 	}
// 	printf("monitor finished after %-6ld ms [%ld]\n", get_time(MILLISECOND)- monitor->sync->t_start, monitor->param.max_meal);
// 	return (NULL);
// }

void *monitor_life(void *in_monitor)
{
    t_monitor *monitor = (t_monitor *)in_monitor;

    while (!get_bool(monitor->sync->mutex, monitor->sync->end))
    {
        for (long index = 0; index < monitor->param.n_philo; ++index)
        {
            pthread_mutex_lock(&monitor->philos[index].utils.mutex);
            bool is_dead = monitor->philos[index].info.dead;
            pthread_mutex_unlock(&monitor->philos[index].utils.mutex);

            if (is_dead)
            {
                set_bool(monitor->sync->mutex, &monitor->sync->end, true);
                break;
            }

            long next_pos = monitor->philos[index].utils.next_pos;
            long prev_pos = monitor->philos[index].utils.prev_pos;

            pthread_mutex_lock(&monitor->philos[index].utils.mutex);
            long n_meal = monitor->philos[index].info.n_meal;
            pthread_mutex_unlock(&monitor->philos[index].utils.mutex);

            pthread_mutex_lock(&monitor->philos[next_pos].utils.mutex);
            long next_n_meal = monitor->philos[next_pos].info.n_meal;
            pthread_mutex_unlock(&monitor->philos[next_pos].utils.mutex);

            pthread_mutex_lock(&monitor->philos[prev_pos].utils.mutex);
            long prev_n_meal = monitor->philos[prev_pos].info.n_meal;
            pthread_mutex_unlock(&monitor->philos[prev_pos].utils.mutex);

            if (next_n_meal < n_meal || prev_n_meal < n_meal)
            {
                // No action needed, just move to the next philosopher
                continue;
            }

            pthread_mutex_lock(&monitor->philos[index].utils.mutex);
            bool rdy_to_eat = monitor->philos[index].info.rdy_to_eat;
            pthread_mutex_unlock(&monitor->philos[index].utils.mutex);

            if (!rdy_to_eat)
            {
                pthread_mutex_lock(&monitor->philos[next_pos].utils.mutex);
                t_statut next_statut = monitor->philos[next_pos].utils.statut;
                pthread_mutex_unlock(&monitor->philos[next_pos].utils.mutex);

                pthread_mutex_lock(&monitor->philos[prev_pos].utils.mutex);
                t_statut prev_statut = monitor->philos[prev_pos].utils.statut;
                pthread_mutex_unlock(&monitor->philos[prev_pos].utils.mutex);

                if (next_statut != EAT && prev_statut != EAT)
                {
                    pthread_mutex_lock(&monitor->philos[index].utils.mutex);
                    monitor->philos[index].info.rdy_to_eat = true;
                    pthread_mutex_unlock(&monitor->philos[index].utils.mutex);
                }
            }
        }

        if ((get_time(MILLISECOND) - monitor->sync->t_start) % 50 == 0)
        {
            meal_statut_printer(monitor);
        }

        // usleep(1000);
    }

    printf("monitor finished after %-6ld ms [%ld]\n", get_time(MILLISECOND) - monitor->sync->t_start, monitor->param.max_meal);
    return NULL;
}

