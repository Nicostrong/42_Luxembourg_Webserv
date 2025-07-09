import sys
import socket
import json
import os
from urllib.parse import parse_qs, quote

query_string = os.environ.get('QUERY_STRING', '')
params = parse_qs(query_string)
shift = params.get('shift', [None])[0]
text = params.get('text', [None])[0]

if len(sys.argv) != 6 and shift is None and text is None:
    print(f"Usage:{sys.argv[0]} PORT HOST TARGETSCRIPT shift text")
    exit()
else:
    if shift is None or text is None:
        input_data = {
         "shift": sys.argv[4],
         "text": sys.argv[5],
        }
    else:
        input_data = {
         "shift": shift,
         "text": text,
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
