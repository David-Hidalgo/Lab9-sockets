#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: client <server_ip> <message>\n";
        return 1;
    }

    const char* serverIP = argv[1];
    std::string message = argv[2];

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Socket creation failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Connect failed: " << std::strerror(errno) << "\n";
        close(clientSocket);
        return 1;
    }

    int sent = send(clientSocket, message.c_str(), static_cast<int>(message.size()), 0);
    if (sent < 0) {
        std::cerr << "Send failed: " << std::strerror(errno) << "\n";
    } else {
        char buffer[1024];
        int received = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (received > 0) {
            buffer[received] = '\0';
            std::cout << "Server reply: " << buffer << std::endl;
        }
    }

    close(clientSocket);
    return 0;
}
