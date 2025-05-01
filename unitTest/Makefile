# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 08:27:57 by nfordoxc          #+#    #+#              #
#    Updated: 2025/05/01 15:05:40 by fdehan           ###   ########.fr        #
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

RM				=	rm -f

################################################################################
#	Test class Server full													   #
################################################################################

SERVER_SRC		=	../class/Server.cpp \
					../class/Location.cpp \
					../class/Directive.cpp \
					../class/MethodHTTP.cpp \
					../class/HandleConfig.cpp \
					../class/HttpBase.cpp \
					../class/HttpRequest.cpp \
					../class/EventMonitoring.cpp \
					../class/EventData.cpp \
					../class/HttpResponse.cpp \
					../class/Socket.cpp \
					../class/Nico.cpp \
					../class/Ressource.cpp \
					../class/RessourcesManager.cpp \
					../class/RequestHandling.cpp \
					main_fullServer.cpp

SERVER_OBJ		=	$(SERVER_SRC:.cpp=.o)

SERVER_NAME		=	test_classServer

################################################################################
#	Test networking												   #
################################################################################

NET_SRC			=	../class/Server.cpp \
					../class/Location.cpp \
					../class/Directive.cpp \
					../class/MethodHTTP.cpp \
					../class/HandleConfig.cpp \
					../class/HttpBase.cpp \
					../class/HttpRequest.cpp \
					../class/EventMonitoring.cpp \
					../class/EventData.cpp \
					../class/HttpResponse.cpp \
					../class/Socket.cpp \
					../class/Ressource.cpp \
					../class/RessourcesManager.cpp \
					../class/RequestHandling.cpp \
					main_networking.cpp

NET_OBJ			=	$(NET_SRC:.cpp=.o)

NET_NAME		=	test_networking

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
NB_SERVER		=	$(words $(SERVER_SRC))
NB_NET			=	$(words $(NET_SRC))
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

.PHONY : all server networking deb_serv deb_net clean fclean re help

all: 		help

server:		NUM_FILES=$(NB_SERVER)
server:		$(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(SERVER_OBJ) $(MYLIBS) -o $(SERVER_NAME)
	@echo "$(CGREEN)The programm $(SERVER_NAME) successfully compilled"

networking:	NUM_FILES=$(NB_NET)
networking:	$(NET_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(NET_OBJ) $(MYLIBS) -o $(NET_NAME)
	@echo "$(CGREEN)The programm $(NET_NAME) successfully compilled"

%.o :		%.cpp
	$(call compile_c_to_o)

deb_serv:		server 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(SERVER_NAME) $(DEB_OUT)

deb_net:		networking 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(NET_NAME) $(DEB_OUT)

clean:
	$(call delete_progress, *.o)
	$(call delete_progress, ../class/*.o)

fclean: 	clean
	$(call delete_file, $(SERVER_NAME))
	$(call delete_file, $(NET_NAME))

re : 		fclean all

help:
	@echo "usage: make server|networking|..."
	@echo "usage: make deb_serv | deb_net for running with valgrind"
