/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:19:04 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 16:05:45 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		ft_and(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				*args;
	int				alw[5];

	ft_alw_init(alw, 30, 30, 2);
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		proc->carry = 0;
		return (-MEM_SIZE);
	}
	acb[2] += 10;
	acb[3] = 3;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	(proc->reg)[args[2]] = args[0] & args[1];
	if ((proc->reg)[args[2]] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	acb[3] = 0;
	free(acb);
	free(args);
	proc->carry = 1;
	return (MEM_SIZE);
}

int		ft_or(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				*args;
	int				alw[5];

	ft_alw_init(alw, 30, 30, 2);
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		proc->carry = 0;
		return (-MEM_SIZE);
	}
	acb[2] += 10;
	acb[3] = 3;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	(proc->reg)[args[2]] = args[0] | args[1];
	if ((proc->reg)[args[2]] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	acb[3] = 0;
	free(acb);
	free(args);
	proc->carry = 1;
	return (MEM_SIZE);
}

int		ft_xor(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				*args;
	int				alw[5];

	ft_alw_init(alw, 30, 30, 2);
	alw[4] = 4;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		return (-MEM_SIZE);
	}
	acb[2] += 10;
	acb[3] = 3;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	(proc->reg)[args[2]] = args[0] | args[1];
	if ((proc->reg)[args[2]] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	acb[3] = 0;
	free(acb);
	free(args);
	proc->carry = 1;
	return (MEM_SIZE);
}

int		ft_zjmp(unsigned char *arena, t_caret *proc)
{
	int		addr;

	addr = ft_get_val(arena, 2, proc->pc + 1);
	if (proc->carry == 1)
	{
		proc->pc += (addr % IDX_MOD);
		while (proc->pc >= MEM_SIZE)
			proc->pc -= MEM_SIZE;
		while ((proc->pc + addr) < 0)
			proc->pc += MEM_SIZE;
	}
	return (MEM_SIZE);
}
