# Ревью ядра 10.04.2016

* Нет нужды создавать отдельные файлы **Shah.cpp** и **Mate.cpp**, в которых реализуется маленький метод, проще сделать так же, как и в **GameSituation.h**, т.е. реализовать их в файлах **Shah.h** и **Mate.h**

* В файле **PromotionIsAvailable.cpp** перекидывается исключение:
```cpp
try
{
  game->promotePiece(position);
}
catch (std::exception &e)
{
  throw e;
}
```
Во-первых, ты назвал объект ни о чём не говорящим названием. Во-вторых, зачем вообще перекидывать исключение? В-третьих, кидается объект класса 'exception', почему бы не создать свой собственный?

* Некоторые комментарии оформлены не в стиле `doxygen`, например, в файлах **AbstractShogiGameLogic.h** и **ShogiGameLogic.h** :
```cpp
/*
 * @brief Реализация AbstractShogiGameLogic.
 */
class ShogiGameLogic: public AbstractShogiGameLogic
```
 По факту не хватает *
 
 * Присутствую описки в комментариях, например, в файле **ShogiGameAPI.h** :
```cpp
/**
 * @brief Выбрать фигуру.
 * Созраняет фигуру для дальнейших действий.
 * @param position Позиция фигуры.
 */
virtual void pickPiece(const Position& position)=0;
```
 
 * Не все методы прокомментированы, например в файле **AbstractGameLoader.h** :
```cpp
/**
 *
 */
virtual void loadGame(const Save &save, AbstractBoard &board) = 0;
```
