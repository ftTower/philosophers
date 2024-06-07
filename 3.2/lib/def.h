/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:35:04 by tauer             #+#    #+#             */
/*   Updated: 2024/06/06 18:43:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

//? error

t_error	error_mutex(t_table *table, int mutex_error_code, long comp_index,
			long statut);
void	error_catcher(t_error error_code);

//? init

bool	init_table(t_table *table, t_error *error_code, int argc, char **argv);

//? philo

void	*philo_life(void *in_philo);

//? utils

bool	ft_atoi(const char *str, long *out_value, bool is_time);
void	final_table(t_table *table);