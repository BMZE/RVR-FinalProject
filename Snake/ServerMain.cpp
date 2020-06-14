#include "Server.h"

int main(int argc, char **argv)
{
    Server server(argv[1], argv[2]);
    server.ProcessMessages();

    return 0;
}