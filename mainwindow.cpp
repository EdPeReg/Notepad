#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setText("WELCOME!!, CREATE A NEW FILE :)");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    ui->textEdit->clear();
    isNewFile = true;
}

/* Will open a file and set its content to our text edit. */
void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home");
    QFile file(filename);
    QTextStream in(&file);

    currentFile = filename;

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(currentFile);

    // Read all the text from the file and set it in our text edit.
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

/* Will save the file, overwriting the same file. */
void MainWindow::on_action_Save_triggered()
{
    if(isNewFile) {
        on_action_Save_As_triggered();
    } else {
        saveFile(currentFile);
    }
}

/* Will save the file, having the option the save it as a new file. */
void MainWindow::on_action_Save_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save As", "/home");
    saveFile(filename);
}

void MainWindow::on_action_Exit_triggered()
{
    QMessageBox msgBox;

    msgBox.setText("File Not Saved");
    msgBox.setInformativeText("Do you want to save?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);

    if(!isFileSaved) {
        int option = msgBox.exec();
        switch(option) {
            case QMessageBox::Save:
                on_action_Save_As_triggered();
            break;

            case QMessageBox::Cancel:
                QApplication::exit();
            break;
        }
    } else {
        QApplication::exit();
    }
}

void MainWindow::on_action_Copy_triggered()
{
   ui->textEdit->copy();
}

void MainWindow::on_action_Cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_Paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_action_Undo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_Redo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::saveFile(const QString& fileName) {
    QFile file(fileName);
    QTextStream out(&file);

    isFileSaved = true;
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Cannot write in the file: " + file.errorString());
        return;
    }
    setWindowTitle(currentFile);

    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}
