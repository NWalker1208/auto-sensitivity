#ifndef SENSITIVITYSETTING_H
#define SENSITIVITYSETTING_H

#include <QSettings>

enum Sensitivity {
    Most = 0,
    High = 1,
    Medium = 2,
    Low = 3
};

class SensitivityControl
{
public:
    SensitivityControl();

    Sensitivity value() const;

    void setValue(Sensitivity val);
    bool refresh();

private:
    const QString touchpadDir = QString("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\PrecisionTouchPad");
    const QString sensitivityKey = QString("AAPThreshold");

    QSettings registry;
    Sensitivity currentSetting;
};

#endif // SENSITIVITYSETTING_H
