#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const static char* msg1 = "Send me your ID";
const static char* msg2 = "I need you to do something for me";
const static char* msg3 = " code ";
const static char* msg4 = "Compute the sum of first 5 digits of your student ID";
const static char* msg5 = "Send me the integral part of the first coordinate";
const static char* msg6 = "Send me the integral part of the second coordinate";
const static char* msg7 = "X.Y.";
const static char* msg8 = "PRIMENUMBER";
const static char* msg9 = "Then send me the string Trinity";
const static char* msg10 = "Ako nazyvame cislene sustavy, ktore mozeme rozvinut do mocninoveho radu";
const static char* msg11 = "Ako sa vola obojsmerna komunikacia, v pripade ze v jednej jednotke casu ide komunikacia iba jednym smerom";
const static char* msg12 = "BONUS";

const static char* serverPrefix = "[SERVER]";
const static char* clientPrefix = "[CLIENT]";

const static char* host = "147.175.115.34";
const static int port = 777;
const static int id = 135721;
const static int second_id = 135721;

int static status, valread, client_fd;
struct sockaddr_in serv_addr;

const static int bufferSize = 1024;
static char buffer[bufferSize] = {0};

const static int lineSize = 1024;
static char line[lineSize] = {0};

// void slowPrint(char* line) {
//     printf("asd");
//     for (int i = 0; i < strlen(line); i++) {
//         printf("%c", line[i]);
//         usleep(1000000);
//     }
// }

void appendFile(char* message, char* sender) {
    FILE* file = fopen("myfile2.txt", "a");
    fprintf(file, "%s %s\n", sender, message);
    fflush(file);
}

int parseLine(const char* input) {
    if (strstr((char*)input, msg1))
        return 1;
    if (strstr((char*)input, msg2))
        return 2;
    if (strstr((char*)input, msg3))
        return 3;
    if (strstr((char*)input, msg4))
        return 4;
    if (strstr((char*)input, msg5))
        return 5;
    if (strstr((char*)input, msg6))
        return 6;
    if (strstr((char*)input, msg7))
        return 7;
    if (strstr((char*)input, msg8))
        return 8;
    if (strstr((char*)input, msg9))
        return 9;
    if (strstr((char*)input, msg10))
        return 10;
    if (strstr((char*)input, msg11))
        return 11;
    if (strstr((char*)input, msg12))
        return 0;
    return -1;
}

int main(int argc, char const* argv[]) {

    FILE* file = fopen("myfile2.txt", "a");

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    while (1) {
        valread = read(client_fd, buffer, 1024 - 1);

        if (!valread) {
            continue;
        }

        switch (parseLine(buffer)) {
        case 1:
            printf("%s", buffer);
            break;

        default:
            break;
        }
    }

    // // slowPrint(buffer);

    // snprintf(line, 1024, "%d\n", id);
    // send(client_fd, line, strlen(line), 0);

    // send(client_fd, line, strlen(line), 0);
    // printf("client: %s\n", line);

    // valread = read(client_fd, buffer, 1024 - 1);
    // // slowPrint(buffer);

    close(client_fd);

    fclose(file);
    return 0;
}
