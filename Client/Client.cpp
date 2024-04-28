#include "Client.hpp"

Client::Client()
{
    this->pass = "";
    this->nick_name = "";
    this->user_name = "";
	this->ip = "";
	this->socket = -1;
    this->logged_in = 0;
}

int         Client::getSocket() { return this->socket; }

bool		Client::getLoggedIn() { return this->logged_in; }

std::string Client::getIp(){ return this->ip; }

std::string Client::getUserName(){ return this->user_name; }

std::string Client::getNickName(){ return this->nick_name;}

std::string Client::getPass(){ return this->pass; }

void        Client::setSocket(int sockfd) { this->socket = sockfd; }

void        Client::setUserName(std::string user_name) { this->user_name = user_name; }

void        Client::setNickName(std::string nick_name) { this->nick_name = nick_name; }

void        Client::setPass(std::string pass) { this->pass = pass; }

void        Client::setLoggedIn(bool sign) { this->logged_in = sign; }

void		Client::setIp(std::string ip) { this->ip = ip;}

void        Client::print(std::string str) { send(this->socket, str.c_str(), str.size(), 0); }

Client::~Client() { }