#include "fullscreendetector.h"
#include <windows.h>
#include <QDebug>

FullscreenDetector::FullscreenDetector() {

}

bool FullscreenDetector::foregroundFullscreen() {
    HWND window = GetForegroundWindow();

    RECT windowRect;
    GetWindowRect(window, &windowRect);

    HMONITOR monitor = MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info;
    info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(monitor, &info);
    RECT monitorRect = info.rcMonitor;

#ifdef QT_DEBUG
    //qDebug() << windowRect.left << windowRect.top << windowRect.right << windowRect.bottom;
    //qDebug() << monitorRect.left << monitorRect.top << monitorRect.right << monitorRect.bottom;
#endif

    return windowRect.left == monitorRect.left &&
           windowRect.top == monitorRect.top &&
           windowRect.right == monitorRect.right &&
           windowRect.bottom == monitorRect.bottom;
}
