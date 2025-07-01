#!/usr/bin/env python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pseudo.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copilot <copilot@assistant.ai>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/01 00:00:00 by copilot           #+#    #+#              #
#    Updated: 2025/07/01 00:00:00 by copilot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import cgi
import urllib.parse
import html

def parse_cookies():
    """Parse cookies from HTTP_COOKIE environment variable"""
    cookies = {}
    cookie_header = os.environ.get('HTTP_COOKIE', '')
    if cookie_header:
        for cookie in cookie_header.split(';'):
            if '=' in cookie:
                name, value = cookie.strip().split('=', 1)
                cookies[name] = urllib.parse.unquote(value)
    return cookies

def get_form_data():
    """Get form data from GET parameters"""
    form = cgi.FieldStorage()
    return form.getvalue("pseudo", "").strip()

def send_headers(redirect_url=None):
    """Send HTTP headers"""
    if redirect_url:
        print(f"Status: 302 Found")
        print(f"Location: {redirect_url}")
    print("Content-Type: text/html")
    print()  # Empty line to separate headers from body

def send_cookie(pseudo):
    """Send Set-Cookie header"""
    encoded_pseudo = urllib.parse.quote(pseudo)
    print(f"Set-Cookie: pseudo={encoded_pseudo}; Path=/")

def main():
    # Parse existing cookies
    cookies = parse_cookies()
    existing_pseudo = cookies.get('pseudo', '')
    
    # Get pseudo from GET parameter
    form_pseudo = get_form_data()
    
    # If we received a pseudo via GET, set the cookie and redirect
    if form_pseudo:
        send_cookie(form_pseudo)
        send_headers(redirect_url="/cgi/pseudo.py")
        print("<html><body>")
        print("<p>Redirection en cours...</p>")
        print("<script>window.location.href='/cgi/pseudo.py';</script>")
        print("</body></html>")
        return
    
    # Regular page rendering
    send_headers()
    
    print("<html>")
    print("<head>")
    print("<title>Système de Pseudo</title>")
    print("<style>")
    print("body { font-family: Arial, sans-serif; max-width: 600px; margin: 50px auto; padding: 20px; }")
    print(".form-container { background: #f5f5f5; padding: 20px; border-radius: 8px; }")
    print(".welcome { background: #e8f5e8; padding: 20px; border-radius: 8px; border-left: 4px solid #4CAF50; }")
    print("input[type='text'] { padding: 10px; margin: 5px; border: 1px solid #ddd; border-radius: 4px; }")
    print("input[type='submit'] { padding: 10px 20px; background: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer; }")
    print("input[type='submit']:hover { background: #0056b3; }")
    print("</style>")
    print("</head>")
    print("<body>")
    
    if existing_pseudo:
        # Cookie exists, show welcome message
        escaped_pseudo = html.escape(existing_pseudo)
        print(f"<div class='welcome'>")
        print(f"<h1>Bienvenu {escaped_pseudo} sur le site</h1>")
        print(f"<p>Vous êtes connecté avec le pseudo: <strong>{escaped_pseudo}</strong></p>")
        print(f"<a href='/cgi/logout.py'>Se déconnecter</a>")
        print("</div>")
    else:
        # No cookie, show form
        print("<div class='form-container'>")
        print("<h1>Connexion</h1>")
        print("<p>Veuillez entrer votre pseudo pour accéder au site:</p>")
        print("<form method='GET' action='/cgi/pseudo.py'>")
        print("<label for='pseudo'>Pseudo:</label><br>")
        print("<input type='text' id='pseudo' name='pseudo' required placeholder='Entrez votre pseudo'><br><br>")
        print("<input type='submit' value='Se connecter'>")
        print("</form>")
        print("</div>")
    
    print("</body>")
    print("</html>")

if __name__ == "__main__":
    main()