# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: satkins <satkins@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2018/10/16 20:25:44 by satkins          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = n_puzzle

CC = clang++

FLAGS =  -std=c++14 -fsanitize=address
CFLAGS = -std=c++14 -Wc++11-extensions -c

################################################################################
# SOURCE FILES                                                                 #
################################################################################

SRC =		\
			puzzle \
			parser \
			AI \
			utils


################################################################################
# Source directories identifiers                                               #
################################################################################

SRCDIR = src/

FULLSRC = $(patsubst %, %.o, $(addprefix $(SRCDIR), $(SRC)))

MAINPATH = src/main.cpp

################################################################################
# INCLUDE PATHS                                                                #
################################################################################

INCLUDES = \
		-I inc

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(FULLSRC)
	@ echo "$(YELLOW)Compiling programs$(RES)"
	$(CC) $(FLAGS) $(INCLUDES) $(FULLSRC) $(MAINPATH) -o $(NAME)
	@echo "$(GREEN)Binaries Compiled$(RES)"

%.o: %.cpp
	@ echo "$(YELLOW)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += -g -DDEBUG
debug: clean $(NAME)

clean:
	rm -f $(FULLSRC)
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	rm -f $(NAME)
	@ echo "$(RED)Removing library file and binary...$(RES)"

re: fclean all
	@ echo "$(GREEN)Binary Remade$(RES)"
