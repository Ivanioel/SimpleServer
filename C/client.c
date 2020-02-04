#include <stdio.h>
#include <time.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <sys/types.h> 

#define SERVER_PORT 9999
#define TAM_BUFF 1024

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in server;
    char msg[TAM_BUFF]; 
    printf("Introduce un mensaje en minusculas: ");
    scanf("%s", msg);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear el socket\n");
        return 1;
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET; 
    // LocalHost
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // htons guarda los bytes del puerto en orden en memoria
    server.sin_port = htons(SERVER_PORT);

    if ((connect(sock, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        perror("Error al hacer la conexion\n");
        return 1;
    }

    printf("Conexion con el servidor realizada con exito\nEnviando mensaje:\n");
    printf("%s\n", msg);
    send(sock, msg, TAM_BUFF, 0);

    recv(sock, msg, TAM_BUFF, 0);
    printf("%s\n", msg);
    close(sock);
    return 0;
}
