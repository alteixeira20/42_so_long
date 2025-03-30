# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 15:53:16 by paalexan          #+#    #+#              #
#    Updated: 2025/03/30 15:58:50 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & Flags
CC		:= cc
CFLAGS		:= -Wall -Werror -Wextra -g
VFLAGS		:= --leak-check=full --show-leak-kinds=all --track-origins=yes
MLX_FLAGS	:= -Lmlx -lXext -lX11

# Source Directories
SRC_MAIN	:= src
SRC_MAPS	:= src/map
SRC_GAME	:= src/game
OBJ_DIR		:= obj

# Source Bonus Directories
SRCB_MAIN	:= srcb
SRCB_MAPS	:= srcb/map
SRCB_GAME	:= srcb/game
OBJB_DIR	:= objb

# Minilibx-linux
MLX_DIR		:= minilibx-linux
MLX		:= $(MLX_DIR)/libmlx.a

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

# Source Bonus Files
SRCB			:= $(SRCB_MAIN)/so_long_bonus.c \
			   $(SRCB_MAPS)/map_parser_bonus.c \
			   $(SRCB_MAPS)/map_validation_bonus.c $(SRCB_MAPS)/map_validation_utils_bonus.c \
			   $(SRCB_MAPS)/map_pathfinding_bonus.c $(SRCB_MAPS)/map_pathfinding_utils_bonus.c \
			   $(SRCB_GAME)/game_init_bonus.c $(SRCB_GAME)/game_render_bonus.c \
			   $(SRCB_GAME)/game_assets_bonus.c $(SRCB_GAME)/game_animations_bonus.c \
			   $(SRCB_GAME)/game_input_bonus.c $(SRCB_GAME)/game_input_utils_bonus.c

OBJB			:= $(patsubst $(SRCB_MAIN)/%.c, $(OBJB_DIR)/%.o, $(SRCB))

# Executable
GAME			:= so_long
BONUS			:= so_long_bonus

# Targets Mandatory
$(OBJ_DIR)/%.o: $(SRC_MAIN)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_MAPS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_GAME)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	
# Targets Bonus
$(OBJB_DIR)/%.o: $(SRCB_MAIN)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJB_DIR)/%.o: $(SRCB_MAPS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJB_DIR)/%.o: $(SRCB_GAME)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rules
all: $(LIBFT) $(MLX) $(GAME)

bonus: $(BONUS)

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

$(BONUS): $(LIBFT) $(MLX) $(OBJB)
	@rm -f $(GAME)
	@$(CC) $(CFLAGS) $(OBJB) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(GAME)
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Bonus Game$(RESET) compiled $(GREEN)successfully$(RESET)."


start:
	@bash -c ' \
		# Check for .ber maps in working directory \
		EXISTING_MAPS=$$(find . -maxdepth 1 -name "*.ber"); \
		if [ ! -z "$$EXISTING_MAPS" ]; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Found map(s) in current directory:"; \
			echo "$$EXISTING_MAPS"; \
			read -p "Do you want to $(RED)delete$(RESET) them before continuing? (y/n): " DELETE_CONFIRM; \
			if [ "$$DELETE_CONFIRM" = "y" ]; then \
				rm -f *.ber; \
				echo "$(ORANGE)$(PREFIX)$(RESET) Deleted old map(s)."; \
			else \
				echo "$(ORANGE)$(PREFIX)$(RESET) Keeping existing map(s)."; \
			fi; \
		fi; \
		while true; do \
			clear; \
			echo "$(ORANGE)Choose map type:$(RESET)"; \
			echo " 1) Invalid"; \
			echo " 2) Valid"; \
			echo " $(GREY)$(BOLD)q) Quit$(RESET)"; \
			echo ""; \
			read -p "Enter your choice: " TYPE_CHOICE; \
			if [ "$$TYPE_CHOICE" = "q" ]; then exit 0; fi; \
			if [ "$$TYPE_CHOICE" = "1" ]; then \
				MAP_DIR="maps/invalid"; \
			elif [ "$$TYPE_CHOICE" = "2" ]; then \
				MAP_DIR="maps/valid"; \
			else \
				echo "Invalid choice. Please choose 1, 2, or q."; \
				sleep 1; continue; \
			fi; \
			MAPS=($$(find $$MAP_DIR -name "*.ber" | sort)); \
			TOTAL_MAPS=$${#MAPS[@]}; \
			PAGE_SIZE=5; \
			CURRENT_PAGE=0; \
			while true; do \
				clear; \
				echo "$(ORANGE)Available Maps in $$MAP_DIR $(RESET)(Page $$((CURRENT_PAGE+1))):"; \
				START=$$((CURRENT_PAGE * PAGE_SIZE)); \
				END=$$((START + PAGE_SIZE)); \
				INDEX=0; \
				for MAP in $${MAPS[@]:$$START:$$PAGE_SIZE}; do \
					echo " $$((START+INDEX+1))) $$(basename $$MAP)"; \
					INDEX=$$((INDEX+1)); \
				done; \
				echo ""; \
				if [ "$$TOTAL_MAPS" -gt "$$PAGE_SIZE" ]; then \
					[ "$$END" -lt "$$TOTAL_MAPS" ] && echo "$(GREY)$(BOLD)n) Next Page$(RESET)"; \
					[ "$$CURRENT_PAGE" -gt 0 ] && echo "$(GREY)$(BOLD)p) Previous Page$(RESET)"; \
				fi; \
				echo "$(GREY)$(BOLD)b) Back$(RESET)"; \
				echo "$(GREY)$(BOLD)q) Quit$(RESET)"; \
				echo ""; \
				read -p "Choose a map (number) or navigate (n/p/b/q): " CHOICE; \
				if [ "$$CHOICE" = "n" ] && [ $$END -lt $$TOTAL_MAPS ]; then \
					CURRENT_PAGE=$$((CURRENT_PAGE + 1)); \
				elif [ "$$CHOICE" = "p" ] && [ "$$CURRENT_PAGE" -gt 0 ]; then \
					CURRENT_PAGE=$$((CURRENT_PAGE - 1)); \
				elif [ "$$CHOICE" = "b" ]; then \
					break; \
				elif [ "$$CHOICE" = "q" ]; then \
					exit 0; \
				elif [[ "$$CHOICE" =~ ^[0-9]+$$ ]] && [ "$$CHOICE" -ge 1 ] && [ "$$CHOICE" -le $$TOTAL_MAPS ]; then \
					SELECTED_MAP=$${MAPS[$$((CHOICE-1))]}; \
					cp "$$SELECTED_MAP" "./$$(basename $$SELECTED_MAP)"; \
					echo "Map $(ORANGE)$$(basename $$SELECTED_MAP)$(RESET) copied to working directory."; \
					read -p "Do you want to $(GREEN)start$(RESET) the game? (y/n): " RUN_GAME; \
					if [ "$$RUN_GAME" = "y" ]; then \
						./so_long "$$(basename $$SELECTED_MAP)"; \
						rm -f "$$(basename $$SELECTED_MAP)"; \
						echo "Map $(ORANGE)$$(basename $$SELECTED_MAP)$(RESET) removed from working directory."; \
					else \
						echo "You can now manually run: ./so_long $$(basename $$SELECTED_MAP)"; \
					fi; \
					exit 0; \
				else \
					echo "Invalid choice! Please enter a valid number."; \
					sleep 1; \
				fi; \
			done; \
		done'

valgrind_test:
	@echo "$(ORANGE)$(PREFIX)$(RESET) Running Valgrind leak checks on invalid maps..."
	@for map in maps/invalid/*.ber; do \
		valgrind --leak-check=full --error-exitcode=42 ./$(GAME) $$map > /dev/null 2>&1; \
		if [ $$? -eq 42 ]; then \
			echo "$(RED)$(PREFIX)$(RESET) Map $$map $(RED)failed$(RESET) Valgrind test."; \
		else \
			echo "$(GREEN)$(PREFIX)$(RESET) Map $$map $(GREEN)passed$(RESET) Valgrind test."; \
		fi; \
	done

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJB_DIR)
	@rm -f $(GAME)
	@echo "$(ORANGE)$(PREFIX)$(RESET) All executables and objects were cleaned $(GREEN)successfully$(RESET)."

fclean: clean
	@rm -rf $(LIBFT_DIR)
	@echo "$(ORANGE)$(PREFIX)$(RESET) Libft was cleaned $(GREEN)successfully$(RESET)."

re: fclean all

# Colors
PREFIX	:= $(shell tput bold)[So_Long]
BOLD 	:= $(shell tput bold)
GREEN	:= $(shell tput setaf 2)
RED  	:= $(shell tput setaf 1)
YELLOW	:= $(shell tput setaf 3)
RESET	:= $(shell tput sgr0)
GREY	:= $(shell tput setaf 8)
ORANGE	:= $(shell tput setaf 214)

.PHONY: all clean fclean re bonus start valgrind_test
