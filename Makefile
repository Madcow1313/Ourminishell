NAME = minishell

LIBA_C = ./logic/libft/*.c

LIBA_H = ./logic/libft/libft.h

LIBA = libft.a

SOURCE = main.c ./parser_utils/ft_strlen.c ./simple_parser/lexic_part1.c \
		./simple_parser/lexic_part2.c \
		./simple_parser/prepare_list.c ./parser_utils/ft_strchr.c \
		./simple_parser/empty_built_ins.c \
		./parser_utils/ft_strlcpy.c ./simple_parser/lexic_part3.c \
		./parser_utils/ft_strnstr.c ./simple_parser/command_adjusting.c \
		./parser_utils/ft_strncmp.c ./parser_utils/ft_strjoin.c \
		./simple_parser/get_descriptors.c ./simple_parser/get_normal.c ./simple_parser/no_space.c \
		./signal_handler/get_signal.c ./simple_parser/shit.c \
		./logic/builtins/builtins.c ./logic/check_pipe_semicol.c ./logic/errors.c \
		./logic/single_command.c ./logic/start_cmd.c ./logic/builtins/echo.c \
		./logic/builtins/echo_redir.c ./logic/builtins/cd.c ./logic/builtins/pwd.c \
		./logic/builtins/utils/find_old_pwd.c ./logic/builtins/exit.c \
		./logic/builtins/export.c ./logic/builtins/utils/check_export_input.c\
		./logic/builtins/utils/check_valid_fill_envp.c ./logic/builtins/unset.c\
		./logic/builtins/utils/check_replace_envp.c ./logic/builtins/utils/check_valid_unset.c \
		./logic/builtins/env.c ./logic/not_builtins/exec.c

OBJ = $(SOURCE:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -L/usr/include -lreadline

HEADER = ./simple_parser/parser.h \
		./logic/logic.h

INCLUDE = -I./simple_parser/  -I/usr/local/opt/readline/include

LIB_MAC = -L/usr/local/opt/readline/lib

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
		$(CC) -fsanitize=address $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBA) $(LFLAGS) -o $(NAME) -lreadline $(LIB_MAC)
		
#-fsanitize=address

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(OBJ) $(NAME) $(LIBA)

re:		fclean $(NAME)