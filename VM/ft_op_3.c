/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 11:46:46 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 16:06:51 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		ft_load_index(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				*args;
	int				addr;

	ft_alw_init(alw, 30, 6, 2);
	alw[4] = 2;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		return (-MEM_SIZE);
	}
	acb[2] += 10;
	acb[3] = 2;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	addr = (args[0] + args[1]) % IDX_MOD;
	while ((proc->pc + addr) >= MEM_SIZE)
		addr -= MEM_SIZE;
	while ((proc->pc + addr) < 0)
		addr += MEM_SIZE;
	(proc->reg)[args[2]] = ft_get_val(arena, 4, proc->pc + addr);
	free(acb);
	free(args);
	return (MEM_SIZE);
}

int		ft_store_index(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				*args;
	int				addr;

	ft_alw_init(alw, 2, 30, 6);
	alw[4] = 2;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
		free(acb);
	if (ft_acb_check(acb, arena, proc->pc, alw))
		return (-MEM_SIZE);
	acb[0] += 10;
	acb[3] = 1;
	args = ft_get_args(arena, acb, proc->pc, proc->reg);
	addr = args[1] + args[2];
	addr = addr % IDX_MOD;
	while ((proc->pc + addr) >= MEM_SIZE)
		addr -= MEM_SIZE;
	while ((proc->pc + addr) < 0)
		addr += MEM_SIZE;
	ft_mem_write(arena, proc->reg + args[0], 4, proc->pc + addr);
	free(acb);
	free(args);
	return (proc->pc + addr);
}

int		ft_fork(unsigned char *arena, t_caret *proc)
{
	int		addr;
	int		info[2];

	addr = ft_get_val(arena, 2, proc->pc + 1) % IDX_MOD;
	while ((proc->pc + addr) >= MEM_SIZE)
		addr -= MEM_SIZE;
	while ((proc->pc + addr) < 0)
		addr += MEM_SIZE;
	info[0] = proc->carry;
	info[1] = proc->color;
	ft_clist_pb(proc, proc->reg, addr, info);
	return (MEM_SIZE);
}

int		ft_long_load(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				reg_num;

	ft_alw_init(alw, 15, 2, 0);
	alw[4] = 4;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		return (-MEM_SIZE);
	}
	proc->carry = 0;
	if (acb[0] == 3)
	{
		reg_num = (arena)[proc->pc + 6] - 1;
		ft_mem_read(arena, proc->reg + reg_num, 4, proc->pc + 2);
	}
	else if ((reg_num = (arena)[proc->pc + 4] - 1) >= 0)
		ft_mem_read(arena, proc->reg + reg_num, 4,
			ft_get_ind(arena, proc->pc, 2, 0));
	if ((proc->reg)[reg_num] == 0)
		proc->carry = 1;
	free(acb);
	return (MEM_SIZE);
}

int		ft_long_fork(unsigned char *arena, t_caret *proc)
{
	int		addr;
	int		info[2];

	addr = ft_get_val(arena, 2, proc->pc + 1);
	while ((proc->pc + addr) >= MEM_SIZE)
		addr -= MEM_SIZE;
	while ((proc->pc + addr) < 0)
		addr += MEM_SIZE;
	info[0] = proc->carry;
	info[1] = proc->color;
	ft_clist_pb(proc, proc->reg, addr, info);
	return (MEM_SIZE);
}
