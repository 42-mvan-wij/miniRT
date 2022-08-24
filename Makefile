# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/27 15:19:55 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/08/24 16:56:05 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

PROJECT		:= miniRT
NAME		:= miniRT
NAME_BONUS	:= miniRT

LIBFT		:= libft/libft.a
MLX42		:= MLX42/libmlx42.a

CC			:= cc
CFLAGS		+= -Wall -Wextra -Werror -O3 $(if $(DEBUG), -g3) $(if $(SANITIZE), -fsanitize=address -g3)

################################################################################

USER_LIBS += $(LIBFT) $(MLX42)
ifeq ($(and $(shell which pkg-config),$(if $(shell pkg-config --exists --print-errors glfw3 2>&1),,yes)),yes) # if pkg-config is installed, and it can find glfw3, use it
LIB_DIRS += $(shell pkg-config --libs-only-L glfw3)
LIB_LOADS += $(shell pkg-config --libs-only-l glfw3)
else
SYSTEM_LIBS += glfw3
endif
FRAMEWORKS += Cocoa OpenGL IOKit

HEADERS += src/input/input.h src/structs.h src/input/input_structs.h src/utils/error_structs.h src/utils/utils.h src/render/render_structs.h src/render/render.h

INCLUDE_HEADERS := $(dir $(LIBFT))/libft.h $(dir $(MLX42))/include/MLX42/MLX42.h

SOURCES += src/test.c src/input/parse_scene.c src/utils/error.c src/render/render.c

################################################################################

ifdef BONUS
NAME	:= $(NAME_BONUS)
HEADERS +=
SOURCES	+=
CFLAGS	+= -DBONUS
endif

ifdef DEBUG
CFLAGS	+= -g3 -O0 -DDEBUG
endif

################################################################################

HEADERS := $(sort $(HEADERS) $(INCLUDE_HEADERS))

OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))
INCLUDE_FLAGS += $(addprefix -I, $(sort $(dir $(HEADERS))))
LIB_DIRS += $(addprefix -L, $(sort $(dir $(USER_LIBS))))
LIB_LOADS += $(addprefix -l, $(patsubst lib%,%,$(sort $(basename $(notdir $(USER_LIBS))))) $(sort $(SYSTEM_LIBS)) ) $(addprefix -framework , $(sort $(FRAMEWORKS)))

export CFLAGS := $(sort $(CFLAGS))
export LIB_FLAGS := $(sort $(LIB_DIRS)) $(LIB_LOADS)

DATA_FILE := .make_data.txt
MAKE_DATA := $(shell uname) $(CFLAGS) $(LIB_FLAGS) $(INCLUDE_FLAGS) $(sort $(OBJECTS))
ifneq ($(shell echo $(MAKE_DATA)), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES := clean
endif

################################################################################

BLUE_FG := \e[34m
RESET_COLOR := \e[0m
GREEN_FG := \e[32m
CYAN_FG := \e[36m
CLEAR_REST_OF_LINE := \e[K
print_prefix = printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(1)]" "$(2)"
exec_no_nl = printf "$(1)$(CLEAR_REST_OF_LINE)\n"; $(1); printf "\e[A"

################################################################################

all: $(PRE_RULES) $(NAME)

$(NAME): $(USER_LIBS) $(OBJECTS)
	@$(call print_prefix,"$(PROJECT)","make")
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)
	@$(call print_prefix,"$(PROJECT)","make")
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"
	@echo $(MAKE_DATA) > $(DATA_FILE)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(call print_prefix,"$(PROJECT)","make")
	@$(call exec_no_nl,$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@)

$(LIBFT):
	@git submodule update --init --recursive
	$(MAKE) -C $(dir $(LIBFT))

$(MLX42):
	@git submodule update --init --recursive
	$(MAKE) -C $(dir $(MLX42))

debug:
	@$(MAKE) DEBUG=1

clean:
	@git submodule update --init --recursive
	@$(MAKE) -C $(dir $(LIBFT)) clean
	@$(MAKE) -C $(dir $(MLX42)) clean
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -rf $(OBJDIR)

fclean: clean
	@git submodule update --init --recursive
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	@$(MAKE) -C $(dir $(MLX42)) fclean
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(NAME)
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(DATA_FILE)

re: fclean all

run: $(NAME)
	@./$(NAME) $(ARGS)

.PHONY: all debug clean fclean re

################################################################################
