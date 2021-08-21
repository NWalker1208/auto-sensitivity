#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayMenu = new QMenu(this);

    tray = new QSystemTrayIcon(this);
    tray->setContextMenu(trayMenu);
    tray->setIcon(QIcon(":/images/tray.ico"));
    tray->setToolTip(QString("Auto Sensitivity"));
    tray->show();

    QObject::connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::TrayIconActivated);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tray;
    delete trayMenu;
}

void MainWindow::TrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            show();
        }
    } else if (reason == QSystemTrayIcon::Context) {
        close();
    }
}
