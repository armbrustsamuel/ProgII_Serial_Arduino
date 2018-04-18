#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comserial.h"
#include <QtPlugin>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_conectarBtn_pressed();

    void on_desconectarBtn_pressed();

    void WriteData(const QByteArray data);
    void ReadData();

    void on_ajudaBtn_pressed();

    void on_hardwareBtn_pressed();

    void on_versionBtn_pressed();

    void on_enviarDadoBtn_pressed();

    void on_desligaLedBtn_pressed();

    void on_ligaLedBtn_pressed();

    void on_analogicaBtn_pressed();

    void on_sairBtn_pressed();

private:
    Ui::MainWindow *ui;

    QSerialPort *devserial;
    comserial *procSerial;
    QList<QSerialPortInfo> list;

//    void CarregarInfoDispSerial(void);
};

#endif // MAINWINDOW_H
