/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:00 by tauer             #+#    #+#             */
/*   Updated: 2024/05/28 02:09:06 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

#define DEBUG_MODE 1

#define DISPLAY_MODE 1

//?getter and setter
void	increase_long(pthread_mutex_t mutex, long *src);
long	get_long(pthread_mutex_t mutex, long src);
void	set_long(pthread_mutex_t mutex, long *dst, long src);
bool	get_bool(pthread_mutex_t mutex, bool src);
void	set_bool(pthread_mutex_t mutex, bool *dst, bool src);
void	set_statut(t_philo *philo, t_statut src);
t_statut	get_statut(t_philo *philo);

//?init
bool	init_data(t_data *data, char **argv);

//?monitor // philo
void	*philo_life(void *in_philo);
void	*monitor_life(void *in_monitor);

//!printer
void	t_putstr(t_color color, const char *str, bool lignfeed);
void	t_putnbr(t_color color, long value, bool lignfeed, bool format);



//!print
void	debug_philos(t_philo *philos, long size);


//*utils
bool	ft_atoi(const char *str, long *out_value, bool is_time);
long	get_time(t_metric code);


#endif