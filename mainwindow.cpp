#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parametricdataentry.h"
#include <emscripten/emscripten.h>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , combatInventoryWindow(new Combatinventory())
    , parametricDataEntryWindow(new ParametricDataEntry())
{
    ui->setupUi(this);
    qDebug() << "HERE IS THE OUTPUT";
    combatInventoryWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    parametricDataEntryWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    // Ensure defaultStyleSheet is saved in case needed later
    defaultStyleSheet = qApp->styleSheet();

    // Full stylesheet content
    QString styleSheet = R"(
QCheckBox::indicator {
    width: 60px;
    height: 30px;
}

QCheckBox::indicator:checked {
    image: url(":/Icons/switch-on.png");
}

QCheckBox::indicator:unchecked {
    image: url(":/Icons/switch-off.png");
}

QLabel {
    background-color: rgb(66, 81, 60); /* Army green */
    border-color: rgb(98, 99, 94);
    border: 0px solid;
    color: rgb(238, 233, 23);
    font: 700 9pt 'Segoe UI';
}

QLabel#aRowFour,
QLabel#aRowOne,
QLabel#aRowTh
ree,
QLabel#aRowTwo,
QLabel#b2,
QLabel#b3,
QLabel#b3a,
QLabel#essm,
QLabel#sm2,
QLabel#nsm,
QLabel#stingRay,
QLabel#inv,
QLabel#port,
QLabel#stbd,
QLabel#port_2,
QLabel#stbd_2 {
    background-color: rgb(66, 81, 60); /* Army green */
    border-color: rgb(98, 99, 94);
    border: 0px solid;
    color: rgb(238, 233, 23);
    font: 700 9pt 'Segoe UI';
}

QWidget#centralwidget {
    background-color: rgb(66, 81, 60); /* Army green */
}

QWidget#centralwidgetMain,
QWidget#centralwidgetPDE {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 10px solid;
    border-color: rgb(200, 200, 200);
}

QPushButton {
    color: rgb(238, 233, 23);
    font: 700 9pt 'Segoe UI';
    background-color: rgb(66, 81, 60); /* Army green */
    padding: 5px;
    border: 2px inset;
    border-color: rgb(153, 160, 174);
    border-bottom-color: rgb(19, 25, 39);
    border-right-color: rgb(19, 25, 39);
}

QPushButton#positMapBtn,
QPushButton#markMapBtn,
QPushButton#positMapBtn {
    image: url(":/Icons/earth.png");
}

QPushButton:pressed {
    color: rgb(238, 233, 23);
    font: 700 9pt 'Segoe UI';
    background-color: rgb(66, 81, 60); /* Army green */
    padding: 5px;
    border: 2px inset;
    border-color: rgb(19, 25, 39);
    border-bottom-color: grey;
    border-right-color: gray;
}

QPushButton:disabled {
    color: rgb(223, 203, 142);
    font: 700 9pt 'Segoe UI';
    background-color: rgb(114, 114, 126);
}

QLineEdit {
    font: 700 9pt 'Segoe UI';
    background-color: rgb(41, 41, 39);
    color: rgb(255, 255, 255);
    border: 2px inset;
    border-color: rgb(19, 25, 39);
    border-bottom-color: gray;
    border-right-color: gray;
}

QGroupBox#fwdGroupBox_2 {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 3px solid;
    border-bottom-width: 3px solid;
    border-color: rgb(200, 200, 200);
}

QGroupBox#fwdDataGroupBox,
QGroupBox#b2GroupBox,
QGroupBox#b3GroupBox,
QGroupBox#b3aGroupBox,
QGroupBox#essmGroupBox,
QGroupBox#fwdInvEnblGroupBox,
QGroupBox#fwdLabelGroupBox,
QGroupBox#nsmDataGroupBox,
QGroupBox#portNsmGroupBox,
QGroupBox#portStbdGroupBox,
QGroupBox#portStbdGroupBox_2,
QGroupBox#stingRayGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 0px solid;
    border-color: rgb(98, 99, 94);
}

QGroupBox#gunGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 3px solid;
    border-top: 2px solid;
    border-left: 2px solid;
    border-color: rgb(200, 200, 200);
}

QGroupBox#nsmGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 3px solid;
    border-top: 2px solid;
    border-left: 3px solid;
    border-color: rgb(200, 200, 200);
}

QGroupBox#groupBox_14,
QGroupBox#gunScrollAreaGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 0px solid;
    border-color: rgb(200, 200, 200);
}

QGroupBox#sltGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border: 3px solid;
    border-top: 2px solid;
    border-right: 3px solid;
    border-bottom: 3px solid;
    border-color: rgb(200, 200, 200);
}

#buttonBox,
#navBox,
#positSourceBox,
#trueHeadingBox,
#waterDepthBox,
#windSourceBox,
#gunGroupBox,
#nsmGroupBox,
#sltGroupBox {
    background-color: rgb(66, 81, 60); /* Army green */
    border-top: 2px solid;
    border-right: 3px solid;
    border-bottom: 3px solid;
    border-color: rgb(200, 200, 200);
}

QRadioButton {
    color: rgb(238, 233, 23);
}

QRadioButton::indicator {
    width: 10px;
    height: 10px;
    border-radius: 7px;
}

QRadioButton::indicator::unchecked {
    border: 3px solid;
    2px 0;
}

QSlider::handle:horizontal {
    width: 12px;
    height: 20px;
    background-color: rgb(200, 200, 200);
    margin: -6px 0;
}

QLabel344 {
    background-color: rgb(66, 81, 60); /* Army green */
    color: rgb(238, 233, 23);
    background: rgb(41, 41, 39);
    border-color: rgb(98, 99, 94);
}

QScrollArea QWidget {
    background: rgb(41, 41, 39);
}

QScrollBar {
    background-color: rgb(200, 200, 200);
    border: 2px solid;
    border-color: rgb(200, 200, 200);
}

QScrollBar::handle {
    background: rgb(98, 99, 94);
    border-top: 2px solid;
    border-bottom: 2px solid;
    border-color: rgb(200, 200, 200);
    margin: 10px;
}

QScrollBar::groove {
    background: rgb(98, 99, 94);
    border: 1px solid;
    border-color: rgb(200, 200, 200);
}

QScrollBar::sub-line {
    background: rgb(98, 99, 94);
    border: 1px solid;
    border-color: rgb(200, 200, 200);
}

QScrollBar::add-line {
    background: rgb(98, 99, 94);
    border: 1px solid;
    border-color: rgb(200, 200, 200);
}

QScrollBar::up-arrow,
QScrollBar::down-arrow {
    border: 1px solid;
    border-color: rgb(200, 200, 200);
}

#ammoTypeEdit,
#roundsEdit {
    font: 700 9pt "Segoe UI";
    color: rgb(255, 255, 255);
    border: 0px;
    background-color: rgb(41, 41, 39);
}

#positNorth,
#positSouth,
#positEast,
#positWest,
#markNorth,
#markSouth,
#markEast,
#markWest,
#magEast,
#magWest {
    color: rgb(255, 255, 255);
}

QLabel#gun,
QLabel#ammoType,
QLabel#rounds,
QLabel#nsmSemicolon,
QLabel#semicolon,
QLabel#slt {
    background-color: rgb(66, 81, 60); /* Army green */
    color: rgb(238, 233, 23);
    font: 700 9pt "Segoe UI";
}

    )";

    // Set the full stylesheet
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::on_combatButton_clicked()
{
    combatInventoryWindow->resize(800, 600); // Set size as needed
    combatInventoryWindow->show();
}

void MainWindow::on_dataButton_clicked()
{
    parametricDataEntryWindow->resize(650, 900); // Set size as needed
    parametricDataEntryWindow->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete combatInventoryWindow;
    delete parametricDataEntryWindow;
}

