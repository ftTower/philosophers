/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:47:19 by tauer             #+#    #+#             */
/*   Updated: 2024/06/11 02:24:29 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void debug_philos(t_philo *philos, long size)
{
	long index;

	index = -1;
	while (++index < size)
	{
		t_putstr(MAGENTA, "+========================[", false);
		t_putstr(BLUE, "philo : ", false);
		t_putnbr(CYAN, philos[index].id, false, true);
		t_putstr(MAGENTA, "]======", true);
		t_putstr(WHITE, "| param  : ", false);
		if (philos[index].param.n_philo != 0 && philos[index].param.t_die != 0 && philos[index].param.t_eat != 0 && philos[index].param.t_sleep != 0)
			t_putstr(BG_GREEN, "  ", false);
		else
			t_putstr(BG_RED, "  ", false);
		t_putstr(WHITE, " sync  : ", false);
		if (philos[index].sync)
			t_putstr(BG_GREEN, "  ", true);
		else
			t_putstr(BG_RED, "  ", true);
		t_putstr(WHITE, "| statut : ", false);
		if (philos[index].utils.statut == EAT)
			t_putstr(YELLOW, "EATING", true);
		else if (philos[index].utils.statut == SLEEP)
			t_putstr(YELLOW, "SLEEPING", true);
		else if (philos[index].utils.statut == THINK)
			t_putstr(YELLOW, "THINKING", true);
		else if (philos[index].utils.statut == DEAD)
			t_putstr(BG_RED, "DEAD", true);
		else
			t_putstr(RED, "UNSET", true);
		t_putstr(WHITE, "| utils  : ", false);
		t_putstr(BG_RED, "PREV ", false);
		t_putnbr(BG_RED, philos[index].utils.prev_pos, false, true);
		t_putstr(WHITE, " ", false);
		t_putnbr(BG_WHITE, philos[index].id, false, true);
		t_putstr(WHITE, " ", false);
		t_putnbr(BG_GREEN, philos[index].utils.next_pos, false, true);
		t_putstr(BG_GREEN, " NEXT", true);
		t_putstr(WHITE, "| tspawn : ", false);
		t_putnbr(YELLOW, philos[index].info.t_spawn, true, true);
		t_putstr(WHITE, "| n meal : ", false);
		t_putnbr(BLUE, philos[index].info.n_meal, true, true);
	}
	t_putstr(MAGENTA, "+=============================================\n",
			 false);
}

void print_statut_lock(t_statut statut, t_philo *philo, bool print,
					   bool is_fork)
{
	if (!print)
		return;
	if (get_bool(&philo->sync->mutex, &philo->sync->end))
		return;
	pthread_mutex_lock(&philo->sync->write_mutex);
	// t_putnbr(BG_WHITE, get_time(MILLISECOND) - get_long(&philo->info.mutex, &philo->info.t_lastmeal), false, true);
	// t_putstr(WHITE, " ", false);
	// t_putnbr(BG_RED, philo->param.t_die, false, true);
	// t_putstr(WHITE, " : ", false);
	t_putnbr(WHITE, get_time(MILLISECOND) - get_long(&philo->sync->mutex, &philo->sync->t_start), false, true);
	t_putstr(WHITE, " ", false);
	t_putnbr(WHITE, philo->id + 1, false, false);
	t_putstr(WHITE, " ", false);
	
	if (is_fork)
		t_putstr(CYAN, "has taken a fork", true);
	else if (statut == EAT)
		t_putstr(GREEN, "is eating", true);
	else if (statut == SLEEP)
		t_putstr(YELLOW, "is sleeping", true);
	else if (statut == THINK)
		t_putstr(BLUE, "is thinking", true);
	else if (statut == DEAD)
	{
		t_putstr(BG_RED, "is dead", true);
	}
	pthread_mutex_unlock(&philo->sync->write_mutex);
}

void meal_statut_printer(t_monitor *monitor)
{
	long index;
	long n_meal;

	index = -1;
	t_putnbr(MAGENTA, get_time(MILLISECOND) - get_long(&monitor->sync->mutex, &monitor->sync->t_start), false, true);
	t_putstr(MAGENTA, " |", false);
	while (++index < monitor->param.n_philo)
	{
		n_meal = get_long(&monitor->philos[index].info.mutex,
						  &monitor->philos[index].info.n_meal);
		if (monitor->philos[index].info.dead)
			t_putstr(BG_RED, "   ", false);
		else if (monitor->all_status[index] == EAT)
			t_putnbr(BG_GREEN, n_meal, false, false);
		else if (monitor->all_status[index] == THINK)
			t_putnbr(BG_WHITE, n_meal, false, false);
		else if (monitor->all_status[index] == SLEEP)
			t_putnbr(BG_RED, n_meal, false, false);
		else if (monitor->all_status[index] == UNSET)
			t_putnbr(RED, n_meal, false, false);
	}
	t_putstr(MAGENTA, "|", true);
}

void monitor_print(t_monitor *monitor, bool finished)
{
	if (!finished)
		meal_statut_printer(monitor);
	else
	{
		t_putstr(BG_WHITE, "                                  ", true);
		t_putstr(BG_WHITE, "Biggest starvation spotted : ", false);
		t_putnbr(BG_RED, monitor->biggest_starvation * 1000, true, true);
		t_putstr(BG_WHITE, "                                  ", true);
		t_putstr(BG_WHITE, "time to die                : ", false);
		t_putnbr(BG_RED, monitor->param.t_die, true, true);
		t_putstr(BG_WHITE, "                                  ", true);
		
	}
}
