/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:33:20 by tauer             #+#    #+#             */
/*   Updated: 2024/04/30 01:09:56 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	free_lists(t_data *data, long counter)
{
	t_philo	*philo_temp;
	t_fork	*fork_temp;

	while (data->philo)
	{
		philo_temp = data->philo;
		data->philo = philo_temp->next;
		free(philo_temp);
		counter += sizeof(t_philo);
	}
	while (data->fork)
	{
		fork_temp = data->fork;
		data->fork = fork_temp->next;
		free(fork_temp);
		counter += sizeof(t_fork);
	}
	if (counter == data->stat.memory_allocated)
		print_sclr("Memory usage  ", GREEN, false);
	else
		print_sclr("Memory usage  ", RED_, false);
	return (print_sclr("(", WHITE, false), print_dclr(counter, BLUE, false),
		print_sclr("/", WHITE, false), print_dclr(data->stat.memory_allocated,
			BLUE, false), print_sclr(")octets", WHITE, true));
}

void	free_threads(t_data *data)
{
	long	counter;
	t_philo	*philo;

	counter = 0;
	philo = data->philo;
	while (philo)
	{
		thread_handler(data, counter + 1, NULL, JOIN);
		philo = philo->next;
		counter++;
	}
	if (counter == data->param.number_philo)
		print_sclr("\nthread usage  ", GREEN, false);
	else
		print_sclr("\nthread usage  ", RED_, false);
	return (print_sclr("(", WHITE, false), print_dclr(counter, BLUE, false),
		print_sclr("/", WHITE, false), print_dclr(data->param.number_philo,
			BLUE, false), print_sclr(")", WHITE, true));
}

void	texit(t_data *data, bool exit_succes)
{
	if (!exit_succes)
		print_sclr("", CLEAR, false);
	free_threads(data);
	free_lists(data, 0);
	if (!exit_succes)
		tprint("\n✅ EXIT SUCCES", 0, false, GREEN);
	else
		tprint("\n❌ EXIT FAILURE", 0, false, RED_);
	exit(exit_succes);
}
