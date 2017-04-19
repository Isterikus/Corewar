/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 13:35:43 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 16:05:27 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		ft_load(unsigned char *arena, t_caret *proc)
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
	if (acb[0] == 3 && (reg_num = (arena)[proc->pc + 6] - 1) >= 0)
		ft_mem_read(arena, (proc->reg + reg_num), 4, (proc->pc + 2));
	else if ((reg_num = (arena)[proc->pc + 4] - 1) >= 0)
		ft_mem_read(arena, proc->reg + reg_num, 4,
			ft_get_ind(arena, proc->pc, 2, 1));
	if ((proc->reg)[reg_num] == 0)
		proc->carry = 1;
	free(acb);
	return (MEM_SIZE);
}

int		ft_store(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				arg1;
	int				arg2;

	acb = ft_read_acb(arena + proc->pc + 1);
	ft_alw_init(alw, 2, 10, 0);
	alw[4] = 4;
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		return (-MEM_SIZE);
	}
	arg1 = ft_get_val(arena, 1, proc->pc + 2) - 1;
	if (acb[1] == 2 && (arg2 = ft_get_val(arena, 1, proc->pc + 3) - 1) >= 0)
		(proc->reg)[arg2] = (proc->reg)[arg1];
	else if ((arg2 = ft_get_ind(arena, proc->pc, 3, 1)) >= 0)
	{
		ft_mem_write(arena, proc->reg + arg1, 4, arg2);
		free(acb);
		return (arg2);
	}
	free(acb);
	return (MEM_SIZE);
}

int		ft_add(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				r1;
	int				r2;
	int				r3;

	ft_alw_init(alw, 2, 2, 2);
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		proc->carry = 0;
		return (-MEM_SIZE);
	}
	r1 = (arena)[proc->pc + 2] - 1;
	r2 = (arena)[proc->pc + 3] - 1;
	r3 = (arena)[proc->pc + 4] - 1;
	(proc->reg)[r3] = (proc->reg)[r1] + (proc->reg)[r2];
	if ((proc->reg)[r3] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	free(acb);
	proc->carry = 1;
	return (MEM_SIZE);
}

int		ft_sub(unsigned char *arena, t_caret *proc)
{
	unsigned char	*acb;
	int				alw[5];
	int				r1;
	int				r2;
	int				r3;

	ft_alw_init(alw, 2, 2, 2);
	alw[4] = 4;
	acb = ft_read_acb(arena + proc->pc + 1);
	if (ft_acb_check(acb, arena, proc->pc, alw))
	{
		free(acb);
		return (-MEM_SIZE);
	}
	r1 = (arena)[proc->pc + 2] - 1;
	r2 = (arena)[proc->pc + 3] - 1;
	r3 = (arena)[proc->pc + 4] - 1;
	(proc->reg)[r3] = (proc->reg)[r1] - (proc->reg)[r2];
	if ((proc->reg)[r3] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	free(acb);
	proc->carry = 1;
	return (MEM_SIZE);
}
