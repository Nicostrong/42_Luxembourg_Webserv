# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 08:27:57 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/19 15:47:52 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

################################################################################
#	Makefile variables														   #
################################################################################

CXX				=	c++
CXXFLAGS		=	-Wall -Werror -Wextra -g -O3
CXX_OPT			=	-std=c++98
CXX_DEF			=	-DDEBUG=1

DEB				=	valgrind
DEB_OPT			=	--tool=memcheck \
					--leak-check=full \
					--show-leak-kinds=all \
					--track-origins=yes \
					--track-fds=yes

ARG0			=	"../config/webserver.conf"

ARG1			=	"../good_config/good_1.conf"

RM				=	rm -f

################################################################################
#	Test class Server full													   #
################################################################################

SERVER_SRC		=	../class/parser/CheckerTokens_e.cpp \
					../class/parser/CheckerTokens_m.cpp \
					../class/parser/CheckerTokens_p.cpp \
					../class/parser/CheckerTokens.cpp \
					../class/parser/ParserServerConfig_e.cpp \
					../class/parser/ParserServerConfig_gs.cpp \
					../class/parser/ParserServerConfig_p.cpp \
					../class/parser/ParserServerConfig.cpp \
					../class/parser/Token_e.cpp \
					../class/parser/Token_gs.cpp \
					../class/parser/Token_m.cpp \
					../class/parser/Token_p.cpp \
					../class/parser/Token.cpp \
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
					../class/http/HttpBase.cpp \
					../class/http/HttpRequest.cpp \
					../class/http/HttpHandling.cpp \
					../class/http/HttpResponse.cpp \
					../class/http/HttpParser.cpp \
					../class/http/HttpExceptions.cpp \
					../class/http/HttpSevereExceptions.cpp \
					../class/events/EventData.cpp \
					../class/events/EventMonitoring.cpp \
					../class/http/HttpResponse.cpp \
					../class/handling/ResponseHandling.cpp \
					../class/handling/RequestHandling.cpp \
					../class/networking/Socket.cpp \
					../class/utils/Ressource.cpp \
					../class/utils/Uri.cpp \
					../class/utils/File.cpp \
					../class/utils/Buffer.cpp \
					../class/utils/Pipe.cpp \
					../class/utils/Ip.cpp \
					../class/networking/Body.cpp \
					../class/networking/Chunk.cpp \
					../class/HandleConfig.cpp \
					main_fullServer.cpp

SERVER_OBJ		=	$(SERVER_SRC:.cpp=.o)

SERVER_NAME		=	test_classServer

################################################################################
#	Test networking															   #
################################################################################

NET_SRC			=	../class/parser/CheckerTokens.cpp \
					../class/parser/CheckerTokens_e.cpp \
					../class/parser/CheckerTokens_m.cpp \
					../class/parser/CheckerTokens_p.cpp \
					../class/parser/ParserServerConfig.cpp \
					../class/parser/ParserServerConfig_p.cpp \
					../class/parser/ParserServerConfig_e.cpp \
					../class/parser/ParserServerConfig_gs.cpp \
					../class/parser/Token.cpp \
					../class/parser/Token_m.cpp \
					../class/parser/Token_p.cpp \
					../class/parser/Token_e.cpp \
					../class/parser/Token_gs.cpp \
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
					../class/utils/Buffer.cpp \
					../class/utils/Endpoint.cpp \
					../class/utils/File.cpp \
					../class/utils/Ip.cpp \
					../class/utils/Pipe.cpp \
					../class/utils/Ressource.cpp \
					../class/utils/Uri.cpp \
					../class/events/EventData.cpp \
					../class/events/EventMonitoring.cpp \
					../class/http/HttpBase.cpp \
					../class/http/HttpExceptions.cpp \
					../class/http/HttpParser.cpp \
					../class/http/HttpRequest.cpp \
					../class/http/HttpResponse.cpp \
					../class/http/HttpSevereExceptions.cpp \
					../class/http/HttpHandling.cpp \
					../class/networking/Body.cpp \
					../class/networking/Chunk.cpp \
					../class/networking/Listener.cpp \
					../class/networking/ListenerManager.cpp \
					../class/networking/Socket.cpp \
					../class/networking/SocketManager.cpp \
					../class/handling/MyCGI.cpp \
					../class/handling/MyCGI_ev.cpp \
					../class/handling/MyCGI_gs.cpp \
					../class/handling/MyCGI_m.cpp \
					../class/handling/RequestHandling.cpp \
					../class/handling/ResponseHandling.cpp \
					../class/cgi/CgiParser.cpp \
					../class/cgi/CgiResponse.cpp \
					../class/cgi/CgiResponseHandling.cpp \
					../class/HandleConfig.cpp \
					main_networking.cpp

