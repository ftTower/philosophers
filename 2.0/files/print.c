/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:12:54 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 22:55:49 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	t_print(t_color color, const char *str)
{
	const char *colors[] = {
		"\033[38;5;196m",
		"\033[38;5;46m",
		"\033[38;5;226m",
		"\033[38;5;21m",
		"\033[38;5;201m",
		"\033[38;5;51m",
		"\033[38;5;15m",
	};
	printf("%s%s\033[0m", colors[color], str);
}

void	print_data(t_data *data)
{
	long	index;

	printf("\n");
	t_print(WHITE, "============================\n");
	printf("n_philo %ld\n", data->n_philo);
	printf("n_meal %ld\n", data->n_meal);
	printf("t_eat %ldms\n", data->t_eat);
	printf("t_die %ldms\n", data->t_die);
	printf("t_sleep %ldms\n", data->t_sleep);
	t_print(WHITE, "============================\n");
	index = -1;
	while (++index < data->n_philo)
	{
		// data->philo[index]
		printf("[%ld] (%ld|%ld) (t_meal %ld) (n_meal %ld) (philo-data-n_phi : %ld)\n", data->philo[index].id, data->philo[index].l_fork.id,
			data->philo[index].r_fork->id, data->philo[index].t_meal,
			data->philo[index].n_meal, data->philo[index].data->n_philo);
	}
}

void	debug_print(t_statut code, t_philo *philo, long elapsed)
{
	if (philo->id % 2 == 0 && code == L_FORK && !end(philo->data))
		printf("%-6ld : %ld has taken left  fork %ld\n", elapsed, philo->id,
			philo->l_fork.id);
	else if (philo->id % 2 == 0 && code == R_FORK && !end(philo->data))
		printf("%-6ld : %ld has taken right fork %ld\n", elapsed, philo->id,
			philo->r_fork->id);
	else if (philo->id % 2 != 0 && code == L_FORK && !end(philo->data))
		printf("%-6ld : %ld has taken left  fork %ld\n", elapsed, philo->id,
			philo->l_fork.id);
	else if (philo->id % 2 != 0 && code == R_FORK && !end(philo->data))
		printf("%-6ld : %ld has taken right fork %ld\n", elapsed, philo->id,
			philo->r_fork->id);
	else if (code == EAT && !end(philo->data))
		printf("%-6ld : \033[38;5;190m%ld is eating\033[0m [%ld meals]\n",
			elapsed, philo->id, philo->n_meal);
	else if (code == SLEEP && !end(philo->data))
		printf("%-6ld : %ld is sleeping\n", elapsed, philo->id);
	else if (code == THINK && !end(philo->data))
		printf("%-6ld : %ld is thinking\n", elapsed, philo->id);
	else if (code == DEAD)
		printf("%-6ld : %ld is dead\n", elapsed, philo->id);
	else
		t_print(RED, "ERROR\n");
}

void	print_statut(t_statut code, t_data *data, t_philo *philo,
		bool subject_print)
{
	long	elapsed;

	elapsed = get_time(philo->data, MILLISECOND) - data->t_simulation;
	if (philo->dead)
		return ;
	mutex_handler(data, &philo->data->write, M_LOCK);
	if (!subject_print)
		debug_print(code, philo, elapsed);
	else
	{
		if (!philo)
			t_print(RED, "No philo for printing statut...\n");
		else
		{
			printf("%-6ld : %ld", elapsed, philo->id);
			if ((code == L_FORK || code == R_FORK) && !end(philo->data))
				t_print(CYAN, " has taken a fork\n");
			else if (code == EAT && !end(philo->data))
				t_print(GREEN, " is eating\n");
			else if (code == SLEEP && !end(philo->data))
				t_print(YELLOW, " is sleeping\n");
			else if (code == THINK && !end(philo->data))
				t_print(BLUE, " is thinking\n");
			else if (code == DEAD)
				t_print(RED, " is dead\n");
			else if (end(philo->data))
				t_print(RED, " simulation finished...\n");
			else
				t_print(RED, "Wrong code for printing statut...\n");
		}
	}
	printf("\033[0m");
	mutex_handler(data, &philo->data->write, M_UNLOCK);
}
