#ifndef USB_BLOCKER_H
#define USB_BLOCKER_H

#include <QObject>
#include <QString>
#include <windows.h>
#include <setupapi.h>

#pragma comment (lib, "Setupapi.lib")

class UsbBlocker : public QObject {
    Q_OBJECT
public:
    explicit UsbBlocker(QObject *parent = nullptr);
    bool disableUsbDevice(const QString &deviceInstanceId);
    bool enableUsbDevice(const QString &deviceInstanceId);
};

#endif // USB_BLOCKER_H
