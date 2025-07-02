# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    set_cookie.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/02 16:16:45 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
from urllib.parse import parse_qs, quote

query_string = os.environ.get('QUERY_STRING', '')
params = parse_qs(query_string)
pseudo = params.get('pseudo', [None])[0]

if pseudo:
    pseudo = pseudo.strip()[:50]
    pseudo_encoded = quote(pseudo)
else:
    pseudo_encoded = "Unknown"
print("Status: 302", end='\r\n')
print("Location: /", end='\r\n')
print("Content-Type: text/html; charset=utf-8", end='\r\n')
print(f"Set-Cookie: pseudo={pseudo_encoded}; Path=/; Max-age=600", end='\r\n')
print("\r\n")