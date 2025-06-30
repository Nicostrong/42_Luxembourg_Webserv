# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 09:29:06 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/30 08:47:18 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
import sys
import re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
UPLOAD_DIR = os.path.join(SCRIPT_DIR, "..", "files")

#ALLOWED_EXTENSIONS = {
#    '.txt', '.pdf', '.doc', '.docx', '.jpg', '.jpeg', '.png', '.gif', 
#    '.csv', '.xls', '.xlsx', '.ppt', '.pptx', '.zip', '.rar', '.tar', 
#    '.gz', '.mp3', '.mp4', '.avi', '.mov', '.py', '.js', '.html', 
#    '.css', '.json', '.xml', '.md', '.sh'
#}

MAX_FILE_SIZE = 10 * 1024 * 1024  # 10MB

status = 0
texte = ""

#def is_allowed_file(filename):
#    if not filename:
#        return False
#    
#    _, ext = os.path.splitext(filename.lower())
#    return ext in ALLOWED_EXTENSIONS

def get_file_size(file_data):
    """Retourne la taille du fichier en bytes"""
    if isinstance(file_data, bytes):
        return len(file_data)
    elif isinstance(file_data, str):
        return len(file_data.encode('utf-8'))
    return 0

def extract_boundary_from_data(data):
    """Extrait la boundary des données - gère les données binaires"""
    if isinstance(data, bytes):
        try:
            header_part = data[:500].decode('utf-8', errors='ignore')
        except:
            header_part = str(data[:500])
    else:
        header_part = data[:500]
    
    lines = header_part.split('\n')
    for line in lines[:10]:
        line = line.strip()
        if line.startswith('--') and len(line) > 10:
            return line[2:].strip('\r')

    if isinstance(data, bytes):
        boundary_match = re.search(rb'--([a-zA-Z0-9]+)', data[:500])
        if boundary_match:
            return boundary_match.group(1).decode('ascii', errors='ignore')
    else:
        boundary_match = re.search(r'^--([a-zA-Z0-9]+)', header_part, re.MULTILINE)
        if boundary_match:
            return boundary_match.group(1)
    
    return None

def parse_multipart_binary(data, boundary):
    """Parse multipart data en gérant correctement les fichiers binaires"""
    files = {}
    boundary_bytes = ("--" + boundary).encode('ascii')
    
    if isinstance(data, str):
        data = data.encode('utf-8')
    
    parts = data.split(boundary_bytes)
    
    for part in parts:
        if not part or part.strip() == b'--':
            continue
        
        if b'\r\n\r\n' in part:
            headers_part, body_part = part.split(b'\r\n\r\n', 1)
        elif b'\n\n' in part:
            headers_part, body_part = part.split(b'\n\n', 1)
        else:
            continue
        
        try:
            headers_str = headers_part.decode('utf-8', errors='ignore')
        except:
            continue
        
        headers_lines = headers_str.split('\n')
        disposition_line = None
        for line in headers_lines:
            if 'content-disposition' in line.lower():
                disposition_line = line
                break
                
        if not disposition_line:
            continue
        
        if 'name="' in disposition_line:
            name = disposition_line.split('name="')[1].split('"')[0]
            filename = ""
            if 'filename="' in disposition_line:
                filename = disposition_line.split('filename="')[1].split('"')[0]
                filename = os.path.basename(filename)
            
            if body_part.endswith(b'\r\n'):
                body_clean = body_part[:-2]
            elif body_part.endswith(b'\n'):
                body_clean = body_part[:-1]
            else:
                body_clean = body_part
            
            if filename:  # Seulement si on a un filename non vide
                files[name] = (filename, body_clean)
    
    return files

def response():
    print(f"Status: {status} OK", end='\r\n')
    print("Content-Type: text/html\r\n", end='\r\n')
    html = f"""
<html>
	<head><title>WEBSERVER - upload result - WEBSERVER</title>
	<link rel="stylesheet" href="http://localhost:8080/styles/style.css">
	<link rel="stylesheet" href="http://localhost:8080/styles/form.css">
	<link rel="icon" href="http://localhost:8080/images/favicon.png" type="image/png">
	</head>
	<body>
		<header class="header">
			<a href="./index.html" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="./upload.html">Upload</a>
			<a	href="./upload.html">Download</a>
			<a	href="./delete.html">Delete</a>
			<a	href="/cgi/hello_world.py">Hello World Python</a>
			<a	href="/cgi/hello_world.php">Hello World PHP</a>
			<a	href="/cgi/debug.php">DEBUG PHP</a>
		</nav>
		<div class="upload-container">
			{texte}
			<div class="info">
				<h3>Upload Information:</h3>
				<p>All file types are accepted</p>
				<p>Maximum file size: {MAX_FILE_SIZE // (1024*1024)}MB</p>
			</div>
		</div>
	</body>
</html>
"""
    print(html)
    sys.exit(0)

def main():
    global status, texte

    upload_path = os.path.normpath(UPLOAD_DIR)
    
    if not os.path.exists(upload_path):
        try:
            os.makedirs(upload_path)
        except:
            status = 500
            texte = "<h2>Error: Unable to create upload directory.</h2>"
            response()
    
    if not os.access(upload_path, os.W_OK):
        status = 500
        texte = "<h2>Error: No permission to write on the directory \"uploads\".</h2>"
        response()

    content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    
    if not content_length:
        status = 400
        texte = "<h2>Error: No data received.</h2>"
        response()

    try:
        raw_data = sys.stdin.buffer.read(content_length)
    except:
        try:
            raw_data = sys.stdin.read(content_length)
            if isinstance(raw_data, str):
                raw_data = raw_data.encode('utf-8')
        except Exception as e:
            status = 400
            texte = f"<h2>Error: Unable to read data.</h2><p>{e}</p>"
            response()

    print(f"Data size received: {len(raw_data)} bytes", file=sys.stderr)

    boundary = extract_boundary_from_data(raw_data)
    
    if not boundary:
        status = 400
        texte = "<h2>Error: Boundary not found.</h2>"
        response()

    print(f"Boundary found: {boundary}", file=sys.stderr)

    files = parse_multipart_binary(raw_data, boundary)
    uploaded = []
    rejected = []
    
    print(f"Files parsed: {list(files.keys())}", file=sys.stderr)
    
    # *** MODIFICATION PRINCIPALE : Traiter TOUS les champs de fichiers ***
    for field_name, (filename, file_bin) in files.items():
        if filename:  # Si le fichier a un nom
            print(f"Processing file: {field_name} -> {filename}", file=sys.stderr)
            
            # Vérifier la taille du fichier
            file_size = get_file_size(file_bin)
            if file_size > MAX_FILE_SIZE:
                rejected.append(f"{filename} (file too large: {file_size // (1024*1024)}MB)")
                print(f"File rejected (size): {filename} - {file_size} bytes", file=sys.stderr)
                continue
            
            # Vérifier que le fichier n'est pas vide
            if file_size == 0:
                rejected.append(f"{filename} (empty file)")
                print(f"File rejected (empty): {filename}", file=sys.stderr)
                continue
            
            # Éviter les doublons de noms de fichiers
            original_filename = filename
            counter = 1
            while os.path.exists(os.path.join(upload_path, filename)):
                name, ext = os.path.splitext(original_filename)
                filename = f"{name}_{counter}{ext}"
                counter += 1
            
            # Sauvegarder le fichier
            filepath = os.path.join(upload_path, filename)
            try:
                with open(filepath, "wb") as f:
                    f.write(file_bin)
                uploaded.append(filename)
                print(f"File saved: {filepath} ({file_size} bytes)", file=sys.stderr)
            except Exception as e:
                status = 500
                texte = f"<h2>Error: Unable to write the file {filename}.</h2><p>{e}</p>"
                response()

    status = 200
    if uploaded or rejected:
        texte = ""
        if uploaded:
            texte += "<h2>Files uploaded successfully:</h2>\n\t<ul class='success-list'>\n"
            for fname in uploaded:
                texte += f"\t\t<li class='success'>{fname}</li>\n"
            texte += "\t</ul>\n"
        
        if rejected:
            texte += "<h2>Files rejected:</h2>\n\t<ul class='error-list'>\n"
            for reason in rejected:
                texte += f"\t\t<li class='error'>{reason}</li>\n"
            texte += "\t</ul>\n"
    else:
        texte = "<h2>No files uploaded.</h2>"
        
    response()

if __name__ == "__main__":
    main()