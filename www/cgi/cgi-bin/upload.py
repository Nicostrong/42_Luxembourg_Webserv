# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 07:56:38 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/04 07:57:29 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/python3
import cgi
import os

upload_dir = "uploads/"
os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()

file_item = form["file"] if "file" in form else None

print("Content-Type: text/html\n")
print("<html><body>")

if file_item and file_item.filename:
    file_path = os.path.join(upload_dir, os.path.basename(file_item.filename))
    
    with open(file_path, "wb") as f:
        f.write(file_item.file.read())

    print(f"<p>Fichier {file_item.filename} envoyé avec succès !</p>")
else:
    print("<p>Erreur : Aucun fichier reçu.</p>")

print("</body></html>")