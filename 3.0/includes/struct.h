/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:17 by tauer             #+#    #+#             */
/*   Updated: 2024/05/21 02:25:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_statut_code
{
	L_FORK,
	R_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	UNASSIGNED,
}		t_statut_code;

typedef struct s_lifetime
{
	long			t_eat;
	long			t_die;
	long			t_sleep;
	long			n_philo;
	long			max_meal;
}					t_lifetime;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	long			id;
}					t_fork;

typedef struct s_statut
{
	t_statut_code statut;
	long			n_meal;
	pthread_mutex_t mutex;
}	t_statut;

typedef struct s_sync
{
	long	n_threads;
	bool	*ready;
}	t_sync;

typedef struct s_philo
{
	long			id;
	t_lifetime		lifetime;
	t_statut		statut;
	t_fork			first_fork;
	t_fork			second_fork;
	t_sync			*sync;
	pthread_t		thread;
	pthread_mutex_t mutex;
}					t_philo;


typedef struct s_data
{
	t_lifetime		lifetime;
	t_sync			sync;
	t_philo			*philos;
	t_fork			*forks;
}	t_data;

#endif