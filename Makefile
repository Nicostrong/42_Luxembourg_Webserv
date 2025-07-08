# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 08:27:57 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/08 12:40:59 by fdehan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#	Makefile variables														   #
################################################################################

CXX				=	c++
CXXFLAGS		=	-Wall -Werror -Wextra -g
CXX_OPT			=	-std=c++98
CXX_DEF			=	-DDEBUG=1

DEB				=	valgrind
DEB_OPT			=	--tool=memcheck \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-fds=yes


ARG0			=	

ARG1			=	

ARG2			=	

ARG3			=	

ARG4			=	

RM				=	rm -f

################################################################################
#	Librairies																   #
################################################################################

LIB_LIBFT_DIR	=	
LIB_PRINTF_DIR	=	
LIB_GNL_DIR		=	

LIBFT_NAME		=	
FTPRINTF_NAME	=	
LIB_GNL_NAME	=	

LIB_PROG		=
LIB_OPTI		=
LIB_OPTI		=
LIB_NAME		=

MYLIBS			=	

MYLIBS_BONUS	=	

################################################################################
#	Mandatory part															   #
################################################################################

SRC				=	./src/main.cpp \
					./class/parser/CheckerTokens.cpp \
					./class/parser/CheckerTokens_e.cpp \
					./class/parser/CheckerTokens_m.cpp \
					./class/parser/CheckerTokens_p.cpp \
					./class/parser/ParserServerConfig.cpp \
					./class/parser/ParserServerConfig_p.cpp \
					./class/parser/ParserServerConfig_e.cpp \
					./class/parser/ParserServerConfig_gs.cpp \
					./class/parser/Token.cpp \
					./class/parser/Token_m.cpp \
					./class/parser/Token_p.cpp \
					./class/parser/Token_e.cpp \
					./class/parser/Token_gs.cpp \
					./class/server/CGIDirective_e.cpp \
					./class/server/CGIDirective_gs.cpp \
					./class/server/CGIDirective_m.cpp \
					./class/server/CGIDirective.cpp \
					./class/server/Directive_e.cpp \
					./class/server/Directive_gs.cpp \
					./class/server/Directive_m.cpp \
					./class/server/Directive.cpp \
					./class/server/Location_e.cpp \
					./class/server/Location_gs.cpp \
					./class/server/Location_m.cpp \
					./class/server/Location.cpp \
					./class/server/MethodHTTP_e.cpp \
					./class/server/MethodHTTP_gs.cpp \
					./class/server/MethodHTTP_m.cpp \
					./class/server/MethodHTTP.cpp \
					./class/server/Server_e.cpp \
					./class/server/Server_ev.cpp \
					./class/server/Server_gs.cpp \
					./class/server/Server_p.cpp \
					./class/server/Server_m.cpp \
					./class/server/Server.cpp \
					./class/server/ServerManager_gs.cpp \
					./class/server/ServerManager_m.cpp \
					./class/server/ServerManager_p.cpp \
					./class/server/ServerManager.cpp \
					./class/utils/Buffer.cpp \
					./class/utils/Endpoint.cpp \
					./class/utils/File.cpp \
					./class/utils/Ip.cpp \
					./class/utils/Pipe.cpp \
					./class/utils/Ressource.cpp \
					./class/utils/Uri.cpp \
					./class/utils/Fd.cpp \
					./class/events/EventData.cpp \
					./class/events/EventMonitoring.cpp \
					./class/http/HttpBase.cpp \
					./class/http/HttpExceptions.cpp \
					./class/http/HttpParser.cpp \
					./class/http/HttpRequest.cpp \
					./class/http/HttpResponse.cpp \
					./class/http/HttpSevereExceptions.cpp \
					./class/http/HttpHandling.cpp \
					./class/networking/Body.cpp \
					./class/networking/Chunk.cpp \
					./class/networking/Listener.cpp \
					./class/networking/ListenerManager.cpp \
					./class/networking/Socket.cpp \
					./class/networking/SocketManager.cpp \
					./class/handling/RequestHandling.cpp \
					./class/handling/ResponseHandling.cpp \
					./class/cgi/CgiParser.cpp \
					./class/cgi/CgiResponse.cpp \
					./class/cgi/CgiResponseHandling.cpp \
					./class/cgi/MyCGI.cpp \
					./class/cgi/MyCGI_ev.cpp \
					./class/cgi/MyCGI_gs.cpp \
					./class/cgi/MyCGI_m.cpp \
					./class/cgi/CgiBody.cpp \
					./class/cgi/CgiChunk.cpp \
					./class/HandleConfig.cpp \
					main_networking.cpp


OBJ				=	$(SRC:.cpp=.o)

NAME			=	webserv

################################################################################
#	Bonus part																   #
################################################################################

SRC_BONUS		=	

OBJ_BONUS		=	$(SRC_BONUS:.cpp=.o)

NAME_BONUS		=	

################################################################################
#	Tester part
################################################################################

SRC_TESTER		=	
BONUS_TESTER	=	

OBJ_TESTER		=	$(SRC_TESTER:.cpp=.o)
OBJ_BONUS_TESTER=	$(BONUS_TESTER:.cpp=.o)

TESTER			=	
TESTER_BONUS	=	

################################################################################
#	Colors																	   #
################################################################################

RESET			=	'\033[0m'

# Regular

BLACK			=	'\033[0;30m'
RED				=	'\033[0;31m'
GREEN			=	'\033[0;92m'
YELLOW			=	'\033[0;93m'
BLUE			=	'\033[0;94m'
PURPLE			=	'\033[0;95m'
CYAN			=	'\033[0;96m'
WHITE			=	'\033[0;97m'

# Bold

BBLACK			=	'\033[1;30m'
BRED			=	'\033[1;31m'
BGREEN			=	'\033[1;92m'
BYELLOW			=	'\033[1;93m'
BBLUE			=	'\033[1;94m'
BPURPLE			=	'\033[1;95m'
BCYAN			=	'\033[1;96m'
BWHITE			=	'\033[1;97m'

# Blink

CBLACK			=	'\033[5;30m'
CRED			=	'\033[5;31m'
CGREEN			=	'\033[5;32m'
CYELLOW			=	'\033[5;93m'
CBLUE			=	'\033[5;34m'
CPURPLE			=	'\033[5;35m'
CCYAN			=	'\033[5;36m'
CWHITE			=	'\033[5;97m'

################################################################################
#	Progress bar															   #
################################################################################

CURRENT_FILE	= 	0
NB_SRC			=	$(words $(SRC))
NB_BONUS		=	$(words $(SRC_BONUS))
NB_TESTER		=	$(words $(SRC_TESTER))
NB_TESTER_BONUS	=	$(words $(BONUS_TESTER))
SLEEP_TIME		=	0.001

################################################################################
#	Functions
################################################################################

define compile_c_to_o
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CXX_DEF) -c -o $@ $<
	@printf $(BLUE)"\r\033[K\033[0KCompiling files => $< ["
	@for i in $$(seq 0 $$(($(CURRENT_FILE)*100/$(NUM_FILES)))); do \
		printf $(YELLOW)"="; \
	done
	@printf $(BBLUE)"] $(CURRENT_FILE)/$(NUM_FILES)$(RESET)"
	@if [ $(CURRENT_FILE) -eq $(NUM_FILES) ]; then \
		echo ; \
	fi
	@$(eval CURRENT_FILE=$(if \
		$(filter $(CURRENT_FILE), $(NUM_FILES)), 0, $(CURRENT_FILE)))
endef

define delete_progress
	@$(RM) $(1) > /dev/null 2>&1
	@for i in $$(seq 100 -1 0); do \
		printf "\r\033[K\033[0K"; \
		if [ $$((i % 4)) -eq 0 ]; then \
			printf "$(BRED)DELETE - ["; \
		elif [ $$((i % 4)) -eq 1 ]; then \
			printf "$(BRED)DELETE / ["; \
		elif [ $$((i % 4)) -eq 2 ]; then \
			printf "$(BRED)DELETE | ["; \
		else \
			printf "$(BRED)DELETE \\ ["; \
		fi; \
		for j in $$(seq 0 $$i); do \
			printf '='; \
		done; \
		printf " %d/100 ]$(RESET)" $$i; \
		sleep $(SLEEP_TIME); \
	done
	@printf "\r\033[K\033[0K$(GREEN)All files $(1) of $(NAME) deleted$(RESET)\n"
endef

define delete_file
	@$(RM) $(1) > /dev/null 2>&1
	@printf "\r\033[K\033[0K$(GREEN)$(1) deleted$(RESET)\n"
endef

################################################################################
#	Rules																	   #
################################################################################

.PHONY : all $(NAME) deb clean fclean re help

all: 		$(NAME)

$(NAME):	NUM_FILES=$(NB_SRC)
$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(OBJ) $(MYLIBS) -o $(NAME)
	@echo "$(CGREEN)The programm $(NAME) successfully compilled"

%.o :		%.cpp
	$(call compile_c_to_o)

deb:			all
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
ifeq ($(arg),ARG0)
	$(DEB) $(DEB_OPT) ./$(NAME) $(ARG0) $(DEB_OUT)
else ifeq ($(arg),ARG1)
	$(DEB) $(DEB_OPT) ./$(NAME) $(ARG1) $(DEB_OUT)
else ifeq ($(arg),ARG2)
	$(DEB) $(DEB_OPT) ./$(NAME) $(ARG2) $(DEB_OUT)
else ifeq ($(arg),ARG3)
	$(DEB) $(DEB_OPT) ./$(NAME) $(ARG3) $(DEB_OUT)
else ifeq ($(arg),ARG4)
	$(DEB) $(DEB_OPT) ./$(NAME) $(ARG4) $(DEB_OUT)
else ifneq ($(arg),)
	$(DEB) $(DEB_OPT) ./$(NAME) $(arg) $(DEB_OUT)
else
	@echo "$(RESET)Usage: make deb arg=ARG0|ARG1|ARG2|ARG3|ARG4|personal_arg"
endif

clean:
	$(call delete_progress, ./src/*.o)
	$(call delete_progress, ./class/*.o)
	$(call delete_progress, ./class/*/*.o)

fclean: 	clean
	$(call delete_file, $(NAME))

re : 		fclean all

help:
	@echo "usage: make"
	@echo "usage: make deb_webserv for running with valgrind"