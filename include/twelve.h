#pragma once // Защита от повторного включения

#include <string>           // Для работы со строками
#include <initializer_list> // Для инициализации списка
#include <iostream>         // Для вывода в поток
#include <stdexcept>        // Для обработки исключений
#include <cstddef>          // Для size_t
#include "myarray.h"        // Подключение класса MyArray

// Класс Twelve — реализует целое число в двенадцатеричной системе.
// Внутри использует MyArray как динамический буфер для хранения цифр.
// Объекты неизменяемы: все операции возвращают новый объект.

class Twelve
{
public: // Открытая часть класса
    // Конструктор по умолчанию, создаёт число 0
    Twelve();
    // Конструктор: создаёт число с заданным количеством цифр и значением по умолчанию
    Twelve(const size_t &n, unsigned char defaultDigit = 0);
    // Конструктор: инициализация из списка цифр (от младшей к старшей)
    Twelve(const std::initializer_list<unsigned char> &digits);
    // Конструктор: инициализация из строки
    Twelve(const std::string &digitsStr);

    // Правило пяти: копирующий конструктор
    Twelve(const Twelve &other);
    // Правило пяти: перемещающий конструктор
    Twelve(Twelve &&other) noexcept;
    // Правило пяти: копирующее присваивание
    Twelve &operator=(const Twelve &other);
    // Правило пяти: перемещающее присваивание
    Twelve &operator=(Twelve &&other) noexcept;
    // Виртуальный деструктор
    virtual ~Twelve() noexcept;

    // Арифметические операции: сложение и вычитание
    Twelve add(const Twelve &other) const;      // Возвращает сумму
    Twelve subtract(const Twelve &other) const; // Возвращает разность

    // Методы для операций с присваиванием (возвращают новый объект)
    Twelve addAssign(const Twelve &other) const { return add(other); }           // Сложение с присваиванием
    Twelve subtractAssign(const Twelve &other) const { return subtract(other); } // Вычитание с присваиванием

    // Операции сравнения
    bool equals(const Twelve &other) const;      // Проверка на равенство
    bool lessThan(const Twelve &other) const;    // Проверка на меньше
    bool greaterThan(const Twelve &other) const; // Проверка на больше

    // Преобразование к строке и вывод
    std::string ToString() const;                // Преобразует число в строку
    std::ostream &print(std::ostream &os) const; // Выводит число в поток

private: // Закрытая часть класса
    // Внутренний динамический массив для хранения цифр
    MyArray digits_; // Младшая цифра хранится в индексе 0

    // Приватный конструктор: инициализация из MyArray
    Twelve(const MyArray &digits);

    // Вспомогательные методы
    void normalize();                         // Удаляет ведущие нули (оставляет хотя бы одну цифру)
    static unsigned char charToDigit(char c); // Преобразует символ в цифру
    static char digitToChar(unsigned char d); // Преобразует цифру в символ
}; // Конец объявления класса
