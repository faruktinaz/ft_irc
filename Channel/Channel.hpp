#pragma once

#include "../Client/Client.hpp"
#include <iostream>
#include <vector>

class Channel
{
    private:
        std::vector<Client> clients;
        std::string channelName;
		int			channelAdminSetted;
		std::string topic;
    public:
        Channel(std::string name);
        std::vector<Client> getClients();
        std::string         getChannelName();
		int					getChannelAdminSetted();
        // void                setChannelAdmin(Client client);
		void				setClients(std::vector<Client> clients);
		void				addClient(Client client);
		void				setAdmin();
        void                setTopic(std::string new_topi);
        std::string         getTopic();

        ~Channel();

};