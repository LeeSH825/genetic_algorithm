CC = g++
CFAGS = -Wall -Wextra -Werror
NAME = gene
AR = ar
ARFLAGS = rcs
RM = rm -f

SRCS = srcs/cross.cpp \
srcs/fitness.cpp \
srcs/generation.cpp \
srcs/mutation.cpp \
srcs/selection.cpp \
srcs/utils.cpp \
main.cpp

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all : $(NAME)

%.o : %.c
	$(CC) $(CFAGS) -I./ -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS) $(BOBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all