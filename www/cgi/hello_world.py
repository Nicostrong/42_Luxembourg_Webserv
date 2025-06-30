# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hello_world.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 09:18:27 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/30 08:48:10 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')
print()

html = """
<html>
	<head>
		<meta charset="UTF-8">
		<title>WEBSERVER - upload - WEBSERVER</title>
		<link rel="stylesheet" href="http://localhost:8080/styles/style.css">
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
		<h1>Hello World !</h1>
	</body>
</html>
"""

print(html)