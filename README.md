Bienvenue,

comment utiliser ce programme:
- compilier le script avec la commande ./c-wire.sh  <chemin/nom_fichier.csv> <type_sation> <type_consomateurs> (<identifiant>)
- le type de station peut être "hvb" "hva" "lv" tout en minuscule
- le type de consomateur peut etre "all" "comp" "indiv" en minuscule
- on peut mettre un identifiant comme parametre si souhaité il s'agit d'un nombre 

points qui fonctionne bien:
  
  - la verification des option (présence + compatibilité des station et consommateurs)
  - la vérification de la présence des differents repertoires nécessaires
  - le filtrage du fichier data.csv
  - le trie en fonction de la capacité
  - la libération de la mémoire
  - l'execution du programe C depuis le Makefile
    
  

points présents mais qui fonctionnent mal:

  - le temps est bien donné mais il comprend parfois la durée de compilation du programme C (lorsque celui ci est recompilé après modification)
  - le temps est long > 1min pour les station lv 

points qui sont absents de ce projet:
  - la création de graphique
  - l'option help -h d'aide
  - la commande 'clean' n'est pas inclue dans le makefile

RAPPORT:
    Aucune repartition des taches car projet effectué seule
    le plus du gros travaille a été effectué le weekend du 14 decembre.

    
