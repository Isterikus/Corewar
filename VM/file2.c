/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:23:12 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/30 17:36:58 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_dots(char *str, int i)
{
	str[i] = '.';
	str[i + 1] = '.';
	str[i + 2] = '.';
	str[i + 3] = '\0';
}

void	get_rid_from_n(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n')
			(*str)[i] = ' ';
		i++;
	}
}

void	print_comm(t_player *players, int i)
{
	if (ft_strlen(players[i].comment) > 37)
	{
		mvprintw(16 + i * 5, 203, "%.37s", players[i].comment);
		if (ft_strlen(players[i].comment) > 74)
			get_dots(players[i].comment, 71);
		mvprintw(17 + i * 5, 203, "%s", players[i].comment + 37);
	}
	else
		mvprintw(16 + i * 5, 203, players[i].comment);
}

void	print_players(t_player *players, t_vm vm)
{
	int		i;

	i = 0;
	while (i < vm.champs)
	{
		get_rid_from_n(&(players[i].name));
		get_rid_from_n(&(players[i].comment));
		mvprintw(15 + i * 5, 202, "Player %d:", i + 1);
		attron(COLOR_PAIR(i + 1));
		if (ft_strlen(players[i].name) > 28)
			get_dots(players[i].name, 25);
		mvprintw(15 + i * 5, 212, players[i].name);
		attron(COLOR_PAIR(5));
		print_comm(players, i);
		mvprintw(18 + i * 5, 227, "            ");
		mvprintw(18 + i * 5, 202, "Lives in current period = %d",\
			players[i].lives);
		i++;
	}
	mvprintw(11, 202, "Process = %d", count_process(vm.carets));
}

void	print_info(t_vm vm)
{
	mvprintw(3, 202, "                   ");
	mvprintw(7, 202, "                   ");
	mvprintw(3, 202, "Slow: %d", vm.sleep);
	mvprintw(5, 202, "Cycles: %d", vm.cycles);
	mvprintw(7, 202, "Cycles to die: %d", vm.cycles_to_die);
	mvprintw(9, 202, "Cycle delta: %d", CYCLE_DELTA);
}
