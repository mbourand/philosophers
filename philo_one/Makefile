CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=philo_one

INCS=incs/

SRCS= main.c simulation.c philosopher.c utils.c utils2.c simulation2.c utils3.c
SRCS_PATH=srcs/

OBJS_PATH=objs/
OBJ_NAMES=$(SRCS:.c=.o)
OBJS=$(addprefix $(OBJS_PATH),$(OBJ_NAMES))

LIBS=-lpthread -pthread

DEFINES=-D_REENTRANT -DLinux

RED=\033[31;1m
GREEN=\033[32;1m

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo "$(GREEN)Compiling $<"
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I $(INCS) $(LIBS) $(DEFINES) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "\n$(GREEN)Compiling $(NAME)"
	@$(CC) $(CFLAGS) -I $(INCS) $(LIBS) $(DEFINES) $(OBJS) -o $(NAME)

clean:
	@echo "$(RED)Cleaning..."
	@rm -Rf $(OBJS_PATH)

fclean:
	@echo "$(RED)Full Cleaning..."
	@rm -Rf $(OBJS_PATH)
	@rm -Rf $(NAME)

re: fclean all
