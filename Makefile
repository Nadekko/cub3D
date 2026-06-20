CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3

NAME    = cub3d
NAME_B  = cub3d_bonus

SRC_DIRS = \
	_mandatory \
	_mandatory/parse \
	_mandatory/utils \
	_mandatory/exec

SRC_DIRS_B = \
	_bonus \
	_bonus/parse_bonus \
	_bonus/utils_bonus \
	_bonus/exec_bonus

SRC     = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC_B   = $(foreach dir,$(SRC_DIRS_B),$(wildcard $(dir)/*.c))

OBJ     = $(SRC:.c=.o)
OBJ_B   = $(SRC_B:.c=.o)

HEADER  = cub.h
HEADER_B = cub_bonus.h

LIBFT   = libft/libft.a

MLX_DIR = minilibx-linux
MLX     = $(MLX_DIR)/libmlx.a

GREEN   = \033[0;32m
BLUE    = \033[0;34m
CYAN    = \033[0;36m
YELLOW  = \033[0;33m
PURPLE  = \033[0;35m
RED     = \033[0;31m
NC      = \033[0m

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "$(PURPLE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "$(GREEN)$(NAME) compiled successfully.$(NC)"

bonus: $(MLX) $(LIBFT) $(NAME_B)

$(NAME_B): $(OBJ_B) $(LIBFT) $(MLX)
	@echo "$(PURPLE)Linking $(NAME_B)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ_B) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "$(GREEN)$(NAME_B) compiled successfully.$(NC)"

%.o: %.c $(HEADER)
	@echo "$(BLUE)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(CYAN)Building libft...$(NC)"
	@make --no-print-directory -C libft

$(MLX_DIR):
	@echo "$(YELLOW)Cloning MiniLibX...$(NC)"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@echo "$(CYAN)Building MiniLibX...$(NC)"
	@make -s -C $(MLX_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@rm -f $(OBJ) $(OBJ_B)
	@make clean -C libft
	@if [ -d "$(MLX_DIR)" ]; then make clean -s -C $(MLX_DIR); fi
	@echo "$(GREEN)Clean done.$(NC)"

fclean: clean
	@echo "$(RED)Removing binaries...$(NC)"
	@rm -f $(NAME) $(NAME_B)
	@make fclean -C libft
	@rm -rf $(MLX_DIR)
	@echo "$(GREEN)Full clean done.$(NC)"

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
