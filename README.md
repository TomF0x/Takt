# Takt Ransomware

---

**Présentation du projet :**

Takt Rannsomware est comme son nom l'indique un ransomware marchant sur Linux et Windows, il crypte l'entiéreté des informations personelles de la victime avec du AES 256. Le ransomware se spread aussi par le réseau afin d'avoir toujours plus de victime.

**Les techno :**

- Language : Golang (ransomware), Python (serveur side pour recevoir la clé, les informations sur la victime par socket)
- VirtualBox/VmWare (pour virtualiser les victimes)

**Les étapes :**

- Finaliser la version linux de Takt ( Gérer les quelques détections, préparer la demande de paiement) 
- Commencer la version windows de Takt (L'opti pour windows qui est bien plus lent)
- Régler les problèmes de détection nombreuses de windows
- préparer la demande de paiement
- Commencer à s'occuper du spread par réseau
- Sortir la version finale

**Requirements :**

- Un vps pour les info victime

**Difficulté technique :**

Actuellement aucune.
