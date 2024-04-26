/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:47:20 by tauer             #+#    #+#             */
/*   Updated: 2024/04/25 21:15:45 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef DEF_H
# define DEF_H

typedef	struct s_fork
{
	
}	t_fork;

typedef struct s_philo
{
	
	
}	t_philo;

typedef struct s_param
{
	long number_philo;
	long number_eat;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
}	t_param;

typedef struct s_data
{
	t_philo *philo;
	t_param param;
}	t_data;

#endif
