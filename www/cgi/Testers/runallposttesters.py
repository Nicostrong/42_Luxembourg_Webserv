# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    runallposttesters.py                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 10:59:30 by gzenner           #+#    #+#              #
#    Updated: 2025/07/09 09:36:34 by gzenner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import subprocess as sp

port = "8080"
localhost = "localhost"
shift = "50"

sp.run(["clear"])
sp.run(["python3", "post_tester_colorize.py", port, localhost, "colorize.py", "0", "200", "0"])
sp.run(["python3", "post_tester_caesar.py", port, localhost, "caesar.py", shift, "Hello World"])
sp.run(["python3", "post_tester_calculator.py", port, localhost, "calculator.py", "25", "25", "*"])
sp.run(["python3", "post_tester_cheerup.py", port, localhost, "cheerup.py", "minishell"])
sp.run(["python3", "post_tester_compress.py", port, localhost, "compress.py", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxyyyyyzzzzzzzzzzzzzzzzzzz"])
sp.run(["python3", "post_tester_convert.py", port, localhost, "convert.py", "255", "16"])
sp.run(["python3", "post_tester_crypto.py", port, localhost, "crypto.py", "1234", "100", "1234"])
sp.run(["python3", "post_tester_excuse.py", port, localhost, "excuse.py", "Flavian", "wanted to do CGI", "dog", "kept barking"])
sp.run(["python3", "post_tester_password.py", port, localhost, "password.py", "100"])
sp.run(["python3", "post_tester_retirement.py", port, localhost, "retirement.py", "01.01.2001"])
sp.run(["python3", "post_tester_rps.py", port, localhost, "rps.py", "paper"])