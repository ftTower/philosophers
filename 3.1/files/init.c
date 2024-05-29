/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:24:47 by tauer             #+#    #+#             */
/*   Updated: 2024/05/29 21:25:38 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

bool	param_getter(t_param *template, char **argv)
{
	if (!ft_atoi(argv[0], &template->n_philo, false) || !ft_atoi(argv[1],
			&template->t_eat, true) || !ft_atoi(argv[2], &template->t_die, true)
		|| !ft_atoi(argv[3], &template->t_sleep, true))
		return (printf("failed to atoi input\n"), true);
	return (ft_atoi(argv[4], &template->max_meal, false), false);
}

bool	monitor_maker(t_data *data, t_param template)
{
	long	index;

	data->monitor.all_status = malloc(sizeof(t_statut) * template.n_philo);
	if (!data->monitor.all_status)
		return (free(data->philos), true);
	index = -1;
	while (++index < template.n_philo)
		data->monitor.all_status[index] = UNSET;
	data->monitor.param = template;
	data->monitor.sync = data->philos->sync;
	data->monitor.philos = data->philos;
	return (false);
}

bool	philos_maker(t_data *data, t_param template)
{
	long	index;

	data->philos = malloc(sizeof(t_philo) * template.n_philo);
	if (!data->philos)
		return (printf("failed to malloc philos\n"), true);
	index = -1;
	while (++index < template.n_philo)
	{
		data->philos[index].id = index;
		data->philos[index].info.rdy_to_eat = false;
		data->philos[index].utils.next_pos = index + 1;
		data->philos[index].utils.prev_pos = (index - 1) % template.n_philo;
		if (index == 0)
			data->philos[index].utils.prev_pos = template.n_philo - 1;
		else if (index == template.n_philo - 1)
			data->philos[index].utils.next_pos = 0;
		data->philos[index].param = template;
		data->philos[index].sync = &data->sync;
		data->philos[index].utils.statut = UNSET;
		data->philos[index].info.n_meal = 0;
		data->philos[index].info.dead = false;
		data->philos[index].info.t_lastmeal = 0;
		// if (pthread_mutex_init(&data->philos[index].utils.mutex, NULL) != 0)
		// 	return (free(data->philos), printf("failed to init mutex\n"), true);
	}
	return (false);
}

bool	init_data(t_data *data, char **argv)
{
	t_param template;

	data->sync.all_ready = false;
	data->sync.end = false;
	if (param_getter(&template, argv) || philos_maker(data, template)
		|| monitor_maker(data, template))
		return (printf("failed to init data\n"), true);
	return (printf("init ok\n"),false);
}