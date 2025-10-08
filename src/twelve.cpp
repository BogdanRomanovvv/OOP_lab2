#include "twelve.h"
#include <cctype>
#include <sstream>
#include <cstring>

unsigned char Twelve::charToDigit(char c)
{
    if (c >= '0' && c <= '9')
        return static_cast<unsigned char>(c - '0');
    char up = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    if (up == 'A')
        return 10;
    if (up == 'B')
        return 11;
    throw std::invalid_argument(std::string("Invalid digit character: ") + c);
}

char Twelve::digitToChar(unsigned char d)
{
    if (d <= 9)
        return static_cast<char>('0' + d);
    if (d == 10)
        return 'A';
    if (d == 11)
        return 'B';
    return '?';
}

// ===== Приватные конструкторы и вспомогательные методы =====
Twelve::Twelve(const MyArray &digits) : digits_(digits)
{
    normalize();
}

// По умолчанию создаёт число 0
Twelve::Twelve() : digits_(1, 0)
{
}

// Конструктор по размеру и значению по умолчанию
Twelve::Twelve(const size_t &n, unsigned char defaultDigit) : digits_((n < 1) ? 1 : n, (defaultDigit <= 11 ? defaultDigit : 0))
{
}

// Конструктор из initializer_list (ожидается порядок: младшие -> старшие)
Twelve::Twelve(const std::initializer_list<unsigned char> &digits)
{
    size_t n = digits.size();
    if (n == 0)
    {
        digits_.moveAssign(MyArray(1, 0));
        return;
    }
    unsigned char *raw = new unsigned char[n];
    size_t idx = 0;
    for (auto d : digits)
    {
        if (d > 11)
        {
            delete[] raw;
            throw std::invalid_argument("digit > 11 in initializer_list");
        }
        raw[idx++] = d;
    }
    digits_.moveAssign(MyArray(raw, n));
    delete[] raw;
    normalize();
}

// Конструктор из строки: порядок MSB...LSB (например "1B" -> '1' старшая, 'B' младшая)
Twelve::Twelve(const std::string &digitsStr)
{
    std::string s;
    for (char c : digitsStr)
        if (!std::isspace(static_cast<unsigned char>(c)))
            s.push_back(c);
    if (s.empty())
        throw std::invalid_argument("Empty string");
    size_t n = s.size();
    unsigned char *raw = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
    {
        // Младшую цифру берём с конца строки
        raw[i] = charToDigit(s[n - 1 - i]);
    }
    digits_.moveAssign(MyArray(raw, n));
    delete[] raw;
    normalize();
}

Twelve::Twelve(const Twelve &other) : digits_(other.digits_)
{
    // Копирующий конструктор (MyArray копирует данные)
}

Twelve::Twelve(Twelve &&other) noexcept : digits_(std::move(other.digits_))
{
    // Перемещающий конструктор
}

Twelve &Twelve::copyAssign(const Twelve &other)
{
    if (this == &other)
        return *this;
    digits_.copyAssign(other.digits_);
    return *this;
}

Twelve &Twelve::moveAssign(Twelve &&other) noexcept
{
    if (this == &other)
        return *this;
    digits_.moveAssign(std::move(other.digits_));
    return *this;
}

Twelve::~Twelve() noexcept
{
    // MyArray сам освободит память
}

// Удаление ведущих нулей (старшие нули), оставляем хотя бы одну цифру
void Twelve::normalize()
{
    size_t sz = digits_.size();
    if (sz == 0)
    {
        digits_.moveAssign(MyArray(1, 0));
        return;
    }
    // Находим индекс старшей ненулевой цифры
    ptrdiff_t hi = static_cast<ptrdiff_t>(sz) - 1;
    while (hi > 0 && digits_.get(static_cast<size_t>(hi)) == 0)
        --hi;
    size_t newSize = static_cast<size_t>(hi) + 1;
    if (newSize != sz)
    {
        unsigned char *raw = new unsigned char[newSize];
        for (size_t i = 0; i < newSize; ++i)
            raw[i] = digits_.get(i);
        digits_.moveAssign(MyArray(raw, newSize));
        delete[] raw;
    }
}

// ===== Арифметические операции =====
Twelve Twelve::add(const Twelve &other) const
{
    size_t aSz = digits_.size();
    size_t bSz = other.digits_.size();
    size_t maxLen = (aSz > bSz) ? aSz : bSz;
    unsigned char *res = new unsigned char[maxLen + 1];
    unsigned carry = 0;
    for (size_t i = 0; i < maxLen; ++i)
    {
        unsigned a = (i < aSz) ? digits_.get(i) : 0;
        unsigned b = (i < bSz) ? other.digits_.get(i) : 0;
        unsigned sum = a + b + carry;
        res[i] = static_cast<unsigned char>(sum % 12);
        carry = sum / 12;
    }
    res[maxLen] = static_cast<unsigned char>(carry);
    size_t realSize = maxLen + (carry ? 1 : 0);
    MyArray out(res, realSize);
    delete[] res;
    return Twelve(out);
}

Twelve Twelve::subtract(const Twelve &other) const
{
    if (this->lessThan(other))
        throw std::logic_error("Cannot subtract: result would be negative");
    size_t aSz = digits_.size();
    unsigned char *res = new unsigned char[aSz];
    int borrow = 0;
    for (size_t i = 0; i < aSz; ++i)
    {
        int a = digits_.get(i);
        int b = (i < other.digits_.size()) ? other.digits_.get(i) : 0;
        int sub = a - b - borrow;
        if (sub < 0)
        {
            sub += 12;
            borrow = 1;
        }
        else
            borrow = 0;
        res[i] = static_cast<unsigned char>(sub);
    }
    MyArray out(res, aSz);
    delete[] res;
    Twelve result(out);
    return result;
}

// ===== Операции сравнения =====
bool Twelve::equals(const Twelve &other) const
{
    size_t aSz = digits_.size();
    size_t bSz = other.digits_.size();
    if (aSz != bSz)
        return false;
    for (size_t i = 0; i < aSz; ++i)
        if (digits_.get(i) != other.digits_.get(i))
            return false;
    return true;
}

bool Twelve::lessThan(const Twelve &other) const
{
    size_t aSz = digits_.size();
    size_t bSz = other.digits_.size();
    if (aSz != bSz)
        return aSz < bSz;
    for (ptrdiff_t i = static_cast<ptrdiff_t>(aSz) - 1; i >= 0; --i)
    {
        unsigned char ad = digits_.get(static_cast<size_t>(i));
        unsigned char bd = other.digits_.get(static_cast<size_t>(i));
        if (ad < bd)
            return true;
        if (ad > bd)
            return false;
    }
    return false;
}

bool Twelve::greaterThan(const Twelve &other) const
{
    return (!equals(other)) && (!lessThan(other));
}

// ===== ToString / print =====
std::string Twelve::ToString() const
{
    std::ostringstream oss;
    size_t sz = digits_.size();
    for (ptrdiff_t i = static_cast<ptrdiff_t>(sz) - 1; i >= 0; --i)
    {
        oss << digitToChar(digits_.get(static_cast<size_t>(i)));
    }
    return oss.str();
}

std::ostream &Twelve::print(std::ostream &os) const
{
    os << ToString();
    return os;
}
