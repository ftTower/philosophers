/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:09:49 by tauer             #+#    #+#             */
/*   Updated: 2024/06/12 00:10:30 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	debug_scenario(t_philo *philos, long index)
{
	t_putstr(MAGENTA, "+========================[", false);
	t_putstr(BLUE, "philo : ", false);
	t_putnbr(CYAN, philos[index].id, false, true);
	t_putstr(MAGENTA, "]======", true);
	t_putstr(WHITE, "| param  : ", false);
	if (philos[index].param.n_philo > 0)
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
		t_putstr(GREEN, "EATING", true);
	else if (philos[index].utils.statut == SLEEP)
		t_putstr(RED, "SLEEPING", true);
	else if (philos[index].utils.statut == THINK)
		t_putstr(WHITE, "THINKING", true);
	else if (philos[index].utils.statut == DEAD)
		t_putstr(BG_RED, "DEAD", true);
	else
		t_putstr(RED, "UNSET", true);
}

void	debug_utils(t_philo *philos, long index)
{
	return (t_putstr(WHITE, "| utils  : ", false), t_putstr(BG_RED, "PREV ",
			false), t_putnbr(BG_RED, philos[index].utils.prev_pos, false, true),
		t_putstr(WHITE, " ", false), t_putnbr(BG_WHITE, philos[index].id, false,
			true), t_putstr(WHITE, " ", false), t_putnbr(BG_GREEN,
			philos[index].utils.next_pos, false, true), t_putstr(BG_GREEN,
			" NEXT", true), t_putstr(WHITE, "| tspawn : ", false),
		t_putnbr(YELLOW, philos[index].info.t_spawn, true, true),
		t_putstr(WHITE, "| n meal : ", false), t_putnbr(BLUE,
			philos[index].info.n_meal, true, true));
}

void	debug_philos(t_philo *philos, long size)
{
	long	index;

	if (!DEBUG_MODE)
		return ;
	index = -1;
	while (++index < size)
	{
		debug_scenario(philos, index);
		debug_utils(philos, index);
	}
	t_putstr(MAGENTA, "+=============================================\n",
		false);
}