NET_OBJ			=	$(NET_SRC:.cpp=.o)

NET_NAME		=	test_networking

################################################################################
#	Test parseur															   #
################################################################################

PAR_SRC			=	../class/parser/CheckerTokens_e.cpp \
					../class/parser/CheckerTokens_m.cpp \
					../class/parser/CheckerTokens_p.cpp \
					../class/parser/CheckerTokens.cpp \
					../class/parser/ParserServerConfig_e.cpp \
					../class/parser/ParserServerConfig_gs.cpp \
					../class/parser/ParserServerConfig_p.cpp \
					../class/parser/ParserServerConfig.cpp \
					../class/parser/Token_e.cpp \
					../class/parser/Token_gs.cpp \
					../class/parser/Token_m.cpp \
					../class/parser/Token_p.cpp \
					../class/parser/Token.cpp \
					../class/server/MethodHTTP_e.cpp \
					../class/server/MethodHTTP_gs.cpp \
					../class/server/MethodHTTP_m.cpp \
					../class/server/MethodHTTP.cpp \
					../class/utils/Ressource.cpp \
					main_parser.cpp

PAR_OBJ			=	$(PAR_SRC:.cpp=.o)

PAR_NAME		=	test_parser

FUNC_SRC		= ../class/Ip.cpp \
				  main_testfunc.cpp

FUNC_OBJ		=	$(FUNC_SRC:.cpp=.o)

FUNC_NAME		=	test_func

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
NB_FUNC			=	$(words $(FUNC_SRC))
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

.PHONY : all server networking parser func deb_serv deb_net deb_par clean fclean re help

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

func:	NUM_FILES=$(NB_FUNC)
func:	$(FUNC_OBJ)
	$(CXX) $(CXXFLAGS) $(CXX_OPT) $(CC_DEF) $(FUNC_OBJ) $(MYLIBS) -o $(FUNC_NAME)
	@echo "$(CGREEN)The programm $(FUNC_NAME) successfully compilled"

%.o :		%.cpp
	$(call compile_c_to_o)

deb_serv:		server 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(SERVER_NAME) 2> error

deb_net:		networking 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(NET_NAME) 2> error

deb_par:		parser 
	@echo "$(BBLUE)==========	RUN DEBUG MODE	==========$(RESET)"
	$(DEB) $(DEB_OPT) ./$(PAR_NAME) 2> error

clean:
	$(call delete_progress, *.o)
	$(call delete_progress, ../class/*.o)
	$(call delete_progress, ../class/server/*.o)
	$(call delete_progress, ../class/parser/*.o)
	$(call delete_progress, ../class/events/*.o)
	$(call delete_progress, ../class/handling/*.o)
	$(call delete_progress, ../class/http/*.o)
	$(call delete_progress, ../class/networking/*.o)
	$(call delete_progress, ../class/utils/*.o)
	$(call delete_progress, error)
	

fclean: 	clean
	$(call delete_file, $(SERVER_NAME))
	$(call delete_file, $(NET_NAME))
	$(call delete_file, $(PAR_NAME))
	$(call delete_file, $(FUNC_NAME))
	$(call delete_progress, error)

re : 		fclean all

help:
	@echo "usage: make server|networking|parser|..."
	@echo "usage: make deb_serv | deb_net | deb_par for running with valgrind"
