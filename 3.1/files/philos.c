/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:35:43 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 00:17:15 by tauer            ###   ########.fr       */
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

void	life(t_philo *philo)
{
	if (get_bool(&philo->info.mutex, philo->info.rdy_to_eat))
	{
		// t_putnbr(YELLOW, philo->id, false, true);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : has eaten", true);
		// pthread_mutex_lock(&philo->utils.mutex);
        // philo->utils.statut = EAT;
        set_statut(philo, EAT);
        // philo->info.t_lastmeal = get_time(MILLISECOND);
		set_long(&philo->info.mutex, &philo->info.t_lastmeal, get_time(MILLISECOND));
		usleep(philo->param.t_eat);
		increase_long(&philo->info.mutex, &philo->info.n_meal);
        // philo->info.n_meal++;
		if (get_long(&philo->info.mutex, philo->info.n_meal) >= philo->param.max_meal)
			set_bool(&philo->info.mutex, &philo->info.dead, true);
        // philo->utils.statut = SLEEP;
		set_statut(philo, SLEEP);
		// t_putnbr(YELLOW, philo->id, false, true);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : his sleeping", true);
		usleep(philo->param.t_sleep);
		set_bool(&philo->info.mutex, &philo->info.rdy_to_eat, false);
        // philo->info.rdy_to_eat = false;
		// pthread_mutex_unlock(&philo->utils.mutex);
	}
	else
	{
		// t_putnbr(YELLOW, philo->id, false, true);
		// t_putstr(WHITE, " : ", false);
		// t_putstr(MAGENTA, " : his thinking", true);
		// if (get_statut(philo) != THINK)
		// pthread_mutex_lock(&philo->utils.mutex);
        // philo->utils.statut = THINK;
    	set_statut(philo, THINK);
		usleep(philo->param.t_eat / 2);
		// pthread_mutex_unlock(&philo->utils.mutex);		
	}
}

void	*philo_life(void *in_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)in_philo;
	
	// while (!get_bool(&philo->sync->mutex, philo->sync->all_ready))
	// 	write(1, "", 0);
	philo->info.t_spawn = get_time(MILLISECOND);
	while (!get_bool(&philo->sync->mutex, philo->sync->end))
	{
		life(philo);
		// usleep(200);
	}
	return (NULL);
}