# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unset_cookie.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 15:22:48 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/04 11:18:02 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os

print("Status: 200", end='\r\n')
print("Content-Type: text/html; charset=utf-8", end='\r\n')
print("Set-Cookie: pseudo=; Path=/; max-age=0", end='\r\n')
print("\r\n")

html = """
<html>
	<head><title>WEBSERVER - unset cookie - WEBSERVER</title>
		<link rel="stylesheet" href="/styles/style.css">
		<link rel="stylesheet" href="/styles/form.css">
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
			<h1>Cookie unset</h1>
			<h10>redirection to index in 5 secondes ...</h10>
			<script>
				setTimeout(function() {
				window.location.href = '/index.html';
				}, 5000);

				console.log('Redirection programmée dans 10 secondes...');
			</script>
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