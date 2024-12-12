#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

#define PLAIN_WIDTH 129
#define PLAIN_HEIGHT 65
#define PI 3.14159265358979323846

char plain[PLAIN_HEIGHT][PLAIN_WIDTH];

void printPlain(char* arrayStart);
void drawFunction(double (*func)(double), char symbol, double x_start, double x_end);
void selection(string name, char symbol);

// Можно добавлять функции, которых нет в math.h
double cube(double x);
double squareFunc(double x);
double ctg(double x);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Инициализация координатной плоскости
    for (int y = 0; y < PLAIN_HEIGHT; y++) {
        for (int x = 0; x < PLAIN_WIDTH; x++) {
            plain[y][x] = '.';
            plain[PLAIN_HEIGHT / 2-1][x] = '-'; // Ось X
        }
        plain[y][PLAIN_WIDTH / 2-1] = '|'; // Ось Y
    }

    plain[PLAIN_HEIGHT / 2][PLAIN_WIDTH - 1] = 'x';
    plain[PLAIN_HEIGHT / 2 - 1][PLAIN_WIDTH - 1] = '>';
    plain[0][PLAIN_WIDTH / 2-2] = 'y';
    plain[0][PLAIN_WIDTH / 2-1] = '^';


    // Блок выбора функции
    int choice;
    cout << "Сколько функций вы хотите видеть? (до 5): "; cin >> choice;
    if (choice <= 5 && choice > 0) {
        for (int i = 1; i <= choice; i++) {
            string functionName;
            cout << i << ". Какую функцию вы хотите видеть? (cos, sin, tg, ctg, log, abs, square, cube) "; cin >> functionName;
            char symbol;
            cout << "Каким символом вы хотите видеть начерченную функцию? ";
            cin >> symbol;
            selection(functionName, symbol);
        }

        // Вывод плоскости
        char* plainPtr = &(plain[0][0]);
        printPlain(plainPtr);
    }
    else {
        cerr << "Ошибка! Out of range." << endl;
    }

    return 0;
}

void printPlain(char* arrayStart) {
    int i = 1;
    while (i <= PLAIN_WIDTH * PLAIN_HEIGHT) {
        cout << *(arrayStart + i - 1);
        if (i % PLAIN_WIDTH == 0) {
            cout << endl;
        }
        i++;
    }
}


void drawFunction(double (*func)(double), char symbol, double x_start, double x_end) {
    for (double x = x_start; x <= x_end; x += 0.1) {
        double y = func(x);

        int screenX = static_cast<int>((x + PI) * (PLAIN_WIDTH / (2 * PI)));
        int screenY = static_cast<int>(-y * 10 + PLAIN_HEIGHT / 2); // Масштаб по y

        // Проверка границ массива
        if (screenX >= 0 && screenX < PLAIN_WIDTH && screenY >= 0 && screenY < PLAIN_HEIGHT) {
            if (plain[screenY][screenX] == '.') { // Проверяем, свободна ли ячейка
                plain[screenY][screenX] = symbol;
            }
        }
    }
}


void selection(string name, char symbol) {
    if (name == "cos") {
        drawFunction(cos, symbol, -PI, PI);
    }
    else if (name == "sin") {
        drawFunction(sin, symbol, -PI, PI);
    }
    else if (name == "tg") {
        drawFunction(tan, symbol, -PI / 2, PI / 2);
    }
    else if (name == "ctg") {
        drawFunction(ctg, symbol, -PI, PI);
    }
    else if (name == "square") {
        drawFunction(squareFunc, symbol, -PI, PI);
    }
    else if (name == "cube") {
        drawFunction(cube, symbol, -PI, PI);
    }
    else if (name == "log") {
        drawFunction(log, symbol, 0.1, 64);
    }
    else if (name == "abs") {
        drawFunction(abs, symbol, -64, 64);
    }
    else {
        cerr << "Ошибка! Программа не поддерживает такую функцию!" << endl;
    }
}


double cube(double x) {
    return x * x * x;
}

double squareFunc(double x) {
    return x * x - 2;
}
double ctg(double x) {
    return cos(x) / sin(x);
}