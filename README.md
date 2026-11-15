# Chess

Шахматы на C++17 с использованием библиотеки [SFML 2](https://www.sfml-dev.org/).

## Требования

- CMake 3.16 или новее
- Компилятор с поддержкой C++17 (GCC или Clang)
- SFML 2.x с модулями `graphics`, `window`, `system`

### Установка зависимостей

**Fedora**

```bash
sudo dnf install gcc-c++ cmake SFML-devel
```

Проверить версию SFML: `dnf info SFML-devel`. Проект рассчитан на версию 2.x.

**Ubuntu / Debian**

```bash
sudo apt install build-essential cmake libsfml-dev
```

**Windows**

Установите SFML 2.x с сайта sfml-dev.org и CMake, затем используйте Visual Studio или MinGW. Сборка описана в разделе «Сборка».

## Сборка

Из корня проекта (папки с `CMakeLists.txt`):

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

- `-S .` — папка с исходниками.
- `-B build` — папка для файлов сборки. Её можно удалить в любой момент.
- `-DCMAKE_BUILD_TYPE=Debug` — сборка с отладочной информацией. Для релиза используйте `Release`.

Для Windows с Visual Studio:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Запуск

```bash
./build/chess
```

На Windows программа находится в `build\Release\chess.exe` (или `build\Debug\chess.exe`).

## Структура проекта

```
Chess/
├── CMakeLists.txt     # описание сборки
├── README.md          # этот файл
├── include/           # заголовочные файлы (.h, .hpp)
└── src/               # исходный код (.cpp)
    ├── main.cpp       # точка входа
    ├── global.cpp
    ├── draw.cpp
    └── TextureLoader.cpp
```

Если создаёте новый файл `.cpp`, добавьте его в список `add_executable` в `CMakeLists.txt`.

## Очистка

```bash
rm -rf build
```

Удаление папки `build` не затрагивает исходный код. Перед коммитом в git добавьте `build/` в `.gitignore`.
