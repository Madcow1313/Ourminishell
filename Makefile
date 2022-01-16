NAME = minishell

LIBA_C = ./logic/libft/*.c

LIBA_H = ./logic/libft/libft.h

LIBA = libft.a

SOURCE = main.c ./parser_utils/ft_strlen.c ./simple_parser/lexic_part1.c \
		./simple_parser/lexic_part2.c \
		./simple_parser/prepare_list.c ./parser_utils/ft_strchr.c \
		./parser_utils/ft_strlcpy.c ./simple_parser/lexic_part3.c \
		./parser_utils/ft_strnstr.c ./simple_parser/command_adjusting.c \
		./parser_utils/ft_strncmp.c ./parser_utils/ft_strjoin.c \
		./simple_parser/get_descriptors.c ./simple_parser/get_normal.c \
		./signal_handler/get_signal.c \
		./logic/not_builtins/exec_error.c ./logic/check_pipe_semicol.c ./logic/errors.c \
		./logic/single_command.c ./logic/start_cmd.c ./logic/builtins/echo.c \
		./logic/builtins/echo_redir.c ./logic/builtins/cd.c ./logic/builtins/pwd.c \
		./logic/builtins/utils/find_old_pwd.c ./logic/builtins/exit.c \
		./logic/builtins/export.c ./logic/builtins/utils/check_export_input.c\
		./logic/builtins/utils/check_valid_fill_envp.c ./logic/builtins/unset.c\
		./logic/builtins/utils/check_replace_envp.c ./logic/builtins/utils/check_valid_unset.c \
		./logic/builtins/env.c ./logic/not_builtins/exec.c ./logic/not_builtins/exec_utils.c \
		./logic/not_builtins/exec_add_func.c ./logic/pipe_case/cmd_with_pipes.c \
		./logic/pipe_case/ft_strcmp.c ./logic/pipe_case/manage_pipes.c ./logic/pipe_case/our_builtin.c \
		./logic/builtins/utils/compare_pwd.c ./logic/init_stdcopies_g_error.c \
		./logic/builtins/utils/count_len_free_array.c ./logic/builtins/utils/fill_unset.c \
		./simple_parser/start_parse_part1.c ./logic/builtins/utils/check_multiple_spaces.c \
		./simple_parser/start_parse_part2.c \
		./simple_parser/command_adjusting_2.c ./simple_parser/get_descriptors_2.c \
		./simple_parser/get_descriptors3.c

OBJ = $(SOURCE:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -L/usr/include -lreadline

HEADER = ./simple_parser/parser.h \
		./logic/logic.h

INCLUDE = -I./simple_parser/  -I/usr/local/opt/readline/include -I./logic/

#LIB_MAC = -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/

LIB_MAC = -L/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/readline/

#LIB_MAC = -L/usr/local/opt/readline/include -I./source/

.c.o: ${HEADER}
		${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(LIBA): $(LIBA_C) $(LIBA_H)
			cd ./logic/libft; \
			make; \
			mv $(LIBA) ../..; \
			cd ./logic/libft; \
			make clean

$(NAME): $(LIBA) $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBA) $(LFLAGS) -o $(NAME) -lreadline $(LIB_MAC)
		stty -echoctl

#$(NAME): $(LIBA) $(OBJ) $(HEADER)
#		$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBA) $(LFLAGS) -o $(NAME) -lreadline $(LIB_MAC)-ltermcap
#		stty -echoctl
		
#-fsanitize=address

norm:
	norminette ./logic/builtins/*.c ./logic/builtins/utils/*.c ./logic/*.c ./logic/not_builtins/*.c ./logic/pipe_case/*.c

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(OBJ) $(NAME) $(LIBA)

re:		fclean $(NAME)