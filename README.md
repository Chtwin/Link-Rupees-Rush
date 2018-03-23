# Tuto SDL pour les utilisateurs de MAC

**Voici un tutoriel qui explique comment insatller la SDL sur Mac (remerciements  à Mme.CHENANE pour le tuto): http://tuto-mac.wixsite.com/tuto-sdl-xcode**<br/>


# Link Rupees Rush

Link Rupees Rush est un jeu dans lequel 2 ia ou plus s'affrontent au cours d'un combat acharné. <br/>
Votre but est de récupérer le maximum de rubis ou bien de tuer votre/vos adversaire(s). <br/>
Voici un visuel de l'arène ci-dessous (sans les pnjs):<br/>
![Visuel_arene](http://www.image-heberg.fr/files/1521061448573218635.png)<br/>

# Installation

Pour faire fonctionner l'arène vous devrez tout d'abord installer **Code Blocks**. <br/>Voici le lien de téléchargement: <http://www.codeblocks.org/downloads><br/>
Ensuite il vous faudra ajouter plusieurs bibliothèques à savoir: la SDL **1.2**, la **SDL ttf**, la **SDL image**, la **SDL mixer**.<br/>
Voici les différents liens pour téléchager ce dont vous besoin:<br/>
La SDL **1.2**: <https://www.libsdl.org/download-1.2.php><br/>
La **SDL ttf**: <https://www.libsdl.org/projects/SDL_ttf/release-1.2.html><br/>
La **SDL image**:<https://www.libsdl.org/projects/SDL_image/release-1.2.html><br/>
La **SDL mixer**:<https://www.libsdl.org/projects/SDL_mixer/release-1.2.html><br/>
**Lien vers la vidéo qui explique comment télécharger et installer la SDL et le projet:** https://www.youtube.com/watch?v=-KT6cJdJakQ&feature=youtu.be&ab_channel=Chtwin<br/>
Note: Ajout de tous les fichiers dll de la vidéo dans un dossier téléchargeable.<br/>

# Configuration

En ce qui concerne la configuration vous aurez besoin d'installer tout ce qui est demandé ci-dessus. Une fois cela installé vous allez devoir télécharger **la dernière
version des dossiers** "arène_code" ainsi que du dossier "Images". Une fois les dossiers téléchargé, vous allez inclure toutes les images du dossier "Images" dans
le dossier "arène_code"**(Il faut bien inclure les images et non tout le dossier)**. Maintenant que vous avez cela, vous êtes normalement en mesure de lancer le programme.
**Il faut démarrer prot-jeu et non le main.c pour que le jeu fonctionne**<br/>
**Pour démarrer le jeu il faut appuyer une fois sur la barre espace**<br/>
**Si l'arène est coupée sur votre écran vous devez modifier l'affichage de votre ordinateur en suivant ce chemin: Menu Windows<Paramètre<Affichage et passez la résolution à 100%. Le jeu s'affiche maintenant en fullscreen correctement.**<br/>

# Règles du jeu
**Les XX symbolisent des nombres ou pourcentages pas encore établi, nous décideront des valeurs finales en fonction des premiers tests d'IA**
### Le 1vs1:
En début de partie, les deux IA se retrouveront face à face au centre de l'arène avec une épée et un bouclier chacune, ainsi que XX rubis chacun. Les déplacements dans les 4 directions sont possibles dès le début de la partie. Au bout de 5 secondes des rubis apparaîtront partout dans l'arène et les IAs ramasseront automatiquement les rubis en passant simplement dessus. Au bout de 10s les IAs pourront s'assener des coups d'épée entre elles. Lorqu'une IA reçoit un coup d'épée elle perd XX rubis et l'IA qui a asséné le coup reçoit XX pourcents des rubis perdus. L'IA peut égalment parer les coups d'épée à l'aide de son bouclier. Ensuite toutes les XX secondes des rubis ainsi qu'un pot vont apparaître au centre de l'arène. Le pot peut être cassé d'un simple coup d'épée, le pot contient soit des rubis ramassables soit une bombe. Si vous ramassez la bombe, elle est stocké dans un slot de votre inventaire, vous pourrez alors la poser quand vous le souhaitez. Après que la bombe soit posé, elle explosera au bout de X secondes et les IAs se trouvant dans un rayon de X perdont autant de rubis qu'un coup d'épée et l'IA ayant posé la bombe recupére XX pourcents de rubis. Une fois XXX secondes écoulés Ganon (une IA) va apparaître au centre de l'arène, il poursuivra l'IA qui a le plus de rubis et lui donnera un coup d'épée qui enlevera XX rubis. Même si l'IA n'a plus le plus de rubis et qu'il a été ciblé par Ganon, ce-dernier lui assenera tout de même le coup d'épée (comme la carapace bleu dans mario kart). Une fois le coup asséné, Ganon retourne au centre de la carte et pourra se redéplacer et redonner son coup au bout de XX secondes. Si le nombre de rubis d'une IA tombe à 0 ou moins il meurt et le survivant se retrouve vainqueur.**/!\ Ganon ne peut pas tuer les IAs, leur nombre de rubis tombera seulement à 1**. A la fin du temps imparti, l'IA qui a le plus de rubis gagne. En cas d'égalité l'IA qui a eu le plus de rubis en 1er gagne.
### A 26 IAs:
Les règles restent fondamentalement les mêmes mise à part celles-ci:<br/>
- les IAs vont debuter en cercle au centre de l'arène.<br/>
- Les rubis et pots vont apparaître dans toute l'arène.<br/>
- Les dégats de Ganon et les temps d'apparitions seront différents du 1vs1.<br/>

## Sondages

Vous pouvez maintenant choisir comment le jeu évoluera sur certains aspects! pour cela il vous suffit de vous rendre sur ce lien: https://docs.google.com/document/d/1_-hLKn6_rfkCmUssCuAujtt3TShWTMhPbLPiDf3e9Js/edit?usp=sharing<br/>

# Développement d'IA
**Il y aura plus d'informations très prochainement**<br/>
En terme d'informations, les IAs connaitront les positions de tous les items et IAs.<br/>
Les actions possibles citées ci-dessus sont: se déplacer, frapper, parer, poser une bombe.<br/>

## Options lors d'un tour.
Lors de votre tour vous pouvez réaliser une de ces actions, vous déplacer dans les 4 directions(haut, bas, gauche, droite), donner un coup d'épée dans la direction dans laquelle regarde votre personnage (ce qui permet de mettre des dégâts à une autre IA ou bien de casser un pot), parer un coup si une IA tente de vous assener un coup ou bien si vous êtes dans l'explosion d'une bombe(vous pouvez parer un nombre limité de fois dans la partie), poser une bombe qui explosera au bout d'un certain temps dans un rayon prédéfini.<br/>
Voici la liste de ce qui est opérationnel: <br/>
- La carte de l'arène 					   : Fonctionnel.
- Données de votre IA (et des autres?)	   : Fonctionnel. (Partiellement fonctionnel?)
- Déplacements (haut, bas, gauche, droite) : Fonctionnel.
- frapper                                  : Entier disponible avec l'animation.<br/>
- parer                                    : Entier disponible avec l'animation.<br/>
- poser une bombe						   : Entier disponible.<br/>
- Ganon (IA du jeu)						   : Fonctionnel.<br/>

## Coder l'IA

**Une partie du code utilise un sytème de timer mais à terme cela sera remplacé par un système de tour**<br/> 
Vous devez coder votre IA dans la fonction **ia_1** et elle doit retourner un entier en respcectant les interdictions indiqués en dessous. Cette fonction se trouve à la fin du header. La fonction **ia_2** vous permet de coder l'IA contre laquelle votre IA se battera. **Dans le header vous pouvez modifier le define NB_PLAYER comme vous le souhaitez, vous pouvez mettre autant de joueurs que vous voulez. En réalité, en modifiant ce fichier vous aller ajouter plein D'IA disposant du code de la fonction ia_2 donc garder ia_1 pour votre véritable IA**.<br/>
Pour coder, vous disposerez de la carte avec la position de tous les items et personnages. De plus, vous disposez actuellment de vos statistiques, mais à terme vous disposerez probablement des statistiques de toutes les IAs.<br/>

### Modifications temporaires

Pour coder vos IAs le code propose des choses qui ne seront pas dans le code final ou bien qui sont modifiés pour faciliter le codage. Par exemple: Ganon attaque toutes les 15 secondes, les rubis apparaissent toutes les 10 secondes. Un tableau des scores très mal fait juste histoire de voir les scores.<br/>

### Interdictions 

**Voici la liste des choses interdites lors de la réalisation de votre IA (cette liste peut évoluer). Si lors ce que vous rendez le code de votre IA une de ces interdictions est transgressée, votre équipe sera automatiquement éliminée!**<br/>
- Utiliser la SDL dans votre IA.<br/>
- Coder totalement ou partiellement votre IA en assembleur.<br/>
- Avoir une partie du code qui fait planter le programme (ex: une boucle infini)<br/>

# Contact & Problèmes

En cas de problème vous pouvez créer des issues sur Github sur notre projet afin que les questions soit visibles par les utilisateurs et les adminisatateurs.
Sinon vous pouvez nous contacter par mail à l'adresse suivante: lubrisoft.corps@gmail.com<br/>
Il est également possible de nous contacter sur Facebook.<br/> <br/>
L'équipe:<br/>
Anis Hannachi<br/>
Thomas Sauwal<br/>
François-Xavier Hilaire<br/>
Mael Adler<br/>
Matthieu Eccher<br/>
