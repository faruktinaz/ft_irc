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

int	Server::getClientIndex(std::string name)
{
	for (size_t i = 0; i < clients.size(); i++)
		if (strcmp(clients[i].getNickName().c_str(), name.c_str()) == 0)
			return (i);
	return (-1);	
}

void Server::checkCommands(Server &server, std::string buffer, int socket)
{
	std::stringstream ss(buffer);
    (void)server;
	(void)socket;
    std::string line;
    this->commands.clear();

    while(std::getline(ss, line))
    {
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(" :\r\n", prev)) != std::string::npos) // buraya ekstra olarak "#" eklendi
        {
            if (pos > prev)
                this->commands.push_back(line.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < line.length())
            this->commands.push_back(line.substr(prev, std::string::npos));
    }
}

void Server::initilizeServer()
{
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == SOCKET_ERROR)
		perr("socket KO", sockfd);

	// baglantı koptugunda hızlıca tekrar kullanılabilmesine olanak sağlayan fonks.
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


void Server::excWho(int id) // test icin 
{
	std::string info= "Username :" + clients[id].getUserName() +"\r\n"+ "Nickname :" + clients[id].getNickName() + "\r\n";
	std::cout << info << std::endl;
}

void Server::executeCommand(int id)
{
	std::vector<std::string> cmds;
	std::vector<fpoint> tfun;
	
	tfun.push_back(&Server::User);
	tfun.push_back(&Server::Nick);
	tfun.push_back(&Server::Pass);
	tfun.push_back(&Server::Join);
	tfun.push_back(&Server::Privmsg);
	tfun.push_back(&Server::Who);
	tfun.push_back(&Server::Kick);
	tfun.push_back(&Server::Part);
	tfun.push_back(&Server::Quit);
	tfun.push_back(&Server::Topic);

	cmds.push_back(USER);
	cmds.push_back(NICK);
	cmds.push_back(PASS);
	cmds.push_back(JOIN);
	cmds.push_back(PRIVMSG);
	cmds.push_back(WHO);
	cmds.push_back(KICK);
	cmds.push_back(PART);
	cmds.push_back(QUIT);
	cmds.push_back(TOPIC);

	for (size_t i = 0; i < cmds.size(); i++)
	{
		for (size_t j = 0; j < commands.size(); j++)
		{
			if ((cmds[i] == commands[j]) && (j+1 < commands.size()))
			{
				if (clients[id].getLoggedIn() || i < 3)
					(this->*tfun[i])(j, id);
				else
				{
					clients[id].print("you need to complete the registration. USER/NICK/PASS\r\n");
					break;
				}
			}
		}
	}
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
		// if (activity < 0){ perr("select error", sockfd );}

		if (FD_ISSET(sockfd, &tmpfds))
		{
			new_socket = accept(sockfd, NULL, NULL);
			Client newC;
			newC.setSocket(new_socket);
			this->clients.push_back(newC);
			if (new_socket < 0)
				perr("accept error failed", sockfd);
			else{
				std::cout << "accept connetion" << std::endl;
				// send(new_socket, "Server Welcome to IRC SERVER\r\n", 23, 0);
				FD_SET(new_socket, &readfds);
				if (new_socket > max_sd)
					max_sd = new_socket;
				connected_clients.push_back(new_socket);
			}
		}
		
		int valread;
		char buffer[1024] = {0};
		for (size_t i = 0; i < connected_clients.size(); i++)
		{
			if (FD_ISSET(connected_clients[i], &tmpfds))
			{
				int valread = recv(connected_clients[i], buffer, sizeof(buffer), 0);
                checkCommands(*this, buffer, connected_clients[i]);
				executeCommand(i);
                if (clients[i].getPass() != "" && clients[i].getNickName() != "" &&
                    clients[i].getUserName() != "" && clients[i].getLoggedIn() == 0)
                {
                    clients[i].setLoggedIn(1);
                    std::cout << "Successfully logged into the system!!" << std::endl;
					clients[i].print(":" + clients[i].getIp() + " 001 " + clients[i].getNickName() + " :Welcome to the Internet Relay Network " \
						+ clients[i].getNickName() + "!" + clients[i].getUserName() + "@" + clients[i].getIp() + "\r\n");
                }
				if (valread > 0)
				{
					// add send message to other clients
					// std::cout << "message from " << i << ": " <<  buffer << std::endl;
					memset(buffer, 0, sizeof(buffer));
				}
				else if (valread == 0)
				{
					std::cout << "client disconnected" << i << std::endl;
					connected_clients.erase(connected_clients.begin()+i);
					--i;
				}
			}
		}
	};
}


Server::~Server() { }