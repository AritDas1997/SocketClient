# SocketClient

A basic TCP client server code implemented in C++.Server and Client communicates with each other by sending messages to each other.
If anyone one i.e either client or server sends "quit" message then the socket connection terminates.Also there is a time-limit feature that is the client
after receiving message from server must respond within 30 seconds with a message to the server.If client fails to send a message within 30 second then the 
server aborts the connection.

