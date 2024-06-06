/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:17 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 00:07:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_metric
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}					t_metric;

typedef enum e_color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	BG_WHITE,
	BG_GREEN,
	BG_RED,
}						t_color;

typedef enum e_statut
{
	EAT,
	SLEEP,
	THINK,
	DEAD,
	UNSET,
}					t_statut;

typedef struct s_sync
{
	bool			all_ready;
	bool			end;
	long			t_start;
	pthread_mutex_t mutex;
}					t_sync;

typedef struct s_param
{
	long			t_eat;
	long			t_die;
	long			t_sleep;
	long			n_philo;
	long			max_meal;
}					t_param;

typedef struct s_memory
{
	t_statut		statut;
	long			prev_pos;
	long			next_pos;
	pthread_t		thread;
	pthread_mutex_t	mutex;
}					t_memory;

typedef struct s_info
{
	long t_spawn;
	long t_lastmeal;
	long n_meal;
	bool rdy_to_eat;
	bool dead;
	pthread_mutex_t mutex;
}	t_info;

typedef struct s_philo
{
	long			id;
	t_param			param;
	t_memory		utils;
	t_info			info;
	t_sync 			*sync;
}					t_philo;

typedef struct s_monitor
{
	t_philo 		*philos;
	t_param			param;
	t_sync			*sync;
	t_statut		*all_status;
	pthread_t		thread;
}					t_monitor;

typedef struct s_data
{
	t_philo			*philos;
	t_monitor		monitor;
	t_sync 			sync;
}					t_data;

#endif