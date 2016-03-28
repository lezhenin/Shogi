#ifndef SHOGI_DIRECTION_H
#define SHOGI_DIRECTION_H


/**
 * @brief Класс, характеризующий направление ходов фигур.
 *
 * Направление внутри класса представлено в виде вектора
 * в двумерном пространстве, значения кординат которого
 * могут быть -1, 0 и 1.
 */
class Direction {

public:
    /**
     * @param     x Координата по оси X
     * @param     Y Координата по оси Y
     * @param limit Количество ходов фигуры по данному направлению.
     */
    Direction(int x, int y, int limit = -1) : x(x),y(y),limit(limit){};
    /*
     * @brief Получить координату по оси X
     */
    int getX() const { return x;}
    /*
     * @brief Получить координату по оси X
     */
    int getY() const { return y;}
    /**
     * @brief Получить максимальное возможное количество ходов
     * фигуры по данному направлению.
     */
    int getLimit() const {return limit;}

private:
    int x;
    int y;
    int limit;
};

#endif //SHOGI_DIRECTION_H
