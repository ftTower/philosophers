/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:47:47 by tauer             #+#    #+#             */
/*   Updated: 2024/04/26 02:24:18 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	setup(t_data *data, char **argv)
{
	null_data(data);
	if (set_param(data, argv))
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 4 && argc < 7 && setup(&data, argv))
		print_data(&data);
	return (0);
}
