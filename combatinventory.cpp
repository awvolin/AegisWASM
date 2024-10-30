#include "combatinventory.h"
#include "ui_combatinventory.h"
#include <QWebSocket>
#include <QVector> // Ensure to include QVector

Combatinventory::Combatinventory(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Combatinventory)
    , socket(new QWebSocket())
{
    ui->setupUi(this);

    // WebSocket code
    QUrl url(QStringLiteral("ws://localhost:8765"));  // Adjust the URL if needed
    socket->open(url);  // Open WebSocket connection

    // Handle WebSocket disconnection
    connect(socket, &QWebSocket::disconnected, this, &Combatinventory::onWebSocketDisconnected);

    QRect screenSize = QApplication::primaryScreen()->availableGeometry();

    int screenHeight = screenSize.height();

    this->setMaximumSize(551, screenHeight);

    resize(551, screenHeight);
    int count = 0;



    timerId = startTimer(5000);

    connect(ui->ESSMinv, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));
    connect(ui->ESSMenbl, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));

    connect(ui->B2inv, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));
    connect(ui->B2enbl, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));

    connect(ui->B3inv, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));
    connect(ui->B3enbl, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));

    connect(ui->B3Ainv, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));
    connect(ui->B3Aenbl, SIGNAL(textChanged(QString)), this, SLOT(fwdChangeAlert()));


    connect(ui->stingStbd, SIGNAL(textChanged(QString)), this, SLOT(stingChangeAlert()));
    connect(ui->stingPort, SIGNAL(textChanged(QString)), this, SLOT(stingChangeAlert()));


    connect(ui->nsmPort, SIGNAL(textChanged(QString)), this, SLOT(nsmChangeAlert()));
    connect(ui->nsmStbd, SIGNAL(textChanged(QString)), this, SLOT(nsmChangeAlert()));


    connect(ui->gunEdit, SIGNAL(textChanged(QString)), this, SLOT(gunChangeAlert()));

    connect(ui->ammoTypeEdit, SIGNAL(textChanged()), this, SLOT(ammoTypeChangeAlert()));

    connect(ui->roundsEdit, SIGNAL(textChanged()), this, SLOT(roundsChangeAlert()));
}
void Combatinventory::onWebSocketDisconnected() {
    qDebug() << "WebSocket disconnected!";
}

Combatinventory::~Combatinventory()
{
    killTimer(timerId);
    delete ui;
}


void Combatinventory::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event); // Suppress unused variable warning

    // Clear previous data in newArray
    std::fill(std::begin(newArray), std::end(newArray), "");

    // Send SQL command to the WebSocket server to fetch CombatSystemInventory items
    if (socket->isValid()) {
        // Send the SQL command
        socket->sendTextMessage("%SELECT * FROM CombatSystemInventory");

        // Define a lambda to handle the response
        connect(socket, &QWebSocket::textMessageReceived, this, [this](const QString &message) {
            // Parse the JSON response
            QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
            if (doc.isArray()) {
                QJsonArray jsonArray = doc.array();

                // Reset newArray
                std::fill(std::begin(newArray), std::end(newArray), "");

                // Populate newArray with the numbers from the JSON response
                for (int i = 0; i < jsonArray.size() && i < 15; ++i) {
                    QJsonArray itemArray = jsonArray[i].toArray();
                    if (itemArray.size() == 2) {
                        newArray[i] = itemArray[0].toString(); // Store the first value (the number)
                    }
                }

                // Set static values
                newArray[12] = "Not Released"; // Keep this as you mentioned
                newArray[14] = "1,2,3"; // Keep this as you mentioned

                // Debug output
                qDebug() << "Combat System Inventory items:" << newArray;

                // Update the database with the fetched values
//                QSqlQuery updateQuery;
//                for (int i = 0; i < 15; i++) {
//                    QString updateSql = QString("UPDATE CombatSystemInventory SET DisplayItem = '%1' WHERE RowID = %2")
//                                            .arg(newArray[i])
//                                            .arg(i + 1);

//                    if (!updateQuery.exec(updateSql)) {
//                        // Handle update errors
//                        qDebug() << "Failed to update value in database for RowID" << (i + 1);
//                        qDebug() << updateQuery.lastError().text();
//                    }
//                }

                // Process ammo types
                QString dbAmmoTypes = newArray[13];
                QString displayAmmoTypes;
                QStringList ammoTypesStringList = dbAmmoTypes.split(",");

                for (const QString &ammo : ammoTypesStringList) {
                    displayAmmoTypes += ammo + "\n";
                }
                ui->ammoTypeEdit->setText(displayAmmoTypes);

                // Process rounds
                QString dbRounds = newArray[14];
                QString displayRounds;
                QStringList roundsStringList = dbRounds.split(",");

                for (const QString &round : roundsStringList) {
                    displayRounds += round + "\n";
                }
                ui->roundsEdit->setText(displayRounds);

                // Center align text in roundsEdit
                QTextCursor cursor = ui->roundsEdit->textCursor();
                QTextBlockFormat format = cursor.blockFormat();
                format.setAlignment(Qt::AlignHCenter);
                cursor.select(QTextCursor::Document);
                cursor.setBlockFormat(format);

                // Update the UI with the fetched values
                ui->ESSMinv->setText(newArray[0]);
                ui->ESSMenbl->setText(newArray[1]);
                ui->B2inv->setText(newArray[2]);
                ui->B2enbl->setText(newArray[3]);
                ui->B3inv->setText(newArray[4]);
                ui->B3enbl->setText(newArray[5]);
                ui->B3Ainv->setText(newArray[6]);
                ui->B3Aenbl->setText(newArray[7]);
                ui->stingPort->setText(newArray[8]);
                ui->stingStbd->setText(newArray[9]);
                ui->nsmPort->setText(newArray[10]);
                ui->nsmStbd->setText(newArray[11]);
                ui->gunEdit->setText(newArray[12]);
            } else {
                qDebug() << "Received unexpected response format";
            }
        });
    } else {
        qDebug() << "WebSocket is not valid";
    }
}

void Combatinventory::fwdChangeAlert(){


    if(newArray[0]!=dbArray[0] || newArray[1]!=dbArray[1]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->essmGroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[0] = newArray[0];
        dbArray[1] = newArray[1];
    }
    if(newArray[2]!=dbArray[2] || newArray[3]!=dbArray[3]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->b2GroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[2] = newArray[2];
        dbArray[3] = newArray[3];
    }
    if(newArray[4]!=dbArray[4] || newArray[5]!=dbArray[5]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->b3GroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[4] = newArray[4];
        dbArray[5] = newArray[5];
    }
    if(newArray[6]!=dbArray[6] || newArray[7]!=dbArray[7]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->b3aGroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[6] = newArray[6];
        dbArray[7] = newArray[7];
    }

}


void Combatinventory::stingChangeAlert(){
    if(newArray[8]!=dbArray[8] && newArray[9]!=dbArray[9]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->stingRayGroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[8] = newArray[8];
        dbArray[9] = newArray[9];
    }

    else if(newArray[8]!=dbArray[8]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->stingPort, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[8] = newArray[8];
    }

    else if(newArray[9]!=dbArray[9]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->stingStbd, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[9] = newArray[9];
    }
}


void Combatinventory::nsmChangeAlert(){
    if(newArray[10]!=dbArray[10] && newArray[11]!=dbArray[11]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->nsmDataGroupBox, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[10] = newArray[10];
        dbArray[11] = newArray[11];
    }

    else if(newArray[10]!=dbArray[10]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->nsmPort, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[10] = newArray[10];
    }

    else if(newArray[11]!=dbArray[11]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->nsmStbd, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[11] = newArray[11];
    }
}


void Combatinventory::gunChangeAlert(){
    if(newArray[12]!=dbArray[12]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->gunEdit, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[12] = newArray[12];
    }
}

void Combatinventory::ammoTypeChangeAlert(){
    if(newArray[13]!=dbArray[13]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->ammoTypeEdit, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[13] = newArray[13];
    }
}

void Combatinventory::roundsChangeAlert(){
    if(newArray[14]!=dbArray[14]){
        QPropertyAnimation *animation = new QPropertyAnimation(ui->roundsEdit, "border");
        animation->setDuration(10000);
        animation->setKeyValueAt(0, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.05, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.1, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.15, QColor(238, 233, 23, 0));
        animation->setKeyValueAt(0.2, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(0.6, QColor(238, 233, 23, 255));
        animation->setKeyValueAt(1, QColor(238, 233, 23, 0));
        animation->start();

        dbArray[14] = newArray[14];
    }
}


void Combatinventory::sizeRefresh(){
    int currentWidth = ui->centralwidget->width();
    int currentHeight = ui->centralwidget->height();

    int centerGui = (currentWidth/2)-275;

    ui->csiGroupBox->setGeometry(centerGui, 0, 551, currentHeight);

    int fwdHeight = ((currentHeight-20)/2);
    ui->fwdGroupBox->setGeometry(10, 10, 531, fwdHeight);
    ui->fwdGroupBox_2->setGeometry(10, 10, 531, fwdHeight);
    ui->fwdGroupBox_2->move(0,0);

    int sltHeight = ((currentHeight-20)/4);
    ui->sltGroupBox->setGeometry(10, 10+fwdHeight, 251, sltHeight);

    int nsmHeight = ((currentHeight-14)/4);
    ui->nsmGroupBox->setGeometry(10, 10+fwdHeight+sltHeight, 251, nsmHeight);

    ui->portStbdGroupBox->setGeometry(119, 10, 109, 26);
    ui->nsmDataGroupBox->setGeometry(119, 36, 109, 29);
    ui->nsm->setGeometry(20, 36, 65, 25);
    ui->semicolon->setGeometry(92, 36, 20, 25);


    int gunHeight = ((currentHeight-18)/2);
    ui->gunGroupBox->setGeometry(260, 10+fwdHeight, 281, gunHeight);
}


void Combatinventory::resizeEvent(QResizeEvent *event)
{
    sizeRefresh();
    QWidget::resizeEvent(event);
}
