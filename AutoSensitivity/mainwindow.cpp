#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mouseSettings(touchpadKey, QSettings::NativeFormat)
{
    ui->setupUi(this);

    trayMenu = new QMenu(this);
    trayMenu->addAction(QString("Settings"));
    trayMenu->addAction(QString("Exit"));

    tray = new QSystemTrayIcon(this);
    tray->setContextMenu(trayMenu);
    tray->setIcon(QIcon(":/images/tray.ico"));
    tray->setToolTip(QString("Auto Sensitivity"));
    tray->show();

    QObject::connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::on_tray_activated);
    QObject::connect(trayMenu, &QMenu::triggered, this, &MainWindow::on_trayMenu_triggered);

    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tray;
    delete trayMenu;
}

bool MainWindow::event(QEvent *event) {
    if (event->type() == QEvent::WindowStateChange) {
        if (windowState().testFlag(Qt::WindowMinimized)) {
            hide();
            return true;
        }
    }
    return QMainWindow::event(event);
}

void MainWindow::refresh() {
    int val = mouseSettings.value(sensitivityKey).toInt();
    ui->defaultSensitivity->setCurrentIndex(val);
}

void MainWindow::updateSensitivity(int value) {
    mouseSettings.setValue(sensitivityKey, value);
}

void MainWindow::on_tray_activated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            showNormal();
            activateWindow();
        }
    }
}

void MainWindow::on_trayMenu_triggered(QAction *action) {
    if (action->text() == "Settings") {
        showNormal();
        activateWindow();
    } else if (action->text() == "Exit") {
        close();
    }
}

void MainWindow::on_defaultSensitivity_currentIndexChanged(int index)
{
    updateSensitivity(index);
}

