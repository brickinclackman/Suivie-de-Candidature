#ifndef FENPRINCIPSC_H
#define FENPRINCIPSC_H

#include <QMainWindow>
#include <QLabel>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class FenPrincipSC;
}
QT_END_NAMESPACE


class FenPrincipSC : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipSC(QWidget *parent = nullptr);
    ~FenPrincipSC();
private slots:
    void ajouterEntreprise();
    void sauvegarderDonnees();
    void chargerDonnees();
private:
    Ui::FenPrincipSC *ui;
    QLabel *label;
    QHeaderView *header;
    int newHeight;
};
#endif // FENPRINCIPSC_H
