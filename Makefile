# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/26 15:56:35 by frmarinh          #+#    #+#              #
#    Updated: 2018/05/26 15:56:42 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_STRACE	=	ft_strace
NAME		=   ft_strace

CC			=	gcc
FLAGS		=
FLAGS_O		=

SRCDIR_STRACE		=	srcs/
OBJDIR_STRACE		=	objs/

INCDIR				=	includes/

SRCBASE_STRACE	=	\
					main.c              	\
					child.c					\
					tracer.c				\
					flags.c					\

INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_STRACE			=	$(addprefix $(SRCDIR_STRACE), $(SRCBASE_STRACE))
OBJS_STRACE			=	$(addprefix $(OBJDIR_STRACE), $(SRCBASE_STRACE:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_STRACE) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make STRACE;  																\
	fi

$(OBJDIR_STRACE):
	mkdir -p $(OBJDIR_STRACE)
	mkdir -p $(dir $(OBJS_STRACE))

$(OBJDIR_STRACE)%.o : $(SRCDIR_STRACE)%.c | $(OBJDIR_STRACE)
	$(CC) $(FLAGS) -c $< -o $@												\
		-I $(INCDIR)														\
		-I $(INCDIR)

fcleanlib:	fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

STRACE: $(OBJDIR_STRACE) $(OBJS_STRACE)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_STRACE) $(OBJS_STRACE)
	echo "📗  MAKE $(NAME_STRACE)"

clean:
	if [ -d $(OBJDIR_STRACE) ]; then rm -R $(OBJDIR_STRACE) && echo "📕  CLEAN  $(OBJDIR_STRACE)"; fi

fclean:		clean
	if test -f $(NAME_STRACE) ; then											\
		rm -R $(NAME_STRACE) && echo "📕  FCLEAN  $(NAME_STRACE)";				\
	else																		\
		printf "\r";															\
	fi

-include $(OBJS:.o=.d)
