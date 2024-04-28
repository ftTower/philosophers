/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:03:59 by tauer             #+#    #+#             */
/*   Updated: 2024/04/27 21:15:20 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

// pthread_create();
// pthread_join();

void	thread_handler(pthread_t *thread, void *(*foo)(void *) ,t_cmd code)
{
	if (code == CREATE)
		pthread_create(thread, NULL, foo, NULL);
}
