NAME = Partie1

CC  = gcc
DEBUG = gdb


RM = rm -f
PTHREAD = -pthread
CFLAGS = -Wall -Wextra -c -g
LDFLAGS = $(PTHREAD) -export-dynamic

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS) 
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: debug valgrind

valgrind: $(NAME)
	valgrind ./$(NAME)

debug: $(NAME)
	$(DEBUG) $(NAME)
