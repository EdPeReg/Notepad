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

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    // Read all the text from the file and set it in our text edit.
    QString text = stream.readAll();
    ui->textEdit->setText(text);

}
