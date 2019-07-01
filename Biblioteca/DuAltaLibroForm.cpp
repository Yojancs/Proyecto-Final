#include "DuAltaLibroForm.h"
#include "ui_DuAltaLibroForm.h"
#include "DuSelectorDialog.h"
#include "DuLibro.h"
#include <QMdiSubWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

DuAltaLibroForm::DuAltaLibroForm(QWidget *parent)
    : DuFormBase(parent)
    , ui(new Ui::DuAltaLibroForm)
{
    ui->setupUi(this);
}

DuAltaLibroForm::~DuAltaLibroForm()
{
    delete ui;
}

void DuAltaLibroForm::on_buttonBox_accepted()
{
    DuLibro libro(ui->nombreLineEdit->text(),
                  ui->autorLineEdit->text().toInt(),
                  ui->editorialLineEdit->text().toInt());
    if (!libro.valida()) {
        return;
    }
    QSqlQuery q;
    q.prepare("INSERT INTO libro (nombre,idAutor,idEditorial) VALUES (?,?,?)");
    q.addBindValue(libro.nombreDescripcion());
    q.addBindValue(libro.idAutor());
    q.addBindValue(libro.idEditorial());
    if (!q.exec()) {
        QMessageBox::critical(this, tr("Error"), q.lastError().text());
        return;
    }
    subWindowDriver()->close();
}

void DuAltaLibroForm::on_buttonBox_rejected()
{
    subWindowDriver()->close();
}

void DuAltaLibroForm::on_autorSeleccionarPushButton_clicked()
{
    DuSelectorDialog d("Seleccionar Autor", "autor", this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    ui->autorLineEdit->setText(QString::number(d.id()));
}

void DuAltaLibroForm::on_editorialSeleccionarPushButton_clicked()
{
    DuSelectorDialog d("Seleccionar Editorial", "editorial", this);
    if (d.exec() == QDialog::Rejected) {
        return;
    }
    ui->editorialLineEdit->setText(QString::number(d.id()));
}
