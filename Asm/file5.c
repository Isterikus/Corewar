/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:55:47 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 18:02:50 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		srav(char *str, int i)
{
	while (str[i] && str[i] != '\n' && str[i] != LABEL_CHAR)
		i++;
	if (str[i] == LABEL_CHAR && i > 0 && str[i - 1] != '%')
		return (1);
	else
		return (0);
}

int		fill_arr(char *str, int i, int *len, t_comm (*comm)[100])
{
	int		j;

	j = 0;
	while (str[i])
	{
		if (srav(str, i))
		{
			(*comm)[j].name = ft_strsub(str, i,
				ft_strchr(str + i, LABEL_CHAR) - (str + i));
			(*comm)[j].place = *len;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\n')
				i++;
			j++;
		}
		count_len(str, &i, len);
		comment(str, &i);
	}
	return (j);
}

int		count_pl(t_comm (*comm)[100], char *str, int i, int fd)
{
	int		j;
	int		len;

	len = 0;
	pass(str, &i, '"');
	comment(str, &i);
	j = fill_arr(str, i, &len, comm);
	while (j < 100)
	{
		(*comm)[j].name = NULL;
		(*comm)[j].place = 0;
		j++;
	}
	wrt_fd(fd, len, 4);
	return (j);
}

int		count_comm_len(char *str, int i, int j)
{
	int				k;
	unsigned char	len;
	int				num;

	k = 0;
	len = 0;
	num = 3;
	while (k < g_op_tab[j].arg_num)
	{
		if (str[i] == 'r')
			len += 1 << (num * 2);
		else if (str[i] == '%')
			len += 2 << (num * 2);
		else
			len += 3 << (num * 2);
		num--;
		k++;
		while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '-' || str[i] == DIRECT_CHAR ||
			str[i] == LABEL_CHAR || str[i] == '_') && str[i] != SEPARATOR_CHAR)
			i++;
		i++;
		sp_t(str, &i);
	}
	return (len);
}

int		find_dif(char *str, t_comm comm[100], int temp_len)
{
	int		i;
	int		k;
	char	*name;

	i = 0;
	k = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_' || str[i] == '-')
		i++;
	name = ft_strsub(str, 0, i);
	while (comm[k].name != NULL && ft_strcmp(comm[k].name, name))
		k++;
	free(name);
	if (comm[k].name == NULL)
	{
		ft_printf("Invalid label: \"%s\"\n", name);
		exit(0);
	}
	return (comm[k].place - temp_len);
}
