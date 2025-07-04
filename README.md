# Крестики-нолики на C++

## Описание проекта
Консольная реализация классической игры "Крестики-нолики" с поддержкой игры между двумя игроками и против компьютера с тремя уровнями сложности. Проект разработан в рамках учебной практики для демонстрации навыков программирования на C++.

## Демо

https://github.com/DenZib-Pha/krestiv2/blob/main/image.png
https://github.com/DenZib-Pha/krestiv2/blob/main/oform.jpg
https://github.com/DenZib-Pha/krestiv2/blob/main/protivV.jpg


## Технологии и особенности
- **Язык:** C++ (стандарт C++17)
- **Платформа:** Windows (совместимо с Linux)
- **Ключевые алгоритмы:**
  - Минимакс для сложного уровня ИИ
  - Логика блокировки для среднего уровня
  - Случайные ходы для легкого уровня
- **Особенности:**
  - Валидация пользовательского ввода
  - Локализация (русский/английский)
  - Чистая архитектура с разделением ответственности


### Проблемы и решения
1. **Конфликт макросов в Windows**  
   Решение: `#define NOMINMAX` перед подключением заголовков

2. **Кодировка русских символов**  
   Решение: `setlocale(LC_ALL, "Russian")`

3. **Производительность минимакса**  
   Оптимизировано для поля 3×3

### Уникальные составляющие
- Три уровня сложности ИИ
- Подробные комментарии для учебных целей
- Система обработки ошибок ввода


### Установка и запуск
**Требования:**
- Компилятор C++ (GCC 9+ / MSVC 2019+)
- CMake 3.10+ (опционально)

