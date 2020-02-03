import socket

serverName = 'localhost'
serverPort = 9999
msg = b"Hola servidor, te esperabas un cliente, pero era yo DIO."

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverName, serverPort))

client_socket.send(msg)
newMsg = client_socket.recv(1024)

print("Lo que me ha dicho el servidor es:\n")
print(newMsg)

client_socket.close()