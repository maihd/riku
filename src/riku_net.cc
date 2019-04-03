// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/net.h>

#if PLATFORM_WINDOWS
#   pragma comment(lib, "ws2_32.lib")
#   include <stdio.h>
#   include <Winsock2.h>
#   include <ws2tcpip.h>
#else
#   include <stdio.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <errno.h>
#   include <string.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <arpa/inet.h>
#   include <sys/wait.h>
#   include <signal.h>
#endif

namespace net
{
    Socket::Socket(void)
        : handle(-1)
        , is_server(false)
    {
#if PLATFORM_WINDOWS
        static bool s_winsock_init;
        if (s_winsock_init)
        {
            int iResult; 
            WSADATA wsaData;

            // Initialize Winsock
            iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
            ALWAYS_ASSERT(iResult != 0, "Failed to initialized WinSocket system.");
            s_winsock_init = true;
        }
#endif
    }

    Socket::~Socket(void)
    {
    }

    void Socket::close(void)
    {
#if PLATFORM_WINDOWS
        ::closesocket(handle);
#else
        ::close(handle);
#endif
        handle = -1;
        is_server = false;
    }

    Socket Socket::accept(void)
    {
        int fd = ::accept(handle, NULL, NULL);
        
        Socket socket;
        socket.handle    = fd;
        socket.is_server = false;
        return socket;
    }

    int Socket::recv(void* buffer, int length)
    {
        return (int)::recv(handle, (char*)buffer, length, 0);
    }

    int Socket::send(const void* buffer, int length)
    {
        return (int)::send(handle, (char*)buffer, length, 0);;
    }

    bool is_ip(const char* input)
    {
        return is_ipv4(input) || is_ipv6(input);
    }

    bool is_ipv4(const char* input)
    {
        struct sockaddr_in sa;
        return inet_pton(AF_INET, input, &(sa.sin_addr)) != 0;
    }

    bool is_ipv6(const char* input)
    {
        struct sockaddr_in6 sa;
        return inet_pton(AF_INET6, input, &(sa.sin6_addr)) != 0;
    }

    Socket connect(const char* host, int port)
    {
        int rv;
        int sockfd;
        struct addrinfo hints, *servinfo, *p;

        memory::zero(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        char port_str[32];
        if ((rv = getaddrinfo(host, string::format(port_str, 32, "%d", port), &hints, &servinfo)) != 0)
        {
            console::error("getaddrinfo: %s\n", gai_strerror(rv));
            return Socket();
        }

        // loop through all the results and connect to the first we can
        for (p = servinfo; p != NULL; p = p->ai_next) 
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {
                perror("client: socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
            {
#if PLATFORM_WINDOWS
                ::closesocket(sockfd);
#else
                ::close(sockfd);
#endif
                perror("client: connect");
                continue;
            }

            break;
        }

        freeaddrinfo(servinfo);
        if (p == NULL) 
        {
            console::error("client: failed to connect\n");
        }


        // Result
        Socket socket;
        socket.handle = sockfd;
        socket.is_server = false;
        return socket;
    }

    Socket create_server(const char* host, int port)
    {
        int rv;
        int sockfd;
        struct addrinfo hints, *servinfo, *p;

        memory::zero(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP
        char port_str[32];
        if ((rv = getaddrinfo(host, string::format(port_str, 32, "%d", port), &hints, &servinfo)) != 0) 
        {
            console::error("getaddrinfo: %s\n", gai_strerror(rv));
            return Socket();
        }

        // loop through all the results and bind to the first we can
        for (p = servinfo; p != NULL; p = p->ai_next) 
        {
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
            {
                perror("server: socket");
                continue;
            }

#if PLATFORM_WINDOWS
            char yes = 1;
#else
            int yes = 1;
#endif
            if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) 
            {
                perror("setsockopt");
                exit(1);
            }

            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
            {
#if PLATFORM_WINDOWS
                ::closesocket(sockfd);
#else
                ::close(sockfd);
#endif
                perror("server: bind");
                continue;
            }

            break;
        }

        freeaddrinfo(servinfo);
        if (p == NULL) 
        {
            console::error("server: failed to bind\n");
            exit(1);
        }

        if (listen(sockfd, 256) == -1) 
        {
            perror("listen");
            exit(1);
        }

        // Result
        Socket socket;
        socket.handle = sockfd;
        socket.is_server = true;
        return socket;
    }
}