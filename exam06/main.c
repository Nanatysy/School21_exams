#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_client
{
    int fd;
    int id;
    struct s_client* next;
}               t_client;

t_client* g_client = NULL;

int sock, id = 0;
fd_set r_fd, w_fd, c_sock;
char msg[42];
char str[42*4096], tmp[42*4096], buf[42*4096 + 42];

void my_syscall_error()
{
    write(2, "Fatal error\n", strlen("Fatal error\n"));
    close(sock);
    exit(1);
}

int get_id(int fd)
{
    t_client* tmp = g_client;

    while (tmp) {
        if (tmp->fd == fd)
            return tmp->id;
        tmp = tmp->next;
    }
    return -1;
}

int get_max_fd()
{
    t_client* tmp = g_client;
    int max = sock;

    while (tmp) {
        if (tmp->fd > max) {
            max = tmp->fd;
        }
        tmp = tmp->next;
    }
    return max;
}

void send_all(int fd, char* msg)
{
    t_client* tmp = g_client;
    while (tmp) {
        if (tmp->fd != fd && FD_ISSET(fd, &w_fd)) {
            if (send(tmp->fd, msg, strlen(msg), 0) < 0) {
                my_syscall_error();
            }
        }
        tmp = tmp->next;
    }
}

int add_client_to_list(int fd)
{
    t_client* client = calloc(1, sizeof(t_client));
    client->fd = fd;
    client->id = id++;
    client->next = NULL;

    t_client* tmp = g_client;

    if (!tmp) {
        g_client = client;
        return client->id;
    }
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = client;
    return client->id;
}

void add_client()
{
    struct sockaddr_in client_add;
    int len = sizeof(client_add);
    int client_fd;
    client_fd = accept(sock, (struct sockaddr *)&client_add, &len);
    if (client_fd < 0) {
        my_syscall_error();
    }
    sprintf(msg, "server: client %d just arrived\n", add_client_to_list(client_fd));
    send_all(client_fd, msg);
    FD_SET(client_fd, &c_sock);
}

int remove_client(int fd)
{
    t_client* tmp = g_client;
    t_client* del;
    int id = get_id(fd);
    if (tmp && tmp->fd == fd) {
        // remove root
        free(g_client);
        g_client = NULL;
    }
    while (tmp->next && tmp->next->fd != fd) {
        tmp = tmp->next;
    }
    del = tmp->next;
    tmp->next = tmp->next->next;
    free(del);
    return(id);
}

void exchange_msg(int fd)
{
    int i = 0;
    int j = 0;

    while (str[i]) {
        tmp[j] = str[i];
        j++;
        if (str[i] == '\n') {
            sprintf(buf, "client %d: %s", get_id(fd), tmp);
            send_all(fd, buf);
            bzero(buf, strlen(buf));
            bzero(tmp, strlen(tmp));
            j = 0;
        }
        i++;
    }
    bzero(str, strlen(str));
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        my_syscall_error();
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));

    uint16_t port = atoi(argv[1]);

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
    servaddr.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(sock, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        my_syscall_error();
    }
    if (listen(sock, 0) != 0) {
        my_syscall_error();
    }

    FD_ZERO(&c_sock);
    FD_SET(sock, &c_sock);
    bzero(buf, strlen(buf));
    bzero(tmp, strlen(tmp));
    bzero(str, strlen(str));
    while (1) {
        w_fd = r_fd = c_sock;

        if (select(get_max_fd() + 1, &r_fd, &w_fd, NULL, NULL) < 0) {
            continue;
        }

        for (int fd = 0; fd <= get_max_fd(); ++fd) {
            if (FD_ISSET(fd, &r_fd)) {
                if (fd == sock) {
                    bzero(msg, strlen(msg));
                    add_client();
                    break;
                }
                if (recv(fd, str, sizeof(str), 0) <= 0) {
                    bzero(msg, strlen(msg));
                    sprintf(msg, "server: client %d just left\n", remove_client(fd));
                    send_all(fd, msg);
                    FD_CLR(fd, &c_sock);
                    close(fd);
                    break;
                }
                else {
                    exchange_msg(fd);
                }
            }

        }
    }

    return (0);
}