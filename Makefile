NAME = minishell
SRCS = child.c env.c env_2.c exec.c ft_cd.c ft_cd_2.c ft_echo.c ft_env_2.c ft_exit.c ft_export.c ft_export2.c ft_main_wait.c ft_one_cmd.c ft_unset.c red.c utils.c utils2.c utils3.c utils4.c \
		ft_here_doc_parse.c ft_hsub_heredoc.c ft_lst.c ft_parse.c ft_parse_2.c ft_parse_free.c ft_part_1.c ft_part_3.c ft_part_3_5.c ft_part_4.c ft_part_4_expand.c ft_part_4_join.c ft_part_5.c ft_part_5_utils.c ft_part_sub_3_5.c parse_utils.c parse_utils_2.c queue.c vector.c \
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
