/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:47:47 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 17:12:08 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void*	routine(void *test)
{
	(void)test;
	return (NULL);
}

bool	setup(t_data *data, char **argv, int argc)
{
	tprint("", 0, false, CLEAR);
	null_data(data);
	if ((argc == 5 || argc == 6) && set_param(data, argv) && philo_maker(data)
		&& fork_maker(data))
		return (thread_maker(data),print_sclr("setup ✅", GREEN, true), sleep(1), print_sclr("",
				CLEAR, false), true);
	return (print_sclr("setup ❌", RED_, true), sleep(1), print_sclr("", CLEAR,
			false), false);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (setup(&data, argv, argc))
		print_data(&data);
	return (texit(&data, EXIT_SUCCESS), 0);
}
