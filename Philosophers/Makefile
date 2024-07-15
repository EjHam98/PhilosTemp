BLACK(str)   = \033[0;30mstr"\x1b[0m # Black - Regular
RED     = \033[0;31m # Red
GREEN   = \033[0;32m # Green
YELLOW  = \033[0;33m # Yellow
BLUE    = \033[0;34m # Blue
PURPLE  = \033[0;35m # Purple
CYAN    = \033[0;36m # Cyan
WHITE   = \033[0;37m # White

BLACK_BOLD  = \033[1;30m # Black - Bold
RED_BOLD    = \033[1;31m # Red
GREEN_BOLD  = \033[1;32m # Green
YELLOW_BOLD = \033[1;33m # Yellow
BLUE_BOLD   = \033[1;34m # Blue
PURPLE_BOLD = \033[1;35m # Purple
CYAN_BOLD   = \033[1;36m # Cyan
WHITE_BOLD  = \033[1;37m # White

BLACK_UNDERLINE   = \033[4;30m # Black - Underline
RED_UNDERLINE     = \033[4;31m # Red
GREEN_UNDERLINE   = \033[4;32m # Green
YELLOW_UNDERLINE  = \033[4;33m # Yellow
BLUE_UNDERLINE    = \033[4;34m # Blue
PURPLE_UNDERLINE  = \033[4;35m # Purple
CYAN_UNDERLINE    = \033[4;36m # Cyan
WHITE_UNDELINE    = \033[4;37m # White

BLACK_BACKGROUND  = \033[40m   # Black - Background
RED_BACKGROUND    = \033[41m   # Red
GREEN_BACKGROUND  = \033[42m   # Green
YELLOW_BACKGROUND = \033[43m   # Yellow
BLUE_BACKGROUND   = \033[44m   # Blue
PURPLE_BACKGROUND = \033[45m   # Purple
CYAN_BACKGROUND   = \033[46m   # Cyan
WHITE_BACKGROUND  = \033[47m   # White
TEXT_RESET        = \033[0m    # Text Reset

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I./inc/
# CFLAGS += -fsanitize=address,undefined -g3
CFLAGS += -fsanitize=thread
NAME = philo
SRCS = ./src/main.c ./src/philos.c ./src/philo_acts.c ./src/philo_utils.c ./src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "\n\n██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\n"

$(NAME): $(OBJS)
	clear
	@echo "$(GREEN_BOLD)Object Files Created!$(TEXT_RESET)"
	@echo "$(YELLOW_BOLD)Compiling...$(TEXT_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN_BOLD)Compilation Complete!$(TEXT_RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@clear
	@echo "$(PURPLE_BOLD)Removing Object Files...$(TEXT_RESET)"
	@rm -rf $(OBJS)
	@echo "$(RED_BOLD)Object Files Removed!$(TEXT_RESET)"
	@echo "\n\n██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\n"

fclean: clean
	clear
	@echo "$(PURPLE_BOLD)Removing Object Files...$(TEXT_RESET)"
	@echo "$(RED_BOLD)Object Files Removed!$(TEXT_RESET)"
	@echo "$(PURPLE_BOLD)Removing Executables...$(TEXT_RESET)"
	@rm -rf $(NAME)
	@echo "$(RED_BOLD)Executables Removed!$(TEXT_RESET)"
	@echo "\n\n██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\n"

re: fclean all

.PHONY: all clean fclean re