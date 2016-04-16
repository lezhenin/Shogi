#ifndef POSITION_H
#define POSITION_H

namespace shogi
{
    /**
     * @brief Класс содержащий пару чисел соответсвующих положению фигуры на доске
     */
    class Position
    {
    public:

        /**
		* @brief Конструктор
		*
		* @param[in] h Порядковый номер горизонтали.
		* @param[in] v Порядковый номер вертикали.
		*/
        Position(const int horizontal, const int vertical);

        /**
		 * @brief Получить порядковый номер вертикали.
		 *
		 * @return Порядковый номер вертикали соотвествующий данной позиции.
		 */
        int getVertical() const;

        /**
		 * @brief Получить порядковый номер горизонтали.
		 *
		 * @return Порядковый номер гоизонтали соотвествующий данной позиции.
		 */
        int getHorizontal() const;

        /**
		 * @brief Сравнить две позиции.
		 *
		 * Сравнивает порядковые номера вертикалей и горизонталей,
		 * содержащихся в двух объектах.
		 */
        bool operator ==(const Position &position) const;

        bool operator !=(const Position &position) const;

        /**
		 * @brief Присвоить значение
		 *
		 * Присваивает занчения данных одного объекта другому.
		 */
        Position &operator =(const Position &position);

        /**
		 * @brief Деструтор
		 */
        ~Position()
        {
        }

    private:

        int vertical;
        int horizontal;
    };
}
#endif // POSITION_H
