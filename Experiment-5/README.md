TCP

Run:


gcc tcp_server.c -o tcp_server -lws2_32
gcc tcp_client.c -o tcp_client -lws2_32

./tcp_server
./tcp_client