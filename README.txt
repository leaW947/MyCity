
------------Introduction------------

J'ai réalisé un jeu de gestion d'une ville. Ce jeu est le début d'un jeu de gestion et
de simulation d'une ville.J'ai programmé ce jeu avec le langage C,
la bibliothèque SDL2 et l'IDE Visual Studio Code.

J'ai créer les graphismes avec Inkscape et PyxelEdit.


-------------Déroulement du jeu--------

	------menu-------
Lors du lancement du projet, on arrive directement sur l'écran de menu. Il suffit de
cliquer sur le bouton "Play" pour commencer a jouer.



	------game-------

	---préambule

Une fois l'écran de jeu affiché, on arrive sur une map en 3D isométrique (ou 2D
isométrique).

Le but du jeu est de construire notre ville en faisant construire diverses bâtiments.
Une fois un bâtiment construit, celui-ci nous rapporte de l'argent. Tout cela en 
faisant face au imprévus que la gestion d'une ville peut engendrer.


      ---Description de l'écran de jeu

-En haut à droite de l'écran, il y a la somme d'argent actuel que nous avons pour 
gérer notre ville.

-En bas à gauche de l'écran il y a les différents index qui vont nous permettre
d'accéder aux inventaires.
	
	-L'index 1 -> Inventaire des routes
	-L'index 2 -> Inventaire des habitations
	-L'index 3 -> Inventaire des bâtiments communautaire
	-L'index 4 -> Inventaire des bâtiments commerciaux



	----construire des routes

Pour pouvoir construire une route il suffit tout d'abords de cliquer sur l'index
correspondant.
Ensuite il y a 5 icons qui apparaît:
	
	-Le premier est une croix qui permet de revenir vers les index.
	-Le deuxième permet de construire une route
	-Le troisième permet de construire un chemin de terre
	-Le quatrième permet de contruire une rivière
	-Le cinquième permet d'ajouter de l'herbe(texture de base de notre map). Sert
à retirer les routes, chemins de terre et rivière. Sert également à réparer la map
après un incendie (voir plus loin).

Pour pouvoir utiliser ces icons il suffit de cliquer dessus et ensuite de cliquer
sur les cases de la map pour changer la texture de chaque tuile.


	----construire des bâtiements

Pour pouvoir construire des bâtiments il suffit d'abords de cliquer sur l'index 
correspondant au type de bâtiment qu'on veut faire construire.
Ensuite l'inventaire des bâtiments s'affiche.

En dessous de chaque bâtiment il y leurs noms et sous leurs noms il y a leurs prix.

Une fois choisi, cliquer sur la bâtiment correspondant. Le bâtiment en question va
s'afficher sur la map et trois nouveau icons vont apparaîtrent.

	-Le premier icon sert a annuler la construction
	-Le deuxième icon sert a valider la construction
	-Le troisième icon sert a tourner le bâtiment pour l'afficher sous un autre
angle.

Pour bouger le bâtiment qui est sur la map, il suffit de cliquer dessus et ensuite de
bouger la souris.Si on a cliquer une première fois sur le bâtiment et qu'on clique
une seconde fois, on peut poser le bâtiment.Et ensuite on peut recliquer dessus 
pour de nouveau le bouger et ainsi de suite... On peut faire cela jusqu'à ce 
qu'on est cliquer sur l'icon valider.

Il y a un losange en dessous de notre bâtiment pour nous permettre de voir où notre
bâtiment va ce poser une fois qu'on aura valider la construction. Le losange nous
permet également de savoir où nous pouvons poser notre bâtiment ou non(le losange est
rouge si on ne peut pas poser le bâtiment, blanc si on peut poser le bâtiment).


Quand on a choisi l'emplacement du bâtiment et qu'on clique sur le bouton valider:

Si on a assez d'argent le bâtiment ce pose et on revient automatiquement vers les 
index. Sinon le bâtiment ne ce pose pas et on revient quand même vers les index mais
le bâtiment disparaît.

Quand un bâtiment est construit tout les x temps il va y avoir une bulle avec un dollar
afficher à l'intèrieur qui s'affichera au dessus de ce bâtiment. Il faut cliquer
sur cette bulle pour pouvoir récolter l'argent que nous a rapportait ce bâtiment. Selon
le type de bâtiment, on ne récoltera pas le même montant.

Si on veut supprimer un bâtiment de la map il suffit de tout d'abords cliquer sur le
bâtiment en question(cela fonctionne uniquement si le bâtiment n'a pas de bulle
afficher au dessus de lui).Ensuite il y a une flèche qui s'affiche au dessus du 
bâtiment pour nous permettre de bien voir le bâtiment qu'on veut supprimer.Et enfin
on peut cliquer sur l'icon jaune en bas à droite de l'écran qui vient de s'afficher.

Une fois le bâtiment supprimer, celui-ci disparaît.



---------------Incendie---------------  

A tout moment un incendie peut ce déclarer sur la map. Lorsque que ça arrive il y a
un bouton rouge qui s'affiche en bas à droite de l'écran. Il suffit de cliquer dessus
pour arrêter l'incendie et éviter des dégâts supplémentaires. 

Attention!!! l'incendie ce propage très vite sur la map. Si le feu touche un 
bâtiment, le bâtiment est brûler et est supprimer. A ce moment là impossible de le
récupérer et il disparaît complétement de la map.

Quand l'incendie est arrêter, on peut voir des tuiles de la map qui sont différentes
des autres à l'endroit où c'est propager le feu.

Il faut reconvrir ces tuiles d'herbe avant qu'un autre incendie ce déclare. 
Parce que si le feu touche une tuiles d'un précedent incendie, alors le feu ce 
propage encore plus vite.

Il faut aussi recouvrir ces tuiles d'herbe pour pouvoir construire dessus. Si on ne
recouvre pas ces tuiles d'herbe on ne pourra pas construire des routes dessus et 
si on fait construire un bâtiment dessus celui-ci aura plus de chance de brûler si 
il y a un autre incendie.
	
 


