NAME = ircserv

SRCS = 	Channel/Channel.cpp Client/Client.cpp Server/Server.cpp \
		main.cpp Commands/Nick.cpp Commands/Pass.cpp Commands/User.cpp \
		Commands/Join.cpp Commands/Privmsg.cpp Commands/Who.cpp Commands/Kick.cpp \
		Commands/Part.cpp Commands/Topic.cpp Commands/Quit.cpp

OBJS = $(SRCS:.cpp=.o)
CXX_STANDARD = c++98
CXX = c++
CXXFLAGS = -g #-fsanitize=address # -Wall -Wextra -Werror -std=$(CXX_STANDARD) -fsanitize=address 

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