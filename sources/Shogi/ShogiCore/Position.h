#ifndef POSITION_H
#define POSITION_H

/** Объект класса хранит пару целых чисел соотносящихся с клеткой на доске.
Значению переменной vertical соответсвует порядковый номер вертикали,
с учетом того, что отсчет идет от правого края доски. Аналогично значение
переменной horizontal соответствует порядковому номеру горизонтали при
отсчете от верхнего края доски.
-----------Жду конструктивную критику по поводу комментария------------ */

class Position
{
public:

    Position(const int h, const int v);

    int getVertical() const;
    int getHorizontal() const;

    inline bool operator == (const Position& pos);

    Position& operator = (const Position& pos);

    ~Position();

private:

    int vertical;
    int horizontal;
};

#endif // POSITION_H
