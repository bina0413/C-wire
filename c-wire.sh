#!/bin/bash

# parametre d'entree : type station, type cosso, identifiant station


erreur(){ # parametre entier positif, message selon code d'erreur
	message0="Une erreur est survenue"
	message1="Verifiez que les répertoires tmp, graphs,codeC, imput et test sont des dossiers existants"
	message2="Le chemin d'entré est invalide ou le fichier n'existe pas"
	message3="Nombre de parametres insuffisant: ./c-wire <chemin> <station> <client> (<identifiant>)"
	message4="Les parametres <2> et {3} peut respectivement prendre les valeurs permis: <"hvb","hva","lv"> et {"all","comp","indiv"}"
	message5="Les staions hvb et hva ne prennent que des entreprises en clients. Entrez des parametres correctes"
	message6="Le fichier C n'existe pas"
	case $1 in

		1)
			echo $message1
			exit 1
			;;
		2)
			echo $message2
			exit 2
			;;
		3)
			echo $message3
			exit 3
			;;
		4)
			echo $message4
			exit 4
			;;
		5)
			echo $message5
			exit 5
			;;
		6)
			echo $message6
			# exit 6
			;;
		*)
			echo $message0
			exit 0
			;;
	esac



}

verif(){
	# existance des dossiers avec -d
	if [ ! -d "tmp" ] || [ ! -d "test" ] || [ ! -d "imput" ] || [ ! -d "graphs" ] || [ ! -d "codeC" ]
	then
		erreur 1
	# existance de data.csv
	elif [ ! -f "$1" ]
	then
		erreur 2
	# existance des parametres station et conso
	elif [ -z "$2" ] || [ -z "$3" ]
	then
		erreur 3
	# validite des parametres
	elif [ "$2" != "hvb" ] && [ "$2" != "hva" ] && [ "$2" != "lv" ]
	then
		erreur 4
	elif [ "$3" != "all" ] && [ "$3" != "comp" ] && [ "$3" != "indiv" ]
	then 
		erreur 4
	# compatibilité de conso avec station		
	elif { [ "$2" = "hvb" ] || [ "$2" = "hva" ] ;} && [ "$3" != "comp" ]; then
		erreur 5	# si pb appel de la fonction erreur avec code d'erreur
	fi
	return 0

}
dossier(){
	if [ ! -d "tmp" ]; then
		mkdir tmp
	else
		rm -rf tmp/* 					# vider le repertoire tmp
	fi

	if [ ! -d "graphs" ]; then
		mkdir graphs
	else
		rm -rf graphs/* 				# vider le repertoire graphs
	fi
}




filtrer(){ # parametre data.csv station conso ident


	case $station in # recuperer le numero de colone a analyser
		hvb) colone1=2;;
		hva) colone1=3;;
		lv) colone1=4;;
	esac
	if [ $conso == "indiv" ]; then
		colone2=5
	else
		colone2=$((colone1+1))	
	fi

	# filtrer par station
	awk -F ';' -v colone1="$colone1" -v colone2="$colone2" '{if ($colone1 != "-" && $colone2 == "-" ) {print $0}}' imput/data.csv > tmp/data_tmp.csv

	# effacer les colone inutiles
	if [ $conso == "indiv" ]; then
		cut -d";" -f"$colone1",6,7,8 tmp/data_tmp.csv > tmp/data_tmp1.csv
		awk -F";" '{gsub("-", "0"); print $0}' tmp/data_tmp1.csv > tmp/data_tmp2.csv
	else
		cut -d";" -f"$colone1",5,7,8 tmp/data_tmp.csv > tmp/data_tmp1.csv
		awk -F";" '{gsub("-", "0"); print $0}' tmp/data_tmp1.csv > tmp/data_tmp2.csv

	fi	

	# filtrer par identifiant si besoin
	if (( $ident != 0 )); then
		awk -F ';' '{ if ($1 == '$ident') {gsub("-", "0"); print $0}}' tmp/data_tmp1.csv > tmp/data_tmp2.csv
	fi
	# retourne le chemin fichier trie au code C
	}

	filtrerLVall() {
	awk -F ';' '{if ($4 != "-" && ($5 == "-" || $6 == "-") ) {print $0}}' imput/data.csv > tmp/data_tmp.csv
	# si la colonne 5 est vide alors copier colonne 6 dans 5 
	awk -F ';' '{if ($5 == "-") {$5 = $6;} gsub("-", "0")}' tmp/data_tmp.csv
	cut -d";" -f4,5,7,8 tmp/data_tmp.csv > tmp/data_tmp1.csv
	awk -F ';' '{ gsub("-", "0"); print $0}' tmp/data_tmp1.csv > tmp/data_tmp2.csv

	
		# filtrer par identifiant si besoin

	if (( $ident != 0 )); then
		awk -F ';' '{ if ($1 == '$ident') {gsub("-", "0"); print $0}}' tmp/data_tmp1.csv > tmp/data_tmp2.csv
	fi

	}


calcul() { # parametre : chemin nouveau fichier csv avec donnees triees
		# verification de l'existance de l'executable
		if [ ! -f "codeC/main.c" ]
		then
			erreur 6
		else
			make -C codeC/
		fi
}

creationFichierSortie(){
echo "Station $station:Capacité:Consomation ($conso)" > $fichier
sort -t ":" -k 2 -n codeC/calcule.csv >> $fichier 
echo "création fichier sortie $fichier est terminée, vous pouvez consulter dans le repertoire courant"

}
creationMinMax(){


	echo "Station LV(MinMax) :Capacité :Consomation (tous)" > lv_all_minmax.csv
	#awk -F ':' '{print $0":"$(($2-$3))}' codeC/calcule.csv >> lv_all_minmax aider par l'ia
	awk -F ':' '{print $0 ":" ($2 - $3)}'  codeC/calcule.csv > temp.csv && mv temp.csv codeC/calcule.csv
	sort -t ":" -k 4 -n codeC/calcule.csv >> lv_all_minmax.csv
	head lv_all_minmax.csv >> temp.csv && mv temp.csv lv_all_minmax.csv
	tail lv_all_minmax.csv >> temp.csv && mv temp.csv lv_all_minmax.csv

	cut -d ':' -f1,2,3 lv_all_minmax.csv > temp.csv && mv temp.csv lv_all_minmax.csv
	echo "création fichier lv_all_minmax.csv terminée, vous pouvez consulter dans le repertoire courant"


}



# ******** MAIN *************

#initialisation des variables

chemin=$1
station=$2 
conso=$3
if [ -z "$4" ] 
then
	ident=0
	fichier=$station"_"$conso".csv"
else
	ident=$4
	fichier=$station"_"$conso"_"$ident".csv"
fi
verif $chemin $station $conso 			# procède aux verifications des parametre
cp $chemin imput/data.csv 				# copier le fichier d'entrée dans imput
dossier									# verifie repertoires graph et tmp
 	
temps1=$(date +%s)	
	if [ $conso == "all" ]	#filtrage des donnees selon les parametre
	then	
		filtrerLVall
	else
		filtrer 			
	fi
	calcul						# appel du programme de calcul C prend le fichier trie en parametre
temps2=$(date +%s)	
duree=$((temps2-temps1)) 		#calcul de la duree de l'execution

creationFichierSortie
if [ $conso == "all" ]
then
	creationMinMax
fi

echo "durée du programme: $duree secondes"


