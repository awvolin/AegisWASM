#include "parametricdataentry.h"
#include "animatedqgroupbox.h"
#include "ui_parametricdataentry.h"

ParametricDataEntry::ParametricDataEntry(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParametricDataEntry)
    , socket(new QWebSocket())
{

    ui->setupUi(this);
    qApp->installEventFilter(this);

    // WebSocket code
    QUrl url(QStringLiteral("ws://localhost:8765"));  // Adjust the URL if needed
    socket->open(url);  // Open WebSocket connection

    // Handle WebSocket disconnection
    connect(socket, &QWebSocket::disconnected, this, &ParametricDataEntry::onWebSocketDisconnected);
    initializeDatabase();


    this->move(10,10);  //Position window
    // Signal & Slot Connection===============
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(resetButtonClicked()));
    connect(ui->applyButton,SIGNAL(clicked()),this,SLOT(fillSlots()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(fillSlots()));

    connect(ui->speedSlider,SIGNAL(valueChanged(int)),this,SLOT(speedSlider()));
    connect(ui->trueDirSlider,SIGNAL(valueChanged(int)),this,SLOT(trueDirSlider()));
    connect(ui->relDirSlider,SIGNAL(valueChanged(int)),this,SLOT(relDirSlider()));
    connect(ui->trueSpeedSlider,SIGNAL(valueChanged(int)),this,SLOT(trueSpeedSlider()));
    connect(ui->relSpeedSlider,SIGNAL(valueChanged(int)),this,SLOT(relSpeedSlider()));
    connect(ui->headingSlider,SIGNAL(valueChanged(int)),this,SLOT(headingSlider()));
    connect(ui->waterDepthSlider,SIGNAL(valueChanged(int)),this,SLOT(waterDepthSlider()));
    connect(ui->surfWaterTempSlider,SIGNAL(valueChanged(int)),this,SLOT(surfWaterTempSlider()));
    connect(ui->setSlider,SIGNAL(valueChanged(int)),this,SLOT(setSlider()));
    connect(ui->driftSlider,SIGNAL(valueChanged(int)),this,SLOT(driftSlider()));
    connect(ui->positMapBtn,SIGNAL(clicked()),this,SLOT(positMap()));
    connect(ui->markMapBtn,SIGNAL(clicked()),this,SLOT(markMap()));

    connect(ui->trueHeadingInput,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingCheck()));
    connect(ui->speedInput,SIGNAL(textChanged(QString)),this,SLOT(speedCheck()));


    connect(ui->positLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positLat1Check()));
    connect(ui->positLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positLat2Check()));
    connect(ui->positLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positLat3Check()));
    connect(ui->positLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positLatCheck()));
    connect(ui->positLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positLatCheck()));
    connect(ui->positLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positLatCheck()));
    connect(ui->positNorth,SIGNAL(clicked()),this,SLOT(positNorth()));
    connect(ui->positSouth,SIGNAL(clicked()),this,SLOT(positSouth()));
    connect(ui->positNorth,SIGNAL(clicked()),this,SLOT(positLatCheck()));
    connect(ui->positSouth,SIGNAL(clicked()),this,SLOT(positLatCheck()));


    connect(ui->positLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positLong1Check()));
    connect(ui->positLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positLong2Check()));
    connect(ui->positLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positLong3Check()));
    connect(ui->positLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positLongCheck()));
    connect(ui->positLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positLongCheck()));
    connect(ui->positLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positLongCheck()));
    connect(ui->positEast,SIGNAL(clicked()),this,SLOT(positEast()));
    connect(ui->positWest,SIGNAL(clicked()),this,SLOT(positWest()));
    connect(ui->positEast,SIGNAL(clicked()),this,SLOT(positLongCheck()));
    connect(ui->positWest,SIGNAL(clicked()),this,SLOT(positLongCheck()));


    connect(ui->markTimeInput1,SIGNAL(textChanged(QString)),this,SLOT(markTime1Check()));
    connect(ui->markTimeInput2,SIGNAL(textChanged(QString)),this,SLOT(markTime2Check()));

    connect(ui->markLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(markLat1Check()));
    connect(ui->markLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(markLat2Check()));
    connect(ui->markLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(markLat3Check()));
    connect(ui->markLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(markLatCheck()));
    connect(ui->markLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(markLatCheck()));
    connect(ui->markLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(markLatCheck()));
    connect(ui->markNorth,SIGNAL(clicked()),this,SLOT(markNorth()));
    connect(ui->markSouth,SIGNAL(clicked()),this,SLOT(markSouth()));
    connect(ui->markNorth,SIGNAL(clicked()),this,SLOT(markLatCheck()));
    connect(ui->markSouth,SIGNAL(clicked()),this,SLOT(markLatCheck()));


    connect(ui->markLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(markLong1Check()));
    connect(ui->markLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(markLong2Check()));
    connect(ui->markLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(markLong3Check()));
    connect(ui->markLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(markLongCheck()));
    connect(ui->markLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(markLongCheck()));
    connect(ui->markLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(markLongCheck()));
    connect(ui->markEast,SIGNAL(clicked()),this,SLOT(markEast()));
    connect(ui->markWest,SIGNAL(clicked()),this,SLOT(markWest()));
    connect(ui->markEast,SIGNAL(clicked()),this,SLOT(markLongCheck()));
    connect(ui->markWest,SIGNAL(clicked()),this,SLOT(markLongCheck()));


    connect(ui->trueDirectionInput,SIGNAL(textChanged(QString)),this,SLOT(trueDirCheck()));
    connect(ui->trueSpeedInput,SIGNAL(textChanged(QString)),this,SLOT(trueSpeedCheck()));
    connect(ui->relDirectionInput,SIGNAL(textChanged(QString)),this,SLOT(relDirCheck()));
    connect(ui->relSpeedInput,SIGNAL(textChanged(QString)),this,SLOT(relSpeedCheck()));
    connect(ui->waterDepthInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthCheck()));
    connect(ui->surfaceWaterTempInput,SIGNAL(textChanged(QString)),this,SLOT(surfWaterTempCheck()));
    connect(ui->setInput,SIGNAL(textChanged(QString)),this,SLOT(setCheck()));
    connect(ui->driftInput,SIGNAL(textChanged(QString)),this,SLOT(driftCheck()));


    connect(ui->magVarCorrInput,SIGNAL(textChanged(QString)),this,SLOT(magVarCorrCheck()));
    connect(ui->magEast,SIGNAL(clicked()),this,SLOT(magEast()));
    connect(ui->magWest,SIGNAL(clicked()),this,SLOT(magWest()));
    connect(ui->magEast,SIGNAL(clicked()),this,SLOT(magVarCorrCheck()));
    connect(ui->magWest,SIGNAL(clicked()),this,SLOT(magVarCorrCheck()));

    connect(ui->trueHeadingMin,&QPushButton::clicked,this, [this]{minimization(1); });
    connect(ui->positSourceMin,&QPushButton::clicked,this, [this]{minimization(2); });
    connect(ui->windSourceMin,&QPushButton::clicked,this, [this]{minimization(3); });
    connect(ui->waterDepthMin,&QPushButton::clicked,this, [this]{minimization(4); });


    connect(ui->trueHeadingInput,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->speedInput,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positNorth,SIGNAL(clicked()),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positSouth,SIGNAL(clicked()),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positEast,SIGNAL(clicked()),this,SLOT(trueHeadingInputAlert()));
    connect(ui->positWest,SIGNAL(clicked()),this,SLOT(trueHeadingInputAlert()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(trueHeadingInputAlert()));

    connect(ui->markTimeInput1,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markTimeInput2,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markLatitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markLatitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markLatitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markNorth,SIGNAL(clicked()),this,SLOT(positSourceInputAlert()));
    connect(ui->markSouth,SIGNAL(clicked()),this,SLOT(positSourceInputAlert()));
    connect(ui->markLongitudeInput1,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markLongitudeInput2,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markLongitudeInput3,SIGNAL(textChanged(QString)),this,SLOT(positSourceInputAlert()));
    connect(ui->markEast,SIGNAL(clicked()),this,SLOT(positSourceInputAlert()));
    connect(ui->markWest,SIGNAL(clicked()),this,SLOT(positSourceInputAlert()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(positSourceInputAlert()));


    connect(ui->trueDirectionInput,SIGNAL(textChanged(QString)),this,SLOT(windSourceInputAlert()));
    connect(ui->trueSpeedInput,SIGNAL(textChanged(QString)),this,SLOT(windSourceInputAlert()));
    connect(ui->relDirectionInput,SIGNAL(textChanged(QString)),this,SLOT(windSourceInputAlert()));
    connect(ui->relSpeedInput,SIGNAL(textChanged(QString)),this,SLOT(windSourceInputAlert()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(windSourceInputAlert()));


    connect(ui->waterDepthInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthInputAlert()));
    connect(ui->surfaceWaterTempInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthInputAlert()));
    connect(ui->setInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthInputAlert()));
    connect(ui->driftInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthInputAlert()));
    connect(ui->magVarCorrInput,SIGNAL(textChanged(QString)),this,SLOT(waterDepthInputAlert()));
    connect(ui->magEast,SIGNAL(clicked()),this,SLOT(waterDepthInputAlert()));
    connect(ui->magWest,SIGNAL(clicked()),this,SLOT(waterDepthInputAlert()));
    connect(ui->resetButton,SIGNAL(clicked()),this,SLOT(waterDepthInputAlert()));

    connect(ui->sec1Reset,SIGNAL(clicked()),this,SLOT(sec1Reset()));
    connect(ui->sec2Reset,SIGNAL(clicked()),this,SLOT(sec2Reset()));
    connect(ui->sec3Reset,SIGNAL(clicked()),this,SLOT(sec3Reset()));
    connect(ui->sec4Reset,SIGNAL(clicked()),this,SLOT(sec4Reset()));
    // end Signal and Slots

    // initialize tooltip=================
    m_tip = new MyToolTip(this);
    m_tip->hide();

}

void ParametricDataEntry::initializeDatabase() {
    // Wait for the socket to connect before sending the message
    connect(socket, &QWebSocket::connected, this, [this]() {

        // Send request to the WebSocket server
        socket->sendTextMessage("%SELECT * FROM ParametricDataEntry");

        // Clear previous data in dbArray
        std::fill(std::begin(dbArray), std::end(dbArray), "");

        // Define a lambda to handle the response
        connect(socket, &QWebSocket::textMessageReceived, this, [this](const QString &message) {
            qDebug() << "Received message:" << message; // Log the received message

            // Parse the JSON response
            QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
            if (doc.isArray()) {

                QJsonArray jsonArray = doc.array();

                // Populate dbArray with data from the JSON response
                std::fill(std::begin(dbArray), std::end(dbArray), "");
                for (int i = 0; i < jsonArray.size() && i < 35; ++i) {
                    QJsonArray itemArray = jsonArray[i].toArray();
                    qDebug() << itemArray.size();
                    if (itemArray.size() == 2) {
                        dbArray[i] = itemArray[0].toString(); // Store the first value (the number)
                        qDebug() << "dbArray[" << i << "] = " << dbArray[i]; // Print the value
                    }

                }


                // Update UI with the fetched values
                ui->trueHeadingEdit->setText(dbArray[0]);
                ui->speedEdit->setText(dbArray[1]);

                ui->positLatitudeEdit1->setText(dbArray[2]);
                ui->positLatitudeEdit2->setText(dbArray[3]);
                ui->positLatitudeEdit3->setText(dbArray[4]);
                ui->positLatitudeDirection->setText(dbArray[5]);

                ui->positLongitudeEdit1->setText(dbArray[6]);
                ui->positLongitudeEdit2->setText(dbArray[7]);
                ui->positLongitudeEdit3->setText(dbArray[8]);
                ui->positLongitudeDirection->setText(dbArray[9]);

                ui->pitchEdit->setText(dbArray[10]);
                ui->rollEdit->setText(dbArray[11]);

                ui->positSourceEdit->setText(dbArray[12]);
                ui->positResetEdit->setText(dbArray[13]);

                ui->markTimeEdit1->setText(dbArray[14]);
                ui->markTimeEdit2->setText(dbArray[15]);

                ui->markLatitudeEdit1->setText(dbArray[16]);
                ui->markLatitudeEdit2->setText(dbArray[17]);
                ui->markLatitudeEdit3->setText(dbArray[18]);
                ui->markLatitudeDirection->setText(dbArray[19]);

                ui->markLongitudeEdit1->setText(dbArray[20]);
                ui->markLongitudeEdit2->setText(dbArray[21]);
                ui->markLongitudeEdit3->setText(dbArray[22]);
                ui->markLongitudeDirection->setText(dbArray[23]);

                ui->windSourceEdit->setText(dbArray[24]);
                ui->trueDirectionEdit->setText(dbArray[25]);
                ui->trueSpeedEdit->setText(dbArray[26]);
                ui->relDirectionEdit->setText(dbArray[27]);
                ui->relSpeedEdit->setText(dbArray[28]);

                ui->waterDepthEdit->setText(dbArray[29]);
                ui->surfaceWaterTempEdit->setText(dbArray[30]);
                ui->setEdit->setText(dbArray[31]);
                ui->driftEdit->setText(dbArray[32]);

                ui->magVarCorrEdit->setText(dbArray[33]);
                ui->magVarrCorrDirection->setText(dbArray[34]);

                // Disable reset buttons
                ui->sec1Reset->setEnabled(false);
                ui->sec2Reset->setEnabled(false);
                ui->sec3Reset->setEnabled(false);
                ui->sec4Reset->setEnabled(false);

                // Call reset function if needed
                resetButtonClicked();
            }
        });
    });
}





void ParametricDataEntry::onWebSocketDisconnected() {
    qDebug() << "WebSocket disconnected!";
}


ParametricDataEntry::~ParametricDataEntry()
{
    delete ui;
}

// Change top right expand/collapse button, enable section reset when edited=============
void ParametricDataEntry::trueHeadingInputAlert(){
    if(ui->trueHeadingInput->text()!="" || ui->speedInput->text()!="" ||
        ui->positLatitudeInput1->text()!="" || ui->positLatitudeInput2->text()!="" ||
        ui->positLatitudeInput3->text()!="" || positLatDirBool == true ||
        ui->positLongitudeInput1->text()!="" || ui->positLongitudeInput2->text()!="" ||
        ui->positLongitudeInput3->text()!="" || positLongDirBool == true){


        ui->trueHeadingMin->setStyleSheet("QPushButton {"
                                          "color: rgb(238, 233, 23);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px solid;"
                                          "border-color: rgb(238, 233, 23);"
                                          "}");
        ui->sec1Reset->setEnabled(true);
        if (      ui->positLatitudeInput1->text()!="" || ui->positLatitudeInput2->text()!="" ||
            ui->positLatitudeInput3->text()!="" || positLatDirBool == true ||
            ui->positLongitudeInput1->text()!="" || ui->positLongitudeInput2->text()!="" ||
            ui->positLongitudeInput3->text()!="" || positLongDirBool == true)

        {
            ui->positMapBtn->setStyleSheet("QPushButton {"
                                           "font: 700 12pt 'Segoe UI';"
                                           "border: 2px inset;"
                                           "color: rgb(238, 233, 23);"
                                           "border: 2px solid;"
                                           "border-color: rgb(238, 233, 23);"
                                           "}");
        }
    }
    else{
        ui->trueHeadingMin->setStyleSheet("QPushButton {"
                                          "color: rgb(200, 200, 200);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px inset;"
                                          "border-color: rgb(153, 160, 174);"
                                          "border-bottom-color: rgb(19, 25, 39);"
                                          "border-right-color: rgb(19, 25, 39);"
                                          "}"
                                          "QPushButton::pressed {"
                                          "color: rgb(200, 200, 200);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px inset;"
                                          "border-color: rgb(19, 25, 39);"
                                          "border-bottom-color: gray;"
                                          "border-right-color: gray;"
                                          "}");
        ui->sec1Reset->setEnabled(false);
        ui->positMapBtn->setStyleSheet("QPushButton {"
                                       "font: 700 12pt 'Segoe UI';"
                                       "border: 2px inset;"
                                       "border-color: rgb(153, 160, 174);"
                                       "border-bottom-color: rgb(19, 25, 39);"
                                       "border-right-color: rgb(19, 25, 39);"
                                       "}"
                                       "QPushButton::pressed {"
                                       "font: 700 12pt 'Segoe UI';"
                                       "border: 2px inset;"
                                       "border-color: rgb(19, 25, 39);"
                                       "border-bottom-color: gray;"
                                       "border-right-color: gray;"
                                       "}");
    }
}

void ParametricDataEntry::positSourceInputAlert(){
    if(ui->markTimeInput1->text()!="" || ui->markTimeInput2->text()!="" ||
        ui->markLatitudeInput1->text()!="" || ui->markLatitudeInput2->text()!="" ||
        ui->markLatitudeInput3->text()!="" || markLatDirBool == true ||
        ui->markLongitudeInput1->text()!="" || ui->markLongitudeInput2->text()!="" ||
        ui->markLongitudeInput3->text()!="" || markLongDirBool == true){


        ui->positSourceMin->setStyleSheet("QPushButton {"
                                          "color: rgb(238, 233, 23);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px solid;"
                                          "border-color: rgb(238, 233, 23);"
                                          "}");
        ui->markMapBtn->setStyleSheet("QPushButton {"
                                      "font: 700 12pt 'Segoe UI';"
                                      "border: 2px inset;"
                                      "color: rgb(238, 233, 23);"
                                      "border: 2px solid;"
                                      "border-color: rgb(238, 233, 23);"
                                      "}");
        ui->sec2Reset->setEnabled(true);
    }
    else{
        ui->positSourceMin->setStyleSheet("QPushButton {"
                                          "color: rgb(200, 200, 200);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px inset;"
                                          "border-color: rgb(153, 160, 174);"
                                          "border-bottom-color: rgb(19, 25, 39);"
                                          "border-right-color: rgb(19, 25, 39);"
                                          "}"
                                          "QPushButton::pressed {"
                                          "color: rgb(200, 200, 200);"
                                          "font: 700 9pt 'Segoe UI';"
                                          "border: 2px inset;"
                                          "border-color: rgb(19, 25, 39);"
                                          "border-bottom-color: gray;"
                                          "border-right-color: gray;"
                                          "}");
        ui->markMapBtn->setStyleSheet("QPushButton {"
                                      "font: 700 12pt 'Segoe UI';"
                                      "border: 2px inset;"
                                      "border-color: rgb(153, 160, 174);"
                                      "border-bottom-color: rgb(19, 25, 39);"
                                      "border-right-color: rgb(19, 25, 39);"
                                      "}"
                                      "QPushButton::pressed {"
                                      "font: 700 12pt 'Segoe UI';"
                                      "border: 2px inset;"
                                      "border-color: rgb(19, 25, 39);"
                                      "border-bottom-color: gray;"
                                      "border-right-color: gray;"
                                      "}");
        ui->sec2Reset->setEnabled(false);
    }
}

void ParametricDataEntry::windSourceInputAlert(){
    if(ui->trueDirectionInput->text()!="" || ui->trueSpeedInput->text()!="" ||
        ui->relDirectionInput->text()!="" || ui->relSpeedInput->text()!=""){


        ui->windSourceMin->setStyleSheet("QPushButton {"
                                         "color: rgb(238, 233, 23);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px solid;"
                                         "border-color: rgb(238, 233, 23);"
                                         "}");
        ui->sec3Reset->setEnabled(true);
    }
    else{
        ui->windSourceMin->setStyleSheet("QPushButton {"
                                         "color: rgb(200, 200, 200);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px inset;"
                                         "border-color: rgb(153, 160, 174);"
                                         "border-bottom-color: rgb(19, 25, 39);"
                                         "border-right-color: rgb(19, 25, 39);"
                                         "}"
                                         "QPushButton::pressed {"
                                         "color: rgb(200, 200, 200);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px inset;"
                                         "border-color: rgb(19, 25, 39);"
                                         "border-bottom-color: gray;"
                                         "border-right-color: gray;"
                                         "}");
        ui->sec3Reset->setEnabled(false);
    }
}

void ParametricDataEntry::waterDepthInputAlert(){
    if(ui->waterDepthInput->text()!="" || ui->surfaceWaterTempInput->text()!="" ||
        ui->setInput->text()!="" || ui->driftInput->text()!="" ||
        ui->magVarCorrInput->text()!="" || magDirBool == true){


        ui->waterDepthMin->setStyleSheet("QPushButton {"
                                         "color: rgb(238, 233, 23);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px solid;"
                                         "border-color: rgb(238, 233, 23);"
                                         "}");
        ui->sec4Reset->setEnabled(true);
    }

    else{
        ui->waterDepthMin->setStyleSheet("QPushButton {"
                                         "color: rgb(200, 200, 200);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px inset;"
                                         "border-color: rgb(153, 160, 174);"
                                         "border-bottom-color: rgb(19, 25, 39);"
                                         "border-right-color: rgb(19, 25, 39);"
                                         "}"
                                         "QPushButton::pressed {"
                                         "color: rgb(200, 200, 200);"
                                         "font: 700 9pt 'Segoe UI';"
                                         "border: 2px inset;"
                                         "border-color: rgb(19, 25, 39);"
                                         "border-bottom-color: gray;"
                                         "border-right-color: gray;"
                                         "}");
        ui->sec4Reset->setEnabled(false);
    }
}
// End notifying edited and enable/disable section reset================

// Calls Reset for all 4 sections when Reset on bottom is cliced======
void ParametricDataEntry::resetButtonClicked(){
    sec1Reset();
    sec2Reset();
    sec3Reset();
    sec4Reset();
}

// Sectional Reset functions ==========================================
void ParametricDataEntry::sec1Reset()
{
    positView.rootContext()->setContextProperty("parametric", this);
    positView.setSource(QUrl::fromLocalFile(":/qml/positqml.qml"));
    double positLat = ui->positLatitudeEdit1->text().toDouble()
                      + ui->positLatitudeEdit2->text().toDouble()/60
                      + ui->positLatitudeEdit3->text().toDouble()/3600;

    double positLong = ui->positLongitudeEdit1->text().toDouble()
                       + ui->positLongitudeEdit2->text().toDouble()/60
                       + ui->positLongitudeEdit3->text().toDouble()/3600;

    QObject *object = positView.rootObject();
    QObject *coord = object->findChild<QObject*>("coord");
    if (coord)
    {
        if (positLatitudeDirection == "S")
            positLat *= -1;
        if (positLongitudeDirection == "W")
            positLong *= -1;
        coord->setProperty("latitude", positLat);
        coord->setProperty("longitude", positLong);
    }
    ui->positNorth->setAutoExclusive(false);
    ui->positSouth->setAutoExclusive(false);
    ui->positNorth->setChecked(false);
    ui->positSouth->setChecked(false);
    ui->positNorth->setAutoExclusive(true);
    ui->positSouth->setAutoExclusive(true);
    positLatDirBool = false;

    ui->positWest->setAutoExclusive(false);
    ui->positEast->setAutoExclusive(false);
    ui->positWest->setChecked(false);
    ui->positEast->setChecked(false);
    ui->positWest->setAutoExclusive(true);
    ui->positEast->setAutoExclusive(true);
    positLongDirBool = false;

    ui->sec1Reset->setEnabled(false);
    ui->trueHeadingInput->setText("");
    ui->speedInput->setText("");
    ui->positLatitudeInput1->setText("");
    ui->positLatitudeInput2->setText("");
    ui->positLatitudeInput3->setText("");
    ui->positLongitudeInput1->setText("");
    ui->positLongitudeInput2->setText("");
    ui->positLongitudeInput3->setText("");
}

void ParametricDataEntry::sec2Reset()
{
    markView.rootContext()->setContextProperty("parametric", this);
    markView.setSource(QUrl::fromLocalFile(":/qml/markqml.qml"));
    double markLat = ui->markLatitudeEdit1->text().toDouble()
                     + ui->markLatitudeEdit2->text().toDouble()/60
                     + ui->markLatitudeEdit3->text().toDouble()/3600;

    double markLong = ui->markLongitudeEdit1->text().toDouble()
                      + ui->markLongitudeEdit2->text().toDouble()/60
                      + ui->markLongitudeEdit3->text().toDouble()/3600;

    QObject *object = markView.rootObject();
    QObject *coord = object->findChild<QObject*>("coord");
    if (coord)
    {
        if (markLatitudeDirection == "S")
            markLat *= -1;
        if (markLongitudeDirection == "W")
            markLong *= -1;
        coord->setProperty("latitude", markLat);
        coord->setProperty("longitude", markLong);
    }
    ui->markLatitudeInput1->setText("");
    ui->markLatitudeInput2->setText("");
    ui->markLatitudeInput3->setText("");
    ui->markLongitudeInput1->setText("");
    ui->markLongitudeInput2->setText("");
    ui->markLongitudeInput3->setText("");
    ui->markTimeInput1->setText("");
    ui->markTimeInput2->setText("");

    ui->markNorth->setAutoExclusive(false);
    ui->markSouth->setAutoExclusive(false);
    ui->markNorth->setChecked(false);
    ui->markSouth->setChecked(false);
    ui->markNorth->setAutoExclusive(true);
    ui->markSouth->setAutoExclusive(true);
    markLatDirBool = false;

    ui->markWest->setAutoExclusive(false);
    ui->markEast->setAutoExclusive(false);
    ui->markWest->setChecked(false);
    ui->markEast->setChecked(false);
    ui->markWest->setAutoExclusive(true);
    ui->markEast->setAutoExclusive(true);
    markLongDirBool = false;

    ui->sec2Reset->setEnabled(false);
    ui->positSourceMin->setStyleSheet("QPushButton {"
                                      "color: rgb(200, 200, 200);"
                                      "font: 700 9pt 'Segoe UI';"
                                      "border: 2px inset;"
                                      "border-color: rgb(153, 160, 174);"
                                      "border-bottom-color: rgb(19, 25, 39);"
                                      "border-right-color: rgb(19, 25, 39);"
                                      "}"
                                      "QPushButton::pressed {"
                                      "color: rgb(200, 200, 200);"
                                      "font: 700 9pt 'Segoe UI';"
                                      "border: 2px inset;"
                                      "border-color: rgb(19, 25, 39);"
                                      "border-bottom-color: gray;"
                                      "border-right-color: gray;"
                                      "}");
    ui->markMapBtn->setStyleSheet("QPushButton {"
                                  "font: 700 12pt 'Segoe UI';"
                                  "border: 2px inset;"
                                  "border-color: rgb(153, 160, 174);"
                                  "border-bottom-color: rgb(19, 25, 39);"
                                  "border-right-color: rgb(19, 25, 39);"
                                  "}"
                                  "QPushButton::pressed {"
                                  "font: 700 12pt 'Segoe UI';"
                                  "border: 2px inset;"
                                  "border-color: rgb(19, 25, 39);"
                                  "border-bottom-color: gray;"
                                  "border-right-color: gray;"
                                  "}");

}
void ParametricDataEntry::sec3Reset()
{
    ui->trueDirectionInput->setText("");
    ui->trueSpeedInput->setText("");
    ui->relDirectionInput->setText("");
    ui->relSpeedInput->setText("");

    ui->sec3Reset->setEnabled(false);

}
void ParametricDataEntry::sec4Reset()
{
    ui->waterDepthInput->setText("");
    ui->surfaceWaterTempInput->setText("");
    ui->setInput->setText("");
    ui->driftInput->setText("");
    ui->magVarCorrInput->setText("");

    ui->magWest->setAutoExclusive(false);
    ui->magEast->setAutoExclusive(false);
    ui->magWest->setChecked(false);
    ui->magEast->setChecked(false);
    ui->magWest->setAutoExclusive(true);
    ui->magEast->setAutoExclusive(true);
    magDirBool = false;

    ui->sec4Reset->setEnabled(false);
}
// End Sectional Reset=======================================

// Load Posit Map=========================================
void ParametricDataEntry::positMap(){

//    positView.close();
//    double positLong;
//    double positLat;
//    QString latInput1 = ui->positLatitudeInput1->text();
//    QString latInput2 = ui->positLatitudeInput2->text();
//    QString latInput3 = ui->positLatitudeInput3->text();
//    QString longInput1 = ui->positLongitudeInput1->text();
//    QString longInput2 = ui->positLongitudeInput2->text();
//    QString longInput3 = ui->positLongitudeInput3->text();
//    if (latInput1 != NULL && latInput2 != NULL &&latInput3 != NULL)
//    {
//        positLat = latInput1.toDouble()
//                   + latInput2.toDouble()/60
//                   + latInput3.toDouble()/3600;

//    }
//    else
//    {
//        positLat = ui->positLatitudeEdit1->text().toDouble()
//                   + ui->positLatitudeEdit2->text().toDouble()/60
//                   + ui->positLatitudeEdit3->text().toDouble()/3600;
//    }
//    if (longInput1 != NULL && longInput2 != NULL && longInput3 != NULL)
//    {
//        positLong = longInput1.toDouble()
//                    + longInput2.toDouble()/60
//                    + longInput3.toDouble()/3600;
//    }
//    else
//    {
//        positLong = ui->positLongitudeEdit1->text().toDouble()
//                    + ui->positLongitudeEdit2->text().toDouble()/60
//                    + ui->positLongitudeEdit3->text().toDouble()/3600;
//    }

//    QObject *object = positView.rootObject();
//    QObject *coord = object->findChild<QObject*>("coord");
//    if (coord)
//    {
//        if (positLatitudeDirection == "S")
//            positLat *= -1;
//        if (positLongitudeDirection == "W")
//            positLong *= -1;
//    }
//    coord->setProperty("latitude", positLat);
//    coord->setProperty("longitude", positLong);
//    QObject *map = object->findChild<QObject*>("map");
//    if (map)
//    {
//        map->setProperty("zoomLevel", 5);
//        map->setProperty("clat", positLat);
//        map->setProperty("clong", positLong);
//    }
//    positView.setMinimumSize(QSize(800,600));
//    positView.setMaximumSize(QSize(800,600));
//    positView.setX(this->x() + this->width());
//    positView.setY(ui->trueHeadingBox->y() +100);
//    positView.show();
}


// Apply changes from map qml to right side textboxes=============================
void ParametricDataEntry::applyNewPositCoords(QList<int> latitude, QList<int> longitude)
{
    int lat1 = latitude[0];
    int long1 = longitude[0];
    if(lat1 < 0)
    {
        lat1 *= -1;
        ui->positSouth->setChecked(true);
    }
    else
    {
        ui->positNorth->setChecked(true);
    }
    if(long1 < 0)
    {
        long1 *= -1;
        ui->positWest->setChecked(true);
    }
    else
    {
        ui->positEast->setChecked(true);
    }
    positLatDirBool = true;
    positLongDirBool = true;
    ui->positLatitudeInput1->setText(QString::number(lat1));
    ui->positLatitudeInput2->setText(QString::number(latitude[1]));
    ui->positLatitudeInput3->setText(QString::number(latitude[2]));
    ui->positLongitudeInput1->setText(QString::number(long1));
    ui->positLongitudeInput2->setText(QString::number(longitude[1]));
    ui->positLongitudeInput3->setText(QString::number(longitude[2]));
};

// Load Mark Map================================================
void ParametricDataEntry::markMap(){

//    markView.close();
//    double markLat;
//    double markLong;
//    QString latInput1 = ui->markLatitudeInput1->text();
//    QString latInput2 = ui->markLatitudeInput2->text();
//    QString latInput3 = ui->markLatitudeInput3->text();
//    QString longInput1 = ui->markLongitudeInput1->text();
//    QString longInput2 = ui->markLongitudeInput2->text();
//    QString longInput3 = ui->markLongitudeInput3->text();
//    if (latInput1 != NULL && latInput2 != NULL &&latInput3 != NULL)
//    {
//        markLat = latInput1.toDouble()
//                  + latInput2.toDouble()/60
//                  + latInput3.toDouble()/3600;

//    }
//    else
//    {
//        markLat = ui->markLatitudeEdit1->text().toDouble()
//                  + ui->markLatitudeEdit2->text().toDouble()/60
//                  + ui->markLatitudeEdit3->text().toDouble()/3600;
//    }
//    if (longInput1 != NULL && longInput2 != NULL && longInput3 != NULL)
//    {
//        markLong = longInput1.toDouble()
//                   + longInput2.toDouble()/60
//                   + longInput3.toDouble()/3600;
//    }
//    else
//    {
//        markLong = ui->markLongitudeEdit1->text().toDouble()
//                   + ui->markLongitudeEdit2->text().toDouble()/60
//                   + ui->markLongitudeEdit3->text().toDouble()/3600;
//    }

//    QObject *object = markView.rootObject();
//    QObject *coord = object->findChild<QObject*>("coord");
//    if (coord)
//    {
//        if (markLatitudeDirection == "S")
//            markLat *= -1;
//        if (markLongitudeDirection == "W")
//            markLong *= -1;
//    }
//    coord->setProperty("latitude", markLat);
//    coord->setProperty("longitude", markLong);
//    QObject *map = object->findChild<QObject*>("map");
//    if (map)
//    {
//        map->setProperty("zoomLevel", 5);
//        map->setProperty("clat", markLat);
//        map->setProperty("clong", markLong);
//    }
//    markView.setMinimumSize(QSize(800,600));
//    markView.setMaximumSize(QSize(800,600));
//    markView.setX(this->x() + this->width());
//    markView.setY(ui->positSourceBox->y());
//    markView.show();
}

// Apply changes from map qml to right side textboxes=============================
void ParametricDataEntry::applyNewMarkCoords(QList<int> latitude, QList<int> longitude)
{
    int lat1 = latitude[0];
    int long1 = longitude[0];
    if(lat1 < 0)
    {
        lat1 *= -1;
        ui->markSouth->setChecked(true);
    }
    else
    {
        ui->markNorth->setChecked(true);
    }
    if(long1 < 0)
    {
        long1 *= -1;
        ui->markWest->setChecked(true);
    }
    else
    {
        ui->markEast->setChecked(true);
    }
    markLatDirBool = true;
    markLongDirBool = true;
    if (QString::number(lat1) != ui->markLatitudeInput1->text() || QString::number(latitude[1]) != ui->markLatitudeInput2->text()
        || QString::number(latitude[2]) != ui->markLatitudeInput3->text())
    {
        ui->markLatitudeInput1->setText(QString::number(lat1));
        ui->markLatitudeInput2->setText(QString::number(latitude[1]));
        ui->markLatitudeInput3->setText(QString::number(latitude[2]));
    }
    if(QString::number(long1) != ui->markLongitudeInput1->text() || QString::number(longitude[1]) != ui->markLongitudeInput2->text()
        || QString::number(longitude[2]) != ui->markLongitudeInput3->text())
    {
        ui->markLongitudeInput1->setText(QString::number(long1));
        ui->markLongitudeInput2->setText(QString::number(longitude[1]));
        ui->markLongitudeInput3->setText( QString::number(longitude[2]));
    }

};

// Displaying Tooltip when error inputs=============================
void ParametricDataEntry::trueHeadingCheck(){
    bool check;
    QString input = ui->trueHeadingInput->text();
    double val = input.toDouble(&check);

    if(input == "" || (val >= 0 && val <= 359.9 && check == true)){
        ui->trueHeadingInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                            "color: rgb(255, 255, 255);"
                                            "border: 2px inset;"
                                            "border-color: rgb(19, 25, 39);"
                                            "border-bottom-color: gray;"
                                            "border-right-color: gray;");
        ui->headingSlider->setValue((val*10));
    }
    else{
        ui->trueHeadingInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                            "color: rgb(255, 255, 255);\n"
                                            "border: 2px solid;\n"
                                            "border-color: red;\n"
                                            "border-bottom-color: red;\n"
                                            "border-right-color: red;");
        m_tip->showText(ui->trueHeadingInput, "Out of limits [0.0, 359.9]");
    }
}

void ParametricDataEntry::speedCheck(){
    bool check;
    QString input = ui->speedInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 64 && check == true)){
        ui->speedInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                      "color: rgb(255, 255, 255);"
                                      "border: 2px inset;"
                                      "border-color: rgb(19, 25, 39);"
                                      "border-bottom-color: gray;"
                                      "border-right-color: gray;");
        ui->speedSlider->setValue((val));
    }
    else{
        ui->speedInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                      "color: rgb(255, 255, 255);\n"
                                      "border: 2px solid;\n"
                                      "border-color: red;\n"
                                      "border-bottom-color: red;\n"
                                      "border-right-color: red;");
        m_tip->showText(ui->speedInput, "Out of limits [0, 64]");
    }
}

void ParametricDataEntry::positLatCheck(){
    bool check1,check2,check3;
    QString input1 = ui->positLatitudeInput1->text();
    QString input2 = ui->positLatitudeInput2->text();
    QString input3 = ui->positLatitudeInput3->text();
    int val1 = input1.toInt(&check1);
    int val2 = input2.toInt(&check2);
    int val3 = input3.toInt(&check3);

    if((val1 >= 0 && val1 <= 90 && check1 == true) &&
        (val2 >= 0 && val2 <= 60 && check2 == true) &&
        (val3 >= 0 && val3 <= 60 && check3 == true) && positLatDirBool == false){
        m_tip->showText(ui->positNorth, "Select Hemisphere ");
    }
}

void ParametricDataEntry::positLat1Check(){
    bool check;
    QString input = ui->positLatitudeInput1->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 90 && check == true)){
        ui->positLatitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->positLatitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->positLatitudeInput1, "Deg out of limits [0, 90]");
    }
}

void ParametricDataEntry::positLat2Check(){
    bool check;
    QString input = ui->positLatitudeInput2->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->positLatitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->positLatitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->positLatitudeInput2, "Mins out of limits [0, 60]");
    }
}

void ParametricDataEntry::positLat3Check(){
    bool check;
    QString input = ui->positLatitudeInput3->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->positLatitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->positLatitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->positLatitudeInput3, "Sec out of limits [0, 60]");
    }
}

void ParametricDataEntry::positLongCheck(){
    bool check1,check2,check3;
    QString input1 = ui->positLongitudeInput1->text();
    QString input2 = ui->positLongitudeInput2->text();
    QString input3 = ui->positLongitudeInput3->text();
    int val1 = input1.toInt(&check1);
    int val2 = input2.toInt(&check2);
    int val3 = input3.toInt(&check3);

    if((val1 >= 0 && val1 <= 180 && check1 == true) &&
        (val2 >= 0 && val2 <= 60 && check2 == true) &&
        (val3 >= 0 && val3 <= 60 && check3 == true) && positLongDirBool == false){
        m_tip->showText(ui->positEast, "Select Hemisphere ");
    }
}

void ParametricDataEntry::positLong1Check(){
    bool check;
    QString input = ui->positLongitudeInput1->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 180 && check == true)){
        ui->positLongitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                                "color: rgb(255, 255, 255);"
                                                "border: 2px inset;"
                                                "border-color: rgb(19, 25, 39);"
                                                "border-bottom-color: gray;"
                                                "border-right-color: gray;");
    }
    else{
        ui->positLongitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                                "color: rgb(255, 255, 255);\n"
                                                "border: 2px solid;\n"
                                                "border-color: red;\n"
                                                "border-bottom-color: red;\n"
                                                "border-right-color: red;");
        m_tip->showText(ui->positLongitudeInput1, "Deg limits are [0, 180]");
    }
}

void ParametricDataEntry::positLong2Check(){
    bool check;
    QString input = ui->positLongitudeInput2->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->positLongitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                                "color: rgb(255, 255, 255);"
                                                "border: 2px inset;"
                                                "border-color: rgb(19, 25, 39);"
                                                "border-bottom-color: gray;"
                                                "border-right-color: gray;");
    }
    else{
        ui->positLongitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                                "color: rgb(255, 255, 255);\n"
                                                "border: 2px solid;\n"
                                                "border-color: red;\n"
                                                "border-bottom-color: red;\n"
                                                "border-right-color: red;");
        m_tip->showText(ui->positLongitudeInput2, "Mins out of limits [0, 60]");
    }
}

void ParametricDataEntry::positLong3Check(){
    bool check;
    QString input = ui->positLongitudeInput3->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->positLongitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                                "color: rgb(255, 255, 255);"
                                                "border: 2px inset;"
                                                "border-color: rgb(19, 25, 39);"
                                                "border-bottom-color: gray;"
                                                "border-right-color: gray;");
    }
    else{
        ui->positLongitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                                "color: rgb(255, 255, 255);\n"
                                                "border: 2px solid;\n"
                                                "border-color: red;\n"
                                                "border-bottom-color: red;\n"
                                                "border-right-color: red;");
        m_tip->showText(ui->positLongitudeInput3, "Sec out of limits [0, 60]");
    }
}

void ParametricDataEntry::markLatCheck(){
    bool check1,check2,check3;
    QString input1 = ui->markLatitudeInput1->text();
    QString input2 = ui->markLatitudeInput2->text();
    QString input3 = ui->markLatitudeInput3->text();
    int val1 = input1.toInt(&check1);
    int val2 = input2.toInt(&check2);
    int val3 = input3.toInt(&check3);

    if((val1 >= 0 && val1 <= 90 && check1 == true) &&
        (val2 >= 0 && val2 <= 60 && check2 == true) &&
        (val3 >= 0 && val3 <= 60 && check3 == true) && markLatDirBool == false){
        m_tip->showText(ui->markNorth, "Select Hemisphere ");
    }
}

void ParametricDataEntry::markLat1Check(){
    bool check;
    QString input = ui->markLatitudeInput1->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 90 && check == true)){
        ui->markLatitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                              "color: rgb(255, 255, 255);"
                                              "border: 2px inset;"
                                              "border-color: rgb(19, 25, 39);"
                                              "border-bottom-color: gray;"
                                              "border-right-color: gray;");
    }
    else{
        ui->markLatitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border: 2px solid;\n"
                                              "border-color: red;\n"
                                              "border-bottom-color: red;\n"
                                              "border-right-color: red;");
        m_tip->showText(ui->markLatitudeInput1, "Deg out of limits [0, 90]");
    }
}

void ParametricDataEntry::markLat2Check(){
    bool check;
    QString input = ui->markLatitudeInput2->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->markLatitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                              "color: rgb(255, 255, 255);"
                                              "border: 2px inset;"
                                              "border-color: rgb(19, 25, 39);"
                                              "border-bottom-color: gray;"
                                              "border-right-color: gray;");
    }
    else{
        ui->markLatitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border: 2px solid;\n"
                                              "border-color: red;\n"
                                              "border-bottom-color: red;\n"
                                              "border-right-color: red;");
        m_tip->showText(ui->markLatitudeInput2, "Mins out of limits [0, 60]");
    }
}

void ParametricDataEntry::markLat3Check(){
    bool check;
    QString input = ui->markLatitudeInput3->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->markLatitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                              "color: rgb(255, 255, 255);"
                                              "border: 2px inset;"
                                              "border-color: rgb(19, 25, 39);"
                                              "border-bottom-color: gray;"
                                              "border-right-color: gray;");
    }
    else{
        ui->markLatitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border: 2px solid;\n"
                                              "border-color: red;\n"
                                              "border-bottom-color: red;\n"
                                              "border-right-color: red;");
        m_tip->showText(ui->markLatitudeInput3, "Sec out of limits [0, 60]");
    }
}

void ParametricDataEntry::markLongCheck(){
    bool check1,check2,check3;
    QString input1 = ui->markLongitudeInput1->text();
    QString input2 = ui->markLongitudeInput2->text();
    QString input3 = ui->markLongitudeInput3->text();
    int val1 = input1.toInt(&check1);
    int val2 = input2.toInt(&check2);
    int val3 = input3.toInt(&check3);

    if((val1 >= 0 && val1 <= 180 && check1 == true) &&
        (val2 >= 0 && val2 <= 60 && check2 == true) &&
        (val3 >= 0 && val3 <= 60 && check3 == true) && markLongDirBool == false){
        m_tip->showText(ui->markEast, "Select Hemisphere ");
    }
}

void ParametricDataEntry::markLong1Check(){
    bool check;
    QString input = ui->markLongitudeInput1->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 180 && check == true)){
        ui->markLongitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->markLongitudeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->markLongitudeInput1, "Deg limits are [0, 180]");
    }
}

void ParametricDataEntry::markLong2Check(){
    bool check;
    QString input = ui->markLongitudeInput2->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->markLongitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->markLongitudeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->markLongitudeInput2, "Mins out of limits [0, 60]");
    }
}

void ParametricDataEntry::markLong3Check(){
    bool check;
    QString input = ui->markLongitudeInput3->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->markLongitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                               "color: rgb(255, 255, 255);"
                                               "border: 2px inset;"
                                               "border-color: rgb(19, 25, 39);"
                                               "border-bottom-color: gray;"
                                               "border-right-color: gray;");
    }
    else{
        ui->markLongitudeInput3->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border: 2px solid;\n"
                                               "border-color: red;\n"
                                               "border-bottom-color: red;\n"
                                               "border-right-color: red;");
        m_tip->showText(ui->markLongitudeInput3, "Sec out of limits [0, 60]");
    }
}


void ParametricDataEntry::markTime1Check(){
    bool check;
    QString input = ui->markTimeInput1->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <=24 && check == true)){
        ui->markTimeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                          "color: rgb(255, 255, 255);"
                                          "border: 2px inset;"
                                          "border-color: rgb(19, 25, 39);"
                                          "border-bottom-color: gray;"
                                          "border-right-color: gray;");
    }
    else{
        ui->markTimeInput1->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                          "color: rgb(255, 255, 255);\n"
                                          "border: 2px solid;\n"
                                          "border-color: red;\n"
                                          "border-bottom-color: red;\n"
                                          "border-right-color: red;");
        m_tip->showText(ui->markTimeInput1, "Hours out of limits [0, 24]");
    }
}

void ParametricDataEntry::markTime2Check(){
    bool check;
    QString input = ui->markTimeInput2->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 60 && check == true)){
        ui->markTimeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                          "color: rgb(255, 255, 255);"
                                          "border: 2px inset;"
                                          "border-color: rgb(19, 25, 39);"
                                          "border-bottom-color: gray;"
                                          "border-right-color: gray;");
    }
    else{
        ui->markTimeInput2->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                          "color: rgb(255, 255, 255);\n"
                                          "border: 2px solid;\n"
                                          "border-color: red;\n"
                                          "border-bottom-color: red;\n"
                                          "border-right-color: red;");
        m_tip->showText(ui->markTimeInput2, "Mins out of limits [0, 59]");
    }
}

void ParametricDataEntry::trueDirCheck(){
    bool check;
    QString input = ui->trueDirectionInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 359 && check == true)){
        ui->trueDirectionInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                              "color: rgb(255, 255, 255);"
                                              "border: 2px inset;"
                                              "border-color: rgb(19, 25, 39);"
                                              "border-bottom-color: gray;"
                                              "border-right-color: gray;");
        //ui->sec3ErrorMsg->setText("");
        ui->trueDirSlider->setValue((val));
    }
    else{
        ui->trueDirectionInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border: 2px solid;\n"
                                              "border-color: red;\n"
                                              "border-bottom-color: red;\n"
                                              "border-right-color: red;");
        m_tip->showText(ui->trueDirectionInput, "Out of limits [0, 359]");
    }
}

void ParametricDataEntry::trueSpeedCheck(){
    bool check;
    QString input = ui->trueSpeedInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 127 && check == true)){
        ui->trueSpeedInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                          "color: rgb(255, 255, 255);"
                                          "border: 2px inset;"
                                          "border-color: rgb(19, 25, 39);"
                                          "border-bottom-color: gray;"
                                          "border-right-color: gray;");
        //ui->sec3ErrorMsg->setText("");
        ui->trueSpeedSlider->setValue((val));
    }
    else{
        ui->trueSpeedInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                          "color: rgb(255, 255, 255);\n"
                                          "border: 2px solid;\n"
                                          "border-color: red;\n"
                                          "border-bottom-color: red;\n"
                                          "border-right-color: red;");
        m_tip->showText(ui->trueSpeedInput, "Out of limits [0, 127]");
    }
}

void ParametricDataEntry::relDirCheck(){
    bool check;
    QString input = ui->relDirectionInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 359 && check == true)){
        ui->relDirectionInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                             "color: rgb(255, 255, 255);"
                                             "border: 2px inset;"
                                             "border-color: rgb(19, 25, 39);"
                                             "border-bottom-color: gray;"
                                             "border-right-color: gray;");
        //ui->sec3ErrorMsg->setText("");
        ui->relDirSlider->setValue((val));
    }
    else{
        ui->relDirectionInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                             "color: rgb(255, 255, 255);\n"
                                             "border: 2px solid;\n"
                                             "border-color: red;\n"
                                             "border-bottom-color: red;\n"
                                             "border-right-color: red;");
        m_tip->showText(ui->relDirectionInput, "Out of limits [0, 359]");
    }
}

void ParametricDataEntry::relSpeedCheck(){
    bool check;
    QString input = ui->relSpeedInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 127 && check == true)){
        ui->relSpeedInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                         "color: rgb(255, 255, 255);"
                                         "border: 2px inset;"
                                         "border-color: rgb(19, 25, 39);"
                                         "border-bottom-color: gray;"
                                         "border-right-color: gray;");
        //ui->sec3ErrorMsg->setText("");
        ui->relSpeedSlider->setValue((val));
    }
    else{
        ui->relSpeedInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                         "color: rgb(255, 255, 255);\n"
                                         "border: 2px solid;\n"
                                         "border-color: red;\n"
                                         "border-bottom-color: red;\n"
                                         "border-right-color: red;");
        m_tip->showText(ui->relSpeedInput, "Out of limits [0, 127]");
    }
}

void ParametricDataEntry::waterDepthCheck(){
    bool check;
    QString input = ui->waterDepthInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 9999 && check == true)){
        ui->waterDepthInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                           "color: rgb(255, 255, 255);"
                                           "border: 2px inset;"
                                           "border-color: rgb(19, 25, 39);"
                                           "border-bottom-color: gray;"
                                           "border-right-color: gray;");
        //ui->sec4ErrorMsg->setText("");
        ui->waterDepthSlider->setValue((val));
    }
    else{
        ui->waterDepthInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                           "color: rgb(255, 255, 255);\n"
                                           "border: 2px solid;\n"
                                           "border-color: red;\n"
                                           "border-bottom-color: red;\n"
                                           "border-right-color: red;");
        m_tip->showText(ui->waterDepthInput, "Out of limits [0, 9999]");
    }
}

void ParametricDataEntry::surfWaterTempCheck(){
    bool check;
    QString input = ui->surfaceWaterTempInput->text();
    int val = input.toInt(&check);

    if(input == "" || (val >= 0 && val <= 120 && check == true)){
        ui->surfaceWaterTempInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                                 "color: rgb(255, 255, 255);"
                                                 "border: 2px inset;"
                                                 "border-color: rgb(19, 25, 39);"
                                                 "border-bottom-color: gray;"
                                                 "border-right-color: gray;");
        //ui->sec4ErrorMsg->setText("");
        ui->surfWaterTempSlider->setValue((val));
    }
    else{
        ui->surfaceWaterTempInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                                 "color: rgb(255, 255, 255);\n"
                                                 "border: 2px solid;\n"
                                                 "border-color: red;\n"
                                                 "border-bottom-color: red;\n"
                                                 "border-right-color: red;");
        m_tip->showText(ui->surfaceWaterTempInput, "Out of limits [0, 120]");
    }
}

void ParametricDataEntry::setCheck(){
    bool check;
    QString input = ui->setInput->text();
    double val = input.toDouble(&check);

    if(input == "" || (val >= 0 && val <= 359.9 && check == true)){
        ui->setInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                    "color: rgb(255, 255, 255);"
                                    "border: 2px inset;"
                                    "border-color: rgb(19, 25, 39);"
                                    "border-bottom-color: gray;"
                                    "border-right-color: gray;");
        ui->setSlider->setValue((val*10));
    }
    else{
        ui->setInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                    "color: rgb(255, 255, 255);\n"
                                    "border: 2px solid;\n"
                                    "border-color: red;\n"
                                    "border-bottom-color: red;\n"
                                    "border-right-color: red;");
        m_tip->showText(ui->setInput, "Out of limits [0.0, 359.9]");
    }
}

void ParametricDataEntry::driftCheck(){
    bool check;
    QString input = ui->driftInput->text();
    double val = input.toDouble(&check);

    if(input == "" || (val >= 0 && val <= 15.9 && check == true)){
        ui->driftInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                      "color: rgb(255, 255, 255);"
                                      "border: 2px inset;"
                                      "border-color: rgb(19, 25, 39);"
                                      "border-bottom-color: gray;"
                                      "border-right-color: gray;");
        ui->driftSlider->setValue((val*10));
    }
    else{
        ui->driftInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                      "color: rgb(255, 255, 255);\n"
                                      "border: 2px solid;\n"
                                      "border-color: red;\n"
                                      "border-bottom-color: red;\n"
                                      "border-right-color: red;");
        m_tip->showText(ui->driftInput, "Out of limits [0.0, 15.9]");
    }
}

void ParametricDataEntry::magVarCorrCheck(){
    bool check;
    QString input = ui->magVarCorrInput->text();
    double val = input.toDouble(&check);

    if(input == "" || (val >= 0 && val <= 90.0 && check == true && magDirBool == true)){
        ui->magVarCorrInput->setStyleSheet("font: 700 9pt 'Segoe UI';"
                                           "color: rgb(255, 255, 255);"
                                           "border: 2px inset;"
                                           "border-color: rgb(19, 25, 39);"
                                           "border-bottom-color: gray;"
                                           "border-right-color: gray;");
    }
    else if(val < 0 || val >= 90.0 || check == false){
        ui->magVarCorrInput->setStyleSheet("font: 700 9pt 'Segoe UI';\n"
                                           "color: rgb(255, 255, 255);\n"
                                           "border: 2px solid;\n"
                                           "border-color: red;\n"
                                           "border-bottom-color: red;\n"
                                           "border-right-color: red;");
        m_tip->showText(ui->magVarCorrInput, "Out of limits [0.0, 90.0]");
    }
    else if(val >= 0 && val <= 90.0 && check == true && magDirBool == false){
        m_tip->showText(ui->magEast, "Select Hemisphere ");
    }
}
// End Displaying Tootlip when Error Inputs===============================

//Call methods from Minimize class to expand/collapse tabs========================
void ParametricDataEntry::minimization(int section){
    Minimize *minimize = new Minimize;
    switch (section){

    case 1:
        minimize->trueHeadingMinimization(ui,trueHeadingMinimized,this);
        trueHeadingMinimized = !trueHeadingMinimized;
        break;
    case 2:
        minimize->positSourceMinimization(ui,positSourceMinimized,this);
        positSourceMinimized = !positSourceMinimized;
        break;
    case 3:
        minimize->windSourceMinimization(ui,windSourceMinimized,this);
        windSourceMinimized = !windSourceMinimized;
        break;
    case 4:
        minimize->waterDepthMinimization(ui,waterDepthMinimized,this);
        waterDepthMinimized = !waterDepthMinimized;
        break;
    }
    // auto-collapse if window height is greater than screen height
    /*if ((ui->centralwidget->geometry().height() > desktop.availableGeometry().height()) && waterDepthMinimized == false)
    {
        if (section != 4 &&  waterDepthMinimized == false)
        {
            minimize->waterDepthMinimization(ui,waterDepthMinimized,this);
            waterDepthMinimized = !waterDepthMinimized;
        }
        if (section == 4 &&  trueHeadingMinimized == false)
        {
            minimize->trueHeadingMinimization(ui,trueHeadingMinimized,this);
            trueHeadingMinimized = !trueHeadingMinimized;
        }
    }
    */
    delete minimize;
}



// Sliders to values =========================================
void ParametricDataEntry::trueDirSlider(){
    ui->trueDirectionInput->setText(QString::number(ui->trueDirSlider->value()));
}

void ParametricDataEntry::relDirSlider(){
    ui->relDirectionInput->setText(QString::number(ui->relDirSlider->value()));
}

void ParametricDataEntry::trueSpeedSlider(){
    ui->trueSpeedInput->setText(QString::number(ui->trueSpeedSlider->value()));
}

void ParametricDataEntry::relSpeedSlider(){
    ui->relSpeedInput->setText(QString::number(ui->relSpeedSlider->value()));
}

void ParametricDataEntry::speedSlider(){
    ui->speedInput->setText(QString::number(ui->speedSlider->value()));
}

void ParametricDataEntry::headingSlider(){
    double sliderValue = ui->headingSlider->value();
    double decimalValue = sliderValue/10;
    ui->trueHeadingInput->setText(QString::number(decimalValue));
}

void ParametricDataEntry::waterDepthSlider(){
    ui->waterDepthInput->setText(QString::number(ui->waterDepthSlider->value()));
}

void ParametricDataEntry::surfWaterTempSlider(){
    ui->surfaceWaterTempInput->setText(QString::number(ui->surfWaterTempSlider->value()));
}

void ParametricDataEntry::setSlider(){
    double sliderValue = ui->setSlider->value();
    double decimalValue = sliderValue/10;
    ui->setInput->setText(QString::number(decimalValue));
}

void ParametricDataEntry::driftSlider(){
    double sliderValue = ui->driftSlider->value();
    double decimalValue = sliderValue/10;
    ui->driftInput->setText(QString::number(decimalValue));
}
// End sliders to values===========================

// Detect direction selected================
void ParametricDataEntry::positNorth(){
    positLatitudeDirection = "N";
    positLatDirBool = true;
}

void ParametricDataEntry::positSouth(){
    positLatitudeDirection = "S";
    positLatDirBool = true;
}

void ParametricDataEntry::positEast(){
    positLongitudeDirection = "E";
    positLongDirBool = true;
}

void ParametricDataEntry::positWest(){
    positLongitudeDirection = "W";
    positLongDirBool = true;
}

void ParametricDataEntry::markNorth(){
    markLatitudeDirection = "N";
    markLatDirBool = true;
}

void ParametricDataEntry::markSouth(){
    markLatitudeDirection = "S";
    markLatDirBool = true;
}

void ParametricDataEntry::markEast(){
    markLongitudeDirection = "E";
    markLongDirBool = true;
}

void ParametricDataEntry::markWest(){
    markLongitudeDirection = "W";
    markLongDirBool = true;
}

void ParametricDataEntry::magEast(){
    magDirection = "Deg E";
    magDirBool = true;
}

void ParametricDataEntry::magWest(){
    magDirection = "Deg W";
    magDirBool = true;
}
// End detect direction selected================

// Performs type checking and apply to database, update left side display=======
void ParametricDataEntry::fillSlots()
{

    positView.close();
    markView.close();

    bool validateth, validatespeed, validateplatdd, validateplatmm, validateplatss, validateplongddd,
        validateplongmm, validateplongss, validatemhour, validatemmin, validatemlatdd, validatemlatmm,
        validatemlatss, validatemlongddd, validatemlongmm, validatemlongss, validatetdir, validatetspeed,
        validaterdir, validaterspeed, validatedepth, validatetemp, validateset, validatedrift, validatecorr;

    QString thinput = ui->trueHeadingInput->text();
    QString speedinput = ui->speedInput->text();
    QString platddinput = ui->positLatitudeInput1->text();
    QString platmminput = ui->positLatitudeInput2->text();
    QString platssinput = ui->positLatitudeInput3->text();
    QString plongdddinput = ui->positLongitudeInput1->text();
    QString plongmminput = ui->positLongitudeInput2->text();
    QString plongssinput = ui->positLongitudeInput3->text();
    QString mhourinput = ui->markTimeInput1->text();
    QString mmininput = ui->markTimeInput2->text();
    QString mlatddinput = ui->markLatitudeInput1->text();
    QString mlatmminput = ui->markLatitudeInput2->text();
    QString mlatssinput = ui->markLatitudeInput3->text();
    QString mlongdddinput = ui->markLongitudeInput1->text();
    QString mlongmminput = ui->markLongitudeInput2->text();
    QString mlongssinput = ui->markLongitudeInput3->text();
    QString tdirinput = ui->trueDirectionInput->text();
    QString tspeedinput = ui->trueSpeedInput->text();
    QString rdirinput = ui->relDirectionInput->text();
    QString rspeedinput = ui->relSpeedInput->text();
    QString depthinput = ui->waterDepthInput->text();
    QString tempinput = ui->surfaceWaterTempInput->text();
    QString setinput = ui->setInput->text();
    QString driftinput = ui->driftInput->text();
    QString corrinput = ui->magVarCorrInput->text();

    double thval = thinput.toDouble(&validateth);
    int speedval = speedinput.toInt(&validatespeed);
    int platddval = platddinput.toInt(&validateplatdd);
    int platmmval = platmminput.toInt(&validateplatmm);
    int platssval = platssinput.toInt(&validateplatss);
    int plongdddval = plongdddinput.toInt(&validateplongddd);
    int plongmmval = plongmminput.toInt(&validateplongmm);
    int plongssval = plongssinput.toInt(&validateplongss);
    int mhourval = mhourinput.toInt(&validatemhour);
    int mminval = mmininput.toInt(&validatemmin);
    int mlatddval = mlatddinput.toInt(&validatemlatdd);
    int mlatmmval = mlatmminput.toInt(&validatemlatmm);
    int mlatssval = mlatssinput.toInt(&validatemlatss);
    int mlongdddval = mlongdddinput.toInt(&validatemlongddd);
    int mlongmmval = mlongmminput.toInt(&validatemlongmm);
    int mlongssval = mlongssinput.toInt(&validatemlongss);
    int tdirval = tdirinput.toInt(&validatetdir);
    int tspeedval = tspeedinput.toInt(&validatetspeed);
    int rdirval = rdirinput.toInt(&validaterdir);
    int rspeedval = rspeedinput.toInt(&validaterspeed);
    int depthval = depthinput.toInt(&validatedepth);
    int tempval = tempinput.toInt(&validatetemp);
    double setval = setinput.toDouble(&validateset);
    double driftval = driftinput.toDouble(&validatedrift);
    double corrval = corrinput.toDouble(&validatecorr);

    if(thinput != "" && (validateth == true && thval >= 0 && thval <= 359.9))
    {
        ui->trueHeadingEdit->setText(thinput);
    }

    if(speedinput != "" && (validatespeed == true) && speedval >= 0 && speedval <= 64)
    {
        ui->speedEdit->setText(speedinput);
    }

    if((platddinput != "" || platmminput != "" || platssinput != "") && ((validateplatdd == true) && (platddval >= 0) && (platddval <= 90) &&
                                                                          (validateplatmm == true) && (platmmval >= 0) && (platmmval <= 60) &&
                                                                          (validateplatss == true) && (platssval >= 0) && (platssval <= 60) && positLatDirBool == true))
    {
        ui->positLatitudeEdit1->setText(platddinput);
        ui->positLatitudeEdit2->setText(platmminput);
        ui->positLatitudeEdit3->setText(platssinput);
        ui->positLatitudeDirection->setText(positLatitudeDirection);

        QObject *object = positView.rootObject();
        QObject *coord = object->findChild<QObject*>("coord");
        double positLat = (double(platddval) + double(platmmval)/60 + double(platssval)/3600);
        if (coord)
        {
            if (positLatDirBool ==true && positLatitudeDirection == "S")
                positLat *= -1;
            coord->setProperty("longitude", positLat);
        }


    }
    else if((validateplatdd == true) && (platddval >= 0) && (platddval <= 90) &&
             (validateplatmm == true) && (platmmval >= 0) && (platmmval <= 60) &&
             (validateplatss == true) && (platssval >= 0) && (platssval <= 60) && positLatDirBool == false)
    {
        m_tip->showText(ui->positNorth, "Select Hemisphere");
    }

    if((plongdddinput != "" || plongmminput != "" || plongssinput != "") && (validateplongddd == true && plongdddval >= 0 && plongdddval <= 180 &&
                                                                              validateplongmm == true && plongmmval >= 0 && plongmmval <= 60 &&
                                                                              validateplongss == true && plongssval >= 0 && plongssval <= 60 && positLongDirBool == true))
    {
        ui->positLongitudeEdit1->setText(plongdddinput);
        ui->positLongitudeEdit2->setText(plongmminput);
        ui->positLongitudeEdit3->setText(plongssinput);
        ui->positLongitudeDirection->setText(positLongitudeDirection);
        QObject *object = positView.rootObject();
        QObject *coord = object->findChild<QObject*>("coord");

        double positLong = (double(plongdddval) + double(plongmmval)/60 + double(plongssval)/3600);
        if (coord)
        {
            if (positLongDirBool ==true && positLongitudeDirection == "W")
                positLong *= -1;
            coord->setProperty("longitude", positLong);
        }

    }
    else if(validateplongddd == true && plongdddval >= 0 && plongdddval <= 180 &&
             validateplongmm == true && plongmmval >= 0 && plongmmval <= 60 &&
             validateplongss == true && plongssval >= 0 && plongssval <= 60 && positLongDirBool == false)
    {
        m_tip->showText(ui->positEast, "Select Hemisphere ");
    }

    if((mmininput != "" || mhourinput != "") && ((validatemhour == true && mhourval >=0 && mhourval <= 24 &&
                                                   validatemmin == true && mminval >=0 && mminval <= 59)))
    {
        ui->markTimeEdit1->setText(mhourinput);
        ui->markTimeEdit2->setText(mmininput);
    }

    if((mlatddinput != "" || mlatmminput != "" || mlatssinput != "") && ((validatemlatdd == true) && (mlatddval >= 0) && (mlatddval <= 90) &&
                                                                          (validatemlatmm == true) && (mlatmmval >= 0) && (mlatmmval <= 60) &&
                                                                          (validatemlatss == true) && (mlatssval >= 0) && (mlatssval <= 60) && markLatDirBool == true))
    {
        ui->markLatitudeEdit1->setText(mlatddinput);
        ui->markLatitudeEdit2->setText(mlatmminput);
        ui->markLatitudeEdit3->setText(mlatssinput);
        ui->markLatitudeDirection->setText(markLatitudeDirection);

        QObject *object = markView.rootObject();
        QObject *coord = object->findChild<QObject*>("coord");
        double markLat = (double(mlatddval) + double(mlatmmval)/60 + double(mlatssval)/3600);
        if (coord)
        {
            if (markLatDirBool ==true && markLatitudeDirection == "S")
                markLat *= -1;
            coord->setProperty("longitude", markLat);
        }
    }
    else if((validatemlatdd == true) && (mlatddval >= 0) && (mlatddval <= 90) &&
             (validatemlatmm == true) && (mlatmmval >= 0) && (mlatmmval <= 60) &&
             (validatemlatss == true) && (mlatssval >= 0) && (mlatssval <= 60) && markLatDirBool == false)
    {
        m_tip->showText(ui->markNorth, "Select Hemisphere ");
    }

    if((mlongdddinput != "" || mlongmminput != "" || mlongssinput != "") && (validatemlongddd == true && mlongdddval >= 0 && mlongdddval <= 180 &&
                                                                              validatemlongmm == true && mlongmmval >= 0 && mlongmmval <= 60 &&
                                                                              validatemlongss == true && mlongssval >= 0 && mlongssval <= 60 && markLongDirBool == true))
    {
        ui->markLongitudeEdit1->setText(mlongdddinput);
        ui->markLongitudeEdit2->setText(mlongmminput);
        ui->markLongitudeEdit3->setText(mlongssinput);
        ui->markLongitudeDirection->setText(markLongitudeDirection);

        QObject *object = markView.rootObject();
        QObject *coord = object->findChild<QObject*>("coord");

        double markLong = (double(mlongdddval) + double(mlongmmval)/60 + double(mlongssval)/3600);
        if (coord)
        {
            if (markLongDirBool ==true && markLongitudeDirection == "W")
                markLong *= -1;
            coord->setProperty("longitude", markLong);
        }
    }
    else if(validatemlongddd == true && mlongdddval >= 0 && mlongdddval <= 180 &&
             validatemlongmm == true && mlongmmval >= 0 && mlongmmval <= 60 &&
             validatemlongss == true && mlongssval >= 0 && mlongssval <= 60 && markLongDirBool == false)
    {
        m_tip->showText(ui->markEast, "Select Hemisphere ");
    }

    if(tdirinput != "" && validatetdir == true && tdirval >= 0 && tdirval <= 359)
    {
        ui->trueDirectionEdit->setText(tdirinput);
    }

    if(tspeedinput != "" && validatetspeed == true && tspeedval >= 0 && tspeedval <= 127)
    {
        ui->trueSpeedEdit->setText(tspeedinput);
    }

    if(rdirinput != "" && validaterdir == true && rdirval >= 0 && rdirval <= 359)
    {
        ui->relDirectionEdit->setText(rdirinput);
    }

    if(rspeedinput != "" && validaterspeed == true && rspeedval >= 0 && rspeedval <= 127)
    {
        ui->relSpeedEdit->setText(rspeedinput);
    }

    if(depthinput != "" && validatedepth == true && depthval >= 0 && depthval <= 9999)
    {
        ui->waterDepthEdit->setText(depthinput);
    }

    if(tempinput != "" && validatetemp == true && tempval >= 0 && tempval <= 120)
    {
        ui->surfaceWaterTempEdit->setText(tempinput);
    }

    if(setinput != "" && validateset == true && setval >= 0 && setval <= 359.9)
    {
        ui->setEdit->setText(setinput);
    }

    if(driftinput != "" && validatedrift == true && driftval >= 0 && driftval <= 15.9)
    {
        ui->driftEdit->setText(driftinput);
    }

    if(corrinput != "" && validatecorr == true && corrval >= 0 && corrval <= 90 && magDirBool == true)
    {
        ui->magVarCorrEdit->setText(corrinput);
        ui->magVarrCorrDirection->setText(magDirection);
    }

    connect(socket, &QWebSocket::connected, this, [this]() {
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueHeadingEdit->text() + "' WHERE Description = 'True Heading'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->speedEdit->text() + "' WHERE Description = 'Speed'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit1->text() + "' WHERE Description = 'Posit Latitude 1'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit2->text() + "' WHERE Description = 'Posit Latitude 2'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit3->text() + "' WHERE Description = 'Posit Latitude 3'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeDirection->text() + "' WHERE Description = 'Posit Latitude Hemisphere'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit1->text() + "' WHERE Description = 'Posit Longitude 1'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit2->text() + "' WHERE Description = 'Posit Longitude 2'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit3->text() + "' WHERE Description = 'Posit Longitude 3'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeDirection->text() + "' WHERE Description = 'Posit Longitude Hemisphere'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markTimeEdit1->text() + "' WHERE Description = 'Mark Time 1'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markTimeEdit2->text() + "' WHERE Description = 'Mark Time 2'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit1->text() + "' WHERE Description = 'Mark Latitude 1'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit2->text() + "' WHERE Description = 'Mark Latitude 2'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit3->text() + "' WHERE Description = 'Mark Latitude 3'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeDirection->text() + "' WHERE Description = 'Mark Latitude Hemisphere'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit1->text() + "' WHERE Description = 'Mark Longitude 1'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit2->text() + "' WHERE Description = 'Mark Longitude 2'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit3->text() + "' WHERE Description = 'Mark Longitude 3'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeDirection->text() + "' WHERE Description = 'Mark Longitude Hemisphere'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueDirectionEdit->text() + "' WHERE Description = 'True Direction'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueSpeedEdit->text() + "' WHERE Description = 'True Speed'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->relDirectionEdit->text() + "' WHERE Description = 'Rel Direction'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->relSpeedEdit->text() + "' WHERE Description = 'Rel Speed'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->waterDepthEdit->text() + "' WHERE Description = 'Water Depth'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->surfaceWaterTempEdit->text() + "' WHERE Description = 'Surf Water Temp'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->setEdit->text() + "' WHERE Description = 'Set'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->driftEdit->text() + "' WHERE Description = 'Drift'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->magVarCorrEdit->text() + "' WHERE Description = 'Mag Var Corr'");
        socket->sendTextMessage("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->magVarrCorrDirection->text() + "' WHERE Description = 'Mag Var Corr Hemisphere'");

    });


//    QSqlQuery qry;
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueHeadingEdit->text() + "' WHERE Description = 'True Heading'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->speedEdit->text() + "' WHERE Description = 'Speed'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit1->text() + "' WHERE Description = 'Posit Latitude 1'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit2->text() + "' WHERE Description = 'Posit Latitude 2'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeEdit3->text() + "' WHERE Description = 'Posit Latitude 3'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLatitudeDirection->text() + "' WHERE Description = 'Posit Latitude Hemisphere'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit1->text() + "' WHERE Description = 'Posit Longitude 1'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit2->text() + "' WHERE Description = 'Posit Longitude 2'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeEdit3->text() + "' WHERE Description = 'Posit Longitude 3'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->positLongitudeDirection->text() + "' WHERE Description = 'Posit Longitude Hemisphere'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markTimeEdit1->text() + "' WHERE Description = 'Mark Time 1'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markTimeEdit2->text() + "' WHERE Description = 'Mark Time 2'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit1->text() + "' WHERE Description = 'Mark Latitude 1'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit2->text() + "' WHERE Description = 'Mark Latitude 2'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeEdit3->text() + "' WHERE Description = 'Mark Latitude 3'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLatitudeDirection->text() + "' WHERE Description = 'Mark Latitude Hemisphere'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit1->text() + "' WHERE Description = 'Mark Longitude 1'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit2->text() + "' WHERE Description = 'Mark Longitude 2'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeEdit3->text() + "' WHERE Description = 'Mark Longitude 3'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->markLongitudeDirection->text() + "' WHERE Description = 'Mark Longitude Hemisphere'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueDirectionEdit->text() + "' WHERE Description = 'True Direction'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->trueSpeedEdit->text() + "' WHERE Description = 'True Speed'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->relDirectionEdit->text() + "' WHERE Description = 'Rel Direction'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->relSpeedEdit->text() + "' WHERE Description = 'Rel Speed'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->waterDepthEdit->text() + "' WHERE Description = 'Water Depth'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->surfaceWaterTempEdit->text() + "' WHERE Description = 'Surf Water Temp'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->setEdit->text() + "' WHERE Description = 'Set'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->driftEdit->text() + "' WHERE Description = 'Drift'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->magVarCorrEdit->text() + "' WHERE Description = 'Mag Var Corr'");
//    qry.exec("UPDATE ParametricDataEntry SET DisplayItem = '" + ui->magVarrCorrDirection->text() + "' WHERE Description = 'Mag Var Corr Hemisphere'");

    ui->resetButton->QAbstractButton::clicked();
}

void ParametricDataEntry::on_cancelButton_clicked()
{
    close();
}

// function to control disappearance of tooltips by mouse or keyboard press
bool ParametricDataEntry::eventFilter(QObject *obj, QEvent *event)
{

    if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::KeyPress)
    {
        m_tip->hide();
    }

    return QObject::eventFilter(obj, event);
}

// closing all sub-tabs when PDE is closed
void ParametricDataEntry::closeEvent(QCloseEvent *event)
{
    positView.close();
    markView.close();
    close();
}
