NAME	 = philosophers
CFLAGS	 = -Wall -Wextra -g
LDFLAGS	 = -lpthread

SRCS	 = philosophers.c arguments.c initialize.c philosopher.c timedelta.c \
			chopstick_lock.c delay.c
OBJS	:= $(SRCS:.c=.o)
OBJ_DIR	 = build

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@echo "Compiling: \t" $<
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJS))
	@echo "Linking \t" $(NAME)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo ---DONE---

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

$(OBJ_DIR):
	@echo "Build target: \t" $(NAME)
	@echo "Host: \t\t" $$(uname -rms)
	@echo "CFLAGS: \t" $(CFLAGS)
	@echo "LDFLAGS: \t" $(LDFLAGS)
	@echo ---Start---
	@mkdir -p $(OBJ_DIR)
