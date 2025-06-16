
SRCS = src/philosopher_main.c \
			src/initialize_philosopher.c \
			src/philosopher_routine.c \
			src/start_threads.c \
			src/arbitrator_routine.c \
			src/utils.c \

BONUS_SRCS = src_bonus/main.c \
						src_bonus/init.c \
						src_bonus/process.c \
						src_bonus/routine_actions.c \
						src_bonus/utils.c \
						src_bonus/utils2.c \

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

NAME = philo

BONUS = philo_bonus

LDFLAGS = -Wall -Wextra -Werror -pthread -g3

# colors
GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "	 			+---------------------+\n \
					|  $(YELLOW)    PHILO $(GREEN)[OK]$(NC)     |\n \
					+---------------------+"

$(BONUS): $(BONUS_OBJS)
	$(CC) $(LDFLAGS) $(BONUS_OBJS) -o $(BONUS)
	@echo "	 			+---------------------+\n \
					|  $(YELLOW) PHILO_BONUS $(GREEN)[OK]$(NC)  |\n \
					+---------------------+"

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) $(BONUS)

bonus: $(BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean
	make all

.PHONY: all clean fclean re
