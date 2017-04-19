/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 12:42:56 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/30 12:42:48 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse4(char *str, int *i, int (*temp_len)[3])
{
	int		par;

	(*i)++;
	par = ft_atoi(str + *i);
	write((*temp_len)[2], &par, 1);
	(*temp_len)[0]++;
}

void	parse5(char *str, int *i, int *k)
{
	while (str[*i] && (ft_isalpha(str[*i]) || ft_isdigit(str[*i])
		|| str[*i] == '-' || str[*i] == DIRECT_CHAR
	|| str[*i] == LABEL_CHAR || str[*i] == '_') && str[*i] != SEPARATOR_CHAR)
		(*i)++;
	(*i)++;
	sp_t(str, i);
	(*k)++;
}

void	parse6(char *str, int (*temp_len)[3], int j, int i)
{
	int		k;

	(*temp_len)[1] = (*temp_len)[0];
	(*temp_len)[0]++;
	if (g_op_tab[j].arg_len == 1)
	{
		k = count_comm_len(str, i, j);
		write((*temp_len)[2], &k, 1);
		(*temp_len)[0]++;
	}
}
