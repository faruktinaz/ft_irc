#include "Channel.hpp"


Channel::Channel(std::string name) { this->channelName = name; }

std::vector<Client> Channel::getClients() { return this->clients; }

std::string         Channel::getChannelName() { return this->channelName; }

void				Channel::addClient(Client client) { clients.push_back(client); }

// void                Channel::setChannelAdmin(Client client) { client.print("MODE")}

Channel::~Channel() { }
