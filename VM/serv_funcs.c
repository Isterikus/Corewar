/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 17:40:16 by adzikovs          #+#    #+#             */
/*   Updated: 2017/04/19 16:04:07 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

int		*ft_get_args(unsigned char *arena, unsigned char *acb, int pc, int *reg)
{
	int		*res;
	int		i;
	int		carr;
	int		info[2];

	info[0] = (acb[3] % 2) == 0 ? 1 : 0;
	info[1] = (acb[3] % 3) == 0 ? 4 : 2;
	res = (int*)malloc(sizeof(*res) * 3);
	carr = 2;
	i = -1;
	while (++i < 3)
	{
		if ((pc + carr) >= MEM_SIZE)
			pc -= MEM_SIZE;
		if ((acb[i] % 10) == 2)
			res[i] = ((acb[i] / 10) != 1) ? reg[(int)((arena + pc)[carr++]) - 1]
			: (arena + pc)[carr++] - 1;
		else if ((acb[i] % 10) == 3 && (carr += info[1]))
			res[i] = ft_get_val(arena, info[1], pc + carr - info[1]);
		else if ((carr += 2))
			res[i] = ft_get_val(arena, 4, ft_get_ind(arena, pc, carr - 2,
			info[0]));
	}
	return (res);
}

void	ft_alw_init(int *alw, int n1, int n2, int n3)
{
	alw[0] = n1;
	alw[1] = n2;
	alw[2] = n3;
	alw[3] = 0;
	alw[4] = 4;
}

int		ft_acb_check(unsigned char *acb, unsigned char *arena, int pc, int *alw)
{
	int		carr;
	int		i;

	carr = 2;
	i = 0;
	while (acb[i] && i < 4)
	{
		if ((alw[i] % acb[i]) || alw[i] == 0)
			return (1);
		if (acb[i] == 2)
		{
			if (ft_reg_check(arena, pc, carr++))
				return (1);
		}
		else if (acb[i] == 3)
			carr += alw[4];
		else if (acb[i] == 5)
			carr += 2;
		i++;
	}
	while (i++ < 4)
		if (acb[i - 1] || alw[i - 1])
			return (1);
	return (0);
}

int		ft_get_val(unsigned char *arena, int n, int start)
{
	int		res;
	int		i;

	res = 0;
	res = *((char*)(arena + start));
	i = 0;
	while (++i < n)
	{
		if ((start + i) >= MEM_SIZE)
			start -= MEM_SIZE;
		res = res * 256 + *(arena + start + i);
	}
	return (res);
}
