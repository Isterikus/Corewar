/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clist_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:13:45 by adzikovs          #+#    #+#             */
/*   Updated: 2017/03/27 17:46:46 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libop.h"

t_caret	*ft_create_proc(int *reg, int pc, int info[2])
{
	t_caret	*res;
	int		i;

	res = (t_caret*)malloc(sizeof(*res));
	if (reg)
	{
		i = 0;
		while (i < REG_NUMBER)
		{
			(res->reg)[i] = reg[i];
			i++;
		}
	}
	res->pc = pc;
	res->wait = -1;
	res->live = 0;
	res->carry = info[0];
	res->color = info[1];
	res->next = NULL;
	return (res);
}

void	ft_clist_pb(t_caret *begin, int *reg, int pc, int info[2])
{
	t_caret	*temp;

	temp = begin;
	while (temp->next != NULL)
		temp = temp->next;
	pc = begin->pc + pc;
	if (pc < 0)
		pc += MEM_SIZE;
	else if (pc >= MEM_SIZE)
		pc -= MEM_SIZE;
	temp->next = ft_create_proc(reg, pc, info);
}

void	ft_clist_delone(t_caret **begin, int n)
{
	t_caret	*temp;

	while (n-- > 0 && (*begin)->next)
		begin = &((*begin)->next);
	temp = (*begin)->next;
	if (*begin)
		free(*begin);
	*begin = temp;
}

void	ft_clist_del(t_caret **begin)
{
	t_caret	*temp;

	while (*begin)
	{
		temp = (*begin)->next;
		free(*begin);
		*begin = temp;
	}
}
