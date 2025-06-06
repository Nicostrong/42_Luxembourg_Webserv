# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 07:56:38 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/06 09:01:41 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/python3
import cgi
import os

upload_dir = "../uploads/"
os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()

print("Content-Type: text/html\n")
print("<html><body>")

for field in ["file1", "file2"]:
	if field in form:
		file_item = form[field]
		if file_item.filename:
			filename = os.path.basename(file_item.filename)
			file_path = os.path.join(upload_dir, filename)
			with open(file_path, "wb") as f:
				f.write(file_item.file.read())
			print(f"<p>Fichier '{filename}' envoyé avec succès !</p>")
			uploaded = True

if not uploaded:
	print("<p>Erreur : Aucun fichier reçu.</p>")

print("</body></html>")