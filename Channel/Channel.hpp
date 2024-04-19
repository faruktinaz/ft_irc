#pragma once

#include "../Client/Client.hpp"
#include <iostream>
#include <vector>

class Channel
{
    private:
        std::vector<Client> clients;
        std::string channelName;
        std::string ChannelAdmin;

    public:
        Channel(std::string name);
        std::vector<Client> getClients();
        std::string         getChannelName();
        void                setChannelAdmin(std::string adminName);
		void				addClient(Client client);
        ~Channel();

};