# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fish.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 11:37:13 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/04 14:20:11 by nfordoxc         ###   Luxembourg.lu      #
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
		<link rel="stylesheet" href="/styles/style.css">
		<link rel="icon" href="/images/favicon.png" type="image/png">
		<script src="/scripts/cookie.js"></script>
		<script src="/scripts/session.js"></script>
	</head>
	<body>
		<header class="header">
			<a href="/" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="/html/upload.html">Upload</a>
			<a	href="/html/download.html">Download</a>
			<a	href="/html/delete.html">Delete</a>
			<a	href="/html/new.html">New</a>
			<a	href="/cgi/hello_world.py">Hello World Python</a>
			<a	href="/cgi/hello_world.php">Hello World PHP</a>
			<a	href="/cgi/timeout.py">Timeout</a>
			<a	href="/cgi/fish.py">Fish</a>
		</nav>
		<div class="container">
			<img src="/images/418.png" alt="Error 418" width="800" height="400" style="display:block;" />
			<h1>April Fish in Python ! (looking the response code ;) )</h1>
			<div id="status-section" class="user-status">
				<div class="info">
					<span id="status-message">Chargement...</span>
				</div>
			</div>
		</div>
	</body>
</html>
"""

print(html)