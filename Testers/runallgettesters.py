# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    runallgettesters.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 10:59:30 by gzenner           #+#    #+#              #
#    Updated: 2025/07/09 09:19:58 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import subprocess as sp

port = "8080"
localhost = "localhost"
shift = "50"

sp.run(["clear"])
print("\033[38;2;0;200;0mGood Requests:")
sp.run(["python3", "get_tester.py", port, localhost, "/"])

print("\033[38;2;200;0;0mBad Requests:")
sp.run(["python3", "get_tester.py", port, localhost, "/a"])
sp.run(["python3", "get_tester.py", port, localhost, "/asasccasacs"])
sp.run(["python3", "get_tester.py", port, localhost, "/index.html"])