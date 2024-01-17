#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;

class HttpServer {
public:
    HttpServer(io_service& io_service, int port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
          socket_(io_service) {
        startAccept();
    }

private:
    void startAccept() {
        acceptor_.async_accept(socket_,
                               [this](boost::system::error_code ec) {
                                   if (!ec) {
                                       handleRequest();
                                   }
                                   startAccept();
                               });
    }

    void handleRequest() {
        async_read_until(socket_, request_, "\r\n\r\n",
                         [this](boost::system::error_code ec, std::size_t bytes_transferred) {
                             if (!ec) {
                                 std::istream request_stream(&request_);
                                 std::string request_line;
                                 std::getline(request_stream, request_line);

                                 // Assume GET method for simplicity
                                 if (request_line.find("GET") != std::string::npos) {
                                     // Handle the request
                                     std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
                                     async_write(socket_, buffer(response),
                                                 [this](boost::system::error_code ec, std::size_t) {
                                                     if (!ec) {
                                                         socket_.shutdown(tcp::socket::shutdown_send);
                                                     }
                                                 });
                                 }
                             }
                         });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
    streambuf request_;
};

int main() {
    try {
        boost::asio::io_service io_service;
        HttpServer server(io_service, 8080);
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
