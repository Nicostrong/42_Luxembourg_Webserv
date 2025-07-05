# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    chunkedmalformed.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdehan <fdehan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 14:55:21 by fdehan            #+#    #+#              #
#    Updated: 2025/07/04 16:29:43 by fdehan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

print("Status: 200", end='\r\n')
print("Transfer-Encoding: chunked", end='\r\n')
print("Content-Type: text/html; charset=utf-8\r\n", end='\r\n')

chunk1 = "<h1>Chunk1</h1>"
chunk2 = "<h1>Chunk2</h1>"

print(hex(len(chunk1))[2:], end='\r\n')
print(chunk1, end='\r\n')
print(hex(len(chunk2))[2:], end='\r\n')
print(chunk2, end='\r\n')
print("-1", end='\r\n')
print("", end='\r\n')
