NAME = ircserver

SRCS = 	Channel/Channel.cpp Client/Client.cpp Server/Server.cpp \
		main.cpp Commands/Nick.cpp Commands/Pass.cpp Commands/User.cpp \
		Commands/Join.cpp Commands/Privmsg.cpp

OBJS = $(SRCS:.cpp=.o)
CXX_STANDARD = c++98
CXX = c++
CXXFLAGS = -g # -Wall -Wextra -Werror -std=$(CXX_STANDARD) -fsanitize=address 

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -rf $(NAME) .vscode

re: fclean all

.PHONY: all clean fclean re