#include <iostream>
using namespace std;

void placeShipValidation(int firstCellX, int firstCellY, char orientation, int sizeOfShip, int rows, int cols) {

    if (firstCellX < 0 || firstCellX >= rows) {
        cout << "Can't place a ship there";
        return;
    }

    if (firstCellY < 0 || firstCellX >= cols) {
        cout << "Can't place a ship there";
        return;
    }

    if (orientation == 'V') {
        if (firstCellX + sizeOfShip - 1 > rows) {
            cout << "Can't place a ship there";
            return;
        }
    }

    if (orientation == 'H') {
        if (firstCellY + sizeOfShip - 1 > cols) {
            cout << "Can't place a ship there";
            return;
        }
    }

    //Can't place 2 ships on one cell

}

void makeDynamicField(char** field, int rows, int cols) {
    for (int i = 0;i < rows;i++) {
        field[i] = new char[cols];
    }
}

void fillDynamicFieldWithDots(char** field, int rows, int cols) {
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            field[i][j] = '.';
        }
    }
}

void printField(char** field, int rows, int cols) {
    cout << endl;
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

void placeShip(char** field, int firstCellX, int firstCellY, int orientation, int sizeOfShip, int rows, int cols) {
    placeShipValidation(firstCellX, firstCellY, orientation, sizeOfShip, rows, cols);

    if (orientation == 'H') {
        int i = firstCellX;
        for (int j = firstCellY; j < firstCellY + sizeOfShip;j++) {
            field[i][j] = '1';
        }
    }

    if (orientation == 'V') {
        int j = firstCellY;
        for (int i = firstCellX; i < firstCellX + sizeOfShip;i++) {
            field[i][j] = '1';
        }
    }

}

void placeShipsInField(char** field, int rows, int cols, int shipsCount) {
    /* - Лодки.С размер 2 клетки.
       - Подводници.С размер 3 клетки.
       - Разрушите.С размер 4 клетки.
       - Самолетоносач.С размер 5 клетки */
    char boatType;
    int firstCellX, firstCellY;
    char orientation;
    int sizeOfShip;

    for (int i = 0;i < shipsCount;i++) {

        cout << "What ship do you want to place? ('B'/'S'/'D'/'A'): ";
        cin >> boatType;

        cout << "Enter coordinates of the first cell (X/Y): ";
        cin >> firstCellX >> firstCellY;

        cout << "What orientation do you want it to be? ('H'/'V'): ";
        cin >> orientation;

        if (boatType == 'B') {
            sizeOfShip = 2;
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols);
        }

        if (boatType == 'S') {
            sizeOfShip = 3;
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols);

        }

        if (boatType == 'D') {
            sizeOfShip = 4;
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols);
        }

        if (boatType == 'A') {
            sizeOfShip = 5;
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols);
        }
    }

}

int main()
{
    //Стреляне
    //Оповестяване на победителя

    int rows, cols;
    cout << "Board size (rows / columns): ";
    cin >> rows;
    cin >> cols;

    char** fieldPlayerOne = new char* [rows];
    makeDynamicField(fieldPlayerOne, rows, cols);

    char** fieldPlayerTwo = new char* [rows];
    makeDynamicField(fieldPlayerTwo, rows, cols);

    fillDynamicFieldWithDots(fieldPlayerOne, rows, cols);
    fillDynamicFieldWithDots(fieldPlayerTwo, rows, cols);

    int shipsCount;
    cout << "Ships count: ";
    cin >> shipsCount;

    cout << "Player 1 places ships: " << endl;
    placeShipsInField(fieldPlayerOne, rows, cols, shipsCount);
    printField(fieldPlayerOne, rows, cols);

    cout << "Player 2 places ships: " << endl;
    placeShipsInField(fieldPlayerTwo, rows, cols, shipsCount);
    printField(fieldPlayerTwo, rows, cols);

    return 0;
}