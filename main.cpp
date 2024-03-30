#include "Server/Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
		return (0);
	Server server(atoi(argv[1]), argv[2]);
}
