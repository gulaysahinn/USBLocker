#include "usb_blocker.h"

UsbBlocker::UsbBlocker(QObject *parent) : QObject(parent) {}

bool UsbBlocker::disableUsbDevice(const QString &deviceInstanceId) {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) return false;

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        TCHAR deviceId[MAX_PATH];
        if (SetupDiGetDeviceInstanceId(deviceInfoSet, &deviceInfoData, deviceId, MAX_PATH, NULL)) {
            QString devId = QString::fromWCharArray(deviceId);
            if (devId.contains(deviceInstanceId, Qt::CaseInsensitive)) {
                DWORD state = DICS_DISABLE;
                SP_PROPCHANGE_PARAMS params;
                params.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
                params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
                params.StateChange = state;
                params.Scope = DICS_FLAG_GLOBAL;
                params.HwProfile = 0;

                if (SetupDiSetClassInstallParams(deviceInfoSet, &deviceInfoData, (SP_CLASSINSTALL_HEADER*)&params, sizeof(params)) &&
                    SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, deviceInfoSet, &deviceInfoData)) {
                    SetupDiDestroyDeviceInfoList(deviceInfoSet);
                    return true;
                }
            }
        }
    }
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
    return false;
}
