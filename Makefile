TARGET		= minishell

CC			= gcc
CFLAGS		=  -fsanitize=address -g
#-Wall -Werror -Wextras
#CFLAGS		= -fsanitize=address -g
RM			= rm -rf

LIBFT_DIR	= ./libft/
LIBFT_FILE	= libft.a

INCS_DIR	= ./includes/
SRCS_DIR	= ./srcs/
OBJS_DIR	= ./objs/

SRC			= error.c \
			  main.c \
			  parse.c \
			  split.c \
			  utils_cmd_lst.c \
			  utils_redirect.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRC))
OBJS		= $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

$(TARGET) : $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -I $(INCS_DIR) -L$(LIBFT_DIR) -lft -lreadline -I/Users/jji/.brew/opt/readline/include

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)

all : $(TARGET)

clean :
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS_DIR)

fclean : clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(TARGET)

re : clean all

bonus : 

.PHONY : all clean fclean re bonus