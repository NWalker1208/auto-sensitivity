#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    QObject::connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::TrayIconActivated);
    QObject::connect(trayMenu, &QMenu::triggered, this, &MainWindow::TrayIconMenuAction);
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

void MainWindow::TrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            show();
            activateWindow();
            setWindowState(Qt::WindowActive);
        }
    }
}

void MainWindow::TrayIconMenuAction(QAction *action) {
    if (action->text() == "Settings") {
        show();
        activateWindow();
        setWindowState(Qt::WindowActive);
    } else if (action->text() == "Exit") {
        close();
    }
}
