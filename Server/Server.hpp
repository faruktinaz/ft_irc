#pragma once

#include "../Channel/Channel.hpp"
#include "../Client/Client.hpp"
#include <vector>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
#include <string.h>

# define SOCKET_ERROR 	-1
# define PASS			"PASS"
# define JOIN			"JOIN"
# define USER			"USER"
# define WHO			"WHO"
# define QUIT			"QUIT"
# define PART			"PART"
# define TOPIC			"TOPIC"
# define LIST			"LIST"
# define NICK			"NICK"
# define JOIN 			"JOIN"
# define PRIVMSG		"PRIVMSG"
# define KICK			"KICK"

class Server
{
    private:
	    struct sockaddr_in			server_address;
		typedef void(Server::*fpoint)(int, int);
        std::vector<Channel>		channels;
        std::vector<Client>			clients;
        std::vector<std::string>	commands;
		std::vector<int>			connected_clients;

		int							sockfd;
		int							acceptFd;
		int 						port;
		std::string					serverIp;
		std::string					pass;
		fd_set 						readfds;

    public:
		Server(int port, std::string arg_pass);
		std::vector<Channel> 		getChannels();
		std::vector<std::string>	getCommands();
		std::vector<Client> 		getClients();

		void    					Part(int index, int id);
		void    					Topic(int index, int id);
		void    					Quit(int index, int id);
		void						executeCommand(int clientsockt);
		void						User(int index, int id);
		void						Pass(int index, int id);
		void						Nick(int index, int id);
		void						Join(int index, int id);
		void						Who(int index, int id);
		void						List(int index, int id);
		void						Kick(int index, int id);
		void 						excWho(int id);
		void						Privmsg(int index, int id);
		void    					Part2(int index, int id, Channel& channel, int flag);

		int							isInChannel(std::vector<Client> c_clients, std::string name);
		int							getChannelIndex(std::string name);
		int							getClientIndex(std::string name);
		int							getServerFd();
		int							getAcceptFd();
		int							getPort();
		void						initilizeServer();
		int 						perr(std::string err, int sockfd);
		void						checkCommands(Server &server, std::string buffer, int socket);
		~Server();
};
