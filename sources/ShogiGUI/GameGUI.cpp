#include "../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"
#include "BoardFrame.h"
#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtCore/QDebug>
#include <QtCore/QVarLengthArray>
#include <QtWidgets/QAbstractButton>
#include "GameGUI.h"
#include "MainMenuGUI.h"


GameGUI::GameGUI(QWidget *parent) : QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    board = new BoardFrame(this);
    connect(board, SIGNAL(sendMessage(const QString)), this, SLOT(showMessage(QString)));

    connect(board, SIGNAL(sendGameSituation(const std::shared_ptr<shogi::GameSituation> &)),
            this, SLOT(handleGameSituation(const std::shared_ptr<shogi::GameSituation> &)));

    undoButton = new QPushButton(tr("Undo"), this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));

    redoButton = new QPushButton(tr("Redo"), this);
    redoButton->setFocusPolicy(Qt::NoFocus);
    connect(redoButton, SIGNAL(clicked()), this, SLOT(redo()));

    saveButton = new QPushButton(tr("Save"), this);
    saveButton->setFocusPolicy(Qt::NoFocus);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    loadButton = new QPushButton(tr("Load"), this);
    loadButton->setFocusPolicy(Qt::NoFocus);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(load()));

    exitButton = new QPushButton(tr("Exit"), this);
    exitButton->setFocusPolicy(Qt::NoFocus);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));

    menuButton = new QPushButton(tr("Menu"), this);
    menuButton->setFocusPolicy(Qt::NoFocus);
    connect(menuButton, SIGNAL(clicked()), this, SLOT(menu()));

    this->setFixedSize(SCREEN_SIZE);

    status = new QLabel(this);
    status->setWordWrap(true);
    QFont labelFont = status->font();
    labelFont.setPointSize(13);
    status->setFont(labelFont);

    board->move(PADDING, PADDING);
    board->resize(GRAPHIC_ZONE_SIZE);

    undoButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING);
    undoButton->resize(BUTTON_SIZE);
    undoButton->setStyleSheet(QPushButtonStyle);

    redoButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING + BUTTON_SIZE.height() + PADDING);
    redoButton->resize(BUTTON_SIZE);
    redoButton->setStyleSheet(QPushButtonStyle);

    saveButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING + BUTTON_SIZE.height() * 2 + PADDING * 2);
    saveButton->resize(BUTTON_SIZE);
    saveButton->setStyleSheet(QPushButtonStyle);

    loadButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING + BUTTON_SIZE.height() * 3 + PADDING * 3);
    loadButton->resize(BUTTON_SIZE);
    loadButton->setStyleSheet(QPushButtonStyle);

    menuButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING + BUTTON_SIZE.height() * 4 + PADDING * 4);
    menuButton->resize(BUTTON_SIZE);
    menuButton->setStyleSheet(QPushButtonStyle);

    exitButton->move(GRAPHIC_ZONE_SIZE.width() + PADDING * 2,
                     PADDING + BUTTON_SIZE.height() * 5 + PADDING * 5);
    exitButton->resize(BUTTON_SIZE);
    exitButton->setStyleSheet(QPushButtonStyle);

    status->move(PADDING, GRAPHIC_ZONE_SIZE.height() + PADDING * 2);
    status->setFixedWidth(GRAPHIC_ZONE_SIZE.width());

    setWindowTitle(tr("Shogi"));

}


void GameGUI::sendQuestionMessage(const std::shared_ptr<shogi::GameSituation> &situation)
{
    QMessageBox messageBox;
    messageBox.setText(situation->getMessage().c_str());
    messageBox.setInformativeText(tr("Do you want to do it?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int clicked = messageBox.exec();

    if(clicked == QMessageBox::Yes)
    {
        situation->execute();
    }
}

void GameGUI::sendInformativeMessage(const std::shared_ptr<shogi::GameSituation> &situation)
{
    //todo подумать о выделении метода
    QMessageBox messageBox;
    messageBox.setText(situation->getMessage().c_str());
    if (situation->isEndOfGame())
    {
        messageBox.setInformativeText(tr("Game is end!"));
        messageBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    }
    else
    {
        messageBox.setStandardButtons(QMessageBox::Ok);
    }
    int clicked = messageBox.exec();
    switch (clicked)
    {
        case QMessageBox::Retry:
        {
            board->load();
            break;
        }
        case QMessageBox::Close:
            {
                close();
                break;
            }
        default: { }
    }

}

void GameGUI::handleGameSituation(const std::shared_ptr<shogi::GameSituation> &situation)
{
    if (situation->isExecutable())
    {
        sendQuestionMessage(situation);
    }
    else
    {
        sendInformativeMessage(situation);
    }
}

void GameGUI::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Create save"), "save", tr("Shogi saves (*.shs)"));
    QFile saveFile(fileName);
    saveFile.open(QIODevice::WriteOnly);
    if(!saveFile.isOpen() || !saveFile.isWritable())
    {
        return;
    }
    QString saveString = board->save().c_str();
    QTextStream stream(&saveFile);
    stream << saveString;
    saveFile.close();
}

void GameGUI::load()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open save"), "save", tr("Shogi saves (*.shs)"));
    QFile saveFile(fileName);
    saveFile.open(QIODevice::ReadOnly);
    if(!saveFile.isOpen())
    {
        return;
    }
    QString saveString;
    QTextStream stream(&saveFile);
    saveString = stream.readAll();
    saveFile.close();
    board->load(saveString.toStdString());
}

void GameGUI::load(QString &saveDate)
{
    board->load(saveDate.toStdString());
}


void GameGUI::undo()
{
    board->undo();
}

void GameGUI::redo()
{
    board->redo();
}

void GameGUI::exit()
{
    close();
}

void GameGUI::menu()
{
    //todo реализовать переключение между окнами нормаольным способом
    MainMenuG *menu = new MainMenuG(0);
    menu->show();
    close();
}

void GameGUI::showMessage(QString msg)
{
    status->setText(msg.simplified());
}


















