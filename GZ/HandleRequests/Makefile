CC = c++
CFLAG = -Wall -Wextra -Werror -std=c++98
NAME = webserv c++98
NAME = Serverserv
SRC = main.cpp HandleRequests.cpp ../../class/HttpRequest.cpp \
../../class/HttpBase.cpp ../../class/Server.cpp ../../class/Directive.cpp \
../../class/MethodHTTP.cpp ../../class/Location.cpp ../../class/HandleConfig.cpp \
../../class/Socket.cpp ../../class/HttpResponse.cpp ../../class/EventMonitoring.cpp \
../../class/EventData.cpp 
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
