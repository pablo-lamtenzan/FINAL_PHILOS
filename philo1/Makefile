NAME		= philo_one

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I.
LIBS		= -lpthread

SRCS		= main.c actions.c aux.c engine.c engine_helper.c destroy_mutexes.c msg.c parse.c
OBJS		= $(SRCS:.c=.o)

RM			= /bin/rm
all:		$(NAME)

$(NAME):	$(OBJS)
				@echo CC $<
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
			@echo RM $(OBJS) $<
			@$(RM) -f $(OBJS)

fclean:					clean
			@echo RM $(NAME)
			@$(RM) -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re