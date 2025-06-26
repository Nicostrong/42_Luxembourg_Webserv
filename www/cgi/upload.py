# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 09:29:06 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/26 09:58:01 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
import sys

UPLOAD_DIR = "uploads"
status = 200
texte = ""

def get_boundary(content_type):
    parts = content_type.split(";")
    for part in parts:
        if "boundary=" in part:
            return part.split("=")[1].strip()
    return None

def parse_multipart(data, boundary):
    files = {}
    boundary_bytes = ("--" + boundary).encode()
    for part in data.split(boundary_bytes):
        if not part or part == b'--\r\n':
            continue
        headers, _, body = part.partition(b"\r\n\r\n")
        if not headers or not body:
            continue
        headers = headers.decode(errors="ignore")
        disposition = [line for line in headers.split("\r\n") if line.lower().startswith("content-disposition")]
        if not disposition:
            continue
        dispo = disposition[0]
        if 'filename="' in dispo:
            name = dispo.split('name="')[1].split('"')[0]
            filename = dispo.split('filename="')[1].split('"')[0]
            filename = os.path.basename(filename)
            filedata = body[:-2] if body.endswith(b"\r\n") else body
            files[name] = (filename, filedata)
    return files

def response():
    print(f"Status: {status} OK")
    print("Content-Type: text/html\n")
    html = f"""
<html>
    <head><title>WEBSERVER - upload - WEBSERVER</title>
    <link rel="stylesheet" href="/html/style.css">
    <link rel="icon" href="/html/images/favicon.png" type="image/png">
    </head>
    <body>
        {texte}
    </body>
</html>
"""
    print(html)
    sys.exit(0)

def main():
    global status, texte

    if not os.path.exists(UPLOAD_DIR):
        os.makedirs(UPLOAD_DIR)

    content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    content_type = os.environ.get('CONTENT_TYPE', '')
    if not content_length or "multipart/form-data" not in content_type:
        status = 406
        texte = "<h2>Erreur : Pas de fichier uploaded.</h2>"
        response()

    raw_data = sys.stdin.buffer.read(content_length)
    boundary = get_boundary(content_type)
    if not boundary:
        status = 406
        texte = "<h2>Erreur : Boundary manquant.</h2>"
        response()

    files = parse_multipart(raw_data, boundary)
    uploaded = []
    for field in ['file1', 'file2']:
        if field in files and files[field][0]:
            filename, file_bin = files[field]
            if filename:
                filepath = os.path.join(UPLOAD_DIR, filename)
                with open(filepath, "wb") as f:
                    f.write(file_bin)
                uploaded.append(filename)

    status = 200
    if uploaded:
        texte = "<h2>Fichiers uploadés avec succès:</h2>\n\t<ul>\n"
        for fname in uploaded:
            texte += f"\t\t<li>{fname}</li>\n"
        texte += "\t</ul>"
    else:
        texte = "<h2>Aucun fichier n'a été uploadé.</h2>"
    response()

if __name__ == "__main__":
    main()