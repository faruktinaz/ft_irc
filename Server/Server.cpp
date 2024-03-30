#include "Server.hpp"

std::vector<Channel> Server::getChannels() { return this->channels; }
std::vector<Client> Server::getClients() { return this->clients; }
std::vector<std::string> Server::getCommands() { return this->commands; }

int Server::perr(std::string err, int sockfd)
{
	std::cout << err << std::endl;
	close(sockfd);
	exit(-1);
}

void Server::initilizeServer()
{
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == SOCKET_ERROR)
		perr("socket KO", sockfd);

	// bağlantı koptugunda hızlıca tekrar kullanılabilmesine olanak sağlayan fonks.
	int opt = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		perr("error setting socket option", sockfd);


	if ((bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address))) < 0)
    {
		perror("bind KO");
		exit(EXIT_FAILURE);
    }
	else
		std::cout << "bind OK" << std::endl;

	listen(sockfd, 3) == SOCKET_ERROR ? perr("listen error listening on socket", sockfd) : printf("listen OK!\n");
	FD_ZERO(&readfds);
	FD_SET(sockfd, &readfds);
}

Server::Server(int port, std::string arg_pass)
{
	this->port = port;
	this->pass = arg_pass;
	initilizeServer();
	int new_socket;
	int max_sd = sockfd;
	
	while (1)
	{
		fd_set tmpfds = readfds;
		int activity = select(max_sd + 1, &tmpfds, NULL, NULL, NULL);
		if (activity < 0){perr("select error", sockfd);}

		if (FD_ISSET(sockfd, &tmpfds))
		{
			new_socket = accept(sockfd, NULL, NULL);
			if (new_socket < 0)
				perr("accept error failed", sockfd);
			else{
				std::cout << "accept connetion" << std::endl;
				send(new_socket, "Server Welcome to IRC SERVER\r\n", 23, 0);
				FD_SET(new_socket, &readfds);
				if (new_socket > max_sd)
					max_sd = new_socket;
				connected_clients.push_back(new_socket);
			}
		}
		int valread;
		char buffer[1024] = {0};
		for (int i = 0; i < connected_clients.size(); i++)
		{
			if (FD_ISSET(connected_clients[i], &tmpfds))
			{
				int valread = recv(connected_clients[i], buffer, sizeof(buffer), 0);

				//parser(buffer);
				// PASS 12USER3 USER faruk NICK n_faruk

				// PASS 123
				// USER faruk
				// std::string identity = ":n_faruk!faruk@127.0.0.1 JOIN #a\r\n"; // buraya ( ":" + users.getnickname() + "!" + users.getusername() + "@" + users.gethost() + " JOIN " + channelName)
				// send(new_socket , identity.c_str(), identity.size(), 0);

				if (valread > 0)
				{
					// add send message to other clients
					std::cout << "message from " << i << ": " <<  buffer << std::endl;
					memset(buffer, 0, sizeof(buffer));
				}
				else if (valread == 0)
				{
					std::cout << "client disconnected" << i << std::endl;
					close(connected_clients[i]);
					connected_clients.erase(connected_clients.begin()+i);
					--i;
				}
			}
		}
	};
}


Server::~Server() { }