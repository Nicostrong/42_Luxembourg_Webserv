# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    login.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:20 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/27 18:23:41 by fdehan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
import cgi

form = cgi.FieldStorage()
login = form.getvalue("login", "")

if login:
    print(f"Set-Cookie: login={login}; Path=/", end='\r\n')
print("Content-Type: text/html\r\n", end='\r\n')
print("<html><body>")
if login:
    print(f"Hello {login}, you're now connected !")
else:
    print("Please enter your login.")
print("</body></html>")