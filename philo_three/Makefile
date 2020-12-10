CC=gcc
CFLAGS=-Wall -Wextra -Werror

DB=0

ifeq ($(DB),1)
	CFLAGS += -fsanitize=address
else ifeq ($(DB),2)
	CFLAGS += -fsanitize=thread
endif

NAME=philo_three

INCS=incs/

SRCS= main.c simulation.c philosopher.c phil_utils.c string_utils.c time_utils.c \
		mutexint.c init.c string_utils2.c
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
