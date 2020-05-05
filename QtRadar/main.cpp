#include <QApplication>
#include "radarwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QString serialPortName;
    if(argc > 1){
        serialPortName = QString(argv[1]);
    }
    else {
        serialPortName = QString("COM5");
    }

    QSerialPort serialPort;
    serialPort.setPortName(serialPortName);

    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadOnly)) {
        QTextStream(stdout) << QObject::tr("Failed to open port %1, error: %2")
                          .arg(serialPortName)
                          .arg(serialPort.errorString())
                       << endl;
        return 1;
    }

    RadarWindow w(&serialPort);

    w.show();
    return app.exec();

}
