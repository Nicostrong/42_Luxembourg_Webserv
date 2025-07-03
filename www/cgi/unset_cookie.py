# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unset_cookie.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 15:22:48 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/03 11:01:31 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
#from urllib.parse import unquote
#
#http_cookie = os.environ.get('HTTP_COOKIE', '')
#
#if http_cookie:
#	for cookie in http_cookie.split(';'):
#		cookie = cookie.strip()
#		if cookie.startswith('pseudo='):
#		current_pseudo = cookie.split('=', 1)[1]
#		pseudo = unquote(current_pseudo)
#		break

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
	</head>
	<body>
		<header class="header">
			<a href="/index.html" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="/upload.html">Upload</a>
			<a	href="/download.html">Download</a>
			<a	href="/delete.html">Delete</a>
			<a	href="/new.html">New</a>
			<a	href="../cgi/hello_world.py">Hello World Python</a>
			<a	href="../cgi/hello_world.php">Hello World PHP</a>
			<a	href="../cgi/timeout.py">Timeout</a>
			<a	href="../cgi/fish.py">Fish</a>
		</nav>
		<div class="container">
			<h1>Cookie unset</h1>
			<h10>redirection to index in 10 secondes ...</h10>
			<script>
				setTimeout(function() {
				window.location.href = '/index.html';
				}, 10000);

				console.log('Redirection programmée dans 10 secondes...');
			</script>
		</div>
	</body>
</html>
"""

print(html)