/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 19:23:30 by dkovalen          #+#    #+#             */
/*   Updated: 2017/03/30 12:43:57 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/printf_functions/includes/header.h"
# include "op.h"

typedef struct	s_comm
{
	char	*name;
	int		place;
}				t_comm;

/*
**		file1
*/
void			error(int num);
void			find_line(char *str, int i, char *err);
char			*read_s(const char *file);
void			pass(char *str, int *i, char n);
void			sp_t(char *str, int *i);
/*
**		file2
*/
void			comment(char *str, int *i);
void			name_comm(char *str, int i, char *compare);
int				name_comm2(char *str, int i, char *compare);
int				find_next(char *str, int i);
int				check_reg(char *str, int i);
/*
**		file3
*/
int				check_dir(char *str, int i);
int				check_idir(char *str, int i);
void			check_arg_dou(int j, int k, char *str, int i);
void			check_arg(int j, int k, char *str, int i);
void			pass_arg(char *str, int *i);
/*
**		file4
*/
void			check_command(char *str, int *i);
void			pass_magic(int fd);
void			pass_next_str(char *str, int i, int fd, int len);
void			count_command(int j, char *str, int *i, int *len);
void			count_len(char *str, int *i, int *len);
/*
**		file5
*/
int				srav(char *str, int i);
int				fill_arr(char *str, int i, int *len, t_comm (*comm)[100]);
int				count_pl(t_comm (*comm)[100], char *str, int i, int fd);
int				count_comm_len(char *str, int i, int j);
int				find_dif(char *str, t_comm comm[100], int temp_len);
/*
**		file6
*/
void			wrt_fd(int fd, int par, int b);
void			pass_link(char *str, int *i);
void			parse1(char *str, int *i, int *j, int fd);
void			parse2(char *str, t_comm comm[100], int j, int (*temp_len)[3]);
void			parse3(char *str, int *i, int (*temp_len)[3]);
/*
**		file7
*/
void			parse4(char *str, int *i, int (*temp_len)[3]);
void			parse5(char *str, int *i, int *k);
void			parse6(char *str, int (*temp_len)[3], int j, int i);

void			make_new(char *str, char *file);
void			pass(char *str, int *i, char n);
void			comment(char *str, int *i);
void			error(int num);
int				find_next(char *str, int i);
int				name_comm2(char *str, int i, char *compare);
void			sp_t(char *str, int *i);
void			wrt_fd(int fd, int par, int b);

#endif
