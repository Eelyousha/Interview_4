#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PhoneInput->setText("+");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Add_clicked()
{

    if(this->current_file == "")
    {
        QMessageBox::warning(this, "Error" , "Please, use 'READ' for creat new file or \n"
                                             "reading existing file, wich contains data.\n"
                                             "Otherwise you can not add new number" );
        return;
    }

    if(ui->NameInput->text() == "" || ui->NameInput->text() == "")
    {
        QMessageBox::warning(this, "Error" , "You don not enter any data for adding" );
        return;
    }

    QString new_added = ui->PhoneInput->text();
    bool flag = false;
    for(int i = 1; i != new_added.size(); i++)
    {
        if(*(new_added.begin() + i) < '0' || *(new_added.begin() + i) > '9')
            flag = true;
    }
    if(flag)
    {
        QMessageBox::warning(this, "Error" , "You enter incorrect number" );
        return;
    }


    QFile file(current_file);
    if(!file.open(QIODevice::Append))
    {
        QMessageBox::warning(this, "Error" , "File does not save : " + file.errorString());
        return;
    }
    new_added = ui->NameInput->text() + ' ' + ui->PhoneInput->text() + '\n';
    QTextStream out (&file);
    out << new_added;
    ui->NameInput->clear();
    ui->PhoneInput->clear();
    ui->PhoneInput->setText("+");
    file.close();
    this->show_data_from_file();
}

void MainWindow::on_Open_File_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/home",
                                                      tr("(*.txt)"));
    QFile file (fileName);
    current_file = fileName;
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error" , "File does not open : " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in (&file);
    QString cur = in.readAll();
    ui->DataOut->setText(cur);
    file.close();
}

void MainWindow::on_Delete_clicked()
{

    QFile file (current_file);

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Error" , "File does not save : " + file.errorString());
        return;
    }

    ui->DataOut->clear();

    QTextStream out (&file);
    out << "";
    file.close();
}

void MainWindow::show_data_from_file()
{
    QFile file (current_file);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::warning(this, "Error" , "File does not ");
    QTextStream st (&file);
    ui->DataOut->setText(st.readAll());
}
