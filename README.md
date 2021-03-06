hamming
=======
Implémentation du code de hamming en C

compilation
=======
$ `cd hamming` # se déplacer dans le dossier du projet hamming <br />
$ `make` # compile le fichier selon les règles du Makefile

utilisation
=======
$ `./hamming "1001010010"` # lance l'exécution avec la chaine "1001010010" à coder

résultat
=======
	$ ./hamming "1001010010"
	[•] encoding   '1001010010' (len:10)
	[•] sent       '11100010010010' (len:14)
	[•] recieve    '11100110010010' (len:14)
	[?] corrupted parity bits : 2 4
	[?] fixed data bit at index 6
	[•] corrected  '11100010010010' (len:14)
	[•] decoding   '1001010010' (len:10)
	[•] message successfully decoded

fonctionnement
=======
#### ajout des bits de parité
On commence par prendre notre mot de départ, ici `1001010010` puis on lui ajoute un bit de parité à tous les emplacement puissances de 2 pour donner `__1_001_010010`, les '_' représentant les bits de parité.
#### calcul des bits de parité
Chaque bit de parité, aux emplacements 1, 2, 4, 8, 16, 32 ... calculent la parité de la manière suivante.<br />
Soit x la position du bit de parité, on calcule la somme de x bits tout les 2*x bits<br />
Exemple :<br />
Pour le bit de parité 1 :  <b>?</b>?<b>1</b>?<b>0</b>0<b>1</b>?<b>0</b>1<b>0</b>0<b>1</b>0 soit 1+0+1+0+0+1=3, 3 est impair, le bit de parité est mis à 1<br />
Pour le bit de parité 2 :  1<b>?1</b>?0<b>01</b>?0<b>10</b>01<b>0</b> soit 1+0+1+1+0+0=3, 3 est impair, le bit de parité est mis à 1<br />
Pour le bit de parité 4 :  111<b>?001</b>?010<b>010</b> soit 0+0+1+0+1+0=2, 2 est pair, le bit de parité est mis à 0<br />
Pour le bit de parité 8 :  1110001<b>?010010</b> soit 0+1+0+0+1+0=2, 2 est pair, le bit de parité est mis à 0<br />
résultat : <b>11</b>1<b>0</b>001<b>0</b>010010 (parité en gras et données en normal)
#### correction d'un mot reçu
Pour la correction d'un mot on vérifie ses bits de parité, admettons que nous avons reçu 11100<b>1</b>10010010,<br />On recalcule les bits de parité, P1=0, P2=1, P4=1, P8=0, on remarque que les bits de parité 2 et 4 sont incorrects, on peux alors corriger le bit à l'emplacement 2+4 pour retrouver 11100<b>0</b>10010010.<br />
#### suppression des bits de parité
On supprime tous les bits aux emplacements puissances de 2, <b>11</b>1<b>0</b>001<b>0</b>010010 pour retrouver `1001010010`.