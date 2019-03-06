#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


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
    void on_pushButton_open2close_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_clearRec_clicked();

    void on_pushButton_clearSend_clicked();

    void on_pushButton_clear_log_clicked();

    void on_comboBox_baud_currentIndexChanged(const QString &arg1);

    void on_comboBox_dataBits_currentIndexChanged(int index);

    void on_comboBox_stopBits_currentIndexChanged(int index);

    void on_comboBox_parity_currentIndexChanged(int index);

    void on_comboBox_serialName_currentIndexChanged(const QString &arg1);

    void on_checkBox_timer_send_stateChanged(int arg1);

    void on_pushButton_detect_serial_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort* serialPort;
    QTimer *timer;

    bool detectFlag=0;

    int sendNumber=0;
    int receiveNumber=0;

    void serialPortOpen();
    void serialPortDetect();
    void serialPortSend();
    void serialPortReceive();

};

#endif // MAINWINDOW_H
