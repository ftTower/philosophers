/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:17 by tauer             #+#    #+#             */
/*   Updated: 2024/05/22 02:29:31 by tauer            ###   ########.fr       */
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

typedef enum e_metric
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_metric;
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
	long			t_meal;
	long			t_spawn;
	pthread_mutex_t mutex;
}	t_statut;

typedef struct s_sync
{
	long	n_threads;
	long	t_simulation;
	bool	*ready;
	bool	all_ready;
	bool	end;
	pthread_mutex_t mutex;
	pthread_mutex_t write_mutex;
}	t_sync;

typedef struct s_philo
{
	long			id;
	t_lifetime		lifetime;
	t_statut		statut;
	t_fork			first_fork;
	t_fork			*second_fork;
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