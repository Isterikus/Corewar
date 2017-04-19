/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 12:15:08 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/18 18:48:23 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		live(unsigned char *arena, t_caret *proc, int vz, t_player **players)
{
	int		i;
	int		j;

	i = ft_get_val(arena, 4, proc->pc + 1);
	j = 0;
	proc->live++;
	while (j < (vz % 10))
	{
		if (i == (*players)[j].num)
		{
			((*players)[j].lives)++;
			if (vz / 10 == 0)
			{
				ft_printf("A process shows that player %d", (*players)[j].num);
				ft_printf(" (%s) is alive\n", (*players)[j].name);
			}
			return (j + 1);
		}
		j++;
	}
	return (1);
}

t_ops	*ft_op_arr_init(void)
{
	t_ops	*res;

	res = (t_ops*)malloc(sizeof(*res) * 16);
	res[0] = &ft_load;
	res[1] = &ft_load;
	res[2] = &ft_store;
	res[3] = &ft_add;
	res[4] = &ft_sub;
	res[5] = &ft_and;
	res[6] = &ft_or;
	res[7] = &ft_xor;
	res[8] = &ft_zjmp;
	res[9] = &ft_load_index;
	res[10] = &ft_store_index;
	res[11] = &ft_fork;
	res[12] = &ft_long_load;
	res[13] = &ft_long_load_index;
	res[14] = &ft_long_fork;
	res[15] = &ft_aff;
	return (res);
}

int		ft_change_color(unsigned char *arena, int ret, t_caret *proc)
{
	int		i;

	if (ret >= 0 && ret < MEM_SIZE)
	{
		i = 0;
		while (i < 4)
		{
			if ((ret + i) >= MEM_SIZE)
				ret -= MEM_SIZE;
			arena[ret + i++] = proc->color;
		}
	}
	return (0);
}

int		ft_run_op(unsigned char arena[2][4096], t_caret *proc,
			int vz, t_player **players)
{
	t_ops	*op;
	int		ret[2];

	ret[0] = -1;
	op = ft_op_arr_init();
	if ((arena)[0][proc->pc] == 0x09 && proc->carry == 1)
		ret[0] = 0;
	if ((arena)[0][proc->pc] == 1)
		ret[0] = live(arena[0], proc, vz, players);
	else
	{
		ret[1] = op[(int)((arena)[0][proc->pc]) - 1](arena[0], proc);
		ft_change_color(arena[1], ret[1], proc);
	}
	free(op);
	return (ret[0]);
}
