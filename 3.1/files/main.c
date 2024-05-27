/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:13:42 by tauer             #+#    #+#             */
/*   Updated: 2024/05/27 02:00:57 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	life(t_philo *philo)
{
	if (get_statut(philo) == THINK && get_bool(philo->utils.mutex, philo->info.rdy_to_eat))
	{
		// t_putnbr(YELLOW, philo->id, false);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : has eaten", true);
		set_statut(philo, EAT);
		increase_long(philo->utils.mutex, &philo->info.n_meal);
		usleep(philo->param.t_eat);
		set_bool(philo->utils.mutex, &philo->info.rdy_to_eat, false);
		set_statut(philo, SLEEP);
		// t_putnbr(YELLOW, philo->id, false);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : his sleeping", true);
		usleep(philo->param.t_sleep);
	}
	else
	{
		// t_putnbr(YELLOW, philo->id, false);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : his thinking", true);
			set_statut(philo, THINK);
			usleep(philo->param.t_eat / 2);
			
	}
	
}

void	*philo_life(void *in_philo)
{
	t_philo	*philo;

	philo = (t_philo *)in_philo;
	while (!get_bool(philo->sync->mutex, philo->sync->all_ready))
		;
	philo->info.t_spawn = get_time(MILLISECOND);
	while (!get_bool(philo->sync->mutex, philo->sync->end))
	{
		life(philo);
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	long	index;

	if (argc < 5 || argc > 6 || init_data(&data, argv + 1))
		return (printf("failure\n"), EXIT_FAILURE);
	index = -1;
	while (++index < data.philos[0].param.n_philo)
		pthread_create(&data.philos[index].utils.thread, NULL, philo_life,
			&data.philos[index]);
	pthread_create(&data.monitor.thread, NULL, monitor_life, &data.monitor);
	set_bool(data.sync.mutex, &data.sync.all_ready, true);
	data.sync.t_start = get_time(MILLISECOND);
	index = -1;
	while (++index < data.philos[0].param.n_philo)
		pthread_join(data.philos[index].utils.thread, NULL);
	pthread_join(data.monitor.thread, NULL);
	return (debug_philos(data.philos, data.philos[0].param.n_philo), free(data.philos),
		EXIT_SUCCESS);
}
