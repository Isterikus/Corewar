/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:33:58 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:32:00 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ret_len(t_caret *car, t_vm *vm)
{
	int		i;
	int		j;
	int		temp;
	int		len;

	i = 12;
	j = 2;
	len = 0;
	while (j < 8)
	{
		temp = (vm->field[0][car->pc + 1] >> j) & 3;
		if (temp == REG_CODE)
			len += 1;
		else if (temp == IND_CODE)
			len += 2;
		else if (g_op_tab[vm->field[0][car->pc] - 1].b2_dir == 1)
			len += 2;
		else if (temp != 0)
			len += 4;
		i = i * 4;
		j = j + 2;
	}
	return (len);
}

void	move_car(t_caret *car, t_vm *vm)
{
	int		pass;
	int		i;

	i = 0;
	pass = 0;
	if (vm->field[0][car->pc] < 1 || vm->field[0][car->pc] > 16)
		return ;
	if (g_op_tab[vm->field[0][car->pc] - 1].arg_len == 1)
		pass = ret_len(car, vm);
	else
		while (i < g_op_tab[vm->field[0][car->pc] - 1].arg_num)
		{
			if (g_op_tab[vm->field[0][car->pc] - 1].args[i] == REG_CODE)
				pass += 1;
			else if (g_op_tab[vm->field[0][car->pc] - 1].args[i] == IND_CODE)
				pass += 2;
			else if (g_op_tab[vm->field[0][car->pc] - 1].b2_dir == 1)
				pass += 2;
			else
				pass += 4;
			i++;
		}
	if (g_op_tab[vm->field[0][car->pc] - 1].arg_len == 1)
		pass++;
	car->pc += pass + 1;
}

void	run_f(t_vm *vm, t_caret *car, t_player **players)
{
	int		ret;

	if (vm->no_live == 0)
		ret = ft_run_op(vm->field, car,\
			vm->vizualize * 10 + vm->champs, players);
	else
		ret = ft_run_op(vm->field, car, 10 + vm->champs, players);
	(ret) ? move_car(car, vm) : 0;
	(ret > 0) ? (vm->last_live = ret) : 0;
	car->wait = 0;
}

void	cycles_in(t_vm *vm, t_player *players)
{
	t_caret	*car;

	car = vm->carets;
	while (car != NULL)
	{
		if (car->wait == -1)
			car->wait = 0;
		else if (vm->field[0][car->pc] > 0 && vm->field[0][car->pc] < 16)
		{
			if (car->wait > 1)
				car->wait--;
			else if (car->wait == 0)
				car->wait = g_op_tab[vm->field[0][car->pc] - 1].cost - 1;
			else if (car->wait == 1)
				run_f(vm, car, &players);
		}
		else
			(car->pc)++;
		(car->pc >= MEM_SIZE) ? car->pc = car->pc - MEM_SIZE : 0;
		car = car->next;
	}
}

void	machine(t_player *players, t_vm *vm)
{
	int		key;

	ft_print_01(vm->field, players, vm);
	usleep(vm->sleep);
	timeout(0);
	key = wgetch(stdscr);
	if (vm->cycles == 0)
		key = SPACE;
	keys(key, vm);
	if (vm->debug == 1)
		while (wgetch(stdscr) != '\n')
			;
}
