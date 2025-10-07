#include "myarray.h"
#include <cstring>
#include <stdexcept>

MyArray::MyArray() noexcept : size_(0), data_(nullptr)
{
}

MyArray::MyArray(size_t n, unsigned char fill) : size_(0), data_(nullptr)
{
    if (n == 0)
        return;
    size_ = n;
    data_ = new unsigned char[size_];
    unsigned char v = (fill <= 11 ? fill : 0);
    for (size_t i = 0; i < size_; ++i)
        data_[i] = v;
}

MyArray::MyArray(const unsigned char *data, size_t n) : size_(0), data_(nullptr)
{
    if (n == 0)
        return;
    size_ = n;
    data_ = new unsigned char[size_];
    std::memcpy(data_, data, size_ * sizeof(unsigned char));
}

MyArray::MyArray(const MyArray &other) : size_(0), data_(nullptr)
{
    if (other.size_ == 0)
        return;
    size_ = other.size_;
    data_ = new unsigned char[size_];
    std::memcpy(data_, other.data_, size_ * sizeof(unsigned char));
}

MyArray::MyArray(MyArray &&other) noexcept : size_(other.size_), data_(other.data_)
{
    other.size_ = 0;
    other.data_ = nullptr;
}

MyArray &MyArray::operator=(const MyArray &other)
{
    if (this == &other)
        return *this;

    unsigned char *new_data = nullptr;
    if (other.size_ > 0)
    {
        new_data = new unsigned char[other.size_];
        std::memcpy(new_data, other.data_, other.size_ * sizeof(unsigned char));
    }

    delete[] data_;
    data_ = new_data;
    size_ = other.size_;
    return *this;
}

MyArray &MyArray::operator=(MyArray &&other) noexcept
{
    if (this == &other)
        return *this;
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
    return *this;
}

MyArray::~MyArray() noexcept
{
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
}

size_t MyArray::size() const noexcept
{
    return size_;
}

unsigned char MyArray::get(size_t idx) const
{
    if (idx >= size_)
        throw std::out_of_range("MyArray::get index out of range");
    return data_[idx];
}

void MyArray::set(size_t idx, unsigned char value)
{
    if (idx >= size_)
        throw std::out_of_range("MyArray::set index out of range");
    data_[idx] = value;
}

const unsigned char *MyArray::data() const noexcept
{
    return data_;
}
