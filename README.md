# 1CQualification — String search

В решении используется сразу несколько алгоритмов и рассматривается возможность,
что файл может не поместиться в оперативную память.

## Установка

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```


## Использование
```
Search substring in a file, enter pattern in stdin. Type !exit to exit
Usage:
  StringMatch [OPTION...]

  -f, --file arg      File name
  -s, --single        Get first entry only
  -x, --extralarge    Extra large file search. O(nm) solution but can work 
                      with extra large data
  -b, --buffSize arg  Buffer size for extra large mode in bytes. 100Mb by default 
  -v, --verbose       Verbose (default: true)
  -h, --help          Print usage
```

## Алгоритм

В случае большого файла, он разбивается на пересекающиеся куски и каждый кусок обрабатывается как указано ниже.

Для `pattern` размеров 1, 2, 4, 8 используется оптимизация маленьких строк: `pattern` хранится в `uint{16, 32, 64}_t`. Для однобайтовых `pattern` используется `strchr`.

В остальных случаях применяется два алгоритма:

- Только первое вхождение
В этом случае используется сжатый бор. Построение алгоритмом Укконена.
  - Асимптотика построения: O(|text|)
  - Асимптотика ответа: O(|pattern|)
- Все вхождения
Используется алгоритм Кнута-Морриса-Пратта
  - Асимптотика построения: O(1)
  - Асимптотика ответа: O(|text|)

## Тестирование

```bash
mkdir testbuild
cd testbuild
cmake ..
make
ctest
```

## Doxygen документация
<a href="https://alexroar.github.io/1CQualification/annotated.html">link</a>
