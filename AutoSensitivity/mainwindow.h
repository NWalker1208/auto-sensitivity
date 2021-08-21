#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QSettings>

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

public slots:
    void refresh();
    void updateSensitivity(int value);

    void on_tray_activated(QSystemTrayIcon::ActivationReason reason);
    void on_trayMenu_triggered(QAction *action);
    void on_defaultSensitivity_currentIndexChanged(int index);

private:
    const QString touchpadKey = QString("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\PrecisionTouchPad");
    const QString sensitivityKey = QString("AAPThreshold");

    Ui::MainWindow *ui;
    QSystemTrayIcon *tray;
    QMenu *trayMenu;

    QSettings mouseSettings;
};
#endif // MAINWINDOW_H
