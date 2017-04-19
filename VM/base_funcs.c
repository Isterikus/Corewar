/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:22:56 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 15:56:40 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

void			ft_mem_read(void *arena, void *var, int n, int start)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if ((start + i) >= MEM_SIZE)
			start -= MEM_SIZE;
		*((char*)var + n - 1 - i) = *((char*)arena + start + i);
		i++;
	}
}

void			ft_mem_write(void *arena, void *var, int n, int start)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if ((start + i) >= MEM_SIZE)
			start -= MEM_SIZE;
		*((char*)arena + start + i) = *((char*)var + n - 1 - i);
		i++;
	}
}

unsigned char	*ft_read_acb(unsigned char *acb)
{
	unsigned char	*res;
	int				i;

	res = (unsigned char*)malloc(sizeof(*res) * 4);
	res[0] = (*acb & 192) / 64;
	res[1] = (*acb & 48) / 16;
	res[2] = (*acb & 12) / 4;
	res[3] = *acb & 3;
	i = 0;
	while (i < 4)
	{
		if (res[i])
			res[i]++;
		if (res[i] == 4)
			res[i]++;
		i++;
	}
	return (res);
}

int				ft_get_ind(unsigned char *arena, int pc, short addr, int idx)
{
	ft_mem_read(arena, &addr, 2, pc + addr);
	if (idx)
		addr = addr % IDX_MOD;
	while ((pc + addr) >= MEM_SIZE)
		addr -= MEM_SIZE;
	while ((pc + addr) < 0)
		addr += MEM_SIZE;
	return (pc + addr);
}

int				ft_reg_check(unsigned char *arena, int pc, int n)
{
	if ((pc + n) >= MEM_SIZE)
		pc -= MEM_SIZE;
	if ((arena[pc + n] - 1) < 0 || (arena[pc + n] - 1) >= REG_NUMBER)
		return (1);
	else
		return (0);
}
