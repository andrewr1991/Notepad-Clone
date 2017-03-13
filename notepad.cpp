#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}

/*
 * Signals for "File" menu
 */

void Notepad::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void Notepad::on_actionSave_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
            return;
        }
        else {
        QTextStream stream(&file);
        stream << ui->textEdit->toPlainText();
        stream.flush();
        file.close();
        }
    }
}

void Notepad::on_actionQuit_triggered() {
    QCoreApplication::quit();
}

/*
 * Signals for "Edit" menu
 */

void Notepad::on_actionUndo_triggered() {
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered() {
    ui->textEdit->redo();
    ui->textEdit->zoomIn();
}


/*
 * Signals for "Help" menu
 */

void Notepad::on_actionAbout_triggered() {
    QMessageBox myBox;
    QString help = "Welcome to the Notepad clone!\n";
    help += "There are several different options available in the dropdown menu.\n";
    help += "Code taken from official QT tutorial from http://doc.qt.io/qt-5/gettingstartedqt.html\n";
    help += "Additional code and functionality added by Andrew Ridout.\n";
    help += "Enjoy!";
    myBox.setText(help);
    myBox.exec();
}
