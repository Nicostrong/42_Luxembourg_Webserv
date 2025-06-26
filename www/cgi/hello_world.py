# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hello_world.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 09:18:27 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/26 09:15:36 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3

print("Status: 200 OK")
print("Content-Type: text/html")
print()

html = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>WEBSERVER - upload - WEBSERVER</title>
    <link rel="stylesheet" href="/html/style/style.css">
    <link rel="icon" href="/html/images/favicon.png" type="image/png">
</head>
<body>
    <div class="navbar">
        <a href="/html/index.html">Index</a>
    </div>
    <div align="center">
        <h1>Welcome on the WebServer of GneugneuTeam.</h1>
    </div>
    <hr>
    <p>Hello World !</p>
</body>
</html>
"""

print(html)