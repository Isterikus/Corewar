/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:31:34 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/18 18:37:23 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	fill_flags(char **argv, t_vm *vm, t_player **players, int i)
{
	int		j;
	int		argc;

	j = i % 10;
	i = i / 10;
	argc = i % 10;
	if (argc == 0)
	{
		argc = 10;
		i--;
	}
	i = i / 10;
	if (!ft_strcmp(argv[i], "-dump") && i + 1 < argc)
		((vm->dump = ft_atoi(argv[i + 1])) == 0) ? error(3) : 0;
	else if (!ft_strcmp(argv[i], "-n") && i + 1 < argc)
		(*players)[j].num = ft_atoi(argv[i + 1]);
	else if (!ft_strcmp(argv[i], "-d"))
		vm->debug = 1;
	else if (!ft_strcmp(argv[i], "-v"))
		vm->vizualize = 1;
	else if (!ft_strcmp(argv[i], "-l"))
		vm->no_live = 1;
}

void	read_champs(int argc, char **argv, t_vm *vm, t_player **players)
{
	int		i;
	int		j;

	*players = (t_player *)malloc(sizeof(t_player) * 4);
	i = 1;
	j = 0;
	while (j < vm->champs)
	{
		(*players)[j].num = NBR_PLAYER - j;
		j++;
	}
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			fill_flags(argv, vm, players, i * 100 + argc * 10 + j);
		else if (!ft_isdigit(argv[i][0]))
			fill_player(vm, argv[i], players, j++);
		i++;
	}
}

void	keys(int key, t_vm *vm)
{
	if (key == SPACE)
	{
		timeout(-1);
		mvprintw(60, 215, "Paused");
		while (wgetch(stdscr) != SPACE)
			;
		mvprintw(60, 215, "      ");
	}
	else if (key == 27)
	{
		key = wgetch(stdscr);
		key = wgetch(stdscr);
		if (key == 68 && vm->sleep - 10 > 0)
			vm->sleep -= vm->sleep / 10;
		if (key == 67 && vm->sleep)
			vm->sleep += vm->sleep / 10;
		key = 0;
	}
	else if (key == 127)
	{
		endwin();
		exit(0);
	}
}

void	create_fir_car(t_caret **carets, t_player *players, int i, int cou)
{
	(*carets) = (t_caret *)malloc(sizeof(t_caret));
	(*carets)->color = i + 1;
	(*carets)->pc = (int)((double)MEM_SIZE *\
		((double)((double)i / (double)cou)));
	if (players[i].num != 0)
		(*carets)->reg[0] = players[i].num;
	else
	{
		players[i].num = NBR_PLAYER - i;
		(*carets)->reg[0] = NBR_PLAYER - i;
	}
	(*carets)->wait = 0;
	(*carets)->live = 0;
	(*carets)->next = NULL;
}

void	create_carets(t_caret **carets, t_player *players, int cou)
{
	int		i;
	t_caret	*temp;

	i = cou - 1;
	create_fir_car(carets, players, i, cou);
	temp = *carets;
	while (--i >= 0)
	{
		temp->next = (t_caret *)malloc(sizeof(t_caret));
		temp->next->color = i + 1;
		temp->next->pc = (int)((double)MEM_SIZE *\
			((double)((double)i / (double)cou)));
		temp->next->wait = 0;
		if (players[i].num != 0)
			temp->next->reg[0] = players[i].num;
		else
			temp->next->reg[0] = NBR_PLAYER - i;
		temp->next->live = 0;
		temp->next->next = NULL;
		temp = temp->next;
	}
}
