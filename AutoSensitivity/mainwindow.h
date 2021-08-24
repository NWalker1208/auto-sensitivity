#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include "sensitivitycontrol.h"
#include "fullscreendetector.h"
#include "settingsmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool event(QEvent *event);

private slots:
    void refresh();
    void updateSensitivity();

    void on_tray_activated(QSystemTrayIcon::ActivationReason reason);
    void on_trayMenu_triggered(QAction *action);

    void on_windowedSensitivity_currentIndexChanged(int index);
    void on_fullscreenSensitivity_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *tray;
    QMenu *trayMenu;
    QTimer *updateTimer;

    SensitivityControl sensitivity;
    FullscreenDetector detector;
    SettingsManager settings;
};
#endif // MAINWINDOW_H
