#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

#define BUFFER_SIZE 4096
#define TIMEOUT_SEC 5

class Client {
private:
    int sockfd;
    struct sockaddr_in server_addr;

    void create_socket() {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            throw std::runtime_error("Socket creation failed");
        }
    }

    void set_timeout(int seconds) {
        struct timeval tv;
        tv.tv_sec = seconds;
        tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    }

public:
    Client(const std::string& host, int port) {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        
        if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
            throw std::runtime_error("Invalid address/Address not supported");
        }

        create_socket();
        set_timeout(TIMEOUT_SEC);
    }

    void connect() {
        if (::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            throw std::runtime_error("Connection failed");
        }
    }

    void send_request(const std::string& method, const std::string& path, const std::string& version = "HTTP/1.1") {
        std::ostringstream request;
        request << method << " " << path << " " << version << "\r\n"
                << "Host: " << inet_ntoa(server_addr.sin_addr) << ":" << ntohs(server_addr.sin_port) << "\r\n"
                << "Connection: close\r\n"
                << "User-Agent: Optimized-CPP-Client/1.0\r\n"
                << "\r\n";

        std::string request_str = request.str();
        ssize_t sent = send(sockfd, request_str.c_str(), request_str.size(), 0);
        if (sent < 0) {
            throw std::runtime_error("Send failed");
        }
    }

    std::string receive_response() {
        std::string response;
        char buffer[BUFFER_SIZE];
        
        while (true) {
            ssize_t received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
            if (received < 0) {
                throw std::runtime_error("Receive error");
            }
            if (received == 0) break;
            
            buffer[received] = '\0';
            response += buffer;
        }
        return response;
    }

    void close() {
        ::close(sockfd);
    }

    ~Client() {
        close();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <server_port>\n";
        return 1;
    }

    try {
        std::cout << "[debug argv1]" << argv[1] << " [debug argv2]" << argv[2] << "\n";
        Client client(argv[1], std::stoi(argv[2]));
        client.connect();

        // Test sequence
        client.send_request("GET", "/index.html");
        std::cout << "Response:\n" << client.receive_response() << "\n\n";

        client.send_request("GET", "/images");
        std::cout << "Response:\n" << client.receive_response() << "\n\n";

        client.send_request("GET", "/", "HTTP/1.1");
        std::cout << "Response:\n" << client.receive_response() << "\n\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
