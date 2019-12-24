/*
 * Author：DingXintong
 * Data  : 2018.01.18
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->timer=new QTimer(this);

    QObject::connect(this->timer,&QTimer::timeout,this,&MainWindow::serialPortSend);

    this->serialPortDetect();

    this->serialPort=nullptr;

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    this->setFixedSize(this->width(),this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_open2close_clicked()
{
    this->serialPortOpen();
}

void MainWindow::on_pushButton_send_clicked()
{
    if(this->serialPort!=nullptr)
    {
        this->serialPortSend();
    }
}

void MainWindow::serialPortOpen()
{
    if(this->serialPort==nullptr)
    {
        this->serialPort = new QSerialPort(this);

        this->serialPort->setPortName(ui->comboBox_serialName->currentText());
        this->serialPort->setBaudRate(ui->comboBox_baud->currentText().toInt());
        switch(ui->comboBox_dataBits->currentText().toInt())
        {
        case 8:
            this->serialPort->setDataBits(QSerialPort::Data8);break;
        case 7:
            this->serialPort->setDataBits(QSerialPort::Data7);break;
        case 6:
            this->serialPort->setDataBits(QSerialPort::Data6);break;
        case 5:
            this->serialPort->setDataBits(QSerialPort::Data5);break;
        default:
            break;
        }
        switch(ui->comboBox_parity->currentIndex())
        {
        case 0:
            this->serialPort->setParity(QSerialPort::NoParity);
            break;
        case 1:
            this->serialPort->setParity(QSerialPort::OddParity);
            break;
        case 2:
            this->serialPort->setParity(QSerialPort::EvenParity);
            break;
        default:
            break;
        }
        switch (ui->comboBox_stopBits->currentIndex())
        {
        case 0:
            this->serialPort->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            this->serialPort->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            this->serialPort->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }

        if(!serialPort->open( QIODevice::ReadWrite ))
        {
            delete serialPort;
            this->serialPort=nullptr;
            ui->pushButton_open2close->setText("Open");
        }
        else
        {
            ui->pushButton_open2close->setText("Close");
            QObject::connect(this->serialPort,&QSerialPort::readyRead,this,&MainWindow::serialPortReceive);
        }
    }
    else
    {
        serialPort->close();
        delete serialPort;
        serialPort=nullptr;
        ui->pushButton_open2close->setText("Open");
    }

}

void MainWindow::serialPortDetect()
{
    this->detectFlag=1;
    QList<QSerialPortInfo> serialPortList(QSerialPortInfo::availablePorts());
    QSerialPort tempSerial;
    ui->comboBox_serialName->clear();
    for(int i=0;i<serialPortList.size();i++)
    {
        tempSerial.setPort(serialPortList.at(i));
        ui->comboBox_serialName->addItem(serialPortList.at(i).portName());
        tempSerial.close();

    }
    this->detectFlag=0;
}

void MainWindow::serialPortSend()
{
    if(ui->checkBox_hex_send->checkState()==Qt::Unchecked)
    {
        this->serialPort->write(ui->textEdit_send->toPlainText().toLocal8Bit());
        this->sendNumber+=ui->textEdit_send->toPlainText().toLocal8Bit().size();
    }
    else
    {
        this->sendNumber +=
                this->serialPort->write(QByteArray::fromHex( ui->textEdit_send->toPlainText().toLocal8Bit() ));
        //QByteArray::fromHex( ui->textEdit_send->toPlainText().toLocal8Bit() ).size();
    }
    if(ui->checkBox_send_newline->isChecked()){
        this->sendNumber += this->serialPort->write("\r\n", 2);
    }

    ui->label_send_number->setText(QString::number(this->sendNumber));
}

void MainWindow::serialPortReceive()
{
    QByteArray temp(this->serialPort->readAll());
    QString tempStr;
    if(ui->checkBox_hex_show->checkState()==Qt::Unchecked)
    {
        tempStr=QString::fromLocal8Bit(temp);
    }
    else
    {
        tempStr=temp.toHex();
    }

    if(!temp.isEmpty())
    {
        ui->textEdit_receive->moveCursor(QTextCursor::End);
        ui->textEdit_receive->insertPlainText(tempStr);
    }
    this->receiveNumber+=temp.size();
    ui->label_receive_number->setText(QString::number(this->receiveNumber));
    temp.clear();
    tempStr.clear();
}

void MainWindow::on_pushButton_clearRec_clicked()
{
    ui->textEdit_receive->clear();
}

void MainWindow::on_pushButton_clearSend_clicked()
{
    ui->textEdit_send->clear();
}

void MainWindow::on_comboBox_dataBits_currentIndexChanged(int index)
{
    if(this->serialPort)
    {
        switch(index)
        {
        case 0:
            this->serialPort->setDataBits(QSerialPort::Data8);break;
        case 1:
            this->serialPort->setDataBits(QSerialPort::Data7);break;
        case 2:
            this->serialPort->setDataBits(QSerialPort::Data6);break;
        case 3:
            this->serialPort->setDataBits(QSerialPort::Data5);break;
        default:
            break;
        }
    }

}

void MainWindow::on_comboBox_baud_currentIndexChanged(const QString &arg1)
{
    if(this->serialPort)
    {
        this->serialPort->setBaudRate(arg1.toInt());
    }
}

void MainWindow::on_comboBox_stopBits_currentIndexChanged(int index)
{
    if(this->serialPort)
    {
        switch (index)
        {
        case 0:
            this->serialPort->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            this->serialPort->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            this->serialPort->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_comboBox_parity_currentIndexChanged(int index)
{
    if(this->serialPort)
    {
        switch(index)
        {
        case 0:
            this->serialPort->setParity(QSerialPort::NoParity);
            break;
        case 1:
            this->serialPort->setParity(QSerialPort::OddParity);
            break;
        case 2:
            this->serialPort->setParity(QSerialPort::EvenParity);
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_comboBox_serialName_currentIndexChanged(const QString &)
{
    if(this->serialPort&&!this->detectFlag)
    {
        this->serialPort->close();
        delete serialPort;
        this->serialPort=nullptr;
        this->serialPortOpen();
    }
}

void MainWindow::on_pushButton_clear_log_clicked()
{
    this->sendNumber=0;
    this->receiveNumber=0;
    ui->label_receive_number->setText(QString::number(0));
    ui->label_send_number->setText(QString::number(0));
}

void MainWindow::on_checkBox_timer_send_stateChanged(int arg1)
{
    if(this->serialPort)
    {
        if(arg1==Qt::Checked)
        {
            this->timer->start(ui->lineEdit_send_time->text().toInt());
        }
        if(arg1==Qt::Unchecked)
        {
            this->timer->stop();
        }
    }

}

void MainWindow::on_pushButton_detect_serial_clicked()
{
    this->serialPortDetect();
}

