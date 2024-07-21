/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 23:38:30 by tauer             #+#    #+#             */
/*   Updated: 2024/07/21 14:58:56 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	t_putstr(t_color color, const char *str, bool lignfeed)
{
	const char	*colors[] = {
		"\033[38;5;196m",
		"\033[38;5;46m",
		"\033[38;5;226m",
		"\033[38;5;21m",
		"\033[38;5;201m",
		"\033[38;5;51m",
		"\033[38;5;15m",
		"\033[48;5;15m",
		"\033[48;5;46m",
		"\033[48;5;196m",
	};

	printf("%s%s\033[0m", colors[color], str);
	if (lignfeed)
		printf("\n");
}

void	t_putnbr(t_color color, long value, bool lignfeed, bool format)
{
	const char	*colors[] = {
		"\033[38;5;196m",
		"\033[38;5;46m",
		"\033[38;5;226m",
		"\033[38;5;21m",
		"\033[38;5;201m",
		"\033[38;5;51m",
		"\033[38;5;15m",
		"\033[48;5;15m",
		"\033[48;5;46m",
		"\033[48;5;196m",
	};

	if (format)
		printf("%s%-5ld\033[0m", colors[color], value);
	else
		printf("%s%-3ld\033[0m", colors[color], value);
	if (lignfeed)
		printf("\n");
}
