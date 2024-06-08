/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:00 by tauer             #+#    #+#             */
/*   Updated: 2024/06/08 01:47:44 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

#define DEBUG_MODE 1

#define DISPLAY_MODE 1

//!init
bool	data_init(t_data *data, int argc, char **argv);
void	data_free(t_data *data);

//!getter and setter
void	set_bool(pthread_mutex_t mutex, bool *value, bool to_set);
bool	get_bool(pthread_mutex_t mutex, bool *to_get);
void	increase_long(pthread_mutex_t mutex, long *to_set);

//!utils
bool	ft_atoi(const char *str, long *out_value, bool is_time);
long	get_time(t_metric code);

//!print

void	terror(const char *which_function,const char *error_msg);
void	p_lifetime(t_lifetime lifetime);
void	p_philos(t_philo *philo);
void	loading(bool *ready, long size);

#endif