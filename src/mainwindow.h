#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "webview.h"
#include "tabbar.h"
#include "topwidget.h"
#include "about.h"
#include "contentmanagerside.h"
#include "localkiwixserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    TabBar*   getTabBar();
    TopWidget* getTopWidget();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void toggleFullScreen();
    void when_ReadingList_toggled(bool state);
    void when_libraryPageDisplayed(bool showed);

private:
    Ui::MainWindow *mp_ui;
    About     *mp_about;
    LocalKiwixServer *mp_localKiwixServer;
};

#endif // MAINWINDOW_H
