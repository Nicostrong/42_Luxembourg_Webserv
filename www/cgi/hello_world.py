# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hello_world.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 09:18:27 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/26 13:54:16 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3

print("Status: 200")
print("Content-Type: text/html; charset=utf-8")
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
	<div class="header">
		<h1>Welcone on the WebServer of GneugneuTeam.</h1>
	</div>
    <div class="navbar">
        <a href="/index.html">Index</a>
    </div>
    <h1>Hello World !</h1>
</body>
</html>
"""

print(html)