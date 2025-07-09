# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    runallgettesters.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 10:59:30 by gzenner           #+#    #+#              #
#    Updated: 2025/07/08 11:12:26 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import subprocess as sp

port = "8080"
localhost = "localhost"
shift = "50"

sp.run(["clear"])
sp.run(["python3", "get_tester.py", port, localhost, "/"])
sp.run(["python3", "get_tester.py", port, localhost, "/a"])
sp.run(["python3", "get_tester.py", port, localhost, "/asasccasacs"])
sp.run(["python3", "get_tester.py", port, localhost, "/index.html"])