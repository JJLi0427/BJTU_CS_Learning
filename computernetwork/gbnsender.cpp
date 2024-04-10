#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <asio.hpp>

using asio::ip::tcp;

int main() {
    asio::io_service io_service;
    tcp::socket socket(io_service);
    socket.connect(tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345));

    std::string message;
    std::cout << "Input message: ";
    std::getline(std::cin, message);

    int window_size;
    std::cout << "Window size: ";
    std::cin >> window_size;

    std::vector<char> window(window_size);
    int base = 0;
    int next_seq_num = 0;

    asio::steady_timer timer(io_service);
    timer.expires_from_now(std::chrono::seconds(1));

    while (base < message.size()) {
        while (next_seq_num < base + window_size && next_seq_num < message.size()) {
            window[next_seq_num % window_size] = message[next_seq_num];
            char seq_num_char = static_cast<char>(next_seq_num);
            asio::write(socket, asio::buffer(&seq_num_char, 1));
            asio::write(socket, asio::buffer(&window[next_seq_num % window_size], 1)); 
            std::cout << "Seq_num: " << next_seq_num << "  Send: " << window[next_seq_num % window_size] << std::endl;
            next_seq_num++;
        }

        char ack;
        asio::async_read(socket, asio::buffer(&ack, 1), [&](const asio::error_code& error, std::size_t length) {
            if (!error) {
                for (int i = 0; i < 25; i++) {
                    std::cout << " ";
                }
                std::cout << "Receive ACK: " << static_cast<int>(ack) << std::endl;
                base = ack + 1;

                if (base == next_seq_num) {
                    timer.cancel();
                } 
                else {
                    timer.expires_from_now(std::chrono::seconds(1));
                }
            } 
            else {
                std::cout << "Error reading ACK: " << error.message() << std::endl;
            }
        });

        timer.async_wait([&](const asio::error_code& error) {
            if (!error) {
                std::cout << "Timeout resend from: " << base << std::endl;
                for (int i = base; i < next_seq_num; i++) {
                    char seq_num_char = static_cast<char>(i);
                    asio::write(socket, asio::buffer(&seq_num_char, 1));
                    asio::write(socket, asio::buffer(&window[i % window_size], 1));
                }
            }
        });

        io_service.run();
        io_service.reset();
    }
    std::cout << "\nAll message have been send, connection closed" << std::endl;
    return 0;
}