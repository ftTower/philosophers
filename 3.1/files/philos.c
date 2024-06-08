/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:35:43 by tauer             #+#    #+#             */
/*   Updated: 2024/06/08 02:39:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

// void life(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->utils.mutex);
//     t_statut statut = philo->utils.statut;
//     bool rdy_to_eat = philo->info.rdy_to_eat;
//     pthread_mutex_unlock(&philo->utils.mutex);

//     if (statut == THINK && rdy_to_eat)
//     {
//         pthread_mutex_lock(&philo->utils.mutex);
//         philo->utils.statut = EAT;
//         philo->info.t_lastmeal = get_time(MILLISECOND);
//         pthread_mutex_unlock(&philo->utils.mutex);

//         usleep(philo->param.t_eat);

//         pthread_mutex_lock(&philo->utils.mutex);
//         philo->info.n_meal++;
//         if (philo->info.n_meal >= philo->param.max_meal)
//             philo->info.dead = true;
//         philo->utils.statut = SLEEP;
//         pthread_mutex_unlock(&philo->utils.mutex);

//         usleep(philo->param.t_sleep);

//         pthread_mutex_lock(&philo->utils.mutex);
//         philo->info.rdy_to_eat = false;
//         pthread_mutex_unlock(&philo->utils.mutex);
//     }
//     else
//     {
//         pthread_mutex_lock(&philo->utils.mutex);
//         philo->utils.statut = THINK;
//         pthread_mutex_unlock(&philo->utils.mutex);

//         usleep(philo->param.t_eat / 2);
//     }
// }



void	life(t_philo *philo, bool print)
{
	if (get_bool(&philo->info.mutex, &philo->info.rdy_to_eat))
	{
		print_action_subject(EAT, philo, print);
        set_statut(philo, EAT);
		set_long(&philo->info.mutex, &philo->info.t_lastmeal, get_time(MILLISECOND));
		usleep(philo->param.t_eat);
		increase_long(&philo->info.mutex, &philo->info.n_meal);
		// if (get_long(&philo->info.mutex, &philo->info.n_meal) >= philo->param.max_meal)
		// 	set_bool(&philo->info.mutex, &philo->info.dead, true);
		set_bool(&philo->info.mutex, &philo->info.rdy_to_eat, false);
		set_statut(philo, SLEEP);
		print_action_subject(SLEEP, philo, print);
		usleep(philo->param.t_sleep);
	}
	else
	{
		if (get_statut(philo) != THINK)
			print_action_subject(THINK, philo, print);
    	set_statut(philo, THINK);
		usleep(philo->param.t_eat);
	}
}

void	*philo_life(void *in_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)in_philo;
	
	while (!get_bool(&philo->sync->mutex, &philo->sync->all_ready))
		write(1, "", 0);
	while (!get_bool(&philo->sync->mutex, &philo->sync->monitor_ready))
		write(1, "", 0);
	philo->info.t_spawn = get_time(MILLISECOND);
	// if (philo->id % 2 == 0)
	// 	set_bool(&philo->info.mutex, &philo->info.rdy_to_eat, true);
	while (!get_bool(&philo->sync->mutex, &philo->sync->end))
	{
		life(philo, true);
		// usleep(200);
	}
	return (NULL);
}