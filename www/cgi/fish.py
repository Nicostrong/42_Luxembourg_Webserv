# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fish.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 11:37:13 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/03 10:14:19 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3

print("Status: 418", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

html = """
<html>
	<head>
		<meta charset="UTF-8">
		<title>WEBSERVER - Fish - WEBSERVER</title>
		<link rel="stylesheet" href="http://localhost:8080/styles/style.css">
		<link rel="icon" href="http://localhost:8080/images/favicon.png" type="image/png">
		<script src="/scripts/cookie.js"></script>
	</head>
	<body>
		<header class="header">
			<a href="http://localhost:8080/index.html" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="http://localhost:8080/upload.html">Upload</a>
			<a	href="http://localhost:8080/download.html">Download</a>
			<a	href="http://localhost:8080/delete.html">Delete</a>
			<a	href="http://localhost:8080/new.html">New</a>
			<a	href="http://localhost:8080/cgi/hello_world.py">Hello World Python</a>
			<a	href="http://localhost:8080/cgi/hello_world.php">Hello World PHP</a>
			<a	href="http://localhost:8080/cgi/timeout.py">Timeout</a>
			<a	href="http://localhost:8080/cgi/fish.py">Fish</a>
		</nav>
		<h1>Fish in Python !</h1>
		<div class="container></div>
	</body>
</html>
"""

print(html)