#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>
#include <string>
#include <random>
#include <QFile>
#include <QTextStream>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lastletter_clicked();

    void on_nextletter_clicked();

    void generate();

    void on_generatebutton_clicked();

    void on_readconfig_clicked();

    void on_writeconfig_clicked();

private:
    Ui::MainWindow *ui;
    int currentNumber = 0;
    int inputtextletters = 0;
    QString backroundemojistring = "";
    QString foregroundemojisstring = "";
    QString inputtextstring = "";
};
#endif // MAINWINDOW_H
