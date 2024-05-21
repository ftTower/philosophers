/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 00:08:00 by tauer             #+#    #+#             */
/*   Updated: 2024/05/20 00:31:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H


//! routine
void	*monitor_routine(void *in_data);
void	*routine(void *data);

//? getter and setter
void	set_bool(t_data *data, mtx *mutex, bool *dest, bool value);
bool	get_bool(t_data *data, mtx *mutex, bool *value);
void	set_long(t_data *data, mtx *mutex, long *dest, long value);
bool	get_long(t_data *data, mtx *mutex, long *value);
void	increase_long(t_data *data, mtx *mutex, long *value);

//*init
bool	setup(t_data *data, char **argv);

//*handler
void	s_exit(t_data *data, int exit_statut);
void	*s_malloc(t_data *data, size_t size);
void	thread_handler(t_data *data, t_philo *philo, pthread_t *monitor_thread, t_thread code);
void	mutex_handler(t_data *data, mtx *mutex, t_thread code);

//* syncronise
void	wait_threads(t_data *data);
bool	all_threads_running(t_data *data);
bool	end(t_data *data);

//!life
bool	philo_died(t_philo *philo);

//*print
void	print_statut(t_statut code, t_data *data, t_philo *philo, bool subject_print);
void	print_data(t_data *data);

//*utils
bool	ft_atoi(const char *str, long *out_value);
long	get_time(t_data *data, t_metric code);
void	t_usleep(long usec, t_data *data);

#endif