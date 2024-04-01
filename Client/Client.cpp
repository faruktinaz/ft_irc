#include "Client.hpp"


Client::Client() { }
int         Client::getSocket() { return this->socket; }

std::string Client::getIp(){ return this->ip; }

std::string Client::getUserName(){ return this->user_name; }

std::string Client::getNickName(){ return this->nick_name;}

std::string Client::getPass(){ return this->pass; }



void Client::setSocket(int sockfd) {this->socket = sockfd;}
void Client::setUserName(std::string user_name) {this->user_name = user_name;}
void Client::setNickName(std::string nick_name) {this->nick_name = nick_name;}
void Client::setPass(std::string pass) {this->pass = pass;}


Client::~Client() { }