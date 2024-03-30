#include "Client.hpp"


Client::Client() { }
int         Client::getSocket() { return this->socket; }

std::string Client::getIp(){ return this->ip; }

std::string Client::getUserName(){ return this->user_name; }

std::string Client::getNickName(){ return this->nick_name;}

std::string Client::getPass(){ return this->pass; }

Client::~Client() { }