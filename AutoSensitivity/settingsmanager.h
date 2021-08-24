#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include "sensitivitycontrol.h"

class SettingsManager
{
public:
    SettingsManager();

    Sensitivity getWindowed(Sensitivity defaultVal) const;
    Sensitivity getFullscreen(Sensitivity defaultVal) const;

    void setWindowed(Sensitivity value);
    void setFullscreen(Sensitivity value);

private:
    const QString windowedKey = "windowedSensitivity";
    const QString fullscreenKey = "fullscreenSensitivity";

    QSettings settings;
};

#endif // SETTINGSMANAGER_H
