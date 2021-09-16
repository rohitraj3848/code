int tcpSocketServer(int localPort)
{
    int     fd;
    int     ret;
    struct  sockaddr_in  serv_addr;
    int optval = 1;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        perror("tcpSocketServer:socket");
        return 0;
    }

    memset((char*) &serv_addr, '\0',sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(localPort);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

    ret = bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(ret < 0)
    {
        perror("tcpSocketServer:bind");
        close(fd);
        return 0;
    }
    listen(fd, 5);

    return fd;
}
