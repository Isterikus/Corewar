/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 19:23:15 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/30 17:22:12 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_nc(char *str, int *i, int len)
{
	int		j;

	while (str[*i] == '.' || ft_isalpha(str[*i]))
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	(str[(*i)++] != '"') ? error(3) : 0;
	j = (*i);
	while (str[*i] && ft_isascii(str[*i]) && str[*i] != '"')
		(*i)++;
	(str[*i] != '"') ? error(3) : 0;
	((*i) - j > len) ? error(3) : 0;
	pass(str, i, '\n');
}

int		check_srav(char *str, int i)
{
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == LABEL_CHAR && i > 0 && str[i - 1] != '%')
			return (1);
		i++;
	}
	return (0);
}

void	check_names(char *str, int *i)
{
	comment(str, i);
	name_comm(str, *i, NAME_CMD_STRING);
	check_nc(str, i, PROG_NAME_LENGTH);
	comment(str, i);
	name_comm(str, *i, COMMENT_CMD_STRING);
	check_nc(str, i, COMMENT_LENGTH);
	(!str[*i]) ? error(8) : 0;
	comment(str, i);
}

void	check_err(char *str)
{
	int		i;

	i = 0;
	check_names(str, &i);
	while (str[i])
	{
		if (check_srav(str, i))
		{
			while (str[i] && str[i] != LABEL_CHAR)
			{
				if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
					&& str[i] != '_' && str[i] != '-')
					error(4);
				i++;
			}
			(!str[i]) ? error(4) : 0;
			i += 2;
		}
		check_command(str, &i);
	}
}

int		main(int argc, char const *argv[])
{
	char	*str;
	int		i;

	i = 1;
	str = NULL;
	while (i < argc)
	{
		str = read_s(argv[i]);
		check_err(str);
		make_new(str, (char *)argv[i]);
		free(str);
		i++;
	}
	return (0);
}
