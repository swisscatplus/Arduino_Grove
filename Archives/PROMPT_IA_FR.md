# Demander à une IA d'écrire votre code

Pas le temps de coder ? Une IA (ChatGPT, version gratuite) peut écrire la logique à votre
place. Suivez les étapes ci-dessous.

**Astuce** : demandez toujours le **fichier complet**, jamais un extrait. Un seul copier-coller
suffit alors pour tout remplacer, sans avoir à deviner où coller quoi.

## Étapes

1. Dans Arduino IDE, ouvrez `Arduino_Grove.ino`, cliquez dedans, **Ctrl+A** puis **Ctrl+C**.
2. Allez sur [chatgpt.com](https://chatgpt.com) (la version gratuite suffit).
3. Copiez le **Message n°1** ci-dessous, collez-le dans ChatGPT. Remplacez la ligne
   `[COLLE ICI TON FICHIER Arduino_Grove.ino]` par le fichier copié à l'étape 1 (Ctrl+V
   par-dessus). Envoyez.
4. Décrivez votre idée en une phrase — voir l'exemple **Message n°2**.
5. L'IA répond avec le **fichier complet**. Copiez-le, retournez dans Arduino IDE, **Ctrl+A**
   puis **Ctrl+V** dans `Arduino_Grove.ino` pour tout remplacer.
6. Téléversez, testez. Si ça ne marche pas comme prévu, dites-le à l'IA dans la même
   conversation ("ça ne s'allume pas", "trop rapide"…) et redemandez le fichier complet.

## Message n°1 — à copier-coller en premier

```
Voici mon fichier Arduino (Arduino_Grove.ino) pour un Hackathon, sur une carte Arduino Uno
avec un kit de capteurs Grove Beginner Kit. Tous les capteurs sont déjà branchés et déjà
initialisés par initGroveKit(), que tu ne dois PAS modifier.

Voici le fichier tel qu'il est actuellement :

--- DEBUT DU FICHIER ---
[COLLE ICI TON FICHIER Arduino_Grove.ino]
--- FIN DU FICHIER ---

Utilise UNIQUEMENT les fonctions suivantes pour écrire ma logique. N'invente pas d'autres
fonctions, n'ajoute pas de ligne #include, ne modifie pas setup(), et n'utilise pas pinMode(),
digitalWrite() ou analogRead() directement :

- setLED(bool on) : allume/éteint la LED
- buzz(frequence, duree_ms) : joue un son sur le buzzer (ne bloque pas le programme)
- isButtonPressed() -> bool : true tant que le bouton est appuyé
- readPotentiometer() -> int (0 à 1023)
- readLight() -> int (0 à 1023)
- readSound() -> int (0 à 1023)
- readTemperature() -> float, en degres Celsius
- readHumidity() -> float, en pourcentage
- readPressure() -> float, en hPa
- readAcceleration(float &x, float &y, float &z) : remplit x, y, z avec l'acceleration (en g)
- displayText(ligne1, ligne2 = "", ligne3 = "") : affiche jusqu'a 3 lignes sur l'ecran OLED
- displayClear() : efface l'ecran
- printAllSensors() : affiche toutes les mesures dans le Moniteur Serie (pour tester)

Regles :
1. Ne change QUE le contenu de loop(). Si tu as besoin de variables globales ou de petites
   fonctions, ajoute-les juste avant "void setup()". Ne touche a rien d'autre (pas de nouveau
   #include, pas de changement dans setup() ou dans les commentaires du haut).
2. Reponds-moi TOUJOURS avec le fichier ENTIER, du tout debut jusqu'a la toute fin, dans un
   seul bloc de code — jamais juste un morceau — pour que je puisse tout selectionner et coller
   directement dans Arduino par-dessus mon fichier actuel.
3. Evite les delay() longs qui bloquent le programme, sauf si je te le demande precisement.
4. Explique en 1 a 2 phrases ce que fait le code, AVANT le bloc de code (pas dans le bloc), pour
   que je puisse copier le bloc sans rien devoir enlever.

Attends ma demande avant d'ecrire du code. Voici ma premiere demande :
```

## Message n°2 — exemple de demande

```
Quand j'appuie sur le bouton, fais clignoter la LED 3 fois, puis laisse-la éteinte. Joue aussi
un petit bip à chaque clignotement.
```

## Si l'IA ne respecte pas les règles

Répondez simplement :

```
Redonne-moi le fichier .ino COMPLET, du début à la fin, pas juste un morceau. Reste uniquement
avec les fonctions que je t'ai données au début, et ne touche pas à setup().
```

## Pour aller plus loin

Liste complète des fonctions : [`README.md`](README.md).
