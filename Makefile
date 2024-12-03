NAME 	= philo

OBJDIR		:= ./obj
SRC		= dinner.c error_exit.c main.c minilib.c parse_init.c safe_fun.c set_get.c utils.c monitor.c
OBJS	= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC 		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

LDFLAGS = -pthread


all: $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< 

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -fr $(OBJDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
