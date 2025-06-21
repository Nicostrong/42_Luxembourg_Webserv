# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    upload.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicostrong <nicostrong@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 07:56:38 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/21 16:21:45 by nicostrong       ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/python3
import cgi
import os
import sys

upload_dir = "../uploads/"
os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()
uploaded = False



for field in ["file1", "file2"]:
	if field in form:
		file_item = form[field]
		if file_item.filename:
			filename = os.path.basename(file_item.filename)
			file_path = os.path.join(upload_dir, filename)
			with open(file_path, "wb") as f:
				f.write(file_item.file.read())
			uploaded = True

if uploaded:
	print("Status: 200")
	print("Content-Type: text/html\n")
	print("<html><body>")
	print("<p>Fichier envoyé avec succès !</p>")
	print("</body></html>")
else:
	print("Status: 406")
	print("Content-Type: text/html\n")
	print("<html><body>")
	print("<p>Erreur : Aucun fichier reçu.</p>")
	print("</body></html>")

sys.stdout = sys.__stdout__
sys.stdout.flush()