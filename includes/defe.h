/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:31:45 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 17:14:57 by tauer            ###   ########.fr       */
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
}		t_clr;

typedef enum e_cmd
{
	INIT,
	CREATE,
	JOIN,
	DESTROY,
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
void	thread_handler(t_data *data, long pos, void *(*foo)(void *), t_cmd code);

//! printer
void	tprint(char *msg, long num, bool is_num, t_clr clr_code);
void	print_sclr(char *to_print, t_clr clr_code, bool lignfeed);
void	print_dclr(long to_print, t_clr clr_code, bool lignfeed);

//? print
void	print_table(t_data *data);
void	print_philo(t_data *data, bool got_fork, bool need_clear);


//! setter
bool	philo_bool_setter(t_data *data, long pos, t_set which_code, bool to_set);
bool	philo_long_setter(t_data *data, long pos, t_set which_code, long to_set);
bool	fork_bool_setter(t_data *data, long pos, t_set which_code, bool to_set);
bool	fork_long_setter(t_data *data, long pos, t_set which_code, long to_set);
t_philo	*philo_getter(t_data *data, long pos);

//* routine
void*	routine(void *test);

//! exit
void	texit(t_data *data, bool exit_succes);


#endif