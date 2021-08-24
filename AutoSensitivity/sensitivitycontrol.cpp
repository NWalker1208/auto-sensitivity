#include "sensitivitycontrol.h"
#include <QDebug>

SensitivityControl::SensitivityControl()
    : registry(touchpadDir, QSettings::NativeFormat)
{
    refresh();
}

Sensitivity SensitivityControl::value() const {
    return currentSetting;
}

void SensitivityControl::setValue(Sensitivity val) {
    if (val != (int) currentSetting) {
        registry.setValue(sensitivityKey, (int)val);
        currentSetting = val;
#ifdef QT_DEBUG
        qDebug() << "Updated sensitivity to" << val;
#endif
    }
}

bool SensitivityControl::refresh() {
    int val = registry.value(sensitivityKey).toInt();
    if (val != (int) currentSetting) {
        currentSetting = (Sensitivity)val;
        return true;
    }
    return false;
}
