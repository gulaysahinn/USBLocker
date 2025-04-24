#include "usb_detector.h"
#include <initguid.h>  // Gerekli GUID tanımları için
#include <usbiodef.h>  // GUID_DEVINTERFACE_USB_DEVICE için //tak çıkar mantığı
#include <cfgmgr32.h>  // MAX_DEVICE_ID_LEN tanımı burada  cihaz kimlik tanım uzunluğu


UsbDetector::UsbDetector(QObject *parent) : QObject(parent) {}


//bağlı olan USB cihazlarını algılar ve bir liste olarak döndür.
QVector<UsbDeviceInfo> UsbDetector::getConnectedUsbDevices() {
    QVector<UsbDeviceInfo> devices;//usb cihazları bilgileri saklamak için liste
    HDEVINFO deviceInfoSet;//bilgileri alacağız
    SP_DEVINFO_DATA deviceInfoData;//bilgileri saklayacağız
    DWORD i;
//cihazları listele  SetupDiGetClassDevs fonksiyonu kullandık
    deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVINTERFACE_USB_DEVICE, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);//sadece aktif olanları alır

    if (deviceInfoSet == INVALID_HANDLE_VALUE) return devices; //hata durumunda boş döner

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
//cihaz bilgileri almak için
    for (i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        TCHAR deviceInstanceId[MAX_PATH]; //instance id
        if (SetupDiGetDeviceInstanceId(deviceInfoSet, &deviceInfoData, deviceInstanceId, MAX_DEVICE_ID_LEN, nullptr)) {
            QString deviceID = QString::fromWCharArray(deviceInstanceId);
            UsbDeviceInfo usbInfo;
            usbInfo.deviceID = deviceID;

            int vidIndex = deviceID.indexOf("VID_");
            int pidIndex = deviceID.indexOf("PID_");

            if (vidIndex != -1 && pidIndex != -1) {
                usbInfo.vid = deviceID.mid(vidIndex + 4, 4);
                usbInfo.pid = deviceID.mid(pidIndex + 4, 4);
            }

            devices.append(usbInfo);
        }
    }
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return devices;
}
