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
	./hamming "1001010010"
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
Chaque bit de parité, aux emplacements 1, 2, 4, 8, 16, 32 ... calculent la parité de la manière suivante:<br \>
Soit x la position du bit de parité, on calcule la somme de x bits tout les 2*x bits<b \>
Exemples :<br \>
Pour le bit de parité 1 :  `?_<font color='red'>1</font>_<font color='red'>0</font>0<font color='red'>1</font>_<font color='red'>0</font>1<font color='red'>0</font>0<font color='red'>1</font>0`
#### correction d'un mot reçu

#### suppression des bits de parité