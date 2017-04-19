/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:28:50 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:29:18 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_champs(int argc, char **argv)
{
	int		i;
	int		j;
	int		count;
	char	*temp;

	i = 0;
	count = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && (argv[i][1] && !ft_isdigit(argv[i][1])))
		{
			j = 0;
			while (argv[i][j])
				j++;
			temp = ft_strsub(argv[i], j - 4, 4);
			if (ft_strcmp(temp, ".cor") != 0)
			{
				free(temp);
				error(1);
			}
			free(temp);
			count++;
		}
	(count > 4) ? error(2) : 0;
	(count == 0) ? error(0) : 0;
	return (count);
}

int		get_num(unsigned char *str)
{
	int		magic;

	magic = str[0] << 24;
	magic += str[1] << 16;
	magic += str[2] << 8;
	magic += str[3];
	return (magic);
}

void	fill_name(unsigned char *str, t_player **players, int j)
{
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	(i == 0) ? error(14) : 0;
	(i > PROG_NAME_LENGTH) ? error(8) : 0;
	(*players)[j].name = ft_strsub((char *)str, 0, i);
	i = PROG_NAME_LENGTH + 8;
	while (str[i] != 0)
		i++;
	(i == 0) ? error(14) : 0;
	(i > COMMENT_LENGTH + PROG_NAME_LENGTH + 8) ? error(9) : 0;
	(*players)[j].comment = ft_strsub((char *)str, PROG_NAME_LENGTH + 8, i);
}

void	fill_field(t_vm *vm, int size, unsigned char *str, int j)
{
	int		i;
	int		start;

	i = 0;
	start = MEM_SIZE * ((double)((double)j / (double)vm->champs));
	str += PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
	(!str[i]) ? error(12) : 0;
	while (i < size)
	{
		if (i > CHAMP_MAX_SIZE)
			error(13);
		vm->field[0][start + i] = str[i];
		vm->field[1][start + i] = j + 1;
		i++;
	}
}

void	fill_player(t_vm *vm, char *file, t_player **players, int j)
{
	unsigned char	*str;
	int				fd;
	int				rd;

	((fd = open(file, O_RDONLY)) < 0) ? error(4) : 0;
	str = (unsigned char *)malloc(sizeof(unsigned char) * (FILE_LEN + 2));
	rd = read(fd, str, FILE_LEN + 1);
	(rd == -1) ? error(6) : 0;
	(rd == FILE_LEN + 1) ? error(5) : 0;
	(get_num(str) != COREWAR_EXEC_MAGIC) ? error(7) : 0;
	fill_name(str + 4, players, j);
	(*players)[j].prog_size = get_num(str + PROG_NAME_LENGTH + 8);
	(*players)[j].lives = 0;
	((*players)[j].prog_size == 0) ? error(11) : 0;
	check_bot_size(fd, (*players)[j].prog_size);
	fill_field(vm, (*players)[j].prog_size, str, j);
	free(str);
}
