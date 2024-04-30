/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:31:45 by tauer             #+#    #+#             */
/*   Updated: 2024/05/01 00:58:39 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFE_H
# define DEFE_H


typedef enum e_clr
{
	WH_BL,
	WH_RE,
	RE_WH,
	BLUE,
	RED_,
	WHITE,
	BLACK,
	GREEN,
	CLEAR,
	YELLOW,
}		t_clr;

typedef enum e_cmd
{
	INIT,
	CREATE,
	JOIN,
	DESTROY,
	PRINT_SIMULATION,
	PRINT_P_INFO,
	PRINT_F_INFO,
}		t_cmd;

typedef enum e_set
{
	FULL,
	POS,
	LAST_MEAL,
	LEFT_FORK,
	RIGHT_FORK,
}		t_set;

//! setup data
void	null_data(t_data *data);
bool	set_param(t_data *data, char **argv);

//! setup philo
bool	philo_maker(t_data *data);
void	thread_maker(t_data *data);

//! setup fork
bool	fork_maker(t_data *data);

//! utils utils
void	print_data(t_data *data);

//! process thread
void	thread_handler(t_data *data, long pos, void *(*foo)(void *),
			t_cmd code);

//! printer
void	tprint(char *msg, long num, bool is_num, t_clr clr_code);
void	print_sclr(char *to_print, t_clr clr_code, bool lignfeed);
void	print_dclr(long to_print, t_clr clr_code, bool lignfeed);

//? print
void	print_table(t_data *data);
void	print_philo(t_data *data, bool need_clear, bool need_sleep, t_cmd code);

//! setter
bool	philo_bool_setter(t_data *data, long pos, t_set which_code,
			bool to_set);
bool	philo_long_setter(t_data *data, long pos, t_set which_code,
			long to_set);
bool	fork_bool_setter(t_data *data, long pos, t_set which_code, bool to_set);
bool	fork_long_setter(t_data *data, long pos, t_set which_code, long to_set);
bool	philo_statut_setter(t_data *data, long pos, t_statut statut);

//! simulation
void	simulation(t_data *data);

//* routine
void	*routine(void *data);

//! exit
void	texit(t_data *data, bool exit_succes);

#endif