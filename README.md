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
Voici le cours Openclassroom qui explique comment installer la SDL: <https://openclassrooms.com/courses/apprenez-a-programmer-en-c/installation-de-la-sdl#/id/r-17116><br/>
Voici egalement le lien du cours Openclassroom qui explique comment installer la SDL image et il suffira de suivre le même procédé pour les deux dernières bibliotèques:<https://openclassrooms.com/courses/apprenez-a-programmer-en-c/afficher-des-images#/id/r-17795><br/>
**Si vous rencontrez trop de problèmes lors de l'installation je pourrai également réaliser une vidéo complète qui explique comment tout installer**
Votez ici si vous en avez besoin : <https://www.strawpoll.me/15270315><br/>

# Configuration

En ce qui concerne la configuration vous aurez besoin d'installer tout ce qui est demandé ci-dessus. Une fois cela installé vous allez devoir télécharger **la dernière
version des dossiers** "arène_code" ainsi que du dossier "Images". Une fois les dossiers téléchargé, vous allez inclure toutes les images du dossier "Images" dans
le dossier "arène_code"**(Il faut bien inclure les images et non tout le dossier)**. Maintenant que vous avez cela, vous êtes normalement en mesure de lancer le programme.
**Pour démarrer le jeu il faut appuyer une fois sur la barre espace**<br/>

# Règles du jeu
**Les XX symbolisent des nombres ou pourcentages pas encore établi, nous décideront des valeurs finales en fonction des premiers tests d'IA**
### Le 1vs1:
En début de partie, les deux IA se retrouveront face à face au centre de l'arène avec une épée et un bouclier chacune, ainsi que XX rubis chacun. Les déplacements dans les 4 directions sont possibles dès le début de la partie. Au bout de 5 secondes des rubis apparaîtront partout dans l'arène et les IAs ramasseront automatiquement les rubis en passant simplement dessus. Au bout de 10s les IAs pourront s'assener des coups d'épée entre elles. Lorqu'une IA reçoit un coup d'épée elle perd XX rubis et l'IA qui a asséné le coup reçoit XX pourcents des rubis perdus. L'IA peut égalment parer les coups d'épée à l'aide de son bouclier. Ensuite toutes les XX secondes des rubis ainsi qu'un pot vont apparaître au centre de l'arène. Le pot peut être cassé d'un simple coup d'épée, le pot contient soit des rubis ramassables soit une bombe. Si vous ramassez la bombe, elle est stocké dans un slot de votre inventaire, vous pourrez alors la poser quand vous le souhaitez. Après que la bombe soit posé, elle explosera au bout de X secondes et les IAs se trouvant dans un rayon de X perdont autant de rubis qu'un coup d'épée et l'IA ayant posé la bombe recupére XX pourcents de rubis. Une fois XXX secondes écoulés Ganon (une IA) va apparaître au centre de l'arène, il poursuivra l'IA qui a le plus de rubis et lui donnera un coup d'épée qui enlevera XX rubis. Même si l'IA n'a plus le plus de rubis et qu'il a été ciblé par Ganon, ce-dernier lui assenera tout de même le coup d'épée (comme la carapace bleu dans mario kart). Une fois le coup asséné, Ganon retourne au centre de la carte et pourra se redéplacer et redonner son coup au bout de XX secondes. Si le nombre de rubis d'une IA tombe à 0 ou moins il meurt et le survivant se retrouve vainqueur.**/!\ Ganon ne peut pas tuer les IAs, leur nombre de rubis tombera seulement à 1**. A la fin du temps imparti, l'IA qui a le plus de rubis gagne. En cas d'égalité l'IA qui a eu le plus de rubis en 1er gagne.
### A 26 IAs:
Les règles restent fondamentalement les mêmes mise à part celles-ci:<br/>
- les IAs vont debuter en cercle au centre de l'arène.<br/>
- Les rubis et pots vont apparaître dans toute l'arène.<br/>
- Les dégats de Ganon et les temps d'apparitions seront différents du 1vs1.<br/>

# Développement d'IA

En terme d'informations, les IAs connaitront les positions de tous les items et IAs.<br/>
Les actions possibles citées ci-dessus sont: se déplacer, frapper, parer, utiliser un item.<br/>
Vous aurez d'avantage d'informations très prochainement.<br/>
Vous pouvez désormais déplacer l'IA à l'aide de la fonction **test_ia** contenu dans le header. Vous disposez d'un tableau contenant **uniquement** la position des rubis.<br/>
Nous travaillons sur l'ajout de la position de Ganon ainsi que de la position de l'ia dans le tableau.<br/>

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
