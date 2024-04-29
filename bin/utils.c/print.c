/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:04:56 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 17:30:32 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_scenario_philo(bool full_info, t_philo *philo, t_fork *fork)
{
	print_sclr("PHILOSOPHER N ", WHITE, false);
	print_dclr(philo->pos, BLUE, false);
	print_sclr(" -> ", WHITE, false);
	if (philo->is_full)
		print_sclr("IS FULL   ", RED_, false);
	else
		print_sclr("IS HUNGRY ", GREEN, false);
	print_sclr(" | ASSOCIATED FORK -> ", WHITE, false);
	print_dclr(fork->pos, RED_, false);
	if (full_info)
		return (print_sclr(" | LEFT FORK -> ", WHITE, false),
			print_dclr(philo->left_fork, BLUE, false),
			print_sclr(" | RIGHT FORK-> ", WHITE, false),
			print_dclr(philo->right_fork, BLUE, false),
			print_sclr(" | THREAD ID -> "
			, WHITE, false), print_dclr(philo->id, BLUE, true));
	return (print_sclr("\n", WHITE, false));
}

void	print_philo(t_data *data, bool got_fork, bool need_clear)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = data->philo;
	fork = data->fork;
	print_sclr("\n\n", WHITE, false);
	if (need_clear)
		print_sclr("", CLEAR, false);
	while (philo && fork)
	{
		print_scenario_philo(got_fork, philo, fork);
		philo = philo->next;
		fork = fork->next;
	}
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
	print_philo(data, true, true);
}
