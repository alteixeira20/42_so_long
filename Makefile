# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 15:53:16 by paalexan          #+#    #+#              #
#    Updated: 2025/03/24 19:59:12 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & Flags
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g
VFLAGS		:= --leak-check=full --show-leak-kinds=all --track-origins=yes
MLX_FLAGS	:= -Lmlx -lXext -lX11

# Source Directories
SRC_MAIN	:= src
SRC_MAPS	:= src/map
SRC_GAME	:= src/game
OBJ_DIR		:= obj

# Minilibx-linux
MLX_DIR		:= minilibx-linux
MLX			:= $(MLX_DIR)/libmlx.a

# Libft
LIBFT_REPO	:= https://github.com/alteixeira20/42_libft.git
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

# Source Files
SRC			:= $(SRC_MAIN)/so_long.c \
			   $(SRC_MAPS)/map_parser.c \
			   $(SRC_MAPS)/map_validation.c $(SRC_MAPS)/map_validation_utils.c \
			   $(SRC_MAPS)/map_pathfinding.c $(SRC_MAPS)/map_pathfinding_utils.c \
			   $(SRC_GAME)/game_init.c $(SRC_GAME)/game_input.c \
			   $(SRC_GAME)/game_assets.c $(SRC_GAME)/game_render.c

OBJ			:= $(patsubst $(SRC_MAIN)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Executable
GAME		:= so_long

# Targets
$(OBJ_DIR)/%.o: $(SRC_MAIN)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_MAPS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_GAME)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
# Rules
all: $(LIBFT) $(MLX) $(GAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(ORANGE)$(PREFIX)$(RESET) Cloning $(BOLD)Libft$(RESET) and waiting for compilation..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --silent > /dev/null 2>&1
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Libft$(RESET) compiled $(GREEN)successfully$(RESET)."

$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(GAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(GAME)
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Game$(RESET) compiled $(GREEN)successfully$(RESET)."

start:
	@bash -c ' \
		OLD_MAPS=$$(ls | grep ".ber" || echo ""); \
		if [ ! -z "$$OLD_MAPS" ]; then \
			read -p "Maps found, do you want to delete previous used maps? (y/n): " DELETE_OLD; \
			if [ "$$DELETE_OLD" = "y" ]; then \
				rm -f *.ber; \
				echo "Old maps deleted."; \
			fi; \
		fi; \
		MAPS=($$(ls maps/ | grep ".ber")); \
		TOTAL_MAPS=$${#MAPS[@]}; \
		PAGE_SIZE=5; \
		CURRENT_PAGE=0; \
		while true; do \
			clear; \
			echo "$(ORANGE)Available Maps $(RESET)(Page $$((CURRENT_PAGE+1))):"; \
			START=$$((CURRENT_PAGE * PAGE_SIZE)); \
			END=$$((START + PAGE_SIZE)); \
			INDEX=0; \
			for MAP in $${MAPS[@]:$$START:$$PAGE_SIZE}; do \
				echo " $$((START+INDEX+1))) $$MAP"; \
				INDEX=$$((INDEX+1)); \
			done; \
			echo ""; \
			if [ "$$TOTAL_MAPS" -gt "$$PAGE_SIZE" ]; then \
				[ "$$END" -lt "$$TOTAL_MAPS" ] && echo "$(GREY)$(BOLD)n) Next Page$(RESET)"; \
				[ "$$CURRENT_PAGE" -gt 0 ] && echo "$(GREY)$(BOLD)p) Previous Page$(RESET)"; \
			fi; \
			echo "$(GREY)$(BOLD)q) Quit$(RESET)"; \
			echo ""; \
			read -p "Choose a map (number) or navigate (n/p/q): " CHOICE; \
			if [ "$$CHOICE" = "n" ] && [ $$END -lt $$TOTAL_MAPS ]; then \
				CURRENT_PAGE=$$((CURRENT_PAGE + 1)); \
			elif [ "$$CHOICE" = "p" ] && [ $$CURRENT_PAGE -gt 0 ]; then \
				CURRENT_PAGE=$$((CURRENT_PAGE - 1)); \
			elif [ "$$CHOICE" = "q" ]; then \
				exit 0; \
			elif [[ "$$CHOICE" =~ ^[0-9]+$$ ]] && [ "$$CHOICE" -ge 1 ] && [ "$$CHOICE" -le $$TOTAL_MAPS ]; then \
				SELECTED_MAP=$${MAPS[$$((CHOICE-1))]}; \
				cp "maps/$$SELECTED_MAP" "./$$SELECTED_MAP"; \
				echo "Map $(ORANGE)$$SELECTED_MAP$(RESET) copied to working directory."; \
				read -p "Do you want to $(GREEN)start$(RESET) the game? (y/n): " RUN_GAME; \
				if [ "$$RUN_GAME" = "y" ]; then \
					./so_long "$$SELECTED_MAP"; \
					rm -f "./$$SELECTED_MAP"; \
					echo "Map $(ORANGE)$$SELECTED_MAP$(RESET) removed from working directory."; \
				else \
					echo "You can now manually run: $(ORANGE)./so_long $$SELECTED_MAP$(RESET)"; \
				fi; \
				exit 0; \
			else \
				echo "Invalid choice! Please enter a valid number."; \
				sleep 1; \
			fi; \
		done'

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(GAME)
	@echo "$(ORANGE)$(PREFIX)$(RESET) All executables and objects were cleaned $(GREEN)successfully$(RESET)."

fclean: clean
	@rm -rf $(LIBFT_DIR)
	@echo "$(ORANGE)$(PREFIX)$(RESET) Libft was cleaned $(GREEN)successfully$(RESET)."

re: all clean fclean

# Colors
PREFIX	:= $(shell tput bold)[So_Long]
BOLD 	:= $(shell tput bold)
GREEN	:= $(shell tput setaf 2)
RED  	:= $(shell tput setaf 1)
YELLOW	:= $(shell tput setaf 3)
RESET	:= $(shell tput sgr0)
GREY	:= $(shell tput setaf 8)
ORANGE	:= $(shell tput setaf 214)

.PHONY: all clean fclean re
