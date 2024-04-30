/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:04:56 by tauer             #+#    #+#             */
/*   Updated: 2024/05/01 00:55:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_philo_fork(t_philo *philo, t_fork *fork)
{
	return (print_sclr("PHILOSOPHER N ", WHITE, false), print_dclr(philo->pos,
			BLUE, false), print_sclr(" | ASSOCIATED FORK -> ", WHITE, false),
		print_dclr(fork->pos, RED_, false), print_sclr(" | LEFT FORK -> ",
			WHITE, false), print_dclr(philo->left_fork, BLUE, false),
		print_sclr(" | RIGHT FORK-> ", WHITE, false),
		print_dclr(philo->right_fork, BLUE, false),
		 print_sclr(" | THREAD ID -> ", WHITE, false),
		  print_dclr(philo->id, BLUE, true));
}

void	print_simulation(t_philo *philo)
{
	print_sclr("PHILOSOPHER N ", WHITE, false);
	print_dclr(philo->pos, BLUE, false);
	if (philo->statut == THINKIN)
		print_sclr(" IS THINKING ", GREEN, true);
	else if (philo->statut == SLEEPING)
		print_sclr(" IS SLEEPING ", GREEN, true);
	else if (philo->statut == EATING)
		print_sclr(" IS EATING ", GREEN, true);
	else
		print_sclr(" IS UNASIGNED ", RED_, true);
}

void	print_philo_info(t_philo *philo, long num_philo)
{
	print_sclr("PHILOSOPHER N ", WHITE, false);
	print_dclr(philo->pos, BLUE, false);
	if (philo->statut == THINKIN)
		print_sclr(" IS THINKING ", GREEN, false);
	else if (philo->statut == SLEEPING)
		print_sclr(" IS SLEEPING ", GREEN, false);
	else if (philo->statut == EATING)
		print_sclr(" IS EATING ", GREEN, false);
	else
		print_sclr(" IS UNASIGNED ", RED_, false);
	print_sclr("AND ", WHITE, false);
	if (philo->is_full)
		print_sclr("IS FULL 💀", WHITE, false);
	else
	{
		print_sclr("IS NOT FULL ", GREEN, false);
		print_sclr("LAST MEAL (", WHITE, false);
		print_dclr(philo->last_meal, BLUE, false);
		print_sclr(")", WHITE, false);
	}
	print_sclr(" (", WHITE, false);
	if (philo->prev)
		print_dclr(philo->prev->pos, BLUE, false);
	else
		print_dclr(num_philo, YELLOW, false);
	print_sclr(" prev-next ", WHITE, false);
	if (philo->next)
		print_dclr(philo->next->pos, BLUE, false);
	else
		print_dclr(0, YELLOW, false);
	print_sclr(")", WHITE, true);
}

void	print_philo(t_data *data, bool need_clear, bool need_sleep, t_cmd code)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = data->philo;
	fork = data->fork;
	print_sclr("\n", WHITE, false);
	if (need_clear)
		print_sclr("", CLEAR, false);
	while (philo && fork)
	{
		if (code == PRINT_F_INFO)
			print_philo_fork(philo, fork);
		else if (code == PRINT_P_INFO)
			print_philo_info(philo, data->param.number_philo - 1);
		else if (code == PRINT_SIMULATION)
			print_simulation(philo);
		philo = philo->next;
		fork = fork->next;
	}
	if (need_sleep)
		sleep(3);
}

void	print_table(t_data *data)
{
	tprint("", 0, false, CLEAR);
	tprint("TABLE INFO :", 0, false, RED_);
	tprint("number philo : ", data->param.number_philo, true, WH_BL);
	tprint("number eat   : ", data->param.number_eat, true, WH_BL);
	tprint("time to die  : ", data->param.time_to_die, true, WH_BL);
	tprint("time to eat  : ", data->param.time_to_eat, true, WH_BL);
	tprint("time to eat  : ", data->param.time_to_sleep, true, WH_BL);
	sleep(2);
	tprint("", 0, false, CLEAR);
}

void	print_data(t_data *data)
{
	print_table(data);
	// print_philo(data, true, true, PRINT_F_INFO);
	print_philo(data, true, true, PRINT_P_INFO);
	// print_sclr("", CLEAR, false);
}
