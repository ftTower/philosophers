/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:31:45 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 01:03:28 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFE_H
# define DEFE_H

typedef enum e_clr
{
	WH_BL,
	WH_RE,
	BLUE,
	RED_,
	WHITE,
	BLACK,
	GREEN,
	CLEAR,
}		t_clr;

typedef enum e_cmd {
	INIT,
	CREATE,
	JOIN,
} t_cmd;

//! setup data
void	null_data(t_data *data);
bool	set_param(t_data *data, char **argv);

//!setup philo
bool	philo_maker(t_data *data);

//!setup fork
bool	fork_maker(t_data *data);

//! utils utils
void	print_data(t_data *data);

//! process thread
void	thread_handler(pthread_t *thread, void *(*foo)(void *) ,t_cmd code);

//!printer
void	tprint(char *msg, long num, bool is_num ,t_clr clr_code);
void	print_sclr(char *to_print, t_clr clr_code, bool lignfeed);
void	print_dclr(long to_print, t_clr clr_code, bool lignfeed);

#endif