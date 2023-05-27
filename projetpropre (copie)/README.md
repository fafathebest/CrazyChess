
# Crazy Chess

Crazy Chess est une version un peu modifié du célèbre jeu d'échec, apportant de nouvelles pièces, une phase de préparation et d'autres nouvelles fonctionnalités excitantes.


## Présentation

Notre jeu se joue à 2 joueurs et uniquement à la souris.
Dans ce readme nous appellerons joueur 1 celui qui contrôle les blancs et joueur 2 celui qui contrôle les noirs. Pour différencier les pièces, nous avons mis en
majuscule le nom des pièces blanches et en minuscule celui des pièces noires. Au début de la partie, le camp du joueur 1 se trouve en bas de l'échiquier tandis
que celui du joueur 2 se trouve en haut de l'échiquier.


## Lancement du programme
Une fois le programme lancé, vous arrivez sur le menu où vous avez 3 possibilités.
- Play to the game : lance une toute nouvelle partie et écrase toute sauvegarde d'autre partie.
- Continue the game : reprends une sauvegarde si vous avez arreter le programme lors d'une précédente partie.
- Quit the game : arrête le programme.
\
\
Voici les différentes phases du jeu si vous lancez une nouvelle partie :
## Phase de préparation :
Les joueurs vont préparer chacun leur tour la composition de leur camp. Pour placer une pièce, il faut premièrement cliquer sur la pièce voulue dans l'encadré bleu à droite, et ensuite cliquer sur l'échiquier à l'emplacement voulu (voir en bas le nom des pièces). Lorsque le joueur 1 n'a plus de points, c'est au joueur 2 de préparer son armée. La préparation du joueur 2 se déroule de la même manière.

/!\ ATTENTION /!\ le joueur 2 prépare sa composition dans la partie inférieure de l'échiquier aussi (à l'endroit se trouvent normalement les pièces du joueur 1) mais une fois que la partie commence, sa composition est décalé dans son camp, en haut de l'échiquier de façon symétrique à une droite coupant l'échiquier verticalement. Une fois qu'il n'a plus de points, sa composition est renvoyé en haut de l'échiquier, la composition du joueur 1 réapparaît et la phase de bataille commence.

## Phase de bataille :
La phase de bataille se déroule comme dans un jeu d'échec classique. Chaque joueur déplace chacun leur tour une pièce qui leur appartient (le joueur 1 joue en premier).
\
Pour déplacer une pièce, il faut cliquer sur la pièce que l'on souhaite bouger.
Une fois une pièce sélectionnée, les cases représentant un mouvement possible vont être surlignées en blanc sur l'échiquier. Les cases contenants un mouvements qui
élimine une pièce seront eux surlignés en rouge.
\
Une fois les mouvements possible affichés, le joueur n'a plus qu'a cliquer sur le mouvement qu'il souhaite effectuer. C'est ensuite à l'autre joueur de jouer.

## Phase de fin :
Pour terminer une partie, il y a 3 possibilités :
- Echec et mat : il faut que l'un des 2 joueurs mette en échec et mat le Roi adverse. C'est à dire que peut importe le mouvement que son adversaire va faire, le joueur peut éliminer le Roi au prochain tour. Dans ce cas là, le joueur gagne.

- Pat : si un des joueurs se trouve dans une situation où il n'est pas en échec mais qu'il ne peut effectuer aucun mouvement, il y a pat. Cela signifie qu'il y a égalité.

- Nulle : si il ne reste que les 2 Rois sur l'échiquier, la partie est nulle et se finit en égalité.
Lorsqu'une partie se finit, l'écran de fin apparaît et ensuite renvoie vers le menu.
## Affichage et prix des Pièces
Sur l'interface de jeu, les pièces seront représentées par des initiales. Les blancs en majuscule et les noirs en minuscules.

/!\ ATTENTION /!\ Certaines pièces ayant la même initiale, il y en a qui n'ont pas leur initiale (knight et prince).
| Nom | Symbole | Prix |
| - | - | - |
| Pawn | P | 1 |
| Rook | R | 5 |
| Knight | N | 3 |
| Bishop | B | 3 |
| Queen | Q | 10 |
| King | K | ratio |
|  |  | |
| Prince | I | 6 |
| Centaur | C | 7 |
| Valiant | V | 25 |
| Archer | A | 8 |
