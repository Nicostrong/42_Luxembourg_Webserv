# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parser_tester.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 08:33:32 by nfordoxc          #+#    #+#              #
#    Updated: 2025/05/02 11:48:06 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

params=(
	""
	"'sdfgsdg' 'sdgf' 'sdfgdfg'"
	"54545125 45131351 3135135"
	"./bad_config/toto"
)

bad_conf=(
	./bad_config/.conf	
	./bad_config/bad.conf
	./bad_config/brace_0.conf
	./bad_config/brace_1.conf
	./bad_config/brace_2.conf
	./bad_config/brace_3.conf
	./bad_config/empty.conf
	./bad_config/no_readable.conf
	./bad_config/semi_colon_0.conf
	./bad_config/semi_colon_1.conf
	./bad_config/semi_colon_2.conf
	./bad_config/semi_colon_3.conf
)

good_conf=(
	./good_config/good_0.conf
	./good_config/good_1.conf
	./good_config/good_2.conf
	./good_config/good_3.conf
	./good_config/good_4.conf
	./good_config/good_5.conf
	./good_config/good_6.conf	
)

chmod -r ./bad_config/not_readable.conf
make parser
name=./test_parser
error_count=0
clear

echo -e "\033[1;94m _______   ______   _______    _______       ______\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|     /      |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |       /  / |  |\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |      /__/  |  |\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |            |  |\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|            |__|\033[0m"
echo ""

for i in "${!params[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ${name} ${params[i]}\033[1;93m"
	${name} ${params[i]} &> TEMPFILE
	if grep -iq "error" $TEMPFILE || grep -iq "usage" $TEMPFILE; then
		echo -e "\033[1;92m\t✅\tOK => Bad arg catching.\033[0m"
	else
		echo -e "\033[1;91m\t❌\tKO => Bad arg not cathing.\033[0m"
		((error_count++))
	fi
	rm $TEMPFILE
done

echo -e "\033[1;94m _______   ______   _______    _______      ________\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    /  __    |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |      /__/  /  /\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |          /  /\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |        /  /____\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|       |________|\033[0m"
echo ""

for i in "${!bad_conf[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ${name} ${bad_conf[i]}\033[1;93m"
	${name} ${bad_conf[i]} &> TEMPFILE
	if grep -iq "error" $TEMPFILE $TEMPFILE; then
		echo -e "\033[1;92m\t✅\tOK => Error config file catching.\033[0m"
	else
		echo -e "\033[1;91m\t❌\tKO => Error config file not cathing.\033[0m"
		((error_count++))
	fi
	rm $TEMPFILE
done


echo -e "\033[1;94m _______   ______   _______    _______      _______\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    |____   |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |          __|  |\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |         |__   |\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |        ____|  |\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|       |_______|\033[0m"
echo ""

for i in "${!bad_conf[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ${name} ${good_conf[i]}\033[1;93m"
	${name} ${good_conf[i]} &> TEMPFILE
	if grep -iq "error" $TEMPFILE $TEMPFILE; then
		echo -e "\033[1;92m\t❌\tKO => Error detectin.\033[0m"
		((error_count++))
	else
		echo -e "\033[1;91m\t✅\tOK => All running correctly.\033[0m"
	fi
	rm $TEMPFILE
done

#echo -e "\033[1;94m _______   ______   _______    _______      __\033[0m"
#echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    |  |   __\033[0m"
#echo -e "\033[1;94m   | |    | |___   |  |____      | |       |  |__|  |\033[0m"
#echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |       |_____   |\033[0m"
#echo -e "\033[1;94m   | |    | |____   _____| |     | |             |  |\033[0m"
#echo -e "\033[1;94m   |_|    |______| |_______|     |_|             |__|\033[0m"
#echo ""
#
#error_count=0
#
#for i in "${!params[@]}"
#do
#	TEMPFILE=$(mktemp)
#	echo -e "\033[1;94mTEST VALGRIND $((i + 1)): ./so_long ${params[i]}\033[1;93m"
#	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./so_long ${params[i]} &> $TEMPFILE
#
#	# Variables pour stocker les valeurs de fuites de mémoire
#	def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
#	ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
#	pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
#	still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
#	suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')
#
#	# Vérifie les fuites de mémoire
#	if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
#		echo -e "\033[1;91mDes fuites de mémoire ont été détectées :\033[0m"
#		grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucune fuite de mémoire détectée.\033[0m"
#	fi
#
#	# Affiche l'utilisation de la heap
#	HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
#	if [ -n "$HEAP_USAGE" ]; then
#		echo -e "\033[1;94mUtilisation totale de la heap :\033[0m"
#		echo "$HEAP_USAGE"
#	fi
#
#	# Vérifie les descripteurs de fichiers non fermés
#	FD_COUNT=$(grep -E "FILE DESCRIPTORS: [0-9]+ open" $TEMPFILE | awk '{print $4}')
#	if [ -n "$FD_COUNT" ] && [ "$FD_COUNT" -gt 3 ]; then
#		echo -e "\033[1;91mDes descripteurs de fichiers non fermés ont été détectés :\033[0m"
#		grep -A 3 "FILE DESCRIPTORS:" $TEMPFILE | grep -v "std"
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucun descripteur de fichier non fermé détecté.\033[0m"
#	fi
#
#	# Affiche les autres erreurs possibles
#	ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
#	if [ -n "$ERROR_SUMMARY" ]; then
#		echo -e "\033[1;94mERROR SUMMARY:\033[0m"
#		echo "$ERROR_SUMMARY"
#	fi
#
#	# Nettoyage
#	rm $TEMPFILE
#done
#
## Bouclage sur les arguments du tableau list_error_map
#for i in "${!list_error_map[@]}"
#do
#	TEMPFILE=$(mktemp)
#	echo -e "\033[1;94mTEST $((i + 1)): ./so_long ./test/mandatory/maps/${list_error_map[i]}\033[1;93m"
#	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./so_long ./test/mandatory/maps/${list_error_map[i]} &> $TEMPFILE
#
#	# Variables pour stocker les valeurs de fuites de mémoire
#	def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
#	ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
#	pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
#	still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
#	suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')
#
#	# Vérifie les fuites de mémoire
#	if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
#		echo -e "\033[1;91mDes fuites de mémoire ont été détectées :\033[0m"
#		grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucune fuite de mémoire détectée.\033[0m"
#	fi
#
#	# Affiche l'utilisation de la heap
#	HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
#	if [ -n "$HEAP_USAGE" ]; then
#		echo -e "\033[1;94mUtilisation totale de la heap :\033[0m"
#		echo "$HEAP_USAGE"
#	fi
#
#	# Vérifie les descripteurs de fichiers non fermés
#	FD_COUNT=$(grep -E "FILE DESCRIPTORS: [0-9]+ open" $TEMPFILE | awk '{print $4}')
#	if [ -n "$FD_COUNT" ] && [ "$FD_COUNT" -gt 3 ]; then
#		echo -e "\033[1;91mDes descripteurs de fichiers non fermés ont été détectés :\033[0m"
#		grep -A 3 "FILE DESCRIPTORS:" $TEMPFILE | grep -v "std"
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucun descripteur de fichier non fermé détecté.\033[0m"
#	fi
#
#	# Affiche les autres erreurs possibles
#	ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
#	if [ -n "$ERROR_SUMMARY" ]; then
#		echo -e "\033[1;94mERROR SUMMARY:\033[0m"
#		echo "$ERROR_SUMMARY"
#	fi
#
#	# Nettoyage
#	rm $TEMPFILE
#done
#
#for prefix in s w e p r
#do
#	case $prefix in
#		s|w) max=5;;
#		e) max=6;;
#		p) max=4;;
#		r) max=1;;
#		ok) max=16;;
#	esac
#	for i in $(seq 1 $max)
#	do
#		TEMPFILE=$(mktemp)
#		echo -e "\033[1;94m${prefix}_${i}.ber\033[1;93m"
#		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./so_long ./test/mandatory/maps/${prefix}_${i}.ber &> $TEMPFILE
#
#		# Variables pour stocker les valeurs de fuites de mémoire
#		def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
#		ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
#		pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
#		still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
#		suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')
#
#		# Vérifie les fuites de mémoire
#		if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
#			echo -e "\033[1;91mDes fuites de mémoire ont été détectées :\033[0m"
#			grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
#			((error_count++))
#		else
#			echo -e "\033[1;92mAucune fuite de mémoire détectée.\033[0m"
#		fi
#
#		# Affiche l'utilisation de la heap
#		HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
#		if [ -n "$HEAP_USAGE" ]; then
#			echo -e "\033[1;94mUtilisation totale de la heap :\033[0m"
#			echo "$HEAP_USAGE"
#		fi
#
#		# Vérifie les descripteurs de fichiers non fermés
#		FD_COUNT=$(grep -E "FILE DESCRIPTORS: [0-9]+ open" $TEMPFILE | awk '{print $4}')
#		if [ -n "$FD_COUNT" ] && [ "$FD_COUNT" -gt 3 ]; then
#			echo -e "\033[1;91mDes descripteurs de fichiers non fermés ont été détectés :\033[0m"
#			grep -A 3 "FILE DESCRIPTORS:" $TEMPFILE | grep -v "std"
#			((error_count++))
#		else
#			echo -e "\033[1;92mAucun descripteur de fichier non fermé détecté.\033[0m"
#		fi
#
#		# Affiche les autres erreurs possibles
#		ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
#		if [ -n "$ERROR_SUMMARY" ]; then
#			echo -e "\033[1;94mERROR SUMMARY:\033[0m"
#			echo "$ERROR_SUMMARY"
#		fi
#
#		# Nettoyage
#		rm $TEMPFILE
#	done
#done
#
#for i in "${!list_valid_map[@]}"
#do
#	TEMPFILE=$(mktemp)
#	echo -e "\033[1;94mTEST $((i + 1)): ./so_long ./test/mandatory/maps/${list_valid_map[i]}\033[1;93m"
#	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./so_long ./test/mandatory/maps/${list_valid_map[i]} &> $TEMPFILE
#	
#	# Variables pour stocker les valeurs de fuites de mémoire
#	def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
#	ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
#	pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
#	still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
#	suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')
#
#	# Vérifie les fuites de mémoire
#	if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
#		echo -e "\033[1;91mDes fuites de mémoire ont été détectées :\033[0m"
#		grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucune fuite de mémoire détectée.\033[0m"
#	fi
#
#	# Affiche l'utilisation de la heap
#	HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
#	if [ -n "$HEAP_USAGE" ]; then
#		echo -e "\033[1;94mUtilisation totale de la heap :\033[0m"
#		echo "$HEAP_USAGE"
#	fi
#
#	# Vérifie les descripteurs de fichiers non fermés
#	FD_COUNT=$(grep -E "FILE DESCRIPTORS: [0-9]+ open" $TEMPFILE | awk '{print $4}')
#	if [ -n "$FD_COUNT" ] && [ "$FD_COUNT" -gt 3 ]; then
#		echo -e "\033[1;91mDes descripteurs de fichiers non fermés ont été détectés :\033[0m"
#		grep -A 3 "FILE DESCRIPTORS:" $TEMPFILE | grep -v "std"
#		((error_count++))
#	else
#		echo -e "\033[1;92mAucun descripteur de fichier non fermé détecté.\033[0m"
#	fi
#
#	# Affiche les autres erreurs possibles
#	ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
#	if [ -n "$ERROR_SUMMARY" ]; then
#		echo -e "\033[1;94mERROR SUMMARY:\033[0m"
#		echo "$ERROR_SUMMARY"
#	fi
#
#	# Nettoyage
#	rm $TEMPFILE
#done

# Bouclage sur tout avec valgrind
echo -e "\033[1;94m _______  _   ___    _\033[0m"
echo -e "\033[1;94m|  ____| |_| |   \  | |\033[0m"
echo -e "\033[1;94m| |__     _  | |\ \ | |\033[0m"
echo -e "\033[1;94m|  __|   | | | | \ \| |\033[0m"
echo -e "\033[1;94m| |      | | | |  \ | |\033[0m"
echo -e "\033[1;94m|_|      |_| |_|   \__|\033[0m"
echo ""

# Affiche le nombre total d'erreurs détectées
echo -e "\n\033[1;93mNombre total d'erreurs détectées : $error_count\033[0m"
echo -e "\n\033[1;92mTester le programme en modifiant le nom des images du jeux.\033[0m"

chmod +r ./bad_config/not_readable.conf
make fclean