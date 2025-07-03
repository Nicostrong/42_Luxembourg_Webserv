import sys
import socket

HOST = 'localhost'
PORT = 2121

if len(sys.argv) < 2:
    request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"
else:
    request = f"GET {sys.argv[1]} HTTP/1.1\r\nHost: {sys.argv[3]}\r\n\r\n"
    PORT = int(sys.argv[2])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(request.encode())
    response = s.recv(4096)

print(response.decode())
