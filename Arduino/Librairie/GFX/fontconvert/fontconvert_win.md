### Petit guide sur l’utilisation de fontconvert.c pour créer vos propres polices avec MinGW.

#### ÉTAPE 1: INSTALLER MinGW

Installez MinGW (Minimalist GNU for Windows) à partir de [MinGW.org] (http://www.mingw.org/).
Veuillez lire attentivement les instructions figurant sur la [Page de démarrage] (http://www.mingw.org/wiki/Getting_Started).
Je suggère d'installer avec le "programme d'installation d'interface utilisateur graphique".
Pour terminer votre installation initiale, vous devez installer plus avant certains "packages".
Pour ce faire, vous ne devez installer que les packages "Basic Setup".
Pour faire ça:

1. Ouvrez le gestionnaire d'installation MinGW
2. Dans le panneau de gauche, cliquez sur "Configuration de base".
3. Sur le panneau de droite, choisissez "mingw32-base", "mingw-gcc-g ++", "mingw-gcc-objc" et "msys-base".
et cliquez sur "Marquer pour l'installation"
4. Dans le menu, cliquez sur "Installation" puis sur "Appliquer les modifications". Dans la fenêtre contextuelle, sélectionnez "Appliquer".


#### ÉTAPE 2: INSTALLER la bibliothèque Freetype

Pour en savoir plus sur le projet freetype, visitez [freetype.org] (https://www.freetype.org/).
Pour télécharger la dernière version de freetype, rendez-vous sur [page de téléchargement] (http://download.savannah.gnu.org/releases/freetype/)
et choisissez le fichier "freetype-2.7.tar.gz" (ou une version plus récente, si disponible).
Pour éviter de longues commandes cd plus tard dans l'invite de commande, je vous suggère de décompresser le fichier dans le répertoire C: \.
(J'ai également renommé le dossier "ft27")
Avant de construire la bibliothèque, il est bon de lire ces articles:
* [Utilisation de MSYS avec MinGW] (http://www.mingw.org/wiki/MSYS)
* [Installation et utilisation de bibliothèques supplémentaires avec MinGW] (http://www.mingw.org/wiki/LibraryPathHOWTO)
* [Inclure le chemin] (http://www.mingw.org/wiki/IncludePathHOWTO)

Le dossier décompressé contient un autre dossier appelé "docs". Ouvrez-le et lisez le fichier INSTALL.UNIX (en utilisant le bloc-notes).
Faites attention au paragraphe 3 (Construire et installer la bibliothèque). Commençons donc l'installation.
Pour donner les commandes appropriées, nous utiliserons l'invite de commande MSYS (pas cmd.exe de Windows) qui ressemble à UNIX.
Suivez le chemin C: \ MinGW \ msys \ 1.0 et double-cliquez sur "msys.bat". L'environnement d'invite de commande apparaît.
Entrez le répertoire "ft27" en utilisant les commandes cd:
```
cd /c
cd ft27
```

puis tapez une à une les commandes:
```
./configure --prefix=/mingw
make
make install
```
Une fois que vous avez terminé, allez dans "C: \ MinGW \ include" et il devrait y avoir un nouveau dossier nommé "freetype2".
Cela, espérons-le, signifie que vous avez correctement installé la bibliothèque!

#### ÉTAPE 3: Construisez fontconvert.c

Avant de continuer, je vous suggère de copier le dossier Adafruit_GFX_library dans le répertoire C: \.
Ensuite, dans le dossier "fontconvert", ouvrez le "fichier makefile" avec un éditeur (j'ai utilisé notepad ++).
Modifiez les commandes pour que le programme ressemble à ceci:
```
all: fontconvert

CC     = gcc
CFLAGS = -Wall -I c:/mingw/include/freetype2
LIBS   = -lfreetype

fontconvert: fontconvert.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm -f fontconvert
```
Retournez dans l'invite de commande et avec une commande cd, entrez le répertoire fontconvert.
```
cd /c/adafruit_gfx_library\fontconvert
```
Donner la commande:
```
make
```
Cette commande créera éventuellement un fichier "fontconvert.exe" dans le répertoire fontconvert.

#### ETAPE 4: Créez vos propres fichiers d'en-tête de police

Maintenant que vous avez un fichier exécutable, vous pouvez l’utiliser pour créer vos propres polices à utiliser avec Adafruit GFX lib.
Donc, si nous supposons que vous avez déjà un fichier .ttf avec vos polices préférées, passez à l’invite de commande et tapez:
```
./fontconvert yourfonts.ttf 9 > yourfonts9pt7b.h
```
Vous pouvez lire plus de détails sur: [learn.adafruit] (https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts).

Taraaaaaammm !! vous venez de créer votre nouveau fichier d'en-tête de police. Mettez-le dans le dossier "Polices", prenez une tasse de café
et commencez à jouer avec votre Arduino (ou autre chose ....) + projet de module d'affichage.
