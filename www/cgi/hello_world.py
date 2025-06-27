# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hello_world.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 09:18:27 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/27 18:23:21 by fdehan           ###   ########.fr        #
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