############################		Variables		############################
OK_COLOR=\x1b[32;01m
DANGER_COLOR=\x1b[1;31m
YELLOW_COLOR=\x1b[0;33m
NO_COLOR=\x1b[0m

NAME = lem-in

INCS_DIR = ./includes
LIBS_DIR = ./libs
OBJS_DIR = ./objs
SRCS_DIR = ./srcs

LIBS = libft libftprintf

SRCS = main.c read_farm_map.c
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%.o))

#FLAGS += -Wall -Wextra -Werror
FLAGS += -I$(INCS_DIR)
FLAGS += $(foreach lib,$(LIBS),-I$(LIBS_DIR)/$(lib)/includes)

LIBS_FLAGS += $(foreach lib,$(LIBS),-L$(LIBS_DIR)/$(lib) -l$(lib:lib%=%))

############################		  Rules 		############################

all: $(NAME)

$(LIBS):
	@echo "$(YELLOW_COLOR)Make $@...$(NO_COLOR)"
	@$(MAKE) -C $(LIBS_DIR)/$@

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@gcc $(FLAGS) -c $< -o $@

$(OBJS): | $(OBJS_DIR)

$(NAME): $(LIBS) $(OBJS)
	@gcc $(FLAGS) $(LIBS_FLAGS) $(OBJS) -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(DANGER_COLOR)Object files cleared$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DANGER_COLOR)Build cleared$(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean

#	by rschuppe