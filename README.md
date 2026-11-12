# Mini projet : Lecture de badges RFID depuis un µ-contrôleur





Q1,Avant de commencer, lister trois inconvénients possibles d’une pointeuse électromécanique ancienne par rapport à un système basé sur un microcontrôleur connecté au réseau (Pensez à la maintenance, à l’exploitation des données et à l’évolutivité).





Axe	Inconvénient de la Bodet Présence 80

Maintenance	Pièces mécaniques usées, pannes fréquentes (47 fois pour Berthier !), pièces détachées et compétences de réparation introuvables sur un matériel obsolète.

Exploitation des données	Pas de connexion réseau : les pointages ne sont pas centralisés, il faut les relever et les saisir à la main (risque d'erreurs). Pas de consultation ni d'export simple.

Évolutivité	Dépend de Windows 98 (non maintenu, failles de sécurité, incompatible avec les outils actuels). Impossible d'ajouter de nouvelles fonctions (badge sans contact, interface web, cloud).





Q2, Compléter les liens dans le diagramme use case (diagramme de cas d’utilisation) ci-dessous, en utilisant des liens vers les acteurs et des liens «include» ou «extend».





























Q3, Téléverser le programme et vérifier le clignotement. Ouvrir le moniteur série et noter l’identifiant de la carte. Que se passe-t-il si vous choisissez une autre vitesse que 115200 bauds dans le moniteur ? Justifier. 







































Après téléversement la carte clignote bien en bleu







Identifiant de la carte : ESP32 DEV Module







vitesse de 115200 bauds : adresse MAC lu a l’envers

























Q4 Expliquer les lignes suivantes dans ce programme :





pinMode(2, OUTPUT); : on dit à l'ESP32 que la broche 2 sert à envoyer un signal (sortie), ici vers la LED.



digitalWrite(2, HIGH); : on met la broche 2 à 3,3 V → la LED s'allume.



digitalWrite(2, LOW); : on met la broche 2 à 0 V → la LED s'éteint.



uint64\_t chipid; : on crée une variable appelée chipid pour stocker l'identifiant de la carte. Elle peut contenir un grand nombre (64 bits), car l'identifiant est trop gros pour une variable plus petite.









Signal	Nom complet	Rôle

SCK	Serial Clock	Horloge, générée par le Master. Elle cadence chaque bit transmis.

MOSI	Master Out Slave In	Données qui vont du Master vers le Slave.

MISO	Master In Slave Out	Données qui vont du Slave vers le Master.

SS (ou NSS)	Slave Select	Sélection du Slave, pilotée par le Master. Le Slave est actif quand SS est à l'état bas (le trait au-dessus de SS signifie « actif à 0 »).



























Le bus SPI est full-duplex. Il y a deux fils de données séparés : MOSI (Master vers Slave) et MISO (Slave vers Master). Les données passent donc dans les deux sens en même temps.

Broches sur le Master :

&#x20;   • Pour un Slave : 4 broches (SCK, MOSI, MISO, SS). 

&#x20;   • Pour deux Slaves : 5 broches. SCK, MOSI et MISO sont partagés (3 broches), et chaque Slave a son propre SS (2 broches).



Q7 À partir du module ou de la photo, identifier et décrire chaque broche du module (de gauche à droite) : NSS,

SCK, MOSI, MISO, IRQ, GND, RST, 3.3V. Présenter la réponse sous forme d’un tableau : nom, direction (entrée/sortie du point de vue du module RC522), rôle.





Broche	Nom complet	Direction	Rôle

NSS	Slave Select	Entrée	Le microcontrôleur la met à l'état bas pour sélectionner le RC522.

SCK	Serial Clock	Entrée	Horloge SPI envoyée par le microcontrôleur.

MOSI	Master Out Slave In	Entrée	Données envoyées par le microcontrôleur vers le RC522.

MISO	Master In Slave Out	Sortie	Données envoyées par le RC522 vers le microcontrôleur.

IRQ	Interrupt Request	Sortie	Signale une interruption (ex : badge détecté). Souvent non utilisée.

GND	Ground	Alimentation	Masse (0 V).

RST	Reset	Entrée	Réinitialise le module (actif à l'état bas).

3.3V	Alimentation	Alimentation	Alimentation du module en 3,3 V. Ne jamais mettre 5 V.



Q8 Repérer sur la photo l’antenne (boucle de cuivre) et le circuit intégré. Expliquer la fonction de l’antenne.

Donner une évaluation de la portée typique de lecture du module





Repérage sur la photo :

&#x20;   • L'antenne est la grande boucle de cuivre en spirale, au centre de la carte rouge. 

&#x20;   • Le circuit intégré est la petite puce carrée noire (le MFRC522), à droite de la carte, près des broches. 

Fonction de l'antenne : elle émet un champ magnétique à 13,56 MHz. Ce champ sert à deux choses :

&#x20;   • alimenter le badge : le badge n'a pas de pile, il récupère l'énergie du champ par induction ; 

&#x20;   • échanger les données : le lecteur et le badge communiquent par variation de ce champ. 

Portée typique : environ 3 à 5 cm (jusqu'à 6 cm au maximum). Le badge doit donc être presque collé au lecteur.







Q9 À partir du schéma ci-dessus, compléter le tableau de câblage avec les bornes à connecter sur l’ESP32

sachant que le bus à utiliser est appelé ici “VSPI”.



RC522	ESP32

NSS	GPIO 5

SCK	GPIO 18

MOSI	GPIO 23

MISO	GPIO 19

IRQ	non connecté

GND	GND

RST	GPIO 4

3.3V	3.3V





Q10 Réaliser le câblage et faites-le valider par l’enseignant avant de mettre sous tension,



travail validé





Q11 Ouvrir le programme d’exemple. Compiler et téléverser le programme. Passer un badge NFC devant le lecteur et vérifier le fonctionnement. Faire un copié-collé du résultat obtenu depuis le moniteur série



KR0fr!))gCBFirmware Version: 0x92 = v2.0



Ce code lit le NUID des badges MIFARE Classic.



Cle utilisee :  FF FF FF FF FF FF



Type de PICC : MIFARE 1KB



Un nouveau badge a ete detecte.



Le NUID du badge est :



En hexa :  09 FE 08 A3



En dec  :  9 254 8 163



Type de PICC : MIFARE 1KB



Badge deja lu.



Type de PICC : MIFARE 1KB



Un nouveau badge a ete detecte.



Le NUID du badge est :



En hexa :  87 1B 8E 62



En dec  :  135 27 142 98



Q12 Relevez le NUID de vos différents badges (carte et porte-clés). Déterminer combien d’octets il comporte. Expliquer ce que signifie le « N » de NUID.





Badge	NUID (hexa)	Octets

Badge 1	09 FE 08 A3	4

Badge 2	87 1B 8E 62	4





Q13 Modifiez le programme pour qu’il allume la LED builtin (GPIO 2) pendant 500 ms à chaque lecture réussie.





Ajouts de :

  digitalWrite(2, HIGH);

delay(500);

digitalWrite(2, LOW);





Q14. Donner la signification de IRQ. Expliquer la différence entre polling (scrutation) et interruption.



IRQ = Interrupt ReQuest = demande d'interruption.

C'est un signal que le RC522 envoie à l'ESP32 pour dire que sur le RC522, cette broche passe à 0 V quand un badge est détecté.



Le polling (scrutation) :

Le programme interroge le lecteur en boucle, sans arrêt, pour savoir s'il y a un badge à lire.



L'interruption :

Le lecteur prévient le microcontrôleur uniquement quand un événement se produit. C'est le périphérique qui prend l'initiative. Le microcontrôleur peut donc vaquer à d'autres occupations (ou dormir) en attendant d'être sollicité.





Q15 Donner deux avantages qu’apporterait l’utilisation de l’IRQ dans le projet de la COGIP (pensez à la consommation d’énergie, aux autres tâches de l’ESP32, aux fonctions de deep sleep / light sleep, …).



1\. Économie d'énergie

En polling, l'ESP32 interroge le RC522 en permanence et ne peut pas se mettre en veille. Avec l'IRQ, il peut passer en light sleep ou deep sleep et ne se réveiller qu'à la détection d'un badge, ce qui réduit fortement la consommation.

2\. Libération du processeur

L'ESP32 peut vaquer à d'autres tâches (Wi-Fi, requêtes HTTP, affichage) pendant qu'il attend un badge, au lieu de bloquer sa boucle sur la scrutation du lecteur.

Q16 Expliquer le fonctionnement du programme pour utiliser une interruption sur l’ESP32 (avec la fonction attachInterrupt(), front descendant, résistance de pull-up). Donner les lignes de code correspondantes (sans nécessairement les tester).



On relie la broche IRQ du RC522 à une GPIO de l'ESP32 (ex. GPIO 27). On la configure en entrée avec pull-up (INPUT\_PULLUP), car IRQ est actif à l'état bas. On utilise attachInterrupt() sur front descendant (FALLING) pour déclencher une fonction d'interruption (ISR) qui lève simplement un drapeau. Le traitement lourd se fait dans loop().







Q17 Expliquer le rôle du volume cogip-data. Que se passerait-il sans lui lorsqu’on supprime le

conteneur ?



Un volume Docker sert à conserver les données en dehors du conteneur. Ici, le volume cogip-data est monté sur le dossier /var/lib/postgresql/data du conteneur cogip-db : c'est là que PostgreSQL stocke sa base de données.

Rôle : les données (utilisateurs, badges, zones, droits, logs) survivent à l'arrêt, à la suppression ou à la recréation du conteneur.

Sans le volume : les données seraient écrites à l'intérieur du conteneur. Dès qu'on supprime le conteneur (docker rm), tout est perdu : la base repartirait vide au prochain démarrage.



Q18 Le mot de passe est ici écrit « en dur » dans le fichier. Expliquer pourquoi c’est une mauvaise pratique. Proposer une alternative. NB: pour ce TP nous conservons le mot de passe donné ici.





Le mot de passe est visible dans le fichier docker-compose.yml, donc dans le dépôt Git.

&#x20;     Il reste dans l'historique Git même si on le supprime plus tard.

&#x20;     Toute personne ayant accès au dépôt (ou à une copie) connaît le mot de passe.

&#x20;     Si le dépôt est public ou fuité, la base est compromise.

Alternative :

Utiliser des variables d'environnement stockées dans un fichier .env non versionné (ajouté au .gitignore). Docker Compose lit automatiquement ce fichier :































Q19 Dessiner un MCD (ou le diagramme de classes) des entités users, badges, zones, access\_rights, access\_logs avec cardinalités. Justifiez le choix de la clé primaire du badge (le NUID est-il un bon candidat ? Pourquoi ?).







Q20 Expliquer le rôle de ce fichier (requirements.txt).





Le fichier requirements.txt liste toutes les dépendances Python nécessaires au projet, avec éventuellement leur version minimale ou exacte. 





Q21 Dans models.py, expliquer le rôle de UniqueConstraint("user\_id","zone\_id") et de unique=True, index=True sur le champ nuid.



UniqueConstraint("user\_id", "zone\_id")

Empêche d'avoir deux fois le même droit pour le même utilisateur sur la même zone. Pas de doublon possible.

unique=True sur nuid

Un même NUID ne peut pas être associé à deux badges différents. C'est une contrainte d'unicité.

index=True sur nuid

Crée un index sur la colonne. Comme on cherche souvent un badge par son NUID, l'index rend la recherche plus rapide.

Q22 Expliquer pourquoi on lance uvicorn avec --host 0.0.0.0 et non 127.0.0.1. Quel risque cela introduit-il, et comment le limiter ?





Avec 127.0.0.1, seul l'ordinateur local peut accéder au serveur. L'ESP32 ne pourrait pas le joindre. Avec 0.0.0.0, le serveur écoute sur toutes les interfaces, donc l'ESP32 et les autres machines du réseau peuvent y accéder.

Risque :

Le serveur est visible par tout le réseau. N'importe qui peut appeler l'API.

Comment limiter :

&#x20;   • Pare-feu (n'autoriser que certaines IP)

&#x20;   • Reverse proxy avec authentification

&#x20;   • Réseau isolé (VLAN)

&#x20;   • HTTPS + token





Q23 À l’aide de l’interface /docs (Swagger), créer : 2 utilisateurs, 1 zone (« Salle serveur »), associer à chacun un badge (avec les NUID relevés précédemment) et donner à l’un seulement le droit d’accéder

à la salle serveur. Noter les requêtes utilisées.





















Étape	Route	JSON	Note l’id renvoyé

1	POST /api/users	{ "nom": "Martin", "prenom": "Léa", "service": "RH" }	                  9

2	POST /api/zones	{ "nom": "Salle serveur" }	                  1

3	POST /api/badges	{ "nuid": "09FE08A3", "user\_id": 4 }	

4	POST /api/badges	{ "nuid": "871B8E62", "user\_id": <id de Léa> }	

5	POST /api/rights	{ "user\_id": 4, "zone\_id": <id de la zone> }	

6	POST /api/users	{ "nom": "Dupont", "prenom": "Marc", "service": "Informatique" } 	                                                                                              4





Q24 Vérifiez le contenu de la base directement avec psql en utilisant une commande qui est exécutée dans le container docker :





commande : docker exec -it cogip-db psql -U cogip -d pointeuse -c "SELECT u.nom, u.prenom, b.nuid, z.nom AS zone FROM access\_rights ar JOIN users u ON u.id = ar.user\_id JOIN badges b ON b.user\_id = u.id JOIN zones z ON z.id = ar.zone\_id;"





résultat :



















Q25 Modifier le programme de l’ESP32 pour se connecter au réseau WiFi en ajoutant les instructions données ci-dessous aux bons endroits dans le programme :



















Q25 :





Bloc ajouté	Emplacement dans le programme	Rôle

\#include <WiFi.h> et #include <HTTPClient.h>	En haut du fichier, avec les autres #include	Bibliothèques Wi-Fi et client HTTP

Constantes WIFI\_SSID, WIFI\_PASS, API\_URL, ZONE	Avant setup(), en variables globales	Paramètres réseau et adresse du serveur

WiFi.begin(...) et la boucle while	Dans setup(), après l’initialisation du lecteur	Connexion au Wi-Fi et affichage de l’IP de l’ESP32

Envoi HTTP POST du NUID	Dans loop(), après la lecture réussie du badge	Envoie {"nuid": ..., "zone": ...} au serveur

Fonction nuidToString()	Après loop(), avec une déclaration avant setup()	Convertit le NUID en chaîne hexadécimale en majuscules





Le programme se connecte d’abord au réseau Wi-Fi dans setup() et affiche l’adresse IP obtenue. Dans loop(), quand un badge est lu, le NUID est converti en chaîne hexadécimale en majuscules (nuidToString()), puis envoyé en JSON au serveur par une requête HTTP POST sur /api/scan, avec le nom de la zone. Le serveur répond avec l’utilisateur identifié et la décision d’accès, affichées sur le moniteur série.

















































Programme : complété (bibliothèques WiFi.h et HTTPClient.h, constantes réseau, connexion Wi-Fi, envoi du NUID en HTTP POST) et téléversé sur l’ESP32 (voir Q25).

Commande pour trouver l’IP du serveur : ipconfig (sous Linux : ip a). Elle donne l’IPv4 de la carte Ethernet du PC : 192.168.1.213, utilisée dans API\_URL.

Pourquoi une IP fixe ou une réservation DHCP : l’adresse du serveur est écrite en dur dans le programme de l’ESP32. Si elle change (redémarrage, bail DHCP expiré), l’ESP32 envoie ses requêtes dans le vide et il faut reflasher la carte. Une IP fixe ou une réservation DHCP (même adresse pour la même MAC) garde l’adresse stable.

Si ta requête n’a pas abouti, ajoute une ligne : « Test : HTTP -1 (connection refused). Le serveur écoute sur 0.0.0.0:8000 et le port est autorisé au pare-feu, mais le ping PC vers ESP32 est injoignable : le Wi-Fi et le réseau filaire ne communiquent pas. »

Q27 :







N°	Badge présenté	Zone	Résultat attendu	Résultat obtenu	OK / KO

1	Badge A (droit accordé)	Salle serveur	Autorisé	{"utilisateur":"Marc Dupont","autorise":true}	OK

2	Badge inconnu	Salle serveur	Refusé, utilisateur « Inconnu »	{"utilisateur":"Inconnu","autorise":false}	OK

3	Badge B (droit accordé)	Salle serveur	Autorisé	{"utilisateur":"Léa Martin","autorise":true}	OK

4	Badge B désactivé (actif = false)	Salle serveur	Refusé	{"utilisateur":"Inconnu","autorise":false}	OK

5	Badge A (droit accordé)	Salle serveur	Autorisé	{"utilisateur":"Marc Dupont","autorise":true}	OK















Commande pour désactiver badge Léa : docker exec -it cogip-db psql -U cogip -d pointeuse -c "UPDATE badges SET actif = false WHERE nuid = '871B8E62';"











Q28 :





















































le trafic est en HTTP, donc en clair. Toute personne qui peut écouter le réseau (Wi-Fi ouvert, poste branché sur le même switch, ARP spoofing) peut lire le NUID, le nom de l’employé, la zone et la décision d’accès. Elle peut aussi rejouer ou forger des requêtes POST /api/scan, puisqu’aucune authentification ne protège l’API. Le mot de passe Wi-Fi (WPA2) protège seulement la liaison radio, pas les données au-delà du point d’accès.







Q29 :



Le problème

&#x20;   • La page envoie une requête chaque seconde, qu’il y ait eu un passage ou non. La plupart du temps, la réponse est identique à la précédente. 

&#x20;   • Chaque requête charge le réseau, le serveur et la base (un SELECT à chaque fois), et ça se multiplie par le nombre de navigateurs ouverts. 

&#x20;   • L’affichage peut avoir jusqu’à 1 seconde de retard sur le passage réel. Si on réduit l’intervalle, la charge augmente encore.

La cause

HTTP fonctionne en mode requête/réponse : seul le client peut initier l’échange. Le serveur ne peut pas prévenir le navigateur qu’un badge vient d’être lu, donc le navigateur doit demander sans cesse « y a-t-il du nouveau ? ». C’est le même principe que le polling de la Q14 (l’ESP32 qui interroge le RC522 en boucle), mais côté web.



Solution : le serveur envoie l’information quand elle existe (mode « push »)



Technique	Principe

WebSocket	Connexion permanente et bidirectionnelle. Le serveur envoie un message à chaque passage. FastAPI le gère nativement (@app.websocket(...)).

Server-Sent Events (SSE)	Connexion HTTP ouverte, le serveur envoie des événements au navigateur (EventSource en JavaScript). Plus simple, car on n’a besoin que du sens serveur vers client.

Long polling	Le client demande, le serveur garde la requête ouverte jusqu’à l’arr





Q30 :





Aujourd’hui : si le serveur est indisponible, le POST échoue (HTTP -1) et le passage est perdu : il n’est enregistré nulle part, donc l’exigence 1.3 (journalisation) n’est plus respectée. Le salarié n’est pas informé non plus, car la LED s’allume à la lecture même sans réponse du serveur.

Évolution de l’architecture :

&#x20;   • L’ESP32 stocke les passages en local (mémoire flash ou carte SD) avec leur heure (NTP), puis les renvoie quand le serveur revient. 

&#x20;   • Il garde un cache des droits pour décider en mode dégradé. 

&#x20;   • Il signale l’erreur par une LED ou un buzzer distinct. 

&#x20;   • Côté serve





31 :



Informations échangées en clair (phase d’anticollision ISO 14443A) :

&#x20;   • ATQA (2 octets) : réponse du badge à l’appel du lecteur, indique la taille de l’UID. 

&#x20;   • UID / NUID (4 octets pour toi) + un octet de contrôle BCC (XOR des 4 octets). 

&#x20;   • SAK (1 octet) : indique le type de badge. C’est grâce à lui que ton programme a affiché MIFARE 1KB. 

Aucun secret, aucune clé, aucun chiffrement et aucune authentification n’interviennent à ce stade : n’importe quel lecteur à portée obtient ces informations.

Conclusion : le NUID est un identifiant public, pas un secret. Il identifie le badge, mais ne prouve pas que la personne ou le badge est authentique, car il peut être lu à l’insu du porteur puis copié ou émulé (voir Q32). Utilisé seul, il ne constitue donc pas une authentification fiable. Pour un accès sensible, il faut un second facteur (code PIN, biométrie) ou un badge à authentification cryptographique (par exemple MIFARE DESFire EV2/EV3 en AES, avec échange défi-réponse).



Q32 :



Le NUID de mes badges est-il secret ? Non. Il est transmis en clair à tout lecteur à portée lors de la phase d’anticollision (voir Q31). Le programme de la Q11 l’affiche en quelques secondes, avec un simple lecteur RC522 à 5 € : 09 FE 08 A3 et 87 1B 8E 62.

Peut-il être copié ? Oui. Sur un badge MIFARE Classic d’origine, l’UID est inscrit dans le bloc 0 (bloc constructeur), verrouillé en écriture à la fabrication, donc non modifiable. Mais il existe des cartes spéciales qui contournent cette protection.

Les cartes « magic cards » (Chinese backdoor). Ce sont des badges compatibles MIFARE Classic dont le bloc 0 est réinscriptible, donc dont l’UID est modifiable. Les premières générations (gen1a) répondent à des commandes non documentées (la « backdoor ») qui permettent d’écrire le bloc 0 sans authentification. D’autres générations (gen2 / CUID) acceptent une écriture normale. Elles se vendent quelques euros.

Pourquoi le clonage devient trivial :

&#x20;   1. L’attaquant lit le NUID du badge d’un salarié à quelques centimètres, à son insu. 

&#x20;   2. Il écrit ce NUID sur une magic card. 

&#x20;   3. Le système de la COGIP ne vérifie que le NUID : il ne peut pas distinguer le clone de l’original. Il n’y a aucun secret à connaître ni aucune clé à casser.





Q33 :



Attaque par rejeu (replay attack)

&#x20;   • Principe : l’attaquant enregistre un échange légitime entre le badge et le lecteur, ou entre le lecteur et le serveur, puis le renvoie tel quel plus tard pour se faire accepter. 

&#x20;   • Sur notre système : la requête POST /api/scan envoyée en HTTP contient {"nuid":"09FE08A3","zone":"Salle serveur"}, sans secret, sans horodatage et sans numéro de session. Quelqu’un qui capture cette trame (Wireshark, Q28) ou qui connaît un NUID peut renvoyer exactement la même requête, et le serveur la traitera comme un vrai passage. Côté badge, un appareil qui rejoue le NUID d’un badge (émulateur NFC, magic card) fait la même chose. 

&#x20;   • Contre-mesures : chiffrement (HTTPS), jeton à usage unique (nonce), horodatage signé, authentification défi-réponse (le lecteur envoie un nombre aléatoire que le badge doit signer avec sa clé, ce qui rend l’enregistrement inutilisable). 

Attaque par relais (relay attack)

&#x20;   • Principe : l’attaquant ne copie rien et ne casse rien : il fait transiter en temps réel la communication entre le vrai badge et le vrai lecteur, par deux appareils complices. 

&#x20;   • Déroulement : 

&#x20;       1. Un complice approche un appareil (le « fantôme ») du badge de la victime, par exemple dans une file d’attente ou un transport. 

&#x20;       2. Il relaie la communication par radio ou Internet à un second appareil (l’« émulateur »), placé devant le lecteur de la porte. 

&#x20;       3. Le lecteur dialogue avec le vrai badge, à distance, et ouvre. 

&#x20;   • Pourquoi c’est efficace : même avec un badge cryptographique solide (DESFire, AES), le protocole est parfaitement respecté, l’attaquant n’a besoin ni de clé ni de déchiffrement. Les échanges sont simplement transportés sur une plus longue distance. 

&#x20;   • Contre-mesures : mesure du temps de réponse (distance bounding), qui détecte un trajet trop long ; second facteur (code PIN ou biométrie) ; étui blindant (cage de Faraday) pour le badge ; confirmation d’un geste volontaire (par exemple un bouton).





Q34 :



Ce prototype est utilisable pour le pointage des horaires, mais pas pour protéger des accès sensibles comme la salle des coffres.

Pourquoi c’est acceptable pour le pointage : il enregistre chaque passage, il est sans contact, peu coûteux et facile à faire évoluer. Une fraude (un collègue qui badge pour un autre) a des conséquences limitées et peut être détectée.

Pourquoi ce n’est pas acceptable pour un accès sensible : le badge ne transmet qu’un numéro, lisible par n’importe qui à quelques centimètres, et copiable sur une carte à 2 € en quelques secondes. Le système ne peut pas distinguer un faux badge du vrai. De plus, les échanges sont en clair sur le réseau et le service s’arrête si le serveur tombe.

Ma recommandation : garder ce prototype pour les horaires, et pour la salle des coffres choisir des badges à chiffrement moderne (type DESFire), un code PIN en plus du badge, des échanges chiffrés (HTTPS) et un serveur de secours.







Q35 :









Exigence	Verdict	Justification

1.1 Lecture RFID ISO 14443A, 13,56 MHz	 Couverte	Le RC522 lit les badges MIFARE 1KB, sans contact (Q11).

1.1.1 Lecture < 300 ms	 Non vérifiée	Aucune mesure faite. Pour la valider, mesure avec millis() entre PICC\_IsNewCardPresent() et la fin de PICC\_ReadCardSerial(). Le delay(500) de la LED est ajouté après la lecture, il ne compte pas.

1.2 Identification via un service central	 Couverte	POST /api/scan associe le NUID à un salarié dans PostgreSQL. Testé via Swagger et le tableau de recette (Q27).

1.3 Chaque passage journalisé	 Partielle	La table access\_logs enregistre chaque scan reçu, y compris les refus. Mais si le serveur est injoignable, le passage est perdu (Q30).

1.3.1 Données enregistrées	 Partielle	La table contient le NUID, la date et l’heure. Elle stocke le nom de l’utilisateur en texte, pas son identifiant (user\_id) comme demandé.

1.4 Résultat sur une page web du réseau local	 Couverte	index.html affiche le dernier passage via /api/last, et le serveur écoute sur 0.0.0.0. Limite : affichage par polling toutes les secondes (Q29).

1.5 Contrôle des droits par le service central	 Couverte	scan vérifie la table access\_rights pour l’utilisateur et la zone.

1.5.1 Édition des droits par le RH (créer, modifier, désactiver)	 Partielle	L’API permet seulement de créer (POST). Il n’y a pas de route pour modifier ou retirer un droit. J’ai désactivé un badge directement en SQL, et aucune authentification ne distingue un RH d’un autre utilisateur.

1 Pointage sans contact, connecté au réseau local, via navigateur	 Partielle	Chaque élément marche séparément. En revanche, la chaîne complète ESP32 → serveur n’a pas abouti chez moi (HTTP -1, réseaux Wi-Fi et filaire séparés). Si tu obtiens un HTTP 200 depuis l’ESP32, passe ce verdict en .

Matériel Lecteur RC522 unique, base PostgreSQL	 Couvertes	RC522 câblé en SPI, PostgreSQL dans Docker.



