/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:56:13 by tauer             #+#    #+#             */
/*   Updated: 2024/04/29 15:15:58 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

void	print_dclr(long to_print, t_clr clr_code, bool lignfeed)
{
	if (clr_code == CLEAR)
		printf(CLR "");
	else if (clr_code == RED_)
		printf(RED "%ld" RST, to_print);
	else if (clr_code == BLUE)
		printf(BLU "%ld" RST, to_print);
	else if (clr_code == BLACK)
		printf(BLA "%ld" RST, to_print);
	else if (clr_code == WHITE)
		printf(WHI "%ld" RST, to_print);
	else if (clr_code == RE_WH)
		printf(WHI "%ld\n" RST, to_print);
	else if (clr_code == WH_BL)
		printf(BLU "%ld" RST, to_print);
	else if (clr_code == GREEN)
		printf(GRE "%ld" RST, to_print);
	else if (clr_code == WH_RE)
		printf(RED "%ld" RST, to_print);
	if (lignfeed)
		printf("\n");
}

void	print_sclr(char *to_print, t_clr clr_code, bool lignfeed)
{
	if (clr_code == CLEAR)
		printf(CLR "");
	else if (clr_code == RED_)
		printf(RED "%s" RST, to_print);
	else if (clr_code == BLUE)
		printf(BLU "%s" RST, to_print);
	else if (clr_code == BLACK)
		printf(BLA "%s" RST, to_print);
	else if (clr_code == WHITE)
		printf(WHI "%s" RST, to_print);
	else if (clr_code == GREEN)
		printf(GRE "%s" RST, to_print);
	else if (clr_code == RE_WH)
		printf(RED "\n❌ %s" RST, to_print);
	else if (clr_code == WH_BL || clr_code == WH_RE)
		printf(WHI "%s" RST, to_print);
	if (lignfeed)
		printf("\n");
}

void	tprint(char *msg, long num, bool is_num, t_clr clr_code)
{
	if (msg && is_num)
		print_sclr(msg, clr_code, false);
	else if (msg && !is_num)
		print_sclr(msg, clr_code, true);
	if (is_num)
		print_dclr(num, clr_code, true);
}
