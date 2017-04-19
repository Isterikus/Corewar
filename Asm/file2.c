/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:48:32 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 15:53:43 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	comment(char *str, int *i)
{
	sp_t(str, i);
	while (str[*i] == COMMENT_CHAR || str[*i] == '\n')
	{
		pass(str, i, '\n');
		sp_t(str, i);
	}
}

void	name_comm(char *str, int i, char *compare)
{
	int		j;

	j = 0;
	while (compare[j])
		if (str[i++] != compare[j++])
			error(3);
}

int		name_comm2(char *str, int i, char *compare)
{
	int		j;

	j = 0;
	while (compare[j])
		if (str[i++] != compare[j++])
			return (0);
	if (str[i] != ' ' && str[i] != '\t')
		return (0);
	return (1);
}

int		find_next(char *str, int i)
{
	comment(str, &i);
	if (!str[i])
		return (1);
	while (ft_isalpha(str[i]) || ft_isdigit(str[i])
		|| str[i] == '-' || str[i] == '_')
		i++;
	if (str[i] == LABEL_CHAR)
		return (1);
	else
		return (0);
}

int		check_reg(char *str, int i)
{
	if (!str[i] || str[i] == '\n')
		return (i);
	if (str[i] != 'r')
		return (i);
	i++;
	if (ft_atoi(str + i) <= 0 || ft_atoi(str + i) > 16)
		return (i);
	return (0);
}
