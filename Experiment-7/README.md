Here’s how to compile, run, and use the server-client Winsock program in C on a Windows machine:

### Prerequisites
1. Ensure you have a C compiler that supports Winsock (e.g., **MinGW** or **Visual Studio**).
2. Winsock requires the `ws2_32` library to be linked during compilation.

### Steps to Compile and Run:

#### 1. Compile the Server and Client:
Assuming you have **MinGW** installed, open the terminal (Command Prompt or PowerShell), navigate to the directory where your files are located, and compile the code:

- **For the Server (`server.c`)**:
  ```bash
  gcc server.c -o server.exe -lws2_32
  ```

- **For the Client (`client.c`)**:
  ```bash
  gcc client.c -o client.exe -lws2_32
  ```

This command compiles the code and links the `ws2_32` library, which is required for Winsock.

#### 2. Run the Server:
- First, start the server:
  ```bash
  ./server.exe
  ```
  The server will start listening on port `8081`.

#### 3. Run the Client:
- Open another terminal window, and run the client:
  ```bash
  ./client.exe
  ```
  The client will connect to the server at `127.0.0.1` (localhost) and receive the message: `Hello from server!`.

### Communication Flow:
1. The server starts and listens on port `8081`.
2. When the client connects, the server sends the message `"Hello from server!\n"`.
3. The client receives and prints this message.
4. The connection is then closed.

### Multiple Clients:
If you want to connect multiple clients:
1. Keep the server running.
2. In separate terminal windows, run multiple instances of the client with:
   ```bash
   ./client.exe
   ```
Each client will receive the same "Hello from server!" message upon connection.

### Troubleshooting Tips:
- Ensure that the server is running before attempting to connect with the client.
- Verify that the client is connecting to the correct IP address and port.
- Check for any firewall rules that may be blocking the connection.

### Additional Tips:
- To change the port number, modify the `server.c` file and update the port number in the `bind` function.
- To send a different message, modify the `server.c` file and update the message in the `send` function.
- To handle multiple clients simultaneously, consider using multi-threading or asynchronous I/O.

This setup should help you run the program and establish client-server communication!   