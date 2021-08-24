#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
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

    updateTimer = new QTimer(this);
    QObject::connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateSensitivity);
    updateTimer->start(1000);

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
    bool changedExternally = sensitivity.refresh();
    Sensitivity current = sensitivity.value();

    if (changedExternally) {
        if (!detector.foregroundFullscreen())
            settings.setWindowed(current);
        else
            settings.setFullscreen(current);
    }

    ui->windowedSensitivity->setCurrentIndex(settings.getWindowed(current));
    ui->fullscreenSensitivity->setCurrentIndex(settings.getFullscreen(current));
}

void MainWindow::updateSensitivity() {
    Sensitivity defaultVal = sensitivity.value();
    if (!detector.foregroundFullscreen()) {
        sensitivity.setValue(settings.getWindowed(defaultVal));
    } else {
        sensitivity.setValue(settings.getFullscreen(defaultVal));
    }
}

void MainWindow::on_tray_activated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        if (isVisible()) {
            hide();
        } else {
            showNormal();
            activateWindow();
            refresh();
        }
    }
}

void MainWindow::on_trayMenu_triggered(QAction *action) {
    if (action->text() == "Settings") {
        showNormal();
        activateWindow();
        refresh();
    } else if (action->text() == "Exit") {
        close();
    }
}

void MainWindow::on_windowedSensitivity_currentIndexChanged(int index) {
    settings.setWindowed((Sensitivity)index);
    updateSensitivity();
}


void MainWindow::on_fullscreenSensitivity_currentIndexChanged(int index) {
    settings.setFullscreen((Sensitivity)index);
    updateSensitivity();
}
