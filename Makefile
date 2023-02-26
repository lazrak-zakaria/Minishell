NAME = minishell
SRCS = exec/child.c exec/env.c exec/env_2.c exec/exec.c exec/ft_cd.c exec/ft_cd_2.c exec/ft_echo.c exec/ft_exit.c exec/ft_export.c exec/ft_export2.c exec/ft_one_cmd.c exec/ft_unset.c exec/red.c exec/utils.c exec/utils2.c exec/utils3.c exec/utils4.c \
		parsing/ft_here_doc_parse.c parsing/ft_parse.c parsing/ft_part_1.c parsing/ft_part_2.c parsing/ft_part_3.c parsing/ft_part_3_5.c parsing/ft_part_4.c parsing/ft_part_5.c parsing/ft_part_sub_3_5.c parsing/queue.c parsing/vector.c \
		main.c
#     get_next_line.c get_next_line_utils.c 
CC = cc
CFLAGS = -lreadline #-fsanitize=address -g #-Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

# Path for object files
OBJ_PATH = ./objects/

# Set the path for object filescat 
OBJS := $(addprefix $(OBJ_PATH), $(OBJS))

all : $(NAME)

$(OBJ_PATH)%.o: %.c
	cc -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:fclean all
