#!/usr/bin/env python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    logout.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copilot <copilot@assistant.ai>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 00:00:00 by copilot           #+#    #+#              #
#    Updated: 2025/07/01 00:00:00 by copilot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os

def main():
    # Clear the pseudo cookie by setting it to expire in the past
    print("Set-Cookie: pseudo=; Path=/; Expires=Thu, 01 Jan 1970 00:00:00 GMT")
    print("Status: 302 Found")
    print("Location: /cgi/pseudo.py")
    print("Content-Type: text/html")
    print()
    
    print("<html><body>")
    print("<p>Déconnexion en cours...</p>")
    print("<script>window.location.href='/cgi/pseudo.py';</script>")
    print("</body></html>")

if __name__ == "__main__":
    main()