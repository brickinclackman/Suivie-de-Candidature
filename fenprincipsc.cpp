#include "fenprincipsc.h"
#include "ui_fenprincipsc.h"

FenPrincipSC::FenPrincipSC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FenPrincipSC)
{
    ui->setupUi(this);

    ui->TableauCandid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableauCandid->setSelectionMode(QAbstractItemView::NoSelection);
    ui->TableauCandid->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->TableauCandid->setColumnCount(10);
    ui->TableauCandid->setHorizontalHeaderLabels(QStringList() << "Nom\nEntreprise" << "Infos\nEntreprise" << "Poste" << "Lien\nCandidature" << "Téléphone" << "E-Mail" << "Adresse\nPostale" << "Date\nCandidature" << "Date\nRéponse" << "Statut\nRéponse");

    header = ui->TableauCandid->horizontalHeader();
    for (int i = 0; i < ui->TableauCandid->columnCount(); i++) {
        label = new QLabel(ui->TableauCandid->horizontalHeaderItem(i)->text());
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label->setStyleSheet("font-weight: bold; color: #2c3e50; background-color: #f8f9fa; padding: 4px;");
        ui->TableauCandid->setHorizontalHeaderItem(i, new QTableWidgetItem()); // on vide l'ancien texte
        header->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->TableauCandid->setCellWidget(-1, i, label); // hack, on le fait autrement :
        header->setSectionResizeMode(i, QHeaderView::Interactive);
        header->setMinimumSectionSize(60);
    }

    ui->TableauCandid->horizontalHeader()->setDefaultSectionSize(100);
    ui->TableauCandid->horizontalHeader()->setFixedHeight(50);
    ui->TableauCandid->horizontalHeader()->setStretchLastSection(true);

    ui->TableauCandid->setHorizontalHeaderLabels({
        "Nom\nEntreprise",
        "Infos\nEntreprise",
        "Poste",
        "Lien\nCandidature",
        "Téléphone",
        "E-Mail",
        "Adresse\nPostale",
        "Date\nCandidature",
        "Date\nRéponse",
        "Statut\nRéponse"
    });


    ui->TableauCandid->setWordWrap(true);
    ui->TableauCandid->resizeRowsToContents();

    //ui->TableauCandid->setRowCount(10);   // crée 10 ligne

    /**QTableWidgetItem *item = new QTableWidgetItem("Candidature\nenvoyée");
    item->setTextAlignment(Qt::AlignCenter);
    ui->TableauCandid->setItem(0,9,item);**/

    ui->TableauCandid->setAlternatingRowColors(true);
    ui->TableauCandid->verticalHeader()->setVisible(false); // cache la colonne des numéros

    newHeight = ui->TableauCandid->rowHeight(0) + 25;
    ui->TableauCandid->setRowHeight(0, newHeight);

    connect(ui->QPB_AddEnt, &QPushButton::clicked, this, &FenPrincipSC::ajouterEntreprise);
    connect(ui->QPB_Save, &QPushButton::clicked, this, &FenPrincipSC::sauvegarderDonnees);
    connect(ui->QPB_Load, &QPushButton::clicked, this, &FenPrincipSC::chargerDonnees);

}

FenPrincipSC::~FenPrincipSC()
{
    delete ui;
}

void FenPrincipSC::ajouterEntreprise()
{
    // Liste des champs à demander
    QStringList champs = {
        "Nom Entreprise",
        "Infos Entreprise",
        "Poste",
        "Lien Candidature",
        "Téléphone",
        "E-Mail",
        "Adresse Postale",
        "Date Candidature",
        "Date Réponse",
        "Statut Réponse"
    };

    QStringList valeurs;

    // 🧩 Demande les valeurs une par une
    for (const QString &champ : champs) {
        bool ok;
        QString valeur = QInputDialog::getText(
            this,
            "Ajout d'une entreprise",
            QString("Entrez %1 :").arg(champ),
            QLineEdit::Normal,
            "",
            &ok
            );

        if (!ok) {
            QMessageBox::information(this, "Annulé", "Ajout annulé par l'utilisateur.");
            return;
        }

        valeurs << valeur;
    }

    // 🧱 Ajouter la nouvelle ligne
    int newRow = ui->TableauCandid->rowCount();
    ui->TableauCandid->insertRow(newRow);

    for (int i = 0; i < valeurs.size(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(valeurs[i]);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // 🔒 non éditable
        item->setTextAlignment(Qt::AlignCenter);
        ui->TableauCandid->setItem(newRow, i, item);
    }

    ui->TableauCandid->resizeRowsToContents();

    QMessageBox::information(this, "Succès", "Nouvelle entreprise ajoutée !");
}

void FenPrincipSC::sauvegarderDonnees()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder les candidatures", "", "Fichier CSV (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour écriture.");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    // Écrire les en-têtes
    QStringList headers;
    for (int i = 0; i < ui->TableauCandid->columnCount(); ++i) {
        QString text = ui->TableauCandid->horizontalHeaderItem(i)->text();
        text.replace("\n", " - "); // ou garder \n et mettre entre guillemets
        headers << "\"" + text + "\"";
    }
    out << headers.join(";") << "\n";

    // Écrire les lignes
    for (int row = 0; row < ui->TableauCandid->rowCount(); ++row) {
        QStringList line;
        for (int col = 0; col < ui->TableauCandid->columnCount(); ++col) {
            QTableWidgetItem *item = ui->TableauCandid->item(row, col);
            QString text = item ? item->text() : "";
            text.replace("\n", " "); // ou garder et mettre entre guillemets
            line << "\"" + text + "\"";
        }
        out << line.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Succès", "Les données ont été sauvegardées !");
}


void FenPrincipSC::chargerDonnees()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir un fichier de candidatures", "", "Fichier CSV (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    ui->TableauCandid->setRowCount(0); // efface l’ancien contenu

    QString headerLine = in.readLine(); // ignore la première ligne (les titres)

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        QStringList fields = line.split(";");
        int row = ui->TableauCandid->rowCount();
        ui->TableauCandid->insertRow(row);

        for (int col = 0; col < fields.size() && col < ui->TableauCandid->columnCount(); ++col) {
            QString text = fields[col];
            // Enlever les guillemets si présents
            if (text.startsWith("\"") && text.endsWith("\"") && text.length() >= 2) {
                text = text.mid(1, text.length() - 2);
            }
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignCenter);
            ui->TableauCandid->setItem(row, col, item);
        }
    }

    file.close();
    ui->TableauCandid->resizeRowsToContents();

    QMessageBox::information(this, "Chargé", "Les candidatures ont été chargées !");
}
