#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void checkRDP(char *filename, char *outputf)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("Error: Can't Open File %s\n",filename);
        return;
    }
    FILE *output = fopen(outputf, "w");
    if (output == NULL){
        printf("Error: Can't Create File %s\n",outputf);
        fclose(file);
        return;
    }
    char address[100];
    while (fgets(address, sizeof(address), file)){
        address[strcspn(address, "\n")] = '\0';
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1){
            perror("Error: Can't Create Connection TCP (Socket)");
            fclose(file);
            fclose(output);
            return;
        }
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(address);
        server.sin_port = htons(3389);
        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0){
            printf("Closed: %s\r", address);
        }else{
            fprintf(output, "%s\n", address);
        }
    }
    fclose(file);
    fclose(output);
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Please Run To Format --> main.exe or ./main servers.txt result.txt\n");
        return 1;
    } 
    checkRDP(argv[1], argv[2]);
    return 0;
}
