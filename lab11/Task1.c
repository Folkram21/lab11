#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

// структура для координатной точки
struct point {
    float x;
    float y;
    char name;
};

// псевдоним
typedef struct point Point;

// отображение точки
void put_point(Point z) {
    printf("point %c (%.1f, %.1f)\n", z.name, z.x, z.y);
}

// вычисление расстояния между двумя точками
float dist(Point z, Point w) {
    return sqrtf((z.x - w.x) * (z.x - w.x) + (z.y - w.y) * (z.y - w.y));
}

// получение середины отрезка
Point get_midpoint(Point z, Point w) {
    Point mid;
    mid.name = 'M'; // назовем серединную точку буквой M
    mid.x = (z.x + w.x) / 2.0f;
    mid.y = (z.y + w.y) / 2.0f;
    return mid;
}

// определение координатной четверти
void get_quarter(Point z) {
    if (z.x > 0 && z.y > 0)       printf("Точка %c в I четверти\n", z.name);
    else if (z.x < 0 && z.y > 0)  printf("Точка %c во II четверти\n", z.name);
    else if (z.x < 0 && z.y < 0)  printf("Точка %c в III четверти\n", z.name);
    else if (z.x > 0 && z.y < 0)  printf("Точка %c в IV четверти\n", z.name);
    else                          printf("Точка %c лежит на осях\n", z.name);
}

int main() {
    setlocale(LC_CTYPE, "RUS");

    // инициализация 1-ой точки
    Point a;
    a.name = 'A';
    printf("Введите координаты точки A (x y): ");
    scanf("%f %f", &a.x, &a.y);

    // инициализация 2-ой точки
    Point b;
    b.name = 'B';
    printf("Введите координаты точки B (x y): ");
    scanf("%f %f", &b.x, &b.y);

    // вывод точек
    put_point(a);
    put_point(b);

    // расстояние между точками
    printf("Расстояние между A и B: %.2f\n", dist(a, b));

    // вычисление середины
    Point m = get_midpoint(a, b);
    printf("Середина отрезка: ");
    put_point(m);

    // проверка четвертей
    get_quarter(a);
    get_quarter(b);

    return 0;
}
