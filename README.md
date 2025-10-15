# 🧾 Suivi des Candidatures — Application Qt (C++)

## 📖 Description

**Suivi des Candidatures** est une application de bureau développée en **C++ avec Qt**.  
Elle permet de suivre facilement ses candidatures à des offres d’emploi ou d’alternance, via une interface claire et moderne.  

L’utilisateur peut ajouter de nouvelles candidatures, les consulter dans un tableau, puis sauvegarder ou recharger ses données depuis un fichier CSV compatible Excel.

---

## ⚙️ Fonctionnalités principales

✅ **Affichage clair et lisible** dans un tableau (`QTableWidget`)  
➕ **Ajout rapide** via un formulaire (QMessageBox)  
💾 **Sauvegarde au format CSV** (lisible dans Excel / LibreOffice)  
📂 **Chargement des données** depuis un fichier CSV  
🎨 **Interface stylée et moderne** grâce aux feuilles de style Qt (QSS)  
🔒 **Cellules non éditables** pour éviter les erreurs de saisie  

---

## 🖥️ Interface utilisateur

### Widgets principaux

| Widget | Nom Qt | Rôle |
|:--------|:--------|:-----|
| `QTableWidget` | `TableauCandid` | Tableau principal des candidatures |
| `QPushButton` | `QPB_AddEnt` | Ajouter une nouvelle candidature |
| `QPushButton` | `QPB_Save` | Sauvegarder les données |
| `QPushButton` | `QPB_Load` | Charger les données |
| `QGroupBox` | `Statistiques` | Section des statistiques globales |
| `QLabel` | `Title` | Titre principal « Suivi des candidatures » |

---

## 🧱 Structure du projet

```

📁 SuiviCandidatures/
│
├── fenprincipsc.h                # Déclaration de la classe principale
├── fenprincipsc.cpp              # Logique de l'application
├── main.cpp                      # Point d'entrée du programme
├── fenprincipsc.ui               # Interface graphique (Qt Designer)
├── SuiviCandidature-v1.pro       # Fichier de compilation
├── SuiviCandidature-v1.pro.user  # Fichier de compilation d'utilisateur
└── README.md              # Ce fichier

````

---

## 💾 Format du fichier CSV

Les données sont sauvegardées au format **CSV** avec le séparateur `;`.  
Les champs contenant des retours à la ligne ou des espaces sont automatiquement encadrés de guillemets `"..."`.

### Exemple :
```csv
"Nom - Entreprise";"Infos Entreprise";"Poste";"Statut Réponse"
"OpenAI";"Paris, France";"Développeur C++";"Candidature envoyée"
````

---

## 🚀 Utilisation

*Après avoir télécharger le fichier `Application-v1.0.rar`, et le dézipper, veuillez suivrer ces étapes.*
1. Lancer l’application `SuiviCandidature-v1.exe`
2. Cliquer sur **« Ajouter une entreprise »** pour enregistrer une candidature
3. Cliquer sur **« Sauvegarder »** pour exporter les données au format CSV
4. Cliquer sur **« Charger »** pour importer les candidatures depuis un fichier CSV

---

## 🧰 Technologies utilisées

* 🧩 **C++ / Qt 6**
* 🗂️ `QTableWidget`, `QHeaderView`
* 💬 `QMessageBox`, `QFileDialog`
* 📝 `QTextStream`
* 🎨 Feuilles de style **QSS**

---

## 🎨 Style visuel (QSS)

```css
/* Exemple : bouton "Sauvegarder" */
QPushButton#QPB_Save {
    background-color: #27ae60;
    color: white;
    border-radius: 6px;
    padding: 8px 16px;
    font-weight: bold;
}

QPushButton#QPB_Save:hover {
    background-color: #1e8449;
}
```

---

## 📄 Licence

Projet personnel réalisé à des fins d'organisation.
Libre de réutilisation et de modification à but **non commercial**.

---

## 👨‍💻 Auteur

**Martin Ligny**
💡 Passionné par le développement C++, Qt, Python et le design d’interfaces.

---
