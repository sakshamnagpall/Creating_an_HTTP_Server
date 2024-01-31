# Simple C++ HTTP Server

This is a basic HTTP server implemented in C++ that serves static HTML content. The server is created from scratch using sockets and can handle simple HTTP requests.

## Features

- Supports basic HTTP GET requests.
- Serves static HTML content.

## Prerequisites

- C++ compiler (e.g., g++)
- Unix-like operating system (Linux, macOS)

## Build and Run

1. Clone the repository:

    ```bash
    git clone https://github.com/sakshamnagpall/Simple_HTTP_Server.git
    ```

2. Navigate to the project directory:

    ```bash
    cd cpp-html-server
    ```

3. Build the server:

    ```bash
    g++ main.cpp -o http-server
    ```

4. Run the server:

    ```bash
    ./http-server
    ```

    The server will start and listen on port 8080 by default.

5. Open a web browser and visit [http://localhost:8080](http://localhost:8080) to see the "Hello, World!" message.

## Customizing Content

You can customize the HTML content served by modifying the `handleRequest` function in the `main.cpp` file.

```cpp
const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
write(clientSocket, response, strlen(response));

(->)Replace the Hello, World! message with your desired HTML content.
