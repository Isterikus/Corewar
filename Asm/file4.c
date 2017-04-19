/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:52:54 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 18:03:04 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_command(char *str, int *i)
{
	int		j;
	int		k;

	while (str[*i] && !find_next(str, *i))
	{
		comment(str, i);
		j = 0;
		while (j < 16 && !name_comm2(str, *i, g_op_tab[j].name))
			j++;
		(j == 16) ? error(5) : 0;
		while (ft_isalpha(str[*i]))
			(*i)++;
		sp_t(str, i);
		k = 0;
		while (k < g_op_tab[j].arg_num)
		{
			check_arg(j, k++, str, *i);
			pass_arg(str, i);
			sp_t(str, i);
		}
	}
	comment(str, i);
}

void	pass_magic(int fd)
{
	int		i;
	int		magic[4];
	int		mg;

	mg = COREWAR_EXEC_MAGIC;
	i = 0;
	while (i < 4)
	{
		magic[i++] = (unsigned char)mg;
		mg >>= 8;
	}
	while (--i >= 0)
		write(fd, &(magic[i]), 1);
}

void	pass_next_str(char *str, int i, int fd, int len)
{
	int		j;
	char	*temp;

	j = i;
	while (str[j] != '"')
		j++;
	temp = ft_strsub(str, i, j - i);
	j = 0;
	while (temp[j])
	{
		write(fd, &(temp[j]), 1);
		j++;
	}
	free(temp);
	while (j < len + 4)
	{
		write(fd, "\0", 1);
		j++;
	}
}

void	count_command(int j, char *str, int *i, int *len)
{
	int		k;

	k = 0;
	while (k < g_op_tab[j].arg_num)
	{
		if (str[*i] == 'r')
			(*len)++;
		else if (str[*i] == '%')
		{
			if (g_op_tab[j].b2_dir == 1)
				(*len) += 2;
			else
				(*len) += 4;
		}
		else
			(*len) += 2;
		k++;
		while (str[*i] && (ft_isalpha(str[*i]) || ft_isdigit(str[*i])
			|| str[*i] == '-' || str[*i] == DIRECT_CHAR ||
		str[*i] == LABEL_CHAR || str[*i] == '_') && str[*i] != SEPARATOR_CHAR)
			(*i)++;
		(*i)++;
		sp_t(str, i);
	}
}

void	count_len(char *str, int *i, int *len)
{
	int		j;

	while (!find_next(str, *i))
	{
		comment(str, i);
		j = 0;
		while (j < 16 && !name_comm2(str, *i, g_op_tab[j].name))
			j++;
		while (ft_isalpha(str[*i]))
			(*i)++;
		sp_t(str, i);
		(*len)++;
		if (g_op_tab[j].arg_len == 1)
			(*len)++;
		count_command(j, str, i, len);
	}
}
