import sys
import socket
import json

HOST = 'localhost'
PORT = 2121

input_data = {
    "num1": sys.argv[4],
    "num2": sys.argv[5],
    "operator": sys.argv[6]
}

# Properly stringify as JSON
input_str = json.dumps(input_data)
print(f"[debug len]{len(input_str)}")

if len(sys.argv) < 2:
    request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"
else:
    # Add Content-Type header for JSON
    request = (
        f"POST {sys.argv[3]} HTTP/1.1\r\n"
        f"Host: {sys.argv[2]}\r\n"
        f"Content-Type: application/json\r\n"
        f"Content-Length: {len(input_str)}\r\n"
        f"\r\n"
        f"{input_str}"
    )
    PORT = int(sys.argv[1])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(request.encode())
    response = s.recv(4096)

print(response.decode())
