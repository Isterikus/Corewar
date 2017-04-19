/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 10:02:05 by dkovalen          #+#    #+#             */
/*   Updated: 2017/04/19 16:32:51 by dkovalen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <ncurses.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/printf_functions/includes/header.h"
# include <sys/ioctl.h>

# define BLUE		COLOR_PAIR(1)
# define RED		COLOR_PAIR(2)
# define GREEN		COLOR_PAIR(3)
# define YELLOW		COLOR_PAIR(4)
# define WHITE		COLOR_PAIR(5)

# define BCK_BLUE	COLOR_PAIR(6)
# define BCK_RED	COLOR_PAIR(7)
# define BCK_GREEN	COLOR_PAIR(8)
# define BCK_YELLOW	COLOR_PAIR(9)
# define BCK_WHITE	COLOR_PAIR(10)

# define SPACE		32
# define RIGHT		67
# define LEFT		91
# define MIN_WID	242
# define MIN_HEI	66

# define NBR_PLAYER	0xffffffff

# define FILE_LEN	CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 12

typedef struct		s_player
{
	char			*name;
	char			*comment;
	int				num;
	int				prog_size;
	int				lives;
}					t_player;

typedef struct		s_caret
{
	int				color;
	int				live;
	int				pc;
	int				wait;
	int				carry;
	int				reg[16];
	struct s_caret	*next;
}					t_caret;

typedef struct		s_vm
{
	t_caret			*carets;
	void			(*funcs[16])(t_caret *caret, unsigned char *field);
	unsigned char	field[2][4096];
	int				last_live;
	int				dump;
	int				debug;
	int				vizualize;
	int				champs;
	int				cycles;
	int				sleep;
	int				no_live;
	int				cycles_to_die;
}					t_vm;

/*
**		file1
*/
void				error(int num);
void				print_stars(void);
void				put_color(unsigned char col);
int					print_nbr_live(t_caret	*carets, int num);
int					count_process(t_caret *caret);

/*
**		file2
*/
void				get_dots(char *str, int i);
void				get_rid_from_n(char **str);
void				print_comm(t_player *players, int i);
void				print_players(t_player *players, t_vm vm);
void				print_info(t_vm vm);

/*
**		file3
*/
void				put_col_car(t_caret *carets, unsigned char col,
								long int ps);
void				ft_print_01(unsigned char field[2][4096],
								t_player *players, t_vm *vm);
void				set_colors(void);
void				fill_vm(t_vm *vm);
void				check_size(void);

/*
**		file4
*/
int					check_champs(int argc, char **argv);
int					get_num(unsigned char *str);
void				fill_name(unsigned char *str, t_player **players, int j);
void				fill_field(t_vm *vm, int size, unsigned char *str, int j);
void				fill_player(t_vm *vm, char *file,
								t_player **players, int j);

/*
**		file5
*/
void				fill_flags(char **argv, t_vm *vm,
								t_player **players, int i);
void				read_champs(int argc, char **argv,
								t_vm *vm, t_player **players);
void				keys(int key, t_vm *vm);
void				create_fir_car(t_caret **carets,
								t_player *players, int i, int cou);
void				create_carets(t_caret **carets, t_player *players, int cou);

/*
**		file6
*/
int					ret_len(t_caret *car, t_vm *vm);
void				move_car(t_caret *car, t_vm *vm);
void				cycles_in(t_vm *vm, t_player *players);
void				machine(t_player *players, t_vm *vm);

/*
**		file7
*/
void				start_viz(void);
void				check_bot_size(int fd, int size);
void				winners(int champs, int winer, t_player *players);

void				ft_edit_cycle_to_die(t_caret *caret, int *cycle_die);
int					ft_live(t_caret **caret);
int					ft_run_op(unsigned char arena[2][4096], t_caret *proc,
					int vz, t_player **players);

#endif
