# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/16 07:02:04 by gguiulfo          #+#    #+#              #
#*   Updated: 2017/06/06 06:15:44 by jkalia           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		:= kift

CC 			:= gcc
#CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I includes -I libft/includes -I src/sam/includes
CFLAGS		+= `pkg-config --cflags pocketsphinx sphinxbase` -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\"
CFLAGS		+=  -O2 -DUSESDL `sdl-config --cflags`

LDFLAGS		+= `pkg-config --libs pocketsphinx sphinxbase`
LDFLAGS		+= -L libft/ -lft
LDFLAGS		+= `sdl-config --libs`

OBJDIR		:= obj
SRCDIR		:= src
SAMDIR		:= src/sam
OBJEXT		:= o
SRCEXT		:= c

LIBFT		:= libft/libft.a

KIFTFILES	:= kift_main
SAMFILES	:= reciter sam render output debug processframes createtransitions

SRC			:= $(addprefix $(SRCDIR)/, $(addsuffix .$(SRCEXT), $(KIFTFILES))) \
				$(addprefix $(SAMDIR)/, $(addsuffix .$(SRCEXT), $(SAMFILES)))

OBJ			:= $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.$(SRCEXT)=.$(OBJEXT))) \

MAX			:=	$(words $(OBJ))
n			:=	x
increment	=	$1 x
COUNTER		=	$(words $n)$(eval n := $(call increment,$n))

.PHONY = all clean fclean re obj

all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	@printf "\r\e[32mCompiling...(%d/%d)[DONE]\n\e[0m" $(MAX) $(MAX)
	@$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32mCompiled Executable\e[0m\n"

$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAG) -o $@ -c $<
	@printf "\r\e[32mCompiling...(%d/%d)\e[0m" $(COUNTER) $(MAX)

clean:
	@rm -rf $(OBJDIR)
	@printf "\e[32mRemoved Object Files\e[0m\n"
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@printf "\e[32mRemoved Executable\e[0m\n"
	@make -C libft fclean

re: fclean all
