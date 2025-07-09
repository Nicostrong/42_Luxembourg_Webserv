import sys
import socket
import json

if len(sys.argv) != 8:
    print(f"Usage:{sys.argv[0]} PORT HOST TARGETSCRIPT friend task animal bad_action")
    exit()
else:
    input_data = {
        "friend": sys.argv[4],
        "task": sys.argv[5],
        "animal": sys.argv[6],
        "bad_action": sys.argv[7],
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
