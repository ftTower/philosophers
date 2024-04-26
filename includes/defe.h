/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:31:45 by tauer             #+#    #+#             */
/*   Updated: 2024/04/26 02:26:02 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFE_H
# define DEFE_H

//! setup data
void	null_data(t_data *data);
bool	set_param(t_data *data, char **argv);

//! utils utils
void	print_data(t_data *data);

#endif