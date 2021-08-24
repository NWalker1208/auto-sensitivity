#include "settingsmanager.h"

SettingsManager::SettingsManager()
    : settings("Nathan Walker", "Auto Sensitivity")
{}

Sensitivity SettingsManager::getWindowed(Sensitivity defaultVal) const
{
    return (Sensitivity)settings.value(windowedKey, (int)defaultVal).toInt();
}

Sensitivity SettingsManager::getFullscreen(Sensitivity defaultVal) const
{
    return (Sensitivity)settings.value(fullscreenKey, (int)defaultVal).toInt();
}

void SettingsManager::setWindowed(Sensitivity value)
{
    settings.setValue(windowedKey, (int) value);
}

void SettingsManager::setFullscreen(Sensitivity value)
{
    settings.setValue(fullscreenKey, (int) value);
}
