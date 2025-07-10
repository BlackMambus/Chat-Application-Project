#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    read(sock, buffer, 1024);
    std::cout << buffer;

    while (true) {
        std::string message;
        std::cout << "You: ";
        std::getline(std::cin, message);
        send(sock, message.c_str(), message.length(), 0);

        memset(buffer, 0, sizeof(buffer));
        int valread = read(sock, buffer, 1024);
        if (valread <= 0) break;
        std::cout << "Server: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
