# Servidor sencillo que devuelve la hora y 
# un mensaje en mayusculas 

import socket, datetime

# Miramos todos los hosts (Es como poner la broadcast)
HOST = ''
# Un puerto cualquiera poco importante
PORT = 9999

# Creamos un socket que se conectara por Internet y TCP
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Aqui se crea la conexion
# NO CONFUNDIR CON SOCKET
server.bind((HOST, PORT))

# Cola de conexion. Como es una prueba pongo 1
server.listen(1)

print("Escuchando en {}: {}".format(HOST, PORT))

while True:
    # Aceptamos y devolvemos una tupla que sera la conexion.
    client_socket, addr = server.accept()
    print('Conexion entrante de {}:{}'.format(addr[0], addr[1]))
    # Cogemos 1Kb
    msg = client_socket.recv(1024)
    msg = msg.decode("utf-8")
    send_msg = "Has escrito: " + msg.upper() + " a las " + datetime.datetime.now().strftime("%d/%m/%Y - %H:%M:%S")
    client_socket.send(str.encode(send_msg))
    client_socket.close()