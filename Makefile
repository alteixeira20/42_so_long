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
CC			:= cc
CFLAGS			:= -Wall -Werror -Wextra -g
VFLAGS			:= --leak-check=full --show-leak-kinds=all --track-origins=yes
MLX_FLAGS		:= -Lmlx -lXext -lX11

# Source Directories
SRC_MAIN		:= src
SRC_MAPS		:= src/map
SRC_GAME		:= src/game
OBJ_DIR			:= obj

# Source Bonus Directories
SRCB_MAIN		:= srcb
SRCB_MAPS		:= srcb/map
SRCB_GAME		:= srcb/game
OBJB_DIR		:= objb

# Minilibx-linux
MLX_DIR			:= mlx
MLX			:= $(MLX_DIR)/libmlx.a

# Libft
LIBFT_REPO		:= https://github.com/alteixeira20/42_libft.git
LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a

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

# Asset Collections
TEXTURES		:= $(shell find assets -type f -name "*.xpm" | sort)
TEXTURE_TEST_MAP	:= $(shell find assets/maps/valid -type f -name "*.ber" | sort | head -n 1)
HAS_TEXTURE_MAP		:= $(shell if [ -n "$(TEXTURE_TEST_MAP)" ]; then echo 1; else echo 0; fi)
HAS_INVALID_MAP		:= $(shell [ -f assets/maps/invalid/invalid_char.ber ] && echo 1 || echo 0)

# Map Collections
INVALID_MAPS		:= $(shell find assets/maps/invalid -type f -name "*.ber" | sort)

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
all: $(MLX) $(LIBFT) $(GAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(ORANGE)$(PREFIX)$(RESET) Cloning $(BOLD)Libft$(RESET) and waiting for compilation..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --silent > /dev/null 2>&1
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Libft$(RESET) compiled $(GREEN)successfully$(RESET)."

$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Minilibx-linux$(RESET) compiled $(GREEN)successfully$(RESET)."

$(GAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(GAME)
	@echo "$(ORANGE)$(PREFIX)$(RESET) $(BOLD)Game$(RESET) compiled $(GREEN)successfully$(RESET)."

bonus: $(LIBFT) $(MLX) $(OBJB)
	@if [ -f "$(GAME)" ]; then \
		rm -f $(GAME); \
	fi
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
				MAP_DIR="assets/maps/invalid"; \
			elif [ "$$TYPE_CHOICE" = "2" ]; then \
				MAP_DIR="assets/maps/valid"; \
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

test_invalid:
	@bash -c ' \
		if [ ! -f "$(GAME)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No executable found. Please compile the project first (make bonus)."; \
			exit 0; \
		fi; \
		if [ -z "$(INVALID_MAPS)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No invalid maps found in assets/maps/invalid."; \
			exit 0; \
		fi; \
		status=0; passed=0; failed=0; \
		echo "$(ORANGE)$(PREFIX)$(RESET) Running Tests on Invalid Maps..."; \
		for map in $(INVALID_MAPS); do \
			echo ; \
			printf "Testing map %s:\\n" "$(YELLOW)$$(basename "$$map")$(RESET)"; \
			msg_output=$$(./$(GAME) "$$map" 2>&1 || true); \
			first=$$(printf "%s" "$$msg_output" | sed -n '1p'); \
			error_line=$$(printf "%s" "$$msg_output" | sed -n "2p"); \
			err_ok=1; \
			if [ "$$first" = "Error" ] && [ -n "$$error_line" ]; then \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(GREEN)OK$(RESET)"; \
			else \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(RED)KO$(RESET)"; \
				printf "%s\\n" "$$msg_output"; \
				err_ok=0; \
			fi; \
			tmp=$$(mktemp); \
			valgrind --leak-check=full --error-exitcode=42 --log-file=$$tmp ./$(GAME) "$$map" > /dev/null 2>&1 || true; \
			vg_output=$$(cat $$tmp); rm -f $$tmp; \
			vg_ok=1; \
			if printf "%s\\n" "$$vg_output" | grep -q "ERROR SUMMARY: 0"; then \
				printf "  Valgrind: %sOK%s\\n" "$(GREEN)" "$(RESET)"; \
			else \
				printf "  Valgrind: %sKO%s\\n" "$(RED)" "$(RESET)"; \
				printf "%s\\n" "$$vg_output"; \
				vg_ok=0; \
			fi; \
			if [ "$$err_ok" -eq 1 ] && [ "$$vg_ok" -eq 1 ]; then \
				passed=$$((passed + 1)); \
			else \
				failed=$$((failed + 1)); \
				status=1; \
			fi; \
		done; \
		if [ "$$failed" -eq 0 ]; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Congratulations you passed all $(GREEN)$$passed$(RESET) tests."; \
		else \
			echo "$(ORANGE)$(PREFIX)$(RESET) Passed $(GREEN)$$passed$(RESET) tests and $(RED)$$failed$(RESET) tests."; \
		fi; \
		exit $$status'




test_textures:
	@bash -c ' \
		if [ ! -f "$(GAME)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No executable found. Please compile the project first (make bonus)."; \
			exit 0; \
		fi; \
		if [ -z "$(TEXTURES)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No textures found in assets."; \
			exit 0; \
		fi; \
		if [ $(HAS_TEXTURE_MAP) -eq 0 ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No valid map found in assets/maps/valid for texture tests."; \
			exit 1; \
		fi; \
		status=0; passed=0; failed=0; \
		for texture in $(TEXTURES); do \
			bname=$$(basename "$$texture"); \
			dirname=$$(dirname "$$texture"); \
			echo ; \
			printf "Testing texture %s (dir %s):\\n" "$(YELLOW)$$bname$(RESET)" "$$dirname"; \
			save_perms=$$(stat -c %a "$$texture"); \
			chmod 000 "$$texture"; \
			msg_output=$$(./$(GAME) $(TEXTURE_TEST_MAP) 2>&1 || true); \
			chmod $$save_perms "$$texture"; \
			error_line=$$(printf "%s" "$$msg_output" | sed -n "2p"); \
			if printf "%s" "$$error_line" | grep -qi "$$bname"; then \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(GREEN)OK$(RESET)"; \
				passed=$$((passed + 1)); \
			else \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(RED)KO$(RESET)"; \
				printf "%s\\n" "$$msg_output"; \
				failed=$$((failed + 1)); \
				status=1; \
			fi; \
			done; \
		if [ "$$failed" -eq 0 ]; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Congratulations you passed all $(GREEN)$$passed$(RESET) texture tests."; \
		else \
			echo "$(ORANGE)$(PREFIX)$(RESET) Texture tests: $(GREEN)$$passed$(RESET) passed, $(RED)$$failed$(RESET) failed."; \
		fi; \
		exit $$status'

tester: test_invalid test_textures

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

.PHONY: all clean fclean re bonus start test_invalid test_textures tester
