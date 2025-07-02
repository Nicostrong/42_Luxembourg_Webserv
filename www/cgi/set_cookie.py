# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    set_cookie.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/02 13:58:29 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
from datetime import datetime, timedelta
from urllib.parse import parse_qs, quote

expire_date = (datetime.utcnow() + timedelta(minutes=20)).strftime('%a, %d %b %Y %H:%M:%S GMT')

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
print(f"Set-Cookie: pseudo={pseudo_encoded}; Path=/; Max-age=180", end='\r\n')
#print(f"Set-Cookie: pseudo={pseudo_encoded}; Path=/; expires={expire_date}", end='\r\n')
print("\r\n")