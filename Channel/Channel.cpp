#include "Channel.hpp"


Channel::Channel(std::string name) { this->channelName = name; this->channelAdminSetted = 0;}

std::vector<Client> Channel::getClients() { return this->clients; }

std::string         Channel::getChannelName() { return this->channelName; }

void				Channel::addClient(Client client) { clients.push_back(client); }

int					Channel::getChannelAdminSetted() { return this->channelAdminSetted; }

void				Channel::setAdmin() { this->channelAdminSetted = 1; }

void 				Channel::setClients(std::vector<Client> clients) { this->clients = clients;}

std::string         Channel::getTopic() { return topic; }

void                Channel::setTopic(std::string new_topic) { topic = new_topic; }


Channel::~Channel() { }
