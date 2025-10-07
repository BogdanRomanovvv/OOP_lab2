(# OOP_lab2 — краткий гайд по сборке (PowerShell)

## 1) Сборка вручную (PowerShell)

1. Откройте PowerShell и перейдите в корень репозитория:

```powershell
cd D:\OOP_lab2
```

2. Создайте каталог сборки и соберите проект через CMake:

```powershell

mkdir build
cd build
cmake ..                       
cmake --build . --config Release
```

3. Запустите тесты:

```powershell
ctest -C Release --output-on-failure
```



## 2) Сборка через VS Code Dev Container (PowerShell host)


Шаги для использования уже настроенного devcontainer:

1. Установите в VS Code расширение "Dev Containers" (Remote - Containers) если ещё не установлено.
2. Откройте папку проекта `D:\OOP_lab2` в VS Code.
3. Откройте палитру (Ctrl+Shift+P) и выберите "Dev Containers: Reopen in Container". VS Code соберёт образ (если указано `build`) или скачает образ (если указано `image`) и откроет рабочую среду.
4. В терминале внутри контейнера выполните команды сборки (терминал в контейнере обычно bash):

```powershell
# (в PowerShell host, если нужно) cd D:\OOP_lab2
# в терминале контейнера:
mkdir -p build; cd build
cmake ..
cmake --build . --config Release
ctest -C Release --output-on-failure
```

## 3) Сборка в Docker-контейнере (PowerShell host)

1. Убедитесь, что Docker установлен и запущен.
2. Постройте образ (в корне репозитория — там где `Dockerfile` если он есть):

```powershell
cd D:\OOP_lab2
docker build -t oop_lab2:latest .
```

3. Запустите контейнер и выполните сборку внутри него (монтаж текущей папки в контейнер):

```powershell
docker run --rm -it -v "${pwd}:/workspace" -w /workspace oop_lab2:latest bash -lc "cmake -S . -B build && cmake --build build -- -j && ctest --test-dir build --output-on-failure"
```

