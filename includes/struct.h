/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:47:20 by tauer             #+#    #+#             */
/*   Updated: 2024/04/30 02:14:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

# define CLR "\033c"
// # define CLR ""
# define RST "\033[0m"
# define RED "\033[1;31m"
# define BLU "\033[1;34m"
# define WHI "\033[1;255m"
# define BLA "\033[1;59m"
# define GRE "\033[1;32m"

typedef pthread_mutex_t t_mtx;

typedef enum e_statut
{
	EATING,
	SLEEPING,
	THINKIN,
	UNASIGNED,
}	t_statut;

typedef struct s_fork
{
	t_mtx	id;
	long	 pos;
	struct s_fork	*next;
}					t_fork;

typedef struct s_philo
{
	long			pos;
	long			last_meal;
	bool			is_full;
	long			left_fork;
	long			right_fork;
	t_statut		statut;
	pthread_t		id;
	struct s_philo	*next;
}					t_philo;

typedef struct s_param
{
	long			number_philo;
	long			number_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
}					t_param;

typedef struct s_stat
{
	long	memory_allocated;
} t_stat;
typedef struct s_data
{
	t_fork			*fork;
	t_philo			*philo;
	t_stat			stat;
	t_param			param;
}					t_data;

#endif
