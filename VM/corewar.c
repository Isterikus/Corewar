/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:09:09 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:32:34 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libop.h"

/*
**		Starting from 1;
**		CHECK CUROSOUR pc = printf("\033[%02d;%02dH", HEIGHT, WIDTH);
**
**		GET WIN SIZE
**		#include <sys/ioctl.h>
**		#include <stdio.h>
**		#include <unistd.h>
**		struct winsize w;
**		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
**
**		printf ("lines %d\n", w.ws_row);
**		printf ("columns %d\n", w.ws_col);
**
**
**		mvprintw(HEIGHT, WIDTH, "*");
**
**		|1 000 000 microsecond == 1 second|
*/

void	print_now(t_vm vm)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("0x");
	while (i < 64)
	{
		j = 0;
		ft_printf("%#.4x : ", i * 64 + j);
		while (j < 64)
		{
			ft_printf("%.2x ", vm.field[0][64 * i + j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	exit(0);
}

void	rm_pl(t_player **players, int len)
{
	int		i;

	i = 0;
	while (i < len)
		(*players)[i++].lives = 0;
}

int		cycle(t_player *players, t_vm *vm)
{
	int		ctd_f;

	ctd_f = 0;
	while (1)
	{
		if (vm->vizualize == 1)
			machine(players, vm);
		cycles_in(vm, players);
		vm->cycles++;
		if (vm->dump > 0 && vm->dump == vm->cycles)
			print_now(*vm);
		if (vm->vizualize == 1)
			refresh();
		if (vm->cycles - ctd_f == vm->cycles_to_die)
		{
			ft_edit_cycle_to_die(vm->carets, &(vm->cycles_to_die));
			ctd_f = vm->cycles;
			if (vm->cycles_to_die <= 0 || (ft_live(&(vm->carets))))
				return (vm->last_live);
			rm_pl(&players, vm->champs);
		}
	}
	return (1);
}

void	out_info(t_player *players, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_printf("Player {bold}%d{eoc}, weighing ", i + 1);
		ft_printf("{underlined}%d{eoc} bytes\n", players[i].prog_size);
		ft_printf("Name : %s\n", players[i].name);
		ft_printf("Comment : %s\n", players[i].comment);
		if (i + 1 != len)
			ft_printf("\n");
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_player		*players;
	t_vm			vm;
	int				winer;

	(argc == 1) ? error(0) : 0;
	vm.champs = check_champs(argc, argv);
	fill_vm(&vm);
	read_champs(argc, argv, &vm, &players);
	create_carets(&(vm.carets), players, vm.champs);
	if (vm.vizualize == 1)
		start_viz();
	else
		out_info(players, vm.champs);
	winer = cycle(players, &vm);
	if (vm.vizualize == 1)
		endwin();
	winners(vm.champs, winer, players);
	return (0);
}
