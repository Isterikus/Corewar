/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:50:25 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/30 17:22:17 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_dir(char *str, int i)
{
	if (!str[i] || str[i] == '\n')
		return (i);
	if (str[i] != DIRECT_CHAR)
		return (i);
	i++;
	if ((!ft_isdigit(str[i]) && str[i] != '-') && (str[i] != LABEL_CHAR))
		return (i);
	if (str[i++] == LABEL_CHAR)
		while (str[i] != ' ' && str[i] != '\t'
			&& str[i] != ',' && str[i] != '\n')
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])\
				&& str[i] != '_' && str[i] != '-')
				return (i);
			i++;
		}
	else if (str[i - 1] == '-' && !ft_isdigit(str[i]))
		return (i + 1);
	return (0);
}

int		check_idir(char *str, int i)
{
	if (!str[i] || str[i] == '\n')
		return (1);
	if (str[i] == LABEL_CHAR)
	{
		i++;
		while (str[i] != ' ' && str[i] != '\t'
			&& str[i] != ',' && str[i] != '\n')
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])\
				&& str[i] != '_' && str[i] != '-')
				return (i);
			i++;
		}
	}
	else if (ft_isdigit(str[i]) == 0 && str[i] != '-')
		return (1);
	return (0);
}

void	check_arg_dou(int j, int k, char *str, int i)
{
	if (g_op_tab[j].args[k] == (T_REG | T_IND | T_DIR))
	{
		if (check_reg(str, i) && check_dir(str, i) && check_idir(str, i))
			find_line(str, i, "registry/direct/indirect");
	}
	else if (g_op_tab[j].args[k] == (T_REG | T_DIR))
	{
		if (check_reg(str, i) && check_dir(str, i))
			find_line(str, i, "registry/direct");
	}
	else if (g_op_tab[j].args[k] == (T_REG | T_IND))
	{
		if (check_reg(str, i) && check_idir(str, i))
			find_line(str, i, "registry/indirect");
	}
	else if (g_op_tab[j].args[k] == (T_DIR | T_IND))
	{
		if (check_dir(str, i) && check_idir(str, i))
			find_line(str, i, "direct/indirect");
	}
}

void	check_arg(int j, int k, char *str, int i)
{
	if (g_op_tab[j].args[k] == T_REG)
	{
		if (check_reg(str, i))
			find_line(str, check_reg(str, i), "registry");
	}
	else if (g_op_tab[j].args[k] == T_DIR)
	{
		if (check_dir(str, i))
			find_line(str, check_dir(str, i), "direct");
	}
	else if (g_op_tab[j].args[k] == T_IND)
	{
		if (check_idir(str, i))
			find_line(str, i, "indirect");
	}
	else
		check_arg_dou(j, k, str, i);
}

void	pass_arg(char *str, int *i)
{
	while (str[*i] && (ft_isalpha(str[*i]) || ft_isdigit(str[*i]) ||
		str[*i] == '-' || str[*i] == DIRECT_CHAR ||
	str[*i] == LABEL_CHAR || str[*i] == '_') && str[*i] != SEPARATOR_CHAR)
		(*i)++;
	(*i)++;
}
