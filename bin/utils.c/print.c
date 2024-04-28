/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:04:56 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 01:36:57 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_scenario_philo(bool got_fork, t_philo *philo, t_fork *fork)
{
	print_sclr("PHILOSOPHER N ", WHITE, false);
	print_dclr(philo->pos, BLUE, false);
	print_sclr(" -> ", WHITE, false);
	if (philo->is_full)
		print_sclr("IS FULL ", RED_, false);
	else
		print_sclr("IS HUNGRY ", GREEN, false);
	print_sclr(" | ASSOCIATED FORK -> ", WHITE, false);
	print_dclr(fork->pos, RED_, false);
	if (got_fork)
	{
		print_sclr(" | LEFT FORK -> ", WHITE, false);
		print_dclr(philo->left_fork, BLUE, false);
		print_sclr(" | RIGHT FORK -> ", WHITE, false);
		print_dclr(philo->right_fork, BLUE, true);
	}
}

void	print_philo(t_data *data, bool got_fork)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = data->philo;
	fork = data->fork;
	while (philo)
	{
		print_scenario_philo(got_fork, philo, fork);
		philo = philo->next;
		fork = fork->next;
	}
	// sleep(3);
	// tprint("", 0, false, CLEAR);
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
	print_philo(data, true);
}
