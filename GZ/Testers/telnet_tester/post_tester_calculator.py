import sys
import socket
import json

if len(sys.argv) != 7:
    print(f"Usage:{sys.argv[0]} PORT HOST TARGETSCRIPT Num1 Num2 Operator")
    exit()
else:
    input_data = {
        "num1": sys.argv[4],
        "num2": sys.argv[5],
        "operator": sys.argv[6]
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
    try:
        s.connect((sys.argv[2], int(sys.argv[1])))
        s.sendall(request.encode())
        response = s.recv(4096)
    except Exception as e:
        print(e)
        exit()

print(response.decode())
