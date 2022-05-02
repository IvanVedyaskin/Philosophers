NAME = philo_bonus

DIR = philo_bonus

SRC = philosophers_main.c philosophers_mutex.c philosophers_utils.c

SRC_OBJ = $(SRC:%.c=%.o)

SRC_D = $(SRC:%.c=%.d)

CC = cc

CFLAGS = -MD -Wall -Wextra -Werror -pthread

FSA = -fsanitize=address

RM = rm -f

bonus : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ)
	$(CC) $(SRC_OBJ) -o $@

clean: 
	$(RM) $(SRC_OBJ) $(SRC_D)

fclean: clean
	$(RM) $(NAME)

-include $(SRC_D)

re: fclean bonus

.PHONY: bonus clean fclean re
