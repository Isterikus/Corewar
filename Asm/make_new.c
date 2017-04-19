/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:39:02 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 17:45:16 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse7(int *i, int *j, int (*temp_len)[3], int fd)
{
	*i = 0;
	*j = 0;
	(*temp_len)[0] = 0;
	(*temp_len)[2] = fd;
}

void	parse8(char *str, int i, int (*temp_len)[3])
{
	int		par;

	par = ft_atoi(str + i);
	wrt_fd((*temp_len)[2], par, 2);
	(*temp_len)[0] += 2;
}

void	put_in_file(char *str, int fd, t_comm comm[100])
{
	int		i;
	int		j;
	int		k;
	int		temp_len[3];

	parse7(&i, &j, &temp_len, fd);
	while (str[i])
	{
		parse1(str, &i, &j, fd);
		parse6(str, &temp_len, j, i);
		k = 0;
		while (k < g_op_tab[j].arg_num)
		{
			if (str[i] == 'r')
				parse3(str, &i, &temp_len);
			else if (str[i] == '%')
				parse2(str + i++, comm, j, &temp_len);
			else if (str[i] == ':')
				parse2(str + i, comm, j, &temp_len);
			else
				parse8(str, i, &temp_len);
			parse5(str, &i, &k);
		}
		comment(str, &i);
	}
}

void	free_com(t_comm (*comm)[100])
{
	int		i;

	i = 0;
	while ((*comm)[i].name != NULL)
	{
		free((*comm)[i].name);
		i++;
	}
}

void	make_new(char *str, char *file)
{
	int		i;
	int		fd;
	t_comm	comm[100];

	i = 0;
	pass(file, &i, '.');
	file[i] = '\0';
	file = ft_strjoin(file, "cor");
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	ft_printf("Writing to %s\n", file);
	free(file);
	(fd < 0) ? error(6) : 0;
	pass_magic(fd);
	i = 0;
	comment(str, &i);
	pass(str, &i, '"');
	pass_next_str(str, i, fd, PROG_NAME_LENGTH);
	pass(str, &i, '"');
	pass(str, &i, '"');
	count_pl(&comm, str, i, fd);
	pass_next_str(str, i, fd, COMMENT_LENGTH);
	pass(str, &i, '"');
	put_in_file(str + i, fd, comm);
	free_com(&comm);
}
