/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:33:20 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 17:25:09 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	free_lists(t_data *data)
{
	long	counter;
	t_philo *philo_temp;
	t_fork *fork_temp;

	counter = 0;
	while (data->philo)
	{
		philo_temp = data->philo;
		data->philo = philo_temp->next;
		free(philo_temp);
		counter+=sizeof(t_philo);
	}
	while (data->fork)
	{
		fork_temp = data->fork;
		data->fork = fork_temp->next;
		free(fork_temp);
		counter+=sizeof(t_fork);
	}
	return (print_sclr("\nmemory allocated : ", BLUE, false),
		print_dclr(data->stat.memory_allocated, WHITE, false),print_sclr(" octets", WHITE, true),
		print_sclr("memory freed     : ", WHITE, false), print_dclr(counter, WHITE,
			false), print_sclr(" octets", WHITE, true));
}

void	free_threads(t_data *data)
{
	long counter;
	t_philo *philo;

	counter = 1;
	philo = data->philo;
	while(philo)
	{
		thread_handler(data, counter, NULL, DESTROY);
		philo = philo->next;
		counter++;
	}
	print_sclr("destroyed ", WHITE, false);
	print_dclr(counter, BLUE, false);
	print_sclr(" threads", WHITE, true);
}

void	texit(t_data *data, bool exit_succes)
{
	if (!exit_succes)
		print_sclr("", CLEAR, false);
	// free_threads(data);
	free_lists(data);
	if (!exit_succes)
		tprint("✅ EXIT SUCCES", 0, false, GREEN);
	else
		tprint("❌ EXIT FAILURE", 0, false, RED_);
	exit(exit_succes);
}
