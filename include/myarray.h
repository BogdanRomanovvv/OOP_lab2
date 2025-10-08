#pragma once // Защита от повторного включения

#include <cstddef>   // Для size_t
#include <stdexcept> // Для исключений

// Класс реализует динамический массив для хранения элементов типа unsigned char
// Интерфейс объявлен в этом заголовочном файле
class MyArray
{       // Основной класс массива
public: // Открытая часть класса
    // Конструктор по умолчанию, создаёт пустой массив
    MyArray() noexcept;
    // Конструктор: создаёт массив заданного размера, заполняет значением fill
    MyArray(size_t n, unsigned char fill = 0);
    // Конструктор: копирует данные из внешнего буфера
    MyArray(const unsigned char *data, size_t n);

    // Правило пяти: копирующий конструктор
    MyArray(const MyArray &other);
    // Правило пяти: перемещающий конструктор
    MyArray(MyArray &&other) noexcept;
    // Явные методы присваивания
    MyArray &copyAssign(const MyArray &other);     // копирующее присваивание
    MyArray &moveAssign(MyArray &&other) noexcept; // перемещающее присваивание

    // Деструктор: освобождает память
    ~MyArray() noexcept;

    // Возвращает количество элементов в массиве
    size_t size() const noexcept;
    // Получить элемент по индексу (только для чтения, с проверкой границ)
    unsigned char get(size_t idx) const;
    // Установить значение элемента по индексу (может менять данные)
    void set(size_t idx, unsigned char value);

    // Получить указатель на внутренний буфер данных (только для чтения)
    const unsigned char *data() const noexcept;

private:                  // Закрытая часть класса
    size_t size_;         // Текущий размер массива
    unsigned char *data_; // Указатель на выделенную память под элементы
}; // Конец объявления класса
