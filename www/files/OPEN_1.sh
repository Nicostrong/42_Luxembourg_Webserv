# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    OPEN.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:20:49 by nfordoxc          #+#    #+#              #
#    Updated: 2024/10/31 08:49:53 by nfordoxc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/bash

COUNT=3

run=(
	"bash run_make.sh"
	"echo 'valgrind --tool=memcheck --leak-check=full
	--show-leak-kinds=definite,indirect,possible --track-fds=yes ./minishell 2>
	error' &&
		valgrind --tool=memcheck --leak-check=full
			--show-leak-kinds=definite,indirect,possible --track-fds=yes
			./minishell 2> error"
	""
	)

for ((i=0; i < COUNT ; i++))
do
	if [ -n "${run[i]}" ]; then
		gnome-terminal -- zsh -c "cd /home/nfordoxc/Cursus_42_Luxembourg/Git_42_Luxembourg/Minishell;${run[i]};exec bash"
	else
        gnome-terminal -- zsh -c "cd /home/nfordoxc/Cursus_42_Luxembourg/Git_42_Luxembourg/Minishell;exec bash"
    fi
done
