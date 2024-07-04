/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:47:19 by tauer             #+#    #+#             */
/*   Updated: 2024/07/04 16:54:56 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_statut_lock(t_statut statut, t_philo *philo, bool print,
		bool is_fork)
{
	if (!print)
		return ;
	if (get_bool(&philo->sync->mutex, &philo->sync->end)
		|| get_bool(&philo->info.mutex, &philo->info.dead))
		return ;
	pthread_mutex_lock(&philo->sync->write_mutex);
	t_putnbr(WHITE, get_time(MILLISECOND) \
	- get_long(&philo->sync->mutex,
			&philo->sync->t_start), false, true);
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
		t_putstr(BG_RED, "died", true);
	pthread_mutex_unlock(&philo->sync->write_mutex);
}

void	meal_statut_printer(t_monitor *monitor)
{
	long	index;
	long	n_meal;

	index = -1;
	t_putnbr(MAGENTA, get_time(MILLISECOND) - monitor->sync->t_start, false,
		true);
	t_putstr(MAGENTA, " | ", false);
	while (++index < monitor->param.n_philo)
	{
		n_meal = (get_time(MILLISECOND)
				- get_long(&monitor->philos[index].info.mutex,
					&monitor->philos[index].info.t_lastmeal));
		if (monitor->philos[index].info.dead)
			t_putstr(BG_RED, "   ", false);
		else if (monitor->all_status[index] == EAT)
			t_putnbr(BG_GREEN, n_meal, false, true);
		else if (monitor->all_status[index] == THINK)
			t_putnbr(BG_WHITE, n_meal, false, true);
		else if (monitor->all_status[index] == SLEEP)
			t_putnbr(BG_RED, n_meal, false, true);
		else if (monitor->all_status[index] == UNSET)
			t_putnbr(RED, n_meal, false, true);
	}
	t_putstr(MAGENTA, "|", true);
}

void	monitor_print(t_monitor *monitor, bool finished)
{
	if (!finished)
		meal_statut_printer(monitor);
	else
	{
		t_putstr(BG_WHITE, "                                  ", true);
		t_putstr(BG_WHITE, "Biggest starvation spotted : ", false);
		t_putnbr(BG_RED, monitor->biggest_starvation, true, true);
		t_putstr(BG_WHITE, "                                  ", true);
		t_putstr(BG_WHITE, "time to die                : ", false);
		t_putnbr(BG_RED, monitor->param.t_die, true, true);
		t_putstr(BG_WHITE, "                                  ", true);
	}
}
