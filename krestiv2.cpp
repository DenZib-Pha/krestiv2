#define NOMINMAX
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <clocale>
#include <algorithm>

using namespace std;

const int SIZE = 3;
vector<vector<char>> board(SIZE, vector<char>(SIZE, ' '));

// Функция для отображения игрового поля
void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << "|";
        }
        cout << endl;
        if (i < SIZE - 1) {
            cout << "  -----" << endl;
        }
    }
    cout << endl;
}

// Проверка победы
bool checkWin(char player) {
    // Проверка строк и столбцов
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    // Проверка диагоналей
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

// Проверка ничьей
bool checkDraw() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Проверка допустимости хода
bool isValidMove(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

// Ход компьютера (легкий уровень - случайный ход)
void makeEasyComputerMove(char computer) {
    vector<pair<int, int>> availableMoves;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                availableMoves.emplace_back(i, j);
            }
        }
    }

    if (!availableMoves.empty()) {
        int randomIndex = rand() % availableMoves.size();
        int row = availableMoves[randomIndex].first;
        int col = availableMoves[randomIndex].second;
        board[row][col] = computer;
        cout << "Компьютер походил: " << row << " " << col << endl;
    }
}

// Ход компьютера (средний уровень - базовый ИИ)
void makeMediumComputerMove(char computer) {
    char human = (computer == 'X') ? 'O' : 'X';

    // 1. Проверить, может ли компьютер выиграть следующим ходом
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                if (checkWin(computer)) {
                    cout << "Компьютер походил: " << i << " " << j << endl;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 2. Проверить, может ли игрок выиграть следующим ходом, и заблокировать
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = human;
                if (checkWin(human)) {
                    board[i][j] = computer;
                    cout << "Компьютер походил: " << i << " " << j << endl;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 3. Если ничего из вышеперечисленного, сделать случайный ход
    makeEasyComputerMove(computer);
}

// Минимакс алгоритм для сложного уровня
int minimax(char player, char computer, char human) {
    if (checkWin(computer)) return 10;
    if (checkWin(human)) return -10;
    if (checkDraw()) return 0;

    int bestScore = (player == computer) ? -1000 : 1000;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int score = minimax((player == computer) ? human : computer, computer, human);
                board[i][j] = ' ';

                if (player == computer) {
                    bestScore = max(score, bestScore);
                }
                else {
                    bestScore = min(score, bestScore);
                }
            }
        }
    }
    return bestScore;
}

// Ход компьютера (сложный уровень - минимакс алгоритм)
void makeHardComputerMove(char computer) {
    char human = (computer == 'X') ? 'O' : 'X';
    int bestScore = -1000;
    pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = computer;
                int score = minimax(human, computer, human);
                board[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = { i, j };
                }
            }
        }
    }

    if (bestMove.first != -1) {
        board[bestMove.first][bestMove.second] = computer;
        cout << "Компьютер походил: " << bestMove.first << " " << bestMove.second << endl;
    }
}

// Режим игры против компьютера
void playerVsComputer() {
    cout << "Выберите уровень сложности:\n";
    cout << "1 - Легкий\n2 - Средний\n3 - Сложный\n";
    int difficulty;
    cin >> difficulty;

    while (difficulty < 1 || difficulty > 3) {
        cout << "Неверный ввод. Выберите 1, 2 или 3: ";
        cin >> difficulty;
    }

    char human, computer;
    cout << "Выберите символ (X или O, X ходит первым): ";
    cin >> human;

    while (human != 'X' && human != 'O') {
        cout << "Неверный ввод. Выберите X или O: ";
        cin >> human;
    }

    computer = (human == 'X') ? 'O' : 'X';
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        printBoard();

        if (currentPlayer == human) {
            int row, col;
            cout << "Ваш ход. Введите строку и столбец (0-2): ";
            cin >> row >> col;

            while (!isValidMove(row, col)) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "Неверный ход. Попробуйте снова: ";
                cin >> row >> col;
            }

            board[row][col] = human;
        }
        else {
            cout << "Ход компьютера..." << endl;
            switch (difficulty) {
            case 1: makeEasyComputerMove(computer); break;
            case 2: makeMediumComputerMove(computer); break;
            case 3: makeHardComputerMove(computer); break;
            }
        }

        if (checkWin(currentPlayer)) {
            printBoard();
            if (currentPlayer == human) {
                cout << "Поздравляем! Вы победили!" << endl;
            }
            else {
                cout << "Компьютер победил!" << endl;
            }
            gameOver = true;
        }
        else if (checkDraw()) {
            printBoard();
            cout << "Ничья!" << endl;
            gameOver = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Режим игры двух игроков
void playerVsPlayer() {
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        printBoard();

        int row, col;
        cout << "Ход игрока " << currentPlayer << ". Введите строку и столбец (0-2): ";
        cin >> row >> col;

        while (!isValidMove(row, col)) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Неверный ход. Попробуйте снова: ";
            cin >> row >> col;
        }

        board[row][col] = currentPlayer;

        if (checkWin(currentPlayer)) {
            printBoard();
            cout << "Игрок " << currentPlayer << " победил!" << endl;
            gameOver = true;
        }
        else if (checkDraw()) {
            printBoard();
            cout << "Ничья!" << endl;
            gameOver = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    while (true) {
        // Очистка игрового поля
        for (auto& row : board) {
            fill(row.begin(), row.end(), ' ');
        }

        cout << "Добро пожаловать в игру Крестики-нолики!\n";
        cout << "Выберите режим игры:\n";
        cout << "1 - Игра против другого игрока\n";
        cout << "2 - Игра против компьютера\n";
        cout << "3 - Выход\n";

        int choice;
        cin >> choice;

        while (choice < 1 || choice > 3) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Неверный ввод. Выберите 1, 2 или 3: ";
            cin >> choice;
        }

        if (choice == 3) break;

        switch (choice) {
        case 1: playerVsPlayer(); break;
        case 2: playerVsComputer(); break;
        }

        cout << "Хотите сыграть еще? (1 - Да, 0 - Нет): ";
        cin >> choice;
        if (choice != 1) break;
    }

    cout << "Спасибо за игру! До свидания!" << endl;
    system("pause");
    return 0;
}