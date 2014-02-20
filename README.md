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
Chaque bit de parité, aux emplacements 1, 2, 4, 8, 16, 32 ... calculent la parité de la manière suivante.<br />
Soit x la position du bit de parité, on calcule la somme de x bits tout les 2*x bits<br />
Exemple :<br />
Pour le bit de parité 1 :  <font color='red'>?</font>?<font color='red'>1</font>?<font color='red'>0</font>0<font color='red'>1</font>?<font color='red'>0</font>1<font color='red'>0</font>0<font color='red'>1</font>0 soit 1+0+1+0+0+1=3, 3 est impair, le bit de parité est mis à 1<br />
Pour le bit de parité 2 :  1<font color='red'>?1</font>?0<font color='red'>01</font>?0<font color='red'>10</font>01<font color='red'>0</font> soit 1+0+1+1+0+0=3, 3 est impair, le bit de parité est mis à 1<br />
Pour le bit de parité 4 :  111<font color='red'>?001</font>?010<font color='red'>010</font> soit 0+0+1+0+1+0=2, 2 est pair, le bit de parité est mis à 0<br />
Pour le bit de parité 8 :  1110001<font color='red'>?010010</font> soit 0+1+0+0+1+0=2, 2 est pair, le bit de parité est mis à 0<br />
résultat : <font color='red'>11</font>1<font color='red'>0</font>001<font color='red'>0</font>010010 (parité en rouge et données en noir)
#### correction d'un mot reçu
Pour la correction d'un mot on vérifie ses bits de parité, admettons que nous avons reçu 11100<font color='red'>1</font>10010010,<br />On recalcule les bits de parité, P1=0, P2=1, P4=1, P8=0, on remarque que les bits de parité 2 et 4 sont incorrects, on peux alors corriger le bit à l'emplacement 2+4 pour retrouver 11100<font color='red'>0</font>10010010.<br />
#### suppression des bits de parité
On supprime tous les bits aux emplacements puissances de 2 <font color='red'>11</font>1<font color='red'>0</font>001<font color='red'>0</font>010010 pour retrouver `1001010010`.