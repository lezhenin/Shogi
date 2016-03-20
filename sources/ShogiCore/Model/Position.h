#ifndef POSITION_H
#define POSITION_H

///Класс содержащий пару чисел соответсвующих положению фигуры на доске
class Position
{
public:
    ///Конструктор
    Position(const int h, const int v);

    ///Метод, позволяющий получить число соответствующие порядковому номеру вертикали на доске
    int getVertical() const;
    ///Метод, позволяющий получить число соответствующие порядковому номеру горизонтали на доске
    int getHorizontal() const;

    ///Перегрузка операции сравнения
    inline bool operator == (const Position& pos);

    ///Перегрузка операции присвоения
    Position& operator = (const Position& pos);

    ///Деструктор
    ~Position(){};

private:

    int vertical;
    int horizontal;
};

#endif // POSITION_H
