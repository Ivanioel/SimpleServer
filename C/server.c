#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_PORT 9999
#define TAM_BUFF 1024

int main(int argc, char const *argv[])
{
    // Descriptor del socket
    int sock, client;
    struct sockaddr_in self, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[TAM_BUFF];
    ssize_t recv_tam;
    int i;

    // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
    // SOCK_STREAM: TCP | SOCK_DGRAM: UDP
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error en el creacion del socket\n");
        return 1;
    }

    // Configuramos estructura de direccion y puerto.
    bzero(&self, sizeof(self));
    self.sin_family = AF_INET;
    self.sin_port = htons(SERVER_PORT);
    self.sin_addr.s_addr = INADDR_ANY;

    // Ligamos el pruero al socket
    if(bind(sock, (struct sockaddr*)&self, sizeof(self)) != 0) {
        perror("Error en bind.\n");
        return 1;
    }

    // El descriptor y el numero maximo de peticiones que se pueden encolar
    if(listen(sock, 5) != 0){
        perror("Error escuchando.\n");
        return 1;
    }

    printf("Escuchando en [%s:%d]...\n", inet_ntoa(self.sin_addr), ntohs(self.sin_port));
    
    while(1) {
        // Esperamos a las conexiones
        client = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
        printf("Conexión desde [%s:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        recv_tam = recv(client, buffer, TAM_BUFF, 0);
        printf("Mensaje leido: %s\n", buffer);
        for (i = 0; i < strlen(buffer); i++) buffer[i] -= 32;
        send(client, buffer, TAM_BUFF, 0);

        // Cerramos conexion
        close(client);
    }
    
    // Aqui no llegamos por que no hay manejador pero en un proyecto grande lo habria
    close(sock);
    return 0;
}
