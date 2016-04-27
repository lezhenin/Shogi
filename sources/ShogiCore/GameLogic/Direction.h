#ifndef SHOGI_DIRECTION_H
#define SHOGI_DIRECTION_H

namespace shogi
{
    enum Directions
    {
        UP = 1, DOWN = -1,
        RIGHT = 1, LEFT = -1
    };

    /**
     * @brief Класс, характеризующий направление ходов фигур.
     *
     * Направление внутри класса представлено в виде вектора
     * в двумерном пространстве, значения кординат которого
     * должны соответствовать разнице координат фигуры на доске
     * до и после хода на минимальное возможное расстояние в
     * данном направлении.
     */
    class Direction
    {

    public:
        /**
		 * @param     x Координата по оси X
		 * @param     Y Координата по оси Y
		 * @param limit Количество ходов фигуры по данному направлению.
		 */
        Direction(int x, int y, int limit = -1) noexcept : x(x), y(y), limit(limit) { }

        /**
		 * @brief Получить координату по оси X
		 */
        int getX() const noexcept
        {
            return x;
        }

        /**
		 * @brief Получить координату по оси X
		 */
        int getY() const noexcept
        {
            return y;
        }

        /**
		 * @brief Получить максимальное возможное количество ходов
		 * фигуры по данному направлению.
		 */
        int getLimit() const noexcept
        {
            return limit;
        }

    private:

        int x;
        int y;
        int limit;
    };
}

#endif //SHOGI_DIRECTION_H
