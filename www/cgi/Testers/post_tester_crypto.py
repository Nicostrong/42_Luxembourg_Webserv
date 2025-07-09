import sys
import socket
import json

if len(sys.argv) != 7:
    print(f"Usage: {sys.argv[0]} PORT HOST TARGETSCRIPT AMOUNT_BOUGHT VALUE_PAID_PER_COIN AMOUNT_SOLD")
    exit()
else:
    input_data = {
		"amount_bought": sys.argv[4],
		"value_paid": sys.argv[5],
		"amount_sold": sys.argv[6]
	}

    # Properly stringify as JSON
    input_str = json.dumps(input_data)
    print(f"[debug len]{len(input_str)}")
    # Add Content-Type header for JSON
    request = (
        f"POST /cgi/{sys.argv[3]} HTTP/1.1\r\n"
        f"Host: {sys.argv[2]}\r\n"
        f"Content-Type: application/json\r\n"
        f"Content-Length: {len(input_str)}\r\n"
        f"\r\n"
        f"{input_str}"
    )
    PORT = int(sys.argv[1])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((sys.argv[2], int(sys.argv[1])))
    s.sendall(request.encode())
    response = s.recv(4096)

print(response.decode())
