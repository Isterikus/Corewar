/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:25:10 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/18 18:37:18 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	put_col_car(t_caret *carets, unsigned char col, long int ps)
{
	while (carets != NULL)
	{
		if (carets->pc == ps)
		{
			if (col == 1)
				attron(BCK_BLUE);
			else if (col == 2)
				attron(BCK_RED);
			else if (col == 3)
				attron(BCK_GREEN);
			else if (col == 4)
				attron(BCK_YELLOW);
			else
				attron(BCK_WHITE);
		}
		carets = carets->next;
	}
}

void	ft_print_01(unsigned char field[2][4096], t_player *players, t_vm *vm)
{
	int		i;
	int		j;

	i = 0;
	mvprintw(4, 202, "                   ");
	print_stars();
	print_info(*vm);
	print_players(players, *vm);
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (field[1][64 * i + j] != 0)
				put_color(field[1][64 * i + j]);
			put_col_car(vm->carets, field[1][64 * i + j], 64 * i + j);
			mvprintw(i + 1, j * 3 + 3, "%.2x", field[0][64 * i + j]);
			put_color(0);
			j++;
		}
		i++;
	}
	refresh();
}

void	set_colors(void)
{
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_YELLOW);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void	fill_vm(t_vm *vm)
{
	int		i;

	vm->cycles = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->sleep = 1000;
	vm->last_live = -1;
	vm->no_live = 0;
	i = 0;
	while (i < 4096)
	{
		vm->field[0][i] = 0;
		vm->field[1][i] = 0;
		i++;
	}
}

void	check_size(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col < MIN_WID || w.ws_row < MIN_HEI)
	{
		printf("Too few rows and columns. Our \
visualizer should be launched with:\n");
		ft_printf("Lines = %d\n", MIN_HEI);
		ft_printf("Columns = %d\n", MIN_WID);
		ft_printf("Now you have:\nLines = %d\n", w.ws_row);
		ft_printf("Columns = %d\n", w.ws_col);
		ft_printf("Sorry for the inconvenience\n");
		exit(0);
	}
}
