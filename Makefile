NAME = minishell

SOURCE = main.c ./parser_utils/ft_strlen.c ./simple_parser/lexic_part1.c \
		./simple_parser/lexic_part2.c \
		./simple_parser/prepare_list.c ./parser_utils/ft_strchr.c \
		./simple_parser/empty_built_ins.c \
		./parser_utils/ft_strlcpy.c ./simple_parser/lexic_part3.c \
		./parser_utils/ft_strnstr.c ./simple_parser/command_adjusting.c \
		./parser_utils/ft_strncmp.c ./parser_utils/ft_strjoin.c \
		./simple_parser/get_descriptors.c ./simple_parser/get_normal.c

OBJ = $(SOURCE:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -L/usr/include -lreadline

HEADER = ./simple_parser/parser.h

.c.o: ${HEADER}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)
		
#-fsanitize=address

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(OBJ) $(NAME)

re:		fclean $(NAME)