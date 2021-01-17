##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

GPP			=	g++

RM			=	rm -rf

NAME		=	plazza

COMPILEFLAG	=	-g

INCLUDE		=	-Iinclude/ -pthread

CPPFLAGS    =	$(COMPILEFLAG) $(INCLUDE)

SRC			=	src/main.cpp						\
				src/Core/ErrorHandling.cpp			\
				src/Core/Shell.cpp					\
				src/Core/Parser.cpp					\
				src/Plazza/Reception.cpp			\
				src/Plazza/Kitchens.cpp				\
				src/Plazza/Pizza.cpp				\
				src/Encapsulation/Serialization.cpp \
				src/Encapsulation/ThreadPool.cpp	\
				src/Core/IPC.cpp					\
				src/Core/Utils.cpp					\
				src/Encapsulation/condVar.cpp		\
				src/Encapsulation/Fork.cpp

SRCTEST		=	src/Core/ErrorHandling.cpp			\
				src/Core/Shell.cpp					\
				src/Core/Parser.cpp					\
				src/Plazza/Reception.cpp			\
				src/Plazza/Kitchens.cpp				\
				src/Plazza/Pizza.cpp				\
				src/Encapsulation/Serialization.cpp \
				src/Encapsulation/ThreadPool.cpp	\
				src/Core/IPC.cpp					\
				src/Core/Utils.cpp					\
				src/Encapsulation/condVar.cpp		\
				src/Encapsulation/Fork.cpp			\
				tests/Test_reception.cpp			\
				tests/Test_fork.cpp

OBJ			=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo -e "\033[01m\033[31mLinking ...\033[00m"
	@$(GPP) $(OBJ) -o $(NAME) $(CPPFLAGS) $(CPPFLAGS)
	@echo -e "\033[01m\033[32mStandard compilation done => ${NAME}\033[00m"

clean:
	@$(RM) vgcore.* src/Plazza/*.o *.gcno
	@$(RM) src/*.o src/Encapsulation/*.o src/Core/*.o *.gcda
	@echo -e "\033[01m\033[31mRemoving useless files ...\033[00m"

fclean:	clean
	@$(RM) $(NAME) unit_tests
	@echo -e "\033[01m\033[31mRemoving binary : {${NAME}} ...\033[00m"

re:	fclean
	@make all --no-print-directory

tests_run:
	@g++ -o unit_tests $(SRCTEST) --coverage -lcriterion -Iinclude/ -pthread
	@./unit_tests
	@gcovr
	@gcovr -b

.PHONY:	all clean fclean re
