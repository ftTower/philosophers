/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:47:19 by tauer             #+#    #+#             */
/*   Updated: 2024/06/08 02:38:31 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	debug_philos(t_philo *philos, long size)
{
	long	index;

	index = -1;
	while (++index < size)
	{
		t_putstr(MAGENTA, "+========================[", false);
		t_putstr(BLUE, "philo : ", false);
		t_putnbr(CYAN, philos[index].id, false, true);
		t_putstr(MAGENTA, "]======", true);
		t_putstr(WHITE, "| param  : ", false);
		if (philos[index].param.n_philo != 0 && philos[index].param.t_die != 0
			&& philos[index].param.t_eat != 0
			&& philos[index].param.t_sleep != 0)
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

void	print_action_subject(t_statut statut, t_philo *philo, bool print)
{
	if (!print)
		return ;
	pthread_mutex_lock(&philo->sync->write_mutex);
	if (statut == EAT)
	{
		t_putnbr(WHITE, get_time(MILLISECOND) - philo->sync->t_start, false,
			true);
		t_putstr(WHITE, " ", false);
		t_putnbr(WHITE, philo->id + 1, false, false);
		t_putstr(MAGENTA, " has taken a fork", true);
		t_putnbr(WHITE, get_time(MILLISECOND) - philo->sync->t_start, false,
			true);
		t_putstr(WHITE, " ", false);
		t_putnbr(WHITE, philo->id + 1, false, false);
		t_putstr(MAGENTA, " has taken a fork", true);
		t_putnbr(WHITE, get_time(MILLISECOND) - philo->sync->t_start, false,
			true);
		t_putstr(WHITE, " ", false);
		t_putnbr(WHITE, philo->id + 1, false, false);
		t_putstr(MAGENTA, " is eating", true);
	}
	else if (statut == SLEEP)
	{
		t_putnbr(WHITE, get_time(MILLISECOND) - philo->sync->t_start, false,
			true);
		t_putstr(WHITE, " ", false);
		t_putnbr(WHITE, philo->id + 1, false, false);
		t_putstr(MAGENTA, " is sleeping", true);
	}
	else if (statut == THINK)
	{
		t_putnbr(WHITE, get_time(MILLISECOND) - philo->sync->t_start, false,
			true);
		t_putstr(WHITE, " ", false);
		t_putnbr(WHITE, philo->id + 1, false, false);
		t_putstr(MAGENTA, " is thinking", true);
	}
	pthread_mutex_unlock(&philo->sync->write_mutex);
}
