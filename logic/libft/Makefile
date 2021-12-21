NAME = libft.a
	
HEADER	= libft.h

SRCS	= ft_strlen.c \
		 ft_atoi.c \
		 ft_bzero.c \
		 ft_calloc.c \
		 ft_isalpha.c \
		 ft_isdigit.c \
		 ft_isalnum.c \
		 ft_isascii.c \
		 ft_isprint.c \
		 ft_itoa.c \
		 ft_memccpy.c \
		 ft_memset.c \
		 ft_memcpy.c \
		 ft_memmove.c \
		 ft_memchr.c \
		 ft_memcmp.c \
		 ft_putchar_fd.c \
		 ft_putstr_fd.c \
		 ft_putendl_fd.c \
		 ft_putnbr_fd.c \
		 ft_split.c \
		 ft_strdup.c \
		 ft_strlcpy.c \
		 ft_strlcat.c \
		 ft_strmapi.c \
		 ft_strrchr.c \
		 ft_strnstr.c \
		 ft_substr.c \
		 ft_strtrim.c \
		 ft_toupper.c \
		 ft_tolower.c \

SRCS2	= ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

OBJS2	= ${SRCS2:.c=.o}

OBJS	= ${SRCS:.c=.o}

RM	= rm -f

AR	= ar rc

CFLAGS 	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}
	
${NAME}:	${OBJS} ${HEADER}
			${AR} ${NAME} ${OBJS}

clean:
		${RM} ${OBJS} ${OBJS2}

fclean:	clean
		${RM} ${NAME}
		
re:		fclean all

bonus: ${OBJS2}
		${AR} ${NAME} $^

.PHONY: re clean fclean all 