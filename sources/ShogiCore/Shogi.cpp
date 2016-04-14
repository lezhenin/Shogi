#include <algorithm>
#include "Shogi.h"


void Shogi::initGame()
{
    gameLoader->loadGame(*board, &currentPlayer);
}

Shogi::Shogi()
{
    board = new Board();
    gameLogic = new ShogiGameLogic(board);
    gameLoader = new GameLoader();
    gameSaver = new GameSaver();
}

Shogi::~Shogi()
{
    clearToRedo();
    clearToUndo();
    delete board;
    delete gameLogic;
    delete gameLoader;
    delete gameSaver;
}

AbstractBoard &Shogi::getBoard() const {
    return *board;
}

void Shogi::pickPiece(const Position &position)
{
    Piece * piece = this->board->getPiece(position);

    if( piece == nullptr)
    {
        throw std::exception();
    }

    if(piece->getPlayer() != currentPlayer)
    {
        throw std::exception();
    }

    this->pickedPiece = piece;
}

void Shogi::unPickPiece()
{
    this->pickedPiece = nullptr;
}

//TODO: кажется, что если переименовать метод в movePickedPiece, будет легче читаться. Нельзя ведь мувить непикнутый?
//TODO: или position в newPosition
void Shogi::movePiece(const Position &position)
{
    if(pickedPiece == nullptr)
    {
        throw std::exception();
    }
    if(!this->gameLogic->checkMove(this->pickedPiece, position))
    {
        throw std::exception();
    }

    toUndo.push(board->getMemento());
    clearToRedo();

    //TODO: предлагаю следующие 8 строк выделить в метод "попробовать захватить фигуру",
    //передать позицию и параметр "захватить/не захватить" -- по умолчанию "захватить"
    //и вернуть значение, получается или нет
    //если я правильно поняла смысл

    //TODO: и что если там будет своя же фигура?
    //есть подозрение, что checkMove это проверил уже, но в ней я не разобралась
    //лучше бы тут еще разочек, если не сложно
    Piece* piece = this->board->getPiece(position);
    if(piece != nullptr)
    {
        piece->unPromote();
        piece->setPlayer(currentPlayer);
        this->board->getCapturedPieces(currentPlayer).push_back(piece);
        this->board->removePiece(position);
    }

    this->board->removePiece(pickedPiece->getPosition());
    this->board->setPiece(pickedPiece, position);


    //TODO:следующие два if просятся в отдельный метода (или два метода)
    if(gameLogic->checkShah(transformPlayer(currentPlayer)))
    {
        gameSituations.push(std::shared_ptr<GameSituation>(new Shah()));
        if(gameLogic->checkMate(transformPlayer(currentPlayer)))
        {
            gameSituations.push(std::shared_ptr<GameSituation>(new Mate()));
        }
    }
    if(gameLogic->checkPromotion(pickedPiece))
    {
       gameSituations.push(std::shared_ptr<GameSituation>(new PromotionIsAvailable(this,position)));
    }

    unPickPiece();
    currentPlayer = transformPlayer(currentPlayer);
}

Player Shogi::transformPlayer(Player player) const
{
    //TODO: лучше просто if, если сенте, то готе, и наоборот
    //если я правильно поняла смысл, потому что transform -- это тоже очень расплывчато
    // nextPlayer? nextTurn?
    return (Player)(((int)player+1)%2);
}

void Shogi::promotePiece(const Position &position)
{
    if(this->board->getPiece(position) == nullptr)
    {
        throw std::exception();
    }
    if(!gameLogic->checkPromotion(this->board->getPiece(position)))
    {
        throw std::exception();
    }
    this->board->getPiece(position)->promote();
}

void Shogi::dropPiece(const PieceType pieceType, const Position &position)
{
    Piece tmp(pieceType,currentPlayer);
    ListOfPieces::iterator it = std::find_if(board->getCapturedPieces(currentPlayer).begin(),board->getCapturedPieces(currentPlayer).end(),
                     std::bind1st(std::mem_fun(&Piece::equals),&tmp));
    if(it == board->getCapturedPieces(currentPlayer).end())
    {
        throw std::exception();
    }

    //TODO:я не умею компилировать ваш код, но мне бы хотелось сделать метод "проверить, есть ли среди захваченных"
    // и м.б. его даже в board,
    // не кажется, что так полегче читать? И не жадничайте на пробелы
/*
    Piece samplePiece(pieceType, currentPlayer);
    auto firstPiece = board->getCapturedPieces(currentPlayer).begin();
    auto lastPiece = board->getCapturedPieces(currentPlayer).end();

    auto it = std::find_if(firstPiece, lastPiece,
                           std::bind1st(std::mem_fun(&Piece::equals), &samplePiece));

    if(it == lastPiece){
        throw std::exception();
    }
    */
    //--------------------------------

    Piece *piece = *it;

    if(!gameLogic->checkDrop(piece, position))
    {
        throw std::exception();
    }

    toUndo.push(board->getMemento());
    clearToRedo();

    board->getCapturedPieces(currentPlayer).remove(piece);
    board->setPiece(piece, position);

    currentPlayer = transformPlayer(currentPlayer);
}

ListOfGameSituations &Shogi::getGameSituation()
{
    return gameSituations;
}

bool Shogi::undo()
{
    if(!toUndo.empty())
    {
        toRedo.push(board->getMemento());
        board->setMemento(toUndo.top());
        delete toUndo.top();
        toUndo.pop();
        currentPlayer = transformPlayer(currentPlayer);
        return true;
    }
    return false;
}

bool Shogi::redo()
{
    if(!toRedo.empty())
    {
        toUndo.push(board->getMemento());
        board->setMemento(toRedo.top());
        delete toRedo.top();
        toRedo.pop();
        currentPlayer = transformPlayer(currentPlayer);
        return true;
    }
    return false;
}

Player Shogi::getCurrentPlayer () const
{
    return currentPlayer;
}

void Shogi::clearToUndo()
{

    while(!toUndo.empty())
    {
        delete toUndo.top();
        toUndo.pop();
    }
}

void Shogi::clearToRedo()
{
    while(!toRedo.empty())
    {
        delete toRedo.top();
        toRedo.pop();
    }
}































