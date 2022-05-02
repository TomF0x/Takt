**Comment installer tout ça 🛠 :**

**GNU/Linux version 🐧 :**

1. Cloner le repo

```bash 
git clone https://github.com/TomF0x/Takt.git
```

2. build le binaire ou le lancer

```bash
cd Takt/client/Linux/main
go run main.go
```

ou 

```bash
go build main.go
./main
```

**Windows Version :**

1. Build la lib CryptoPP

Pour build la lib CryptoPP, suivre ce tuto : https://www.ired.team/miscellaneous-reversing-forensics/aes-encryption-example-using-cryptopp-.lib-in-visual-studio-c++

2. Build le dll toujours sur visual studio

3. Changer l'ip dans le script p1 dans : Takt/server

4. Renommer le dll en fonction de si vous voulez chiffrer ou déchiffrer

---

**➔ Suite :** [Utilisation](https://github.com/TomF0x/Takt/blob/master/Documentation/Utilisation.md)

**➔ Informations :** [README](https://github.com/TomF0x/Takt/blob/master/README.md)
