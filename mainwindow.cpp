#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setText("WELCOME!!!");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_New_triggered()
{
    ui->textEdit->clear();
}

/* Will open a file and set its content to our text edit. */
void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home");
    QFile file(filename);
    QTextStream stream(&file);

    currentFile = filename;

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(currentFile);

    // Read all the text from the file and set it in our text edit.
    QString text = stream.readAll();
    ui->textEdit->setText(text);
    file.close();
}

/* Will save the file, overwriting the same file. */
void MainWindow::on_action_Save_triggered()
{
    QFile file(currentFile);
    QTextStream stream(&file);

    isSaved = true;
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Cannot write in the file: " + file.errorString());
        return;
    }
    setWindowTitle(currentFile);

    QString text = ui->textEdit->toPlainText();
    stream << text;

    file.close();
}
