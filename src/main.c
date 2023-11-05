#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int showip(char service[], char port[]) {
    int status;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *p;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6, AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    // hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(service, port, &hints, &res)) != 0) // getaddrinfo gets address info like youtube.com
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s\n", service);
    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;  // address in binary form
        char *ipver; // address in text form
        if (p->ai_family == AF_INET)
        { // ipv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else
        { // ipv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr); // convert ipv4 or ipv6 binary to text (ipstr)
        printf("\t%s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res);
    return 0;
}

#include <sys/types.h>
#include <sys/socket.h>

int get_addr(char service[], char port[], struct addrinfo* res) 
{
    int status;
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6, AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    if ((status = getaddrinfo(service, port, &hints, &res)) != 0) // getaddrinfo gets address info like youtube.com
    {
        return status;
    }
    return 0;
}

int main()
{
    
    // showip("youtube.com", NULL);
    // showip("localhost", "80");
    // showip("eolymp.com", "8080");
    struct addrinfo* res = NULL; 
    int status;
    status = get_addr("youtube.com", NULL, res);
    if (status != 0) {
        printf("get addr failed\n");
        return 1;
    } 
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        printf("socket failed errno edited\n");
        return 1;
    }
    int yes = 1;
    // // for servers
    // status = bind(sockfd, res->ai_addr, res->ai_addrlen);
    // if (status != 0)
    // {
    //     printf("bind failed errno edited\n");
    //     return 1;
    // }

    // // lose the pesky "Address already in use" error message
    // if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
    // {
    //     perror("setsockopt");
    //     exit(1);
    // }
    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status != 0) {
        printf("connect failed errno edited\n");
        return 1;
    }

    return 0;
}