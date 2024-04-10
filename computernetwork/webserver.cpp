#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

const std::string root_dir = "/home/ljj/code/network/exp1/html";
const int port_number = 8888;

std::string get_content_type(const std::string& path) {
    if (boost::filesystem::extension(path) == ".html") {
        return "text/html";
    } 
    else if (boost::filesystem::extension(path) == ".jpg") {
        return "image/jpg";
    } 
    else {
        return "application/octet-stream";
    }
}

void handle_request(tcp::socket& socket) {
    try {
        boost::asio::streambuf request;
        boost::asio::read_until(socket, request, "\r\n");

        std::string method, path, protocol;
        std::istream request_stream(&request);
        request_stream >> method >> path >> protocol;

        if (path == "/") {
            path = "/index.html";
        }

        std::string full_path = root_dir + path;

        std::ifstream file(full_path, std::ios::binary);

        boost::asio::streambuf response;
        std::ostream response_stream(&response);

        if (!file) {
            // Open the 404.html file
            std::ifstream file_404(root_dir + "/404.html", std::ios::binary);
            if (!file_404) {
                response_stream << "HTTP/1.0 500 Internal Server Error\r\n";
                response_stream << "Connection: close\r\n\r\n";
                std::cout << "Response: 500 Internal Server Error" << std::endl;
            } else {
                response_stream << "HTTP/1.0 404 Not Found\r\n";
                response_stream << "Content-Type: text/html\r\n";
                response_stream << "Connection: close\r\n\r\n";
                response_stream << file_404.rdbuf();
                std::cout << "Response: 404 Not Found" << std::endl;
            }
        } 
        else {
            response_stream << "HTTP/1.0 200 OK\r\n";
            response_stream << "Content-Type: " << get_content_type(full_path) << "\r\n";
            response_stream << "Connection: close\r\n\r\n";
            response_stream << file.rdbuf();
            std::cout << "Response: 200 OK, Content-Type: " << get_content_type(full_path) << std::endl;
        }

        boost::asio::write(socket, response);
        socket.shutdown(tcp::socket::shutdown_both);
    } catch (boost::system::system_error& e) {
        if (e.code() != boost::asio::error::eof) {
            throw; // Rethrow if it's not the expected exception.
        }
        // Handle EOF exception here if necessary.
        std::cout << "Connection closed by client." << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port_number));

        std::cout << "Started httpserver on port " << port_number << std::endl;

        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            handle_request(socket);
            socket.close();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}