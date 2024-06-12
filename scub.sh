#!/bin/bash

# Couleurs
rouge='\e[1;31m'
jaune='\e[1;33m'
bleu='\e[1;34m'
violet='\e[1;35m'
vert='\e[1;32m'
neutre='\e[0;m'

echo -e "${jaune}"

echo -e "	 ██████ ██    ██ ██████  ██████  ██████  "
echo -e "	██      ██    ██ ██   ██      ██ ██   ██ "
echo -e "	██      ██    ██ ██████   █████  ██   ██ "
echo -e "	██      ██    ██ ██   ██      ██ ██   ██ "
echo -e "	 ██████  ██████  ██████  ██████  ██████  "
echo -e "${neutre}"

echo -e "${bleu} ---------------------- ${vert}SELECT TEST ${bleu}----------------------"
echo -e "${bleu}-----------------------------------------------------------${neutre}"
echo -e "${bleu} --------------- ${vert}Invalid Maps : Type I/i ${bleu}-----------------"
echo -e "${bleu}-----------------------------------------------------------${neutre}"
echo -e "${bleu} ----------------- ${vert}Valid Maps : Type V/v ${bleu}-----------------"
echo -e "${bleu}-----------------------------------------------------------${neutre}"
echo -e "${bleu} -------------------- ${vert}All : Type A/a ${bleu}---------------------"
echo -e "${bleu}-----------------------------------------------------------${neutre}"
echo -e "${vert}"
read -p "                [v/i/a]" rep
case $rep in
V)
	mode=1
	;;
v)
	mode=1
	;;
I)
	mode=2
	;;
i)
	mode=2
	;;
A)
	mode=3
	;;
a)
	mode=3
	;;
*)
	mode=4
	;;
esac
if [ $mode -eq 1 ] || [ $mode -eq 3 ]; then
	make 2>/dev/null >/dev/null              # make et stdout et stderr redirigé vers null cad empeche l'affichage
	cd maps/valid                            # on se déplace dans le fichier des maps non valides
	echo "ARG=(" >>../../maps.sh             # on creer le fichier maps.sh qui sert de liste d'arguments (ARG)
	ls | sed 's/^/"/;s/$/"/' >>../../maps.sh # on le remplis avec la list du dossier et ajoute des double quotes aux extremités avec sed
	echo ")" >>../../maps.sh                 # on ferme la parenthèse de la liste d'argument
	cd ../..                                 # on revient a la racine
	source maps.sh                           # on source le fichier crée plus haut qui contient en ARG tous les noms des maps

	for i in "${ARG[@]}"; do # on parcours la liste d'argument ARG
		echo -e "${bleu}-----------------------------------------------------------${neutre}"
		echo -e "        ${vert}$i${neutre}" # nom de l'argument (map)

		valgrind --track-fds=yes --leak-check=full ./cub3d ./maps/valid/$i 2>tmp >/dev/null # on copie stderr (2) vers un fichier temporaire (tmp) et stdout vers null
		error=$(cat tmp | grep "Error" | wc -l)                                             # on recupère le resultat de grep error sur tmp dans une variable : error
		errorseg=$(cat tmp | grep "segmentation fault" | wc -l)                             # on recupère le resultat de grep error sur tmp dans une variable : error
		errjump=$(cat tmp | grep "Conditional jump" | wc -l)                                # on recupère le resultat de grep error sur tmp dans une variable : error
		leaks=$(cat tmp | grep "no leaks are possible" | wc -l)
		fdclose=$(cat tmp | grep "FILE DESCRIPTOR" | awk '{gsub(/\(/, "", $6); print $6}')
		fdopen=$(cat tmp | grep "FILE DESCRIPTOR" | awk '{print $4}')

		if [ $fdopen -ne $fdclose ]; then
			success=${rouge}
		else
			success=${vert}
		fi

		printf ${bleu}"   Error : "
		if [ $error -eq 1 ] || [ $errjump -eq 1 ]; then # si grep égale 1 alors ok
			printf ${rouge}"[KO]"${neutre}
		else
			printf ${vert}"[OK]"${neutre}
		fi

		printf ${bleu}"   Leaks : "
		if [ $leaks -eq 1 ]; then # si grep égale 1 alors ok
			printf ${vert}"[OK]"${neutre}
		else
			printf ${rouge}"[KO]"${neutre}
		fi

		printf ${bleu}"   FDs : "
		printf ${success}"$fdclose/$fdopen${neutre}\n"
		echo -e "${bleu}-----------------------------------------------------------${neutre}"
		echo ""
		rm tmp

	done
	rm maps.sh # on efface le fichier maps.sh
	if [ $mode -eq 1 ]; then
		make fclean >/dev/null
	fi
fi
if [ $mode -eq 2 ]; then
	make 2>/dev/null >/dev/null
fi
if [ $mode -eq 2 ] || [ $mode -eq 3 ]; then
	cd maps/invalid                                    # on se déplace dans le fichier des maps non valides
	chmod 000 forbidden.cub                            # supprime toutes les permissions des maps et maps/dir pour les tests
	echo "ARG=(" >>../../maps.sh                       # on creer le fichier maps.sh qui sert de liste d'arguments (ARG)
	ls | sed 's/^/"/;s/$/"/' >>../../maps.sh           # on le remplis avec la list du dossier et ajoute des double quotes aux extremités avec sed
	echo '"this-map-doesnt-exist.cub"' >>../../maps.sh # ajout d'une ligne entre double quote grace au single quotes
	echo "\"neither-this-one.cub\"" >>../../maps.sh    # même resultat qu'au dessus mais qvec le backslash
	echo ")" >>../../maps.sh                           # on ferme la parenthèse de la liste d'argument
	cd ../..                                           # on revient a la racine
	source maps.sh                                     # on source le fichier crée plus haut qui contient en ARG tous les noms des maps

	for i in "${ARG[@]}"; do # on parcours la liste d'argument ARG
		echo -e "${bleu}-----------------------------------------------------------${neutre}"
		echo -e "        ${vert}$i${neutre}" # nom de l'argument (map)

		valgrind --track-fds=yes --leak-check=full ./cub3d ./maps/invalid/$i 2>tmp >/dev/null # on copie stderr (2) vers un fichier temporaire (tmp) et stdout vers null
		error=$(cat tmp | grep "Error" | wc -l)                                               # on recupère le resultat de grep error sur tmp dans une variable : error
		leaks=$(cat tmp | grep "no leaks are possible" | wc -l)                               # on recupere la chaine entre "" dans leaks
		fdclose=$(cat tmp | grep "FILE DESCRIPTOR" | awk '{gsub(/\(/, "", $6); print $6}')    # gsub (global substitution) remplace tous ce qu'il y a entre les 2 / ; cad '(' ; par "" dans la colonne 6
		fdopen=$(cat tmp | grep "FILE DESCRIPTOR" | awk '{print $4}')

		if [ $fdopen -ne $fdclose ]; then # si fdopen est different de fdclose
			success=${rouge}
		else
			success=${vert}
		fi

		./cub3d ./maps/invalid/$i 2>&1 >/dev/null | head -2 | tail -1 # 2>&1 redirige stderr (2) vers stdout (1) puis envoie stdout dans null mais garde la redirection pour le pipe de head

		if [ $error -eq 1 ] && [ $leaks -eq 1 ]; then # si grep égale 1 alors ok
			echo -e "${bleu}   Error : ${vert}[OK]${bleu}    Leaks : ${vert}[OK]${bleu}   FDs : ${success}$fdclose/$fdopen${neutre}"
		elif [ $error -eq 1 ] && [ $leaks -ne 1 ]; then
			echo -e "${bleu}   Error : ${vert}[OK]${bleu}    Leaks : ${rouge}[KO]${bleu}   FDs : ${success}$fdclose/$fdopen${neutre}"
		elif [ $error -ne 1 ] && [ $leaks -eq 1 ]; then
			echo -e "${bleu}   Error : ${rouge}[KO]${bleu}   Leaks : ${vert}[OK]${bleu}   FDs : ${success}$fdclose/$fdopen${neutre}"
		else
			echo -e "${bleu}   Error : ${rouge}[KO]${bleu}   Leaks : ${rouge}[KO]${bleu}   FDs : ${success}$fdclose/$fdopen${neutre}"
		fi
		echo -e "${bleu}-----------------------------------------------------------${neutre}"
		echo ""
		rm tmp

	done
	rm maps.sh                           # on efface le fichier maps.sh
	chmod 777 maps/invalid/forbidden.cub # redonne toutes les permissions des maps et maps/dir
	make fclean >/dev/null
fi
