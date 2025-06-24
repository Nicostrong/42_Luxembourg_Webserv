# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 07:56:38 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/22 11:15:50 by nicostrong       ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/python3
import cgi
import os
import warnings

warnings.filterwarnings("ignore", category=DeprecationWarning)

upload_dir = "../uploads/"
os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()
uploaded_files = []
_query = ""
file_names = {"file1": "", "file2": ""}

for field in ["file1", "file2"]:
    if field in form:
        file_item = form[field]
        if file_item.filename:
            filename = os.path.basename(file_item.filename)
            file_path = os.path.join(upload_dir, filename)
            with open(file_path, "wb") as f:
                f.write(file_item.file.read())
            uploaded_files.append(filename)
            file_names[field] = filename
        else:
            file_names[field] = ""
    else:
        file_names[field] = ""

_query = f'file1="{file_names["file1"]}";file2="{file_names["file2"]}"'

if uploaded_files:
    print("Code: 200")
    print("Content-Type: text/html\n")
    print("<html><body>")
    print("<p>Fichier(s) envoyé(s) avec succès !</p>")
    print("<ul>")
    for name in uploaded_files:
        print(f"<li>{name}</li>")
    print("</ul>")
    print(f"<p>_query = {_query}</p>")
    print("</body></html>")
else:
    print("Code: 406")
    print("Content-Type: text/html\n")
    print("<html><body>")
    print("<p>Erreur : Aucun fichier reçu.</p>")
    print(f"<p>_query = {_query}</p>")
    print("</body></html>")