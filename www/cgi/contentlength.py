# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    contentlength.py                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 14:55:21 by fdehan            #+#    #+#              #
#    Updated: 2025/07/04 15:05:19 by fdehan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cl = "<h1>Content-Length</h1>"
print("Status: 200", end='\r\n')
print(f"Content-Length: {len(cl)}", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')

print(cl)
