#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Create Object the Class QSerialPort*/
    devserial = new QSerialPort(this);

    /* Create Object the Class comserial to manipulate read/write of the my way */
    procSerial = new comserial(devserial);



    /* Load Device PortSerial available */
    QStringList DispSeriais = procSerial->CarregarDispositivos();

    /* Inserting in ComboxBox the Devices */
    ui->portaSerialCombBox->addItems(DispSeriais);

    /* Enable PushButton "Conectar" if any port is found.
     * If an error occurs, it is reported in the Log
     */
    if(DispSeriais.length() > 0) {
        ui->conectarBtn->setEnabled(true);
        ui->comandoTextEdit->append("### Porta serial pronta para ser utilizada.");
    }
    else { ui->comandoTextEdit->append("### Nenhuma porta serial foi detectada!"); }


    /* Connect Objects -> Signal and Slots
     * DevSerial with Read Data Serial
     * TextEdit "teLog" with getData() after send data WriteData() [Not apply here in version 5.X]
     */
    connect(devserial, SIGNAL(readyRead()), this, SLOT(ReadData()));
    //connect(ui->teLog, SIGNAL(getData(QByteArray)), this, SLOT(WriteData(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_conectarBtn_pressed()
{
    bool statusOpenSerial;

    statusOpenSerial = procSerial->Conectar(ui->portaSerialCombBox->currentText(),
                                             ui->baudrateComboBox->currentText().toInt()
                                             );
    if (statusOpenSerial) {
        ui->desconectarBtn->setEnabled(true);
        ui->conectarBtn->setEnabled(false);
        ui->comandoTextEdit->append("### Porta serial aberta com sucesso!");
    }
    else {
        ui->comandoTextEdit->append("Falha ao abrir conexão serial.");
    }
}

void MainWindow::on_desconectarBtn_pressed()
{
    bool statusCloseSerial;


    statusCloseSerial = procSerial->Desconectar();

    /* BUG: Existe um bug no close do QtSerialPort, já conhecido pela comunidade onde
     * quando usado com waitForReadyRead, da um erro 12 Timeout no SerialPort e não encerra a conexão
     * porém é reportado o erro mas o device é encerrado.
     * Para contornar o problema no Desconectar eu verifiquei com isOpen logo apos fechar a conexão
     * serial.
     */

    if (statusCloseSerial) {
        ui->desconectarBtn->setEnabled(false);
        ui->conectarBtn->setEnabled(true);
        ui->comandoTextEdit->append("### Porta serial fechada com sucesso!");
    }
    else {
        ui->comandoTextEdit->append("### Falha ao fechar conexão serial.");
    }
}

void MainWindow::WriteData(const QByteArray data)
{
    procSerial->Write(data);
}

void MainWindow::ReadData()
{
    QString data = procSerial->Read();
    qDebug() << "Input: " << data << endl;
    ui->comandoTextEdit->append(data);

}

void MainWindow::on_ajudaBtn_pressed()
{
    QString Cmd = "help\n";
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_hardwareBtn_pressed()
{
    QString Cmd = "hardware\n";
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_versionBtn_pressed()
{
    QString Cmd = "versao\n";
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_enviarDadoBtn_pressed()
{
    QString Cmd = ui->comandoLineEdit->text()+"\n";
    qDebug() << "Output: " << Cmd << endl;
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_desligaLedBtn_pressed()
{
    QString Cmd = "desliga\n";
    qDebug() << "Output: " << Cmd << endl;
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_ligaLedBtn_pressed()
{
    QString Cmd = "liga\n";
    qDebug() << "Output: " << Cmd << endl;
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_analogicaBtn_pressed()
{
    QString Cmd = "analogico\n";
    qDebug() << "Output: " << Cmd << endl;
    WriteData(Cmd.toUtf8());
    ReadData();
}

void MainWindow::on_sairBtn_pressed()
{
    on_desconectarBtn_pressed();
    this->close();
}
