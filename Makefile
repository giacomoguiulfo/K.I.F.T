# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/16 07:02:04 by gguiulfo          #+#    #+#              #
#*   Updated: 2017/06/06 03:26:13 by jkalia           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME	:= kift

CC 		:= gcc
#CFLAGS	+= -Wall -Wextra -Werror
CFLAGS	+= -I includes -I libft/includes
CFLAGS	+= `pkg-config --cflags pocketsphinx sphinxbase` -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\"
LDFLAGS += `pkg-config --libs pocketsphinx sphinxbase`
LDFLAGS += -L libft/ -lft
LIBFT	:= libft/libft.a

FILES	:= kift_main

OBJDIR	:= obj/
SRCDIR	:= src/

SRC = $(addsuffix .c, $(FILES))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

MAX			:=	$(words $(OBJ))
n			:=	x
increment	=	$1 x
COUNTER		=	$(words $n)$(eval n := $(call increment,$n))

.PHONY = all clean fclean re obj

all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@printf "\r\e[32mCompiling...(%d/%d)\e[0m" $(COUNTER) $(MAX)
	@$(CC) $(CFLAGS) $(LDFLAG) -o $@ -c $<

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	@printf "\r\e[32mCompiling...(%d/%d)[DONE]\n\e[0m" $(MAX) $(MAX)
	@$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32mCompiled Executable\e[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@printf "\e[32mRemoved Object Files\e[0m\n"
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@printf "\e[32mRemoved Executable\e[0m\n"
	@make -C libft fclean

re: fclean all
