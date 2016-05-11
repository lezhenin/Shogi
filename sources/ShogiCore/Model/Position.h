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
        Position(const int horizontal, const int vertical) noexcept;

        /**
		 * @brief Получить порядковый номер вертикали.
		 *
		 * @return Порядковый номер вертикали соотвествующий данной позиции.
		 */
        int getVertical() const noexcept;

        /**
		 * @brief Получить порядковый номер горизонтали.
		 *
		 * @return Порядковый номер гоизонтали соотвествующий данной позиции.
		 */
        int getHorizontal() const noexcept;

        /**
		 * @brief Сравнить две позиции.
		 *
		 * Сравнивает порядковые номера вертикалей и горизонталей,
		 * содержащихся в двух объектах.
		 */
        bool operator ==(const Position &position) const noexcept;

        bool operator !=(const Position &position) const noexcept;

        /**
		 * @brief Присвоить значение
		 *
		 * Присваивает занчения данных одного объекта другому.
		 */
        Position &operator =(const Position &position) noexcept;

        /**
		 * @brief Деструтор
		 */
        ~Position()
        {
        }

    private:

        int vertical = 0;
        int horizontal = 0;
    };
}
#endif // POSITION_H
