#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Room.h"
#include <QLinkedList>
#include <QHash>
#include <QQueue>
#include <QPointF>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zorkUL.printWelcome();
    updateRoomItemsView();
    updateProgressBarState();

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintRoomBorder(QPainter* painter,Room* room, int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY){
    int x = offsetX + roomPixels * roomLocX;
    int y = offsetY + roomPixels * roomLocY;
    painter->setPen(QPen(Qt::black,2,Qt::SolidLine));
    painter->setBrush(QBrush(Qt::gray,Qt::SolidPattern));
    painter->drawRect(x, y, roomPixels, roomPixels);


    if(room == this->zorkUL.getCurrentRoom()) {
        painter->setBrush(QBrush(Qt::lightGray,Qt::SolidPattern));
        painter->drawRect(x, y, roomPixels, roomPixels);

        painter->setPen(QPen(Qt::yellow,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
        //painter->drawEllipse(QPoint(x + roomPixels/2, y + roomPixels/2), 5, 5);
        painter->drawImage(QPoint(x + roomPixels/2 - 12, y + roomPixels/2 - 12), QImage(":/imgs/player.png"), QRect(0,0,24,24));
    }
}
void MainWindow::paintRoomItems(QPainter* painter, Room* room,int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY){
    int basex = offsetX + roomPixels * roomLocX;
    int basey = offsetY + roomPixels * roomLocY;

    int count = room->numberOfItems();
    for (int i=0;i<count;i++) {
        int x = basex + 5 + i*6;
        int y = basey + 5;
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::red,Qt::SolidPattern));
        painter->drawEllipse(x, y, 3, 3);
    }

    if(room->getMonster()!=NULL) {
        int x = basex + 5;
        int y = basey + roomPixels - 30;
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::green,Qt::SolidPattern));
        //painter->drawRect(x, y, 10, 10);
        painter->drawImage(QPoint(x, y), QImage(":/imgs/monster.png"), QRect(0,0,24,24));
    }

    if(room->nextRoom("north")!=NULL) {
        QPointF points[3];
        points[0] = QPointF(basex+roomPixels/2, basey);
        points[1] = QPointF(basex+roomPixels/2-4,basey+6);
        points[2] = QPointF(basex+roomPixels/2+4,basey+6);
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawPolygon(points,3);


        setStyleSheet(

                          "QPushButton{"
                          "background-color:rgba(100,225,100,30);"
                          "border-style:outset;"
                          "border-width:4px;"
                          "border-radius:10px;"
                          "border-color:rgba(255,255,255,30);"
                          "font:bold 20px;"
                          "color:rgba(0,0,0,100);"
                          "padding:10px;"
                          "}"

                          "QPushButton:pressed{"
                          "background-color:rgba(100,255,100,200);"
                          "border-color:rgba(255,255,255,30);"
                          "border-style:inset;"
                          "color:rgba(0,0,0,100);"
                          "}"

                          "QPushButton:hover{"
                          "background-color:rgba(100,255,100,100);"
                          "border-color:rgba(255,255,255,200);"
                          "color:rgba(0,0,0,200);"
                          "}");
    }

    if(room->nextRoom("south")!=NULL) {
        QPointF points[3];
        points[0] = QPointF(basex+roomPixels/2, basey+roomPixels);
        points[1] = QPointF(basex+roomPixels/2-4,basey+roomPixels-6);
        points[2] = QPointF(basex+roomPixels/2+4,basey+roomPixels-6);
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawPolygon(points,3);

    }
    if(room->nextRoom("west")!=NULL) {
        QPointF points[3];
        points[0] = QPointF(basex, basey+roomPixels/2);
        points[1] = QPointF(basex+6,basey+roomPixels/2-4);
        points[2] = QPointF(basex+6,basey+roomPixels/2+4);
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawPolygon(points,3);
    }
    if(room->nextRoom("east")!=NULL) {
        QPointF points[3];
        points[0] = QPointF(basex+roomPixels, basey+roomPixels/2);
        points[1] = QPointF(basex+roomPixels-6,basey+roomPixels/2-4);
        points[2] = QPointF(basex+roomPixels-6,basey+roomPixels/2+4);
        painter->setPen(QPen(Qt::black,0,Qt::SolidLine));
        painter->setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter->drawPolygon(points,3);
    }

}



void MainWindow::paintRoom(Room* room, QSet<Room*>& visited, QPainter* painter, int roomPixels, int roomLocX, int roomLocY, int offsetX, int offsetY) {
    if(visited.contains(room)) return;
    visited.insert(room);

    paintRoomBorder(painter,room, roomPixels, roomLocX, roomLocY, offsetX, offsetY);
    paintRoomItems(painter,room, roomPixels, roomLocX, roomLocY, offsetX, offsetY);

    Room* north_room = room->nextRoom("north");
    Room* south_room = room->nextRoom("south");
    Room* east_room = room->nextRoom("east");
    Room* west_room = room->nextRoom("west");

    if(north_room!=NULL) paintRoom(north_room, visited, painter, roomPixels, roomLocX, roomLocY-1, offsetX, offsetY);
    if(south_room!=NULL) paintRoom(south_room, visited, painter, roomPixels, roomLocX, roomLocY+1, offsetX, offsetY);
    if(east_room!=NULL) paintRoom(east_room, visited, painter, roomPixels, roomLocX+1, roomLocY, offsetX, offsetY);
    if(west_room!=NULL) paintRoom(west_room, visited, painter, roomPixels, roomLocX-1, roomLocY, offsetX, offsetY);

}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    int roomPixels = 100;
    int offsetX = 50;
    int offsetY = 50;
    int roomLocX = 3;
    int roomLocY = 2;

    QSet<Room*> visited;
    paintRoom(this->zorkUL.getStartRoom(), visited, &painter, roomPixels, roomLocX, roomLocY, offsetX, offsetY);

    painter.end();
}

void MainWindow::updateRoomItemsView() {
    auto curRoom = zorkUL.getCurrentRoom();
    this->ui->lst_items->clear();
    for (int i=0;i< curRoom->numberOfItems();i++) {
        Item* item = curRoom->getItem(i);
        if(item->getType()!="weapon") continue;

        Weapon* weapon = (Weapon*)item;
        string desp = item->getShortDescription() + "(+" + to_string(weapon->getPower()) + ")";
        this->ui->lst_items->addItem(new QListWidgetItem(QString(desp.c_str())));
    }
}

void MainWindow::updateInventory() {
    Character* player = zorkUL.getPlayer();
    this->ui->lst_inventory->clear();
    for(int i=0;i<player->itemsCount();i++) {
        Item* item = player->getItem(i);
        if(item->getType()!="weapon") continue;

        Weapon* weapon = (Weapon*)item;
        string desp = item->getShortDescription() + "(+" + to_string(weapon->getPower()) + ")";
        this->ui->lst_inventory->addItem(new QListWidgetItem(QString(desp.c_str())));
    }
}

void MainWindow::updateProgressBarState() {
    Room* room = zorkUL.getCurrentRoom();
    Monster* monster = room->getMonster();

    ui->prog_player->setValue(zorkUL.getPlayer()->getHealthy()*100.0/zorkUL.getPlayer()->getMaxHealthy());

    if(monster==NULL) {
        ui->lbl_monster->hide();
        ui->prog_monster->hide();
    }else{
        ui->prog_monster->setValue(monster->getHealthy()*100.0/monster->getMaxHealthy());
        ui->lbl_monster->show();
        ui->prog_monster->show();
    }
}

void MainWindow::on_btn_left_clicked()
{
    zorkUL.processCommand(Command("go","west"));
    updateRoomItemsView();
    updateProgressBarState();
    this->repaint();

//    auto curRoom = this->zorkUL.getCurrentRoom();
//    this->zorkUL.go("west");
//    if(curRoom!=zorkUL.getCurrentRoom()){
//        updateRoomItemsView();
//        updateProgressBarState();
//        this->repaint();
//    }
}

void MainWindow::on_btn_down_clicked()
{
    zorkUL.processCommand(Command("go","south"));
    updateRoomItemsView();
    updateProgressBarState();
    this->repaint();

//    auto curRoom = this->zorkUL.getCurrentRoom();
//    this->zorkUL.go("south");
//    if(curRoom!=zorkUL.getCurrentRoom()){
//        updateRoomItemsView();
//        updateProgressBarState();
//        this->repaint();
//    }
}

void MainWindow::on_btn_right_clicked()
{
    zorkUL.processCommand(Command("go","east"));
    updateRoomItemsView();
    updateProgressBarState();
    this->repaint();

//    auto curRoom = this->zorkUL.getCurrentRoom();
//    this->zorkUL.go("east");
//    if(curRoom!=zorkUL.getCurrentRoom()){
//        updateRoomItemsView();
//        updateProgressBarState();
//        this->repaint();
//    }
}

void MainWindow::on_btn_up_clicked()
{
    zorkUL.processCommand(Command("go","north"));
    updateRoomItemsView();
    updateProgressBarState();
    this->repaint();

//    auto curRoom = this->zorkUL.getCurrentRoom();
//    this->zorkUL.go("north");
//    if(curRoom!=zorkUL.getCurrentRoom()){
//        updateRoomItemsView();
//        updateProgressBarState();
//        this->repaint();
//    }
}

void MainWindow::on_btn_pick_clicked()
{
    int idx = -1;
    int count = ui->lst_items->count();
    for(int i=0; i<count;i++) {
        auto item = ui->lst_items->item(i);
         if(item->isSelected()){
            idx = i;
        }
    }
    if(idx>-1){
        zorkUL.processCommand(Command("take",to_string(idx)));
        this->updateRoomItemsView();
        this->updateInventory();

    }

}

void MainWindow::on_btn_drop_clicked()
{
    int idx = -1;
    int count = ui->lst_inventory->count();
    for(int i=0; i<count;i++) {
        auto item = ui->lst_inventory->item(i);
        if(item->isSelected()){
            idx = i;
        }
    }
    if(idx>-1){
        zorkUL.processCommand(Command("put",to_string(idx)));
        this->updateRoomItemsView();
        this->updateInventory();

    }
}

void MainWindow::on_btn_attack_clicked()
{
    Monster* monster = zorkUL.getCurrentRoom()->getMonster();
    if(monster!=NULL) {
        zorkUL.processCommand(Command("attack",""));
        updateProgressBarState();
        if(zorkUL.getPlayer()->getHealthy()==0) {
            QMessageBox::about(NULL, "Hint", "You Dead!");
            this->close();
        }
        this->repaint();
    }
    if(zorkUL.isGameOver()) {
        QMessageBox::about(NULL, "Hint", "You Win!");
        this->close();
    }

}


void MainWindow::on_menu_exit_triggered()
{
    this->close();
}

void MainWindow::on_btn_teleport_clicked()
{
    zorkUL.processCommand(Command("teleport",""));
    this->repaint();
    this->updateRoomItemsView();
    this->updateInventory();
}
void MainWindow::on_pushButton_clicked()
{
    zorkUL.processCommand(Command("quit",""));

    QMessageBox::about(NULL, "Titlt","Now, You have been transported the initial room.\n");
}

void MainWindow::on_btn_info_clicked()
{
    QMessageBox::about(NULL, "Rules", "1、Controlling the move of player by clicking 'up''left''roght''down'\n"
                                     "2、If there are equipment in the room, player can pick up it intp inventory\n"
                                     "3、Player can drop their equipment on the room where the player is standing\n"
                                     "4、Clicking the teleport can be transported to a random room\n"
                                     "5、Clicking the quit, player will go back to the initial room\n"
                                     "6、Clicking the attrack can hurt the monster, but the monster also can hurt the player\n"
                                     "7、If there is no blood to the monster, the player is win, else the player is lose\n");

}


