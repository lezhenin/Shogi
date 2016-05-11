#include "../ShogiCore/SaveAndLoad/JSON/JSONSaveManager.h"
#include "BoardFrame.h"
#include <QtWidgets/QWidget>
#include <QtGui/QPixmap>
#include <QtCore/QDebug>
#include <QtCore/QVarLengthArray>
#include <QtWidgets/QAbstractButton>
#include "GameGUI.h"


GameGUI::GameGUI(QWidget *parent, bool needLoad): QWidget(parent, Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint)
{
    board = new BoardFrame(this);

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

    menuButton = new QPushButton(tr("Menu"), this);
    menuButton->setFocusPolicy(Qt::NoFocus);

    if(needLoad) load();

    this->setFixedSize(SCREEN_SIZE);

    status = new QLabel(this);
    status->setWordWrap(true);
    QFont labelFont = status->font();
    labelFont.setPointSize(14);
    status->setFont(labelFont);
    connect(board, SIGNAL(sendMessage(const QString)), status, SLOT(setText(QString)));

    connect(board, SIGNAL(sendGameSituation(const std::shared_ptr<shogi::GameSituation> &)),
             this, SLOT(handleGameSituation(const std::shared_ptr<shogi::GameSituation> &)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 1, 12, 6);
    layout->addWidget(undoButton, 0, 7);
    layout->addWidget(redoButton, 1, 7);
    layout->addWidget(saveButton, 2, 7);
    layout->addWidget(loadButton, 3, 7);
    layout->addWidget(menuButton, 4, 7);
    layout->addWidget(exitButton, 5, 7);
    layout->addWidget(status, 6, 7);
    setLayout(layout);

    status->setFixedWidth(status->width());
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
    QString saveString;
    QTextStream stream(&saveFile);
    saveString = stream.readAll();
    saveFile.close();
    board->load(saveString.toStdString());
}

void GameGUI::undo()
{
    board->undo();
}

void GameGUI::redo()
{
    board->redo();
}









