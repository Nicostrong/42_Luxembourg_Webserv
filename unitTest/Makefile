# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 08:27:57 by nfordoxc          #+#    #+#              #
#    Updated: 2025/05/16 16:36:50 by nfordoxc         ###   Luxembourg.lu      #
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

ARG0			=	"../config/webserver.conf"

ARG1			=	"../good_config/good_1.conf"

RM				=	rm -f

################################################################################
#	Test class Server full													   #
################################################################################

SERVER_SRC		=	../class/parsing/CheckerTokens_e.cpp \
					../class/parsing/CheckerTokens_m.cpp \
					../class/parsing/CheckerTokens_p.cpp \
					../class/parsing/CheckerTokens.cpp \
					../class/parsing/ParserServerConfig_e.cpp \
					../class/parsing/ParserServerConfig_gs.cpp \
					../class/parsing/ParserServerConfig_p.cpp \
					../class/parsing/ParserServerConfig.cpp \
					../class/parsing/Token_e.cpp \
					../class/parsing/Token_gs.cpp \
					../class/parsing/Token_m.cpp \
					../class/parsing/Token_p.cpp \
					../class/parsing/Token.cpp \
					../class/server/CGIDirective_e.cpp \
					../class/server/CGIDirective_gs.cpp \
					../class/server/CGIDirective_m.cpp \
					../class/server/CGIDirective.cpp \
					../class/server/Directive_e.cpp \
					../class/server/Directive_gs.cpp \
					../class/server/Directive_m.cpp \
					../class/server/Directive.cpp \
					../class/server/Location_e.cpp \
					../class/server/Location_gs.cpp \
					../class/server/Location_m.cpp \
					../class/server/Location.cpp \
					../class/server/MethodHTTP_e.cpp \
					../class/server/MethodHTTP_gs.cpp \
					../class/server/MethodHTTP_m.cpp \
					../class/server/MethodHTTP.cpp \
					../class/server/Server_e.cpp \
					../class/server/Server_ev.cpp \
					../class/server/Server_gs.cpp \
					../class/server/Server_p.cpp \
					../class/server/Server_m.cpp \
					../class/server/Server.cpp \
					../class/server/ServerManager_gs.cpp \
					../class/server/ServerManager_m.cpp \
					../class/server/ServerManager_p.cpp \
					../class/server/ServerManager.cpp \
					../class/HandleConfig.cpp \
					../class/HttpBase.cpp \
					../class/HttpRequest.cpp \
					../class/EventMonitoring.cpp \
					../class/EventData.cpp \
					../class/HttpResponse.cpp \
					../class/RequestHandling.cpp \
					../class/Socket.cpp \
					../class/Ressource.cpp \
					../class/Uri.cpp \
					main_fullServer.cpp

SERVER_OBJ		=	$(SERVER_SRC:.cpp=.o)

SERVER_NAME		=	test_classServer

################################################################################
#	Test networking															   #
################################################################################

NET_SRC			=	../class/parsing/CheckerTokens_e.cpp \
					../class/parsing/CheckerTokens_m.cpp \
					../class/parsing/CheckerTokens_p.cpp \
					../class/parsing/CheckerTokens.cpp \
					../class/parsing/ParserServerConfig_e.cpp \
					../class/parsing/ParserServerConfig_gs.cpp \
					../class/parsing/ParserServerConfig_p.cpp \
					../class/parsing/ParserServerConfig.cpp \
					../class/parsing/Token_e.cpp \
					../class/parsing/Token_gs.cpp \
					../class/parsing/Token_m.cpp \
					../class/parsing/Token_p.cpp \
					../class/parsing/Token.cpp \
					../class/server/CGIDirective_e.cpp \
					../class/server/CGIDirective_gs.cpp \
					../class/server/CGIDirective_m.cpp \
					../class/server/CGIDirective.cpp \
					../class/server/Directive_e.cpp \
					../class/server/Directive_gs.cpp \
					../class/server/Directive_m.cpp \
					../class/server/Directive.cpp \
					../class/server/Location_e.cpp \
					../class/server/Location_gs.cpp \
					../class/server/Location_m.cpp \
					../class/server/Location.cpp \
					../class/server/MethodHTTP_e.cpp \
					../class/server/MethodHTTP_gs.cpp \
					../class/server/MethodHTTP_m.cpp \
					../class/server/MethodHTTP.cpp \
					../class/server/Server_e.cpp \
					../class/server/Server_ev.cpp \
					../class/server/Server_gs.cpp \
					../class/server/Server_p.cpp \
					../class/server/Server_m.cpp \
					../class/server/Server.cpp \
					../class/server/ServerManager_gs.cpp \
					../class/server/ServerManager_m.cpp \
					../class/server/ServerManager_p.cpp \
					../class/server/ServerManager.cpp \
					../class/HandleConfig.cpp \
					../class/HttpBase.cpp \
					../class/HttpRequest.cpp \
					../class/EventMonitoring.cpp \
					../class/EventData.cpp \
					../class/HttpResponse.cpp \
					../class/Socket.cpp \
					../class/Ressource.cpp \
					../class/RequestHandling.cpp \
					../class/CGI.cpp \
					../class/Uri.cpp \
					main_networking.cpp

NET_OBJ			=	$(NET_SRC:.cpp=.o)

NET_NAME		=	test_networking

################################################################################
#	Test parseur															   #
################################################################################

PAR_SRC			=	../class/parsing/CheckerTokens_e.cpp \
					../class/parsing/CheckerTokens_m.cpp \
					../class/parsing/CheckerTokens_p.cpp \
					../class/parsing/CheckerTokens.cpp \
					../class/parsing/ParserServerConfig_e.cpp \
					../class/parsing/ParserServerConfig_gs.cpp \
					../class/parsing/ParserServerConfig_p.cpp \
					../class/parsing/ParserServerConfig.cpp \
					../class/parsing/Token_e.cpp \
					../class/parsing/Token_gs.cpp \
					../class/parsing/Token_m.cpp \
					../class/parsing/Token_p.cpp \
					../class/parsing/Token.cpp \
					../class/server/MethodHTTP_e.cpp \
					../class/server/MethodHTTP_gs.cpp \
					../class/server/MethodHTTP_m.cpp \
					../class/server/MethodHTTP.cpp \
					../class/Ressource.cpp \
					main_parser.cpp

PAR_OBJ			=	$(PAR_SRC:.cpp=.o)

PAR_NAME		=	test_parser

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
NB_PAR			=	$(words $(PAR_SRC))
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

.PHONY : all server networking parser deb_serv deb_net deb_par clean fclean re help

all: 		help

server:		NUM_FILES=$(NB_SERVER)
server:		$(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(SERVER_OBJ) $(MYLIBS) -o $(SERVER_NAME)
	@echo "$(CGREEN)The programm $(SERVER_NAME) successfully compilled"

networking:	NUM_FILES=$(NB_NET)
networking:	$(NET_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(NET_OBJ) $(MYLIBS) -o $(NET_NAME)
	@echo "$(CGREEN)The programm $(NET_NAME) successfully compilled"

parser:		NUM_FILES=$(NB_PAR)
parser:		$(PAR_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(PAR_OBJ) $(MYLIBS) -o $(PAR_NAME)
	@echo "$(CGREEN)The programm $(PAR_NAME) successfully compilled"

%.o :		%.cpp
	$(call compile_c_to_o)

deb_serv:		server 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(SERVER_NAME)

deb_net:		networking 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(NET_NAME)

deb_par:		parser 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(PAR_NAME) $(ARG0)

clean:
	$(call delete_progress, *.o)
	$(call delete_progress, ../class/*.o)
	$(call delete_progress, ../class/parsing/*.o)
	$(call delete_progress, ../class/server/*.o)

fclean: 	clean
	$(call delete_file, $(SERVER_NAME))
	$(call delete_file, $(NET_NAME))
	$(call delete_file, $(PAR_NAME))

re : 		fclean all

help:
	@echo "usage: make server|networking|parser|..."
	@echo "usage: make deb_serv | deb_net | deb_par for running with valgrind"
