#include <iostream>
using namespace std;
constexpr int MAX = 128;

int placeShipValidation(char** field, int firstCellX, int firstCellY, char orientation, int sizeOfShip, int rows, int cols) {

    if (firstCellX < 0 || firstCellX >= rows) {
        return 1;
    }

    if (firstCellY < 0 || firstCellX >= cols) {
        return 1;
    }

    if (orientation == 'V') {

        int j = firstCellY;
        if (firstCellX + sizeOfShip - 1 >= rows) {
            return 1;
        }
        for (int i = firstCellX; i < firstCellX + sizeOfShip;i++) {
            if (field[i][j] >= 'A' && field[i][j] <= 'Z') {
                return 1;
            }
        }

        
    }

    if (orientation == 'H') {


        int k = firstCellX;
        for (int l = firstCellY; l < firstCellY + sizeOfShip;l++) {
            if (field[k][l] >= 'A' && field[k][l] <= 'Z') {
                return 1;
            }
        }

        if (firstCellY + sizeOfShip - 1 > cols) {
            return 1;
        }
    }
    return 0;

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

int placeShip(char** field, int firstCellX, int firstCellY, int orientation, int sizeOfShip, int rows, int cols, int shipsCount, char differentShipsNumbers) {
    if (placeShipValidation(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols) == 1) {
        return 1;
    }



    if (orientation == 'H') {
        int i = firstCellX;
        for (int j = firstCellY; j < firstCellY + sizeOfShip;j++) {
            field[i][j] = differentShipsNumbers;
        }
    }

    if (orientation == 'V') {
        int j = firstCellY;
        for (int i = firstCellX; i < firstCellX + sizeOfShip;i++) {
            field[i][j] = differentShipsNumbers;
        }
    }

    return 0;
}

int getSizeOfShip(char boatType) {
    int sizeOfShip = 0;
    if (boatType == 'B') {
        sizeOfShip = 2;
        
    }

    if (boatType == 'S') {
        sizeOfShip = 3;
    }

    if (boatType == 'D') {
        sizeOfShip = 4;
    }

    if (boatType == 'A') {
        sizeOfShip = 5;
    }

    return sizeOfShip;
}

void placeShipsInField(char** field, int rows, int cols, int shipsCount) {
    /* - Лодки.С размер 2 клетки.
       - Подводници.С размер 3 клетки.
       - Разрушите.С размер 4 клетки.
       - Самолетоносач.С размер 5 клетки */
    char boatType;
    int firstCellX, firstCellY;
    char orientation;
    int sizeOfShip = 0;
    char differentShipsSymbol = 'A';

    for (int i = 0;i < shipsCount;i++) {
        cout << "What ship do you want to place? ('B'/'S'/'D'/'A'): ";
        cin >> boatType;

        cout << "Enter coordinates of the first cell (X/Y): ";
        cin >> firstCellX >> firstCellY;

        cout << "What orientation do you want it to be? ('H'/'V'): ";
        cin >> orientation;

        sizeOfShip = getSizeOfShip(boatType);

        differentShipsSymbol += i;

        if (placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, differentShipsSymbol) == 1) {
            cout << "Can't place a ship there, try again" << endl;
            placeShipsInField(field, rows, cols, shipsCount - i);
        }


        if (boatType == 'B') {
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, differentShipsSymbol);
        }

        if (boatType == 'S') {
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, differentShipsSymbol);

        }

        if (boatType == 'D') {
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, differentShipsSymbol);
        }

        if (boatType == 'A') {
            placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, differentShipsSymbol);
        }

    }

}

void shoot(int shootCoordinateX, int shootCoordinateY,char** fieldPlayerOne, char** fieldPlayerTwo, int rows, int cols) {
    
        cout << "Player(1) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;
        if (fieldPlayerTwo[shootCoordinateX][shootCoordinateY] >= 'A' && fieldPlayerTwo[shootCoordinateX][shootCoordinateY] <= 'Z') {
            fieldPlayerTwo[shootCoordinateX][shootCoordinateY] = '!';
            cout << "Hit!" << endl;
        }

        printField(fieldPlayerTwo, rows, cols);

        cout << "Player(2) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;
        if (fieldPlayerOne[shootCoordinateX][shootCoordinateY] >= 'A' && fieldPlayerOne[shootCoordinateX][shootCoordinateY] <= 'Z') {
            fieldPlayerOne[shootCoordinateX][shootCoordinateY] = '!';
            cout << "Hit!" << endl;
        }

        printField(fieldPlayerOne, rows, cols);

        for (int i = 0;i < rows; i++) {
            for (int j = 0;j < cols; j++) {
                if (fieldPlayerTwo[i][j] >= 'A' && fieldPlayerTwo[i][j] <= 'Z') {
                    shoot(shootCoordinateX, shootCoordinateY, fieldPlayerOne, fieldPlayerTwo, rows, cols);
                }
            }
        }

        cout << "Player(1) wins!!!" << endl;
        return;
        
        for (int i = 0;i < rows; i++) {
            for (int j = 0;j < cols; j++) {
                if (fieldPlayerOne[i][j] >= 'A' && fieldPlayerOne[i][j] <= 'Z') {
                    shoot(shootCoordinateX, shootCoordinateY, fieldPlayerOne, fieldPlayerTwo, rows, cols);
                }
            }
        }

        cout << "Player(2) wins!!!" << endl;
        return;

}

void read() {
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

    cout << "Player(1) places ships: " << endl;
    placeShipsInField(fieldPlayerOne, rows, cols, shipsCount);
    printField(fieldPlayerOne, rows, cols);

    cout << "Player(2) places ships: " << endl;
    placeShipsInField(fieldPlayerTwo, rows, cols, shipsCount);
    printField(fieldPlayerTwo, rows, cols);

    int shootCoordinateX = 0, shootCoordinateY = 0;

    shoot(shootCoordinateX,shootCoordinateY, fieldPlayerOne,fieldPlayerTwo, rows, cols);
}

int main()
{
    //Стреляне
    //Оповестяване на победителя
    read();
  
    return 0;
}