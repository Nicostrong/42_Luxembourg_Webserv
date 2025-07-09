import sys
import socket

if len(sys.argv) != 4:
    print(f"Usage: {sys.argv[0]} PORT HOST TARGET.")
    exit()
else:
    request = f"GET {sys.argv[3]} HTTP/1.1\r\nHost: {sys.argv[2]}\r\n\r\n"
    PORT = int(sys.argv[1])

print(f"[info request]{request}")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((sys.argv[2], int(sys.argv[1])))
    s.sendall(request.encode())
    response = s.recv(4096)

print(response.decode())
