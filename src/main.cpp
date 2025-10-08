#include <iostream>
#include "twelve.h"

int main()
{
    Twelve t0;
    Twelve t1(3, 1);
    Twelve t2({3, 10, 11});
    Twelve t3("1B");

    std::cout << "t0 = " << t0.ToString() << "\n";
    std::cout << "t1 = " << t1.ToString() << "\n";
    std::cout << "t2 = " << t2.ToString() << "\n";
    std::cout << "t3 = ";
    t3.print(std::cout);
    std::cout << "\n";

    Twelve sum = t2.add(t3);
    std::cout << t2.ToString() << " + " << t3.ToString() << " = " << sum.ToString() << "\n";

    try
    {
        Twelve diff = sum.subtract(t1);
        std::cout << sum.ToString() << " - " << t1.ToString() << " = " << diff.ToString() << "\n";
    }
    catch (const std::exception &ex)
    {
        std::cout << "Ошибка при вычитании: " << ex.what() << "\n";
    }

    std::cout << "t1 == t2 ? " << (t1.equals(t2) ? "да" : "нет") << "\n";
    std::cout << "t1 < t2 ? " << (t1.lessThan(t2) ? "да" : "нет") << "\n";
    std::cout << "t2 > t3 ? " << (t2.greaterThan(t3) ? "да" : "нет") << "\n";

    Twelve aAssign = t1.addAssign(t3);
    std::cout << "t1 + t3 (addAssign) = " << aAssign.ToString() << "\n";

    std::cout << "Готово\n";
    return 0;
}
