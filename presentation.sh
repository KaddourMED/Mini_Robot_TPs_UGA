bold=$(tput bold)
normal=$(tput sgr0)
# C'est le Menu
printf "************************************************************\n"
sleep 0.5
printf "*******************\t${bold}BIENVENUE${normal}\t********************\n"
sleep 0.5
printf "************************************************************\n"
printf "************************************************************\n"
sleep 0.5
printf "**********\t${bold}PRESENTATION DU TP 6/7/8/9${normal}\t************\n"
sleep 0.5
printf "************************************************************\n"
printf "************************************************************\n"
sleep 0.5
printf "*******   ${bold}VOICI LE MENU DES COMMANDES CI DESSOUS${normal}    ********\n"
sleep 0.5
printf "************************************************************\n"
printf "************************************************************\n"
sleep 0.5
printf "\n\n"
printf "${bold}- Veuillez choisir une des propositions suivantes: ${normal}\n\n"
sleep 0.5
printf "${bold} **  TP6  **\n"
sleep 0.5
printf "\nTEST TERRAIN\n\n"
printf "${normal}Terrains Corrects: \n"
printf "1) Terrain1\n"
printf "2) Terrain2\n"
sleep 0.5

printf "${normal}\nTerrains Incorrects: \n"
printf "3) Erreur ouverture de terrain (il faudra entrer un fichier correct)\n"
printf "4) Erreur ligne(s) trop longue(s)\n"
printf "5) Erreur ligne(s) manquante(s)\n"
printf "6) Erreur caractere(s) incorrect(s)\n"
printf "7) Erreur lecture largeur\n"
printf "8) Erreur lecture hauteur\n"
printf "9) Erreur position robot manquante\n"
sleep 0.5

printf "${bold}\nTEST ROBOT\n\n"
sleep 0.5
printf "${normal}10) Tester les fonctionnalites du robot\n"
printf "11) Tester les fonctionnalites du robot en affichant le terrain\n"

sleep 0.5
printf "${bold}\n **  TP7  **\n"
sleep 0.5

printf "\nTESTS FONCTIONNELS\n\n"
sleep 0.5

printf "${normal}12) Tout OK\n"
printf "13) Orientation, abscisse, ordonnee incorrectes\n"
printf "14) Robot tomber a l'eau\n"

sleep 0.5
printf "${bold}\nTESTS ROBUSTESSE\n\n"
sleep 0.5

printf "${normal}15) Erreur ouverture du fichier (il faudra entrer un fichier correct)\n"
printf "16) Erreur bloc non ferme\n"
printf "17) Erreur caractere incorrect\n"

sleep 0.5
printf "${bold}\n **  TP8  **\n"
sleep 0.5

printf "${bold}\nTESTS GENERATIONS TERRAINS\n\n"
sleep 0.5

printf "${normal}18) Generation de 10 terrains de 9*9 avec d = 0.5 (Resultat dans fichier_res)\n "

sleep 0.5
printf "${bold}\nTESTS CURIOSITY PERF\n\n"
sleep 0.5

printf "${normal}19) { 1 M { G } { A } ? C ! } C! (programme donne, 20 terrains, 7*7, d = 0.6)\n"
printf "20) { 7 M { D } { G A } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "21) { 3 M { G } { D A } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "22) { 5 M { G } { G G A G } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "23) { 7 M { D } { G A } ? C ! } C! (20 terrains, 11*11, d = 0.8)\n"


sleep 0.5
printf "${bold}\n **  TP9  **\n\n"
sleep 0.5

printf "${normal}24) Programmes-robots corrects, acceptes par l'observateur\n"
printf "25) Programmes-robots corrects, rejete par l'observateur\n"
printf "26) Programmes-robots incorrects, acceptes par l'observateur\n"
printf "27) Programmes-robots incorrects, rejete par l'observateur\n"

while :
do


printf "\nPress '0' to exit\n"
read k  
case $k in
1 )     ./test_terrain Terrains_Corrects/terrain_1;;
 
2 )     ./test_terrain Terrains_Corrects/terrain_2;;

3 )     ./test_terrain Terrains_Incorrects/terr;;

4 )     ./test_terrain Terrains_Incorrects/terrain_1;;

5 )     ./test_terrain Terrains_Incorrects/terrain_2;;

6* )     ./test_terrain Terrains_Incorrects/terrain_3;;

7* )     ./test_terrain Terrains_Incorrects/terrain_4;;

8* )     ./test_terrain Terrains_Incorrects/terrain_5;;

9* )     ./test_terrain Terrains_Incorrects/terrain_6;;

10*)     ./test_robot;;

11)     ./robot_terrain Terrains_Corrects/terrain_1;;

12*)     ./curiosity-test Tests-TP7/tests-fonctionnels/boucle/chemin.test;;

13*)     ./curiosity-test Tests-TP7/tests-fonctionnels/pas_OK/chemin.test;;

14*)     ./curiosity-test Tests-TP7/tests-fonctionnels/robot_plouf/chemin.test;;

15*)     ./curiosity-test blabla;;

16*)     ./curiosity-test Tests-TP7/tests-robustesse/Erreur_exec_pg/erreur_bloc_non_ferme/chemin.test;;

17*)     ./curiosity-test Tests-TP7/tests-robustesse/Erreur_exec_pg/erreur_carac_incorrect/chemin.test;;

18*)     ./test_generation_terrains 10 9 9 0.5 fichier_res;;

19*)     ./curiosity-perf Programmes_TP8/test1/prg1 20 7 7 0.6 10 10000 fichier_res;;

20*)     ./curiosity-perf Programmes_TP8/test3/prg3 20 7 7 0.6 10 10000 fichier_res;;

21*)     ./curiosity-perf Programmes_TP8/test4/prg4 20 7 7 0.6 10 10000 fichier_res;;

22*)     ./curiosity-perf Programmes_TP8/test5/prg5 20 7 7 0.6 10 10000 fichier_res;;

23*)     ./curiosity-perf Programmes_TP8/test3/prg3 20 11 11 0.8 1 10000 fichier_res;;

24*)     ./curiosity-obs Programmes_TP9/correct-accepte/terrain_sortie_1 Programmes_TP9/correct-accepte/prg1;;

25*)     ./curiosity-obs Programmes_TP9/correct-rejete/terrain1 Programmes_TP9/correct-rejete/prg1;;

26*)     ./curiosity-obs Programmes_TP9/incorrect-accepte/terrain1 Programmes_TP9/incorrect-accepte/prg1;;

27*)     ./curiosity-obs Programmes_TP9/incorrect-rejete/terrain1 Programmes_TP9/incorrect-rejete/prg1;;


0*) printf "\nQuitting from the program\n"
    break;;
 
* )     echo "Try again.";;

esac

read -p "Press enter to continue....."

printf "\n\n"
printf "${bold}- Veuillez choisir une des propositions suivantes: ${normal}\n\n"
printf "${bold} **  TP6  **\n"
printf "\nTEST TERRAIN\n\n"
printf "${normal}Terrains Corrects: \n"
printf "1) Terrain1\n"
printf "2) Terrain2\n"

printf "${normal}\nTerrains Incorrects: \n"
printf "3) Erreur ouverture de terrain (il faudra entrer un fichier correct)\n"
printf "4) Erreur ligne(s) trop longue(s)\n"
printf "5) Erreur ligne(s) manquante(s)\n"
printf "6) Erreur caractere(s) incorrect(s)\n"
printf "7) Erreur lecture largeur\n"
printf "8) Erreur lecture hauteur\n"
printf "9) Erreur position robot manquante\n"

printf "${bold}\nTEST ROBOT\n\n"
printf "${normal}10) Tester les fonctionnalites du robot\n"
printf "11) Tester les fonctionnalites du robot en affichant le terrain\n"

printf "${bold}\n **  TP7  **\n"

printf "\nTESTS FONCTIONNELS\n\n"

printf "${normal}12) Tout OK\n"
printf "13) Orientation, abscisse, ordonnee incorrectes\n"
printf "14) Robot tomber a l'eau\n"

printf "${bold}\nTESTS ROBUSTESSE\n\n"

printf "${normal}15) Erreur ouverture du fichier (il faudra entrer un fichier correct)\n"
printf "16) Erreur bloc non ferme\n"
printf "17) Erreur caractere incorrect\n"

printf "${bold}\n **  TP8  **\n"

printf "${bold}\nTESTS GENERATIONS TERRAINS\n\n"

printf "${normal}18) Generation de 10 terrains de 9*9 avec d = 0.5 (Resultat dans fichier_res)\n "

printf "${bold}\nTESTS CURIOSITY PERF\n\n"

printf "${normal}19) { 1 M { G } { A } ? C ! } C! (programme donne, 20 terrains, 7*7, d = 0.6)\n"
printf "20) { 7 M { D } { G A } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "21) { 3 M { G } { D A } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "22) { 5 M { G } { G G A G } ? C ! } C! (20 terrains, 7*7, d = 0.6)\n"
printf "23) { 7 M { D } { G A } ? C ! } C! (20 terrains, 11*11, d = 0.8)\n"


printf "${bold}\n **  TP9  **\n\n"

printf "${normal}24) Programmes-robots corrects, acceptes par l'observateur\n"
printf "25) Programmes-robots corrects, rejete par l'observateur\n"
printf "26) Programmes-robots incorrects, acceptes par l'observateur\n"
printf "27) Programmes-robots incorrects, rejete par l'observateur\n"


echo "Choisissez Le Numero : "

done



