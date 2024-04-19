#include "../Server/Server.hpp"
#include<string.h>
/*

message from 0: MODE elmaa

message from 0: WHO elmaa

message from 0: MODE elmaa b

message from 0: PRIVMSG elmaa :ben geldim kral

privmsg Pragma Hello! ** burada sadece 1 kişiye mesaj yollanmış
privmsg Pragma,Crocodile Hello to you both! ** burada ise iki kişiye yollanmış
privmsg #kvirc Hello from outside! ** burada channel'a yollanmış

*/

void    Server::Privmsg(int index, int id)
{
    std::string message = "";

    for (size_t i = 2; i < this->commands.size(); i++)
    {
        message += commands[i];
        message += " ";
    }
    // for (size_t i = 0; i < commands.size(); i++)
    // {
    //     std::cout <<"commands[i]" << commands[i] << std::endl;
    // }

    for (size_t i = 0; i < clients.size(); i++)
    {
        if (strcmp(commands[1].c_str(), channels[i].getChannelName().c_str()) == 0)
        {
            std::vector<Client> tmp_client = channels[i].getClients();
            for (size_t j = 0; j < tmp_client.size(); j++)
            {
                tmp_client[j].print(":" + clients[id].getNickName() + "!" + clients[id].getUserName() + '@' + clients[id].getIp() + " PRIVMSG " + channels[i].getChannelName() + " :"+ message + "\r\n");
            }
        }
    }

    // if(this->commands[1].compare(this->clients[i].getNick()) == 0)
    // {
        // clients[i].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
        // client.print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + clients[i].getNick() + " :" + message + "\r\n");
        // return ;
    // }
    // else if (this->commands[1].compare(this->channels[i].getName()) == 0)
    // {
        // for (size_t m = 0; m < this->channels[i].getMembers().size(); m++)
            // this->channels[i].getMembers()[m].print(":" + client.getNick() + "!" + client.getUsername() + '@' + client.getRealIp() + " PRIVMSG " + this->channels[i].getName() + " :"+ message + "\r\n");
        // return ;
    // }
}
