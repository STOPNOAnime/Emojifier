#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generate(){
    #include "font8x8_basic.h"

    QStringList list = foregroundemojisstring.split(QRegExp("\\s+"));

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> distribution(0,list.size()-1);

    std::stringstream ss;

    unsigned char *bitmap = font8x8_basic[inputtextstring[currentNumber].unicode()];

    int x,y;
    int set;
    for (x=0; x < 8; x++) {
        for (y=0; y < 8; y++) {
            set = bitmap[x] & 1 << y;
            ss<<(set ? (list[distribution(g)].toStdString() + " ") : (backroundemojistring.toStdString() + " "));
        }
        ss<<"\n";
    }

    QString result = QString::fromStdString(ss.str());
    ui->outputtext->setText(result);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(result);
}

void MainWindow::on_lastletter_clicked()
{
    if(currentNumber > 0) currentNumber--;
    ui->leternumber->display(currentNumber);

    generate();
}

void MainWindow::on_nextletter_clicked()
{
    if(currentNumber < inputtextletters-1) currentNumber++;
    ui->leternumber->display(currentNumber);

    generate();
}

void MainWindow::on_generatebutton_clicked()
{
    backroundemojistring = ui->backroundemoji->text();
    foregroundemojisstring = ui->foregroundemojis->text();
    inputtextstring = ui->inputtext->toPlainText();
    currentNumber = 0;
    inputtextletters = inputtextstring.size();

    ui->leternumber->display(currentNumber);

    generate();
}

void MainWindow::on_readconfig_clicked()
{
    QFile file("config.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);
    QString backroundconfig = in.readLine();
    QString foregroundconfig = in.readLine();

    ui->backroundemoji->setText(backroundconfig);
    ui->foregroundemojis->setText(foregroundconfig);

}

void MainWindow::on_writeconfig_clicked()
{
    QFile file("config.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);

    out<<ui->backroundemoji->text();
    out<<"\n";
    out<<ui->foregroundemojis->text();
}
