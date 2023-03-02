NAME = minishell
SRCS = exec/child.c exec/env.c exec/env_2.c exec/exec.c exec/ft_cd.c exec/ft_cd_2.c exec/ft_echo.c exec/ft_env_2.c exec/ft_exit.c exec/ft_export.c exec/ft_export2.c exec/ft_main_wait.c exec/ft_one_cmd.c exec/ft_unset.c exec/red.c exec/utils.c exec/utils2.c exec/utils3.c exec/utils4.c \
		parsing/ft_here_doc_parse.c parsing/ft_hsub_heredoc.c parsing/ft_lst.c parsing/ft_parse.c parsing/ft_parse_2.c parsing/ft_parse_free.c parsing/ft_part_1.c parsing/ft_part_3.c parsing/ft_part_3_5.c parsing/ft_part_4.c parsing/ft_part_4_expand.c parsing/ft_part_4_join.c parsing/ft_part_5.c parsing/ft_part_5_utils.c parsing/ft_part_sub_3_5.c parsing/parse_utils.c parsing/parse_utils_2.c parsing/queue.c parsing/vector.c \
		main.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:fclean all
