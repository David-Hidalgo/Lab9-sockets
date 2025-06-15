#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <iostream>

int main() {
    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0) {
        std::cerr << "Socket creation failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        if (errno == EADDRINUSE) {
            std::cerr << "Port already in use. Closing existing socket.\n";
        } else {
            std::cerr << "Bind failed: " << std::strerror(errno) << "\n";
        }
        close(listenSocket);
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) < 0) {
        std::cerr << "Listen failed: " << std::strerror(errno) << "\n";
        close(listenSocket);
        return 1;
    }

    std::cout << "Server listening on port 54000..." << std::endl;

    int clientSocket;
    sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    clientSocket = accept(listenSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientSize);
    if (clientSocket < 0) {
        std::cerr << "Accept failed: " << std::strerror(errno) << "\n";
        close(listenSocket);
        return 1;
    }

    char buffer[1024];
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        const char* reply = "Hello from server";
        send(clientSocket, reply, strlen(reply), 0);
    }

    close(clientSocket);
    close(listenSocket);
    return 0;
}
