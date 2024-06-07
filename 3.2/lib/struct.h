/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:35:16 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 19:35:36 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

typedef enum e_error
{
	SUCCES,
	NB_ARGC,
	ERR_ARGV,
	MALLOC_PHILO,
	MALLOC_FORK,
	MUTEX_EAGAIN,
	MUTEX_EBUSY,
	MUTEX_EINVAL,
	MUTEX_EFAULT,
	THREAD_JOIN,
}					t_error;

typedef struct s_arg
{
	long			time_eat;
	long			time_die;
	long			time_sleep;
	long			nb_philos;
	long			max_meals;
}					t_arg;

typedef struct s_philosopher
{
	long			id;
	long			left_fork;
	long			right_fork;
	struct s_table	*table;
	pthread_mutex_t	mutex;
	pthread_t		thread;
}					t_philosopher;

typedef struct s_table
{
	bool			everyone_ready;
	pthread_mutex_t	*forks;
	t_philosopher	*philos;
	t_arg			arg;
	pthread_mutex_t	mutex_sync;
	pthread_mutex_t	mutex_write;
}					t_table;
