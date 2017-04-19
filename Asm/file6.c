/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:57:32 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:27:08 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	wrt_fd(int fd, int par, int b)
{
	int		temp;

	if (b == 1)
		write(fd, &par, 1);
	else if (b == 2)
	{
		temp = par >> 8;
		write(fd, &temp, 1);
		write(fd, &par, 1);
	}
	else if (b == 4)
	{
		temp = par >> 24;
		write(fd, &temp, 1);
		temp = par >> 16;
		write(fd, &temp, 1);
		temp = par >> 8;
		write(fd, &temp, 1);
		write(fd, &par, 1);
	}
}

void	pass_link(char *str, int *i)
{
	while (str[*i] != LABEL_CHAR)
		(*i)++;
	(*i)++;
}

void	parse1(char *str, int *i, int *j, int fd)
{
	if (find_next(str, *i))
	{
		pass_link(str, i);
		comment(str, i);
	}
	if (!ft_isalpha(str[*i]))
	{
		pass(str, i, '\n');
		comment(str, i);
	}
	*j = 0;
	while (*j < 16 && !name_comm2(str, *i, g_op_tab[*j].name))
		(*j)++;
	if (*j == 16)
		return ;
	while (ft_isalpha(str[*i]))
		(*i)++;
	sp_t(str, i);
	(*j)++;
	write(fd, j, 1);
	(*j)--;
}

void	parse2(char *str, t_comm comm[100], int j, int (*temp_len)[3])
{
	int		par;
	int		i;

	i = 1;
	(str[0] == ':') ? (i = 0) : 0;
	if (str[1] == ':' || str[0] == ':')
	{
		if (g_op_tab[j].arg_len == 1)
			par = find_dif(str + i + 1, comm, (*temp_len)[1]);
		else
			par = find_dif(str + i + 1, comm, (*temp_len)[1]);
		if (g_op_tab[j].b2_dir == 1 || str[0] == ':')
			wrt_fd((*temp_len)[2], par, 2);
		else
			wrt_fd((*temp_len)[2], par, 4);
	}
	else
	{
		par = ft_atoi(str + i);
		(g_op_tab[j].b2_dir == 1) ? wrt_fd((*temp_len)[2], par, 2)
			: wrt_fd((*temp_len)[2], par, 4);
	}
	(*temp_len)[0] += 2;
	if (g_op_tab[j].b2_dir != 1)
		(*temp_len)[0] += 2;
}

void	parse3(char *str, int *i, int (*temp_len)[3])
{
	int		par;

	(*i)++;
	par = ft_atoi(str + *i);
	write((*temp_len)[2], &par, 1);
	(*temp_len)[0]++;
}
