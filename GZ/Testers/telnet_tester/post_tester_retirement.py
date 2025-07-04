import sys
import socket
import json

HOST = 'localhost'
PORT = 2121

if len(sys.argv) != 5:
    print(f"Usage: {sys.argv[0]} PORT HOST TARGETSCRIPT BIRTHDAY(DD.MM.YYYY)")
    exit()
else:
    input_data = {
		"birthday": sys.argv[4]
	}
    # Properly stringify as JSON
    input_str = json.dumps(input_data)
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
