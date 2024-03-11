#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->newAction,&QAction::triggered,this,&MainWindow::newActionSlot);
    connect(ui->openAction,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->saveActionSlot,&QAction::triggered,this,&MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newActionSlot(){
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");
}
void MainWindow::openActionSlot(){
    QString filename = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*");
    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文本文件");
    }
    else
    {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui->textEdit->setText(ba);
        file.close();
    }
}
void MainWindow::saveActionSlot(){
    QString filename = QFileDialog::getSaveFileName(this,"请选择一个文件",QCoreApplication::applicationFilePath());
    if(filename.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一个文本文件");
    }
    else
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8());
        file.write(ba);
    }
}
void MainWindow::keyPressEvent(QKeyEvent *k) {
    if(k->modifiers()==Qt::ControlModifier && k->key()==Qt::Key_S){
        saveActionSlot();
    }
}
