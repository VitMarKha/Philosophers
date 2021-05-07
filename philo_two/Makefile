.PHONY: all clean bonus fclean re run

NAME = philo_two

HEADER = philo_two.h

SRC = main.c \
	init.c \
	time.c \
	ouroboros.c \
	utils.c
	

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra -g

OPTIONOBJ = -o

DEL = rm -rf

GREEN ='\033[1;32m'

WHITE ='\033[0;37m'

YELLOW ='\033[1;33m'

CYAN ='\033[1;36m'

MAGENTA ='\033[1;35m'

all: $(NAME)

$(NAME): $(HEADER) $(SRC)
	@$(CC) $(FLAG) $(SRC) $(OPTIONOBJ) $(NAME)
	@echo $(GREEN)"Philo_two is done!"$(WHITE)	

%.o: %.c $(HEADER)
	$(CC) $(FLAG) $< $(OPTIONOBJ) $@

clean:
	@$(DEL) $(OBJ)
	@echo $(GREEN)"All 'o' files deleted."$(WHITE)

fclean: clean
	@$(DEL) $(NAME)
	@echo $(GREEN)"Everything was cleaned."$(WHITE)

re: fclean all
