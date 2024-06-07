/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:18:43 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 19:36:28 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	thread_maker(t_table *table, t_error *error_code)
{
	long	index;

	index = -1;
	while (++index < table->arg.nb_philos)
		pthread_create(&table->philos[index].thread, NULL, philo_life,
			&table->philos[index]);
	index = -1;
	while (++index < table->arg.nb_philos)
		if (pthread_join(table->philos[index].thread, NULL) != 0)
			return (*error_code = THREAD_JOIN, true);
	return (*error_code = SUCCES, false);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_error	error_code;

	if (init_table(&table, &error_code, argc, argv + 1))
		error_catcher(error_code);
	else if (thread_maker(&table, &error_code))
		error_catcher(error_code);
	return (final_table(&table), free(table.forks), free(table.philos),
		EXIT_SUCCESS);
}
