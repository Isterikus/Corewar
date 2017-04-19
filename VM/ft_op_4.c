/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:02:27 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 16:07:29 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		ft_aff(unsigned char *arena, t_caret *proc)
{
	if ((arena)[proc->pc + 1] != 64 || (arena)[proc->pc + 2] < 1
			|| (arena)[proc->pc + 2] > REG_NUMBER)
		return (-MEM_SIZE);
	write(1, proc->reg + (arena)[proc->pc + 2], 4);
	return (MEM_SIZE);
}

int		ft_long_load_index(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				*args;

	ft_alw_init(alw, 30, 6, 2);
	alw[4] = 2;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
		free(acb);
	if (ft_acb_check(acb, arena, proc->pc, alw))
		return (-MEM_SIZE);
	proc->carry = 0;
	acb[2] += 10;
	acb[3] = 1;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	args[0] = args[0] + args[1];
	while ((proc->pc + args[0]) >= MEM_SIZE)
		args[0] -= MEM_SIZE;
	while ((proc->pc + args[0]) < 0)
		args[0] += MEM_SIZE;
	if (((proc->reg)[args[2]] = ft_get_val(arena, 4, proc->pc + args[0])) == 0)
		proc->carry = 1;
	free(acb);
	free(args);
	return (MEM_SIZE);
}
