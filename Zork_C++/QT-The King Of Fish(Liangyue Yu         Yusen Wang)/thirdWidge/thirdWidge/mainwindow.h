#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <QSet>
#include "ZorkUL.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_btn_left_clicked();

    void on_btn_down_clicked();

    void on_btn_right_clicked();

    void on_btn_up_clicked();

    void on_menu_exit_triggered();

    void on_btn_pick_clicked();

    void on_btn_drop_clicked();

    void on_btn_attack_clicked();

    void on_btn_teleport_clicked();

    void on_btn_info_clicked();

    void on_pushButton_clicked();

private:
    void updateRoomItemsView();
    void updateInventory();
    void updateProgressBarState();

private:
    void paintRoomBorder(QPainter* painter,Room* room, int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY);
    void paintRoomItems(QPainter* painter, Room* room,int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY);
    void paintRoom(Room* room, QSet<Room*>& visited, QPainter* painter, int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY);
    void paintEvent(QPaintEvent*);
    Ui::MainWindow *ui;
    ZorkUL zorkUL;



};


#endif // MAINWINDOW_H
