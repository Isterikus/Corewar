/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:45:13 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/29 19:46:19 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error(int num)
{
	(num == 0) ? ft_printf("{red}ERROR{eoc}\nInvalid file name!\n") : 0;
	(num == 1) ? ft_printf("{red}ERROR{eoc}\nCan't open the file!\n") : 0;
	(num == 2) ? ft_printf("{red}ERROR{eoc}\nAllocation error!\n") : 0;
	(num == 3) ? ft_printf("{red}ERROR{eoc}\nInvalid name/comment!\n") : 0;
	(num == 4) ? ft_printf("{red}ERROR{eoc}\nInvalid user command name!\n") : 0;
	(num == 5) ? ft_printf("{red}ERROR{eoc}\nInvalid basic \
command name!\n") : 0;
	(num == 6) ? ft_printf("{red}ERROR{eoc}\nCan't create the file!\n") : 0;
	(num == 7) ? ft_printf("{red}ERROR{eoc}\nInvalid label!\n") : 0;
	(num == 8) ? ft_printf("{red}ERROR{eoc}\nNo code!\n") : 0;
	exit(0);
}

void	find_line(char *str, int i, char *err)
{
	int		j;
	int		line;
	int		nb;

	j = 0;
	line = 1;
	nb = 0;
	while (j < i)
		if (str[j++] == '\n')
			line++;
	while (str[j--] != '\n')
		nb++;
	ft_printf("{red}ERROR{eoc}\nLine and symbol starting from 1.\n\
Invalid %s in line %d in symbol %d!\n", err, line, nb);
	exit(0);
}

char	*read_s(const char *file)
{
	int		fd;
	int		i;
	char	*str;
	char	buf;

	(ft_strcmp(file + ft_strlen(file) - 2, ".s")) ? error(0) : 0;
	fd = open(file, O_RDONLY);
	(fd < 0) ? error(1) : 0;
	str = (char *)malloc(sizeof(char) * 2);
	(!str) ? error(3) : 0;
	i = 0;
	while (read(fd, &buf, 1))
	{
		str = realloc(str, i + 2);
		(!str) ? error(3) : 0;
		str[i] = buf;
		str[i + 1] = '\0';
		i++;
	}
	return (str);
}

void	pass(char *str, int *i, char n)
{
	while (str[*i] && str[*i] != n)
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	sp_t(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == 9))
		(*i)++;
}
