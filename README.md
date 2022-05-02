# Takt Ransomware 🏴‍☠️

![](https://cdn.discordapp.com/attachments/497025479233241099/969994140983115856/unknown.png)

---

# Documentation 👨🏼‍🏫

**Sommaire :**

[I. Prérequis](https://github.com/TomF0x/Takt/blob/master/Documentation/Pr%C3%A9requis.md)

[II. Installation](https://github.com/TomF0x/Takt/blob/master/Documentation/Installation.md)

[III. Utilisation](https://github.com/TomF0x/Takt/blob/master/Documentation/Utilisation.md)

[IV. Analyse](https://github.com/TomF0x/Takt/blob/master/Documentation/Analyse.md)

**Explication 📜 :**

Takt Ransomware est comme son nom l'indique un rançonlogiciel marchant sur les distributions **GNU/Linux** ainsi que sur **Windows**, il chiffre l'entièreté des informations personnelles de la victime avec du **AES-256**, laissant ainsi le système d’exploitation intacte, il est donc qualifié de Ransomware Crypto (Voir ci-dessus).

**AES-256** : Le chiffrement AES-256 est une méthode de chiffrement symétrique. Cela veut dire que la clé de chiffrement est la même que la clé de déchiffrement à la différence d’un chiffrement asymétrique. La clé fait comme son nom l’indique **256 bits**.

On a décidé d’utiliser les langages de programmation suivant :

- Python (VPS)
- Go Lang (GNU/Linux)
- C++ (Windows)

On utilise aussi un **VPS (Serveur dédié virtuel)** par lequel on fait transiter par socket les informations de la victime ainsi que la clé permettant le déchiffrement des données personnelles.
Lorsqu’une personne est infectée, on a décidé d’envoyer une notification par **webhook discord**, nous permettant de suivre qui a été infecté et à quel moment, avec en plus de son **IP**, son **Hostname** et enfin évidemment la **clé** permettant le déchiffrement des données.

---

**WinSAT exploit 📝 :**

WinSAT va servir à bypass l’**UAC** avec du **DLL Hijacking** et qui va utiliser un dll (contiendra notre script) qui chiffrera et qui fera du **DLL Proxying**. Cet exploit se lance à l’aide d’un script **powershell**.

Le DLL Hijacking c’est tout simplement faire qu’une **application légitime** (aux yeux de Windows) va charger une **DLL**.

C'est un script powershell (un **.ps1**) qui va s’occuper de l’exploit, le script va créer un faux répertoire "**C:\Windows\System32**” qu’on va appeler “**C:\Windows \System32**”, et à l’intérieur on va copier notre application légitime, donc **WinSAT**. Ensuite on va télécharger notre DLL à l’intérieur de ce faux répertoire, puis WinSAT va le lancer. Le DLL s’occupera alors de tout.

**Exploit :** https://github.com/b4keSn4ke/Invoke-WinSATBypass


