#ifndef USB_DETECTOR_H
#define USB_DETECTOR_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

#pragma comment (lib, "Setupapi.lib")

struct UsbDeviceInfo {
    QString deviceID;
    QString description;
    QString vid;
    QString pid;
};

class UsbDetector : public QObject {
    Q_OBJECT
public:
    explicit UsbDetector(QObject *parent = nullptr);
    QVector<UsbDeviceInfo> getConnectedUsbDevices();
};

#endif // USB_DETECTOR_H


