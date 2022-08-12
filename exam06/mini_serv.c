#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct		s_client
{
    int				fd;
    int             id;
    struct s_client	*next;
}	                t_client;

int sock, g_id=0;
fd_set w_fd, r_fd, c_fd;
char msg[42];
char str[42*4096], tmp[42*4096], buf[42*4096 + 42];

t_client *g_clients = NULL;

void syscall_error()
{
    write(2, "Fatal error\n", strlen("Fatal error\n"));
    close(sock);
    exit(1);
}

int get_id(int fd)
{
    t_client *temp = g_clients;

    while (temp)
    {
        if (temp->fd == fd)
            return (temp->id);
        temp = temp->next;
    }
    return (-1);
}

int		get_max_fd()
{
    int	max = sock;
    t_client *temp = g_clients;

    while (temp)
    {
        if (temp->fd > max)
            max = temp->fd;
        temp = temp->next;
    }
    return (max);
}

void	send_all(int fd, char *str_req)
{
    t_client *temp = g_clients;

    while (temp)
    {
        if (temp->fd != fd && FD_ISSET(temp->fd, &cpy_write))
        {
            if (send(temp->fd, str_req, strlen(str_req), 0) < 0)
                syscall_error();
        }
        temp = temp->next;
    }
}

int add_client_to_list(int fd)
{
    t_client *client = calloc(1,sizeof(t_client));
    if (!client) {
        syscall_error();
    }
    t_client *temp = g_clients;
    client->fd = fd;
    client->id = id++;
    client->next = NULL;
    if (!temp) {
        g_clients = client;
    }
    else {
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = client;
    }
    return client->id;
}

void add_client()
{
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int client_fd;

    if ((client_fd = accept(sock_fd, (struct sockaddr *)&clientaddr, &len)) < 0) {
        syscall_error();
    }
    sprintf(msg, "server: client %d just arrived\n", add_client_to_list(client_fd));
    send_all(client_fd, msg);
    FD_SET(client_fd, &curr_sock);
}

int rm_client(int fd)
{
    t_client *temp = g_clients;
    t_client *del;
    int id = get_id(fd);

    if (temp && temp->fd == fd)
    {
        g_clients = temp->next;
        free(temp);
    }
    else
    {
        while(temp && temp->next && temp->next->fd != fd)
            temp = temp->next;
        del = temp->next;
        temp->next = temp->next->next;
        free(del);
    }
    return (id);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        syscall_error();
    }

    struct servaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    uint16_t port = atoi(argv[1]);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
    servaddr.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        syscall_error();
    }

    if (listen(sock_fd, 0) < 0) {
        syscall_error();
    }

    FD_ZERO(&curr_sock);
    FD_SET(sock_fd, &curr_sock)
    bzero(&tmp, sizeof(tmp));
    bzero(&buf, sizeof(buf));
    bzero(&str, sizeof(str));
    while (true) {
        w_fd = r_fd = c_fd;

        if (select(get_max_fd() + 1, &cpy_read, &cpy_write, NULL, NULL) < 0)
            continue;
        for (int fd = 0; fd <= get_max_fd(); fd++)
        {
            if (FD_ISSET(fd, &cpy_read))
            {
                if (fd == sock)
                {
                    bzero(&msg, sizeof(msg));
                    add_client();
                    break;
                }
                else
                {
                    if (recv(fd, str, sizeof(str), 0) <= 0)
                    {
                        bzero(&msg, sizeof(msg));
                        sprintf(msg, "server: client %d just left\n", rm_client(fd));
                        send_all(fd, msg);
                        FD_CLR(fd, &curr_sock);
                        close(fd);
                        break;
                    }
                    else
                    {
                        ex_msg(fd);
                    }
                }
            }

        }
    }
    return (0);
}