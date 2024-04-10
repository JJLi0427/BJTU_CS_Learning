#include <iostream>
#include <cstdlib>
#include <ctime>
#include <asio.hpp>

using asio::ip::tcp;

int main() {
    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));

    tcp::socket socket(io_service);
    acceptor.accept(socket);

    srand(time(0));

    int expected_seq_num = -1;
    while (true) {
        char seq_num_char;
        char data;
        asio::error_code error;
        asio::read(socket, asio::buffer(&seq_num_char, 1), error);  // read sequence number
        asio::read(socket, asio::buffer(&data, 1), error);  // read data

        if (error) {
            if (error == asio::error::eof) {
                std::cout << "\nAll message have been received, connection closed" << std::endl;
            } 
            else {
                std::cout << "Error reading: " << error.message() << std::endl;
            }
            break;
        }

        int seq_num = static_cast<int>(seq_num_char);

        if (expected_seq_num == -1) {
            int random_num = rand() % 10;
            if (random_num == 0) {
                std::cout << "Loss Seq_num: " << seq_num<< std::endl;
                expected_seq_num = seq_num;
                continue;
            }
            std::cout << "Seq_num: " << seq_num << "  Receive: " << static_cast<char>(data) << std::endl;
        }
        else {
            std::cout << "Seq_num: " << seq_num << "  Receive: " << static_cast<char>(data) << std::endl;
            if (seq_num == expected_seq_num) {
                expected_seq_num = -1;
            }
            else {
                seq_num = expected_seq_num - 1;
            }
        }

        asio::write(socket, asio::buffer(&seq_num, 1));
        for (int i = 0; i < 25; i++) {
            std::cout << " ";
        }
        std::cout << "Send ACK: " << seq_num << std::endl;
    }

    return 0;
}