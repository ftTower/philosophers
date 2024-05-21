/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:17 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 00:38:54 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef pthread_mutex_t	mtx;
typedef struct s_data	t_data;

typedef enum e_color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
}						t_color;

typedef enum e_thread
{
	T_CREATE,
	T_MONITOR_CREATE,
	T_JOIN,
	M_INIT,
	M_LOCK,
	M_UNLOCK,
	M_DESTROY,
}						t_thread;

typedef enum e_statut
{
	EAT,
	SLEEP,
	THINK,
	L_FORK,
	R_FORK,
	DEAD,
}						t_statut;

typedef enum e_metric
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_metric;

typedef struct s_fork
{
	long				id;
	pthread_mutex_t		fork;
}						t_fork;

typedef struct s_philo
{
	long				id;
	long				t_meal;
	long				n_meal;
	bool				dead;
	pthread_t			thread;
	t_fork				l_fork;
	t_fork				*r_fork;
	mtx					philo;
	t_data				*data;
}						t_philo;

struct					s_data
{
	long				n_threads;
	long				n_philo;
	long				n_meal;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				t_simulation;
	bool				b_end;
	bool				b_ready;
	mtx					table;
	mtx					write;
	pthread_t			monitor;
	t_philo				*philo;
	t_fork				*fork;
};

extern t_data data; // Declare 'data' as extern

#endif