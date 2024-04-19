#pragma once
#include "iostream"
#include <sys/socket.h>

class Client
{
    private:
        int         socket;
        int         logged_in;
        std::string user_name;
        std::string nick_name;
        std::string pass;
        std::string ip;
    public:
		Client();
        int         getSocket();
        int         getLoggedIn();
        std::string getUserName();
        std::string getNickName();
        std::string getPass();
        std::string getIp();

		void        print(std::string str);
		void        setSocket(int sockfd);
        void        setLoggedIn(int sign);
        void        setUserName(std::string user_name);
        void        setNickName(std::string nick_name);
        void        setPass(std::string pass);
		void		setIp(std::string ip);


		~Client();
};