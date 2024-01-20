#include <iostream>
using namespace std;
constexpr int MAX = 128;

int boardSizeValidation(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        return 1;
    }
    return 0;
}

int shipsCountValidation(int shipsCount) {
    if (shipsCount < 0) {
        return 1;
    }
    return 0;
}

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

void placeShip(char** field, int firstCellX, int firstCellY, int orientation, int sizeOfShip, int rows, int cols, int shipsCount, char differentShipsNumbers) {

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

    printField(field, rows, cols);
    return;
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

        while (placeShipValidation(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols) == 1) {
            cout << endl << "Can't place a ship there" << endl;
            cout << "Enter coordinates again (X/Y): ";
            cin >> firstCellX >> firstCellY;
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

void shoot(char**field, int X, int Y, int& sunkShipsCounter, int rows, int cols, bool& hit) {
    int counter = 0;
    if (field[X][Y] >= 'A' && field[X][Y] <= 'Z' || field[X][Y] == '#') {
        cout << "Hit!" << endl;

        if (X > 0 && Y > 0 && X < rows - 1 && Y < cols - 1) {


            if ((field[X][Y] != field[X - 1][Y]) && (field[X][Y] != field[X][Y - 1]) && (field[X][Y] != field[X + 1][Y]) && (field[X][Y] != field[X][Y + 1])) {
                cout << "You sunk a ship!" << endl;
                sunkShipsCounter++;
            }
        }
        else {
            if (X == 0 && Y == 0) {
                if ((field[X][Y] != field[X + 1][Y]) && (field[X][Y] != field[X][Y + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

            else if (X == 0) {
                if ((field[X][Y] != field[X][Y - 1]) && (field[X][Y] != field[X + 1][Y]) && (field[X][Y] != field[X][Y + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

            else if (Y == 0) {
                if ((field[X][Y] != field[X - 1][Y]) && (field[X][Y] != field[X + 1][Y]) && (field[X][Y] != field[X][Y + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

            else if (X == rows - 1 && Y == cols - 1) {
                if ((field[X][Y] != field[X - 1][Y]) && (field[X][Y] != field[X][Y - 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

            else if (X == rows - 1) {
                if ((field[X][Y] != field[X - 1][Y]) && (field[X][Y] != field[X][Y - 1]) && (field[X][Y] != field[X][Y + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

            else if (Y == cols - 1) {
                if ((field[X][Y] != field[X - 1][Y]) && (field[X][Y] != field[X][Y - 1]) && (field[X][Y] != field[X + 1][Y])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCounter++;
                }
            }

        }
        field[X][Y] = '#';
        hit = 1;
    }
    else {
        cout << "Miss!" << endl;
        hit = 0;
    }
}

void changeSeeFieldHit(char** field, int x, int y) {
    field[x][y] = '#';
}

void changeSeeFieldMiss(char** field, int x, int y) {
    field[x][y] = '0';
}

void result(int shootCoordinateX, int shootCoordinateY,char** fieldPlayerOne, char** fieldPlayerTwo, int rows, int cols, int shipsCount) {
    
    int sunkShipsCounterPlayerOne = 0;
    int sunkShipsCounterPlayerTwo = 0;

    char** whatPlayerOneSees = new char* [rows];
    makeDynamicField(whatPlayerOneSees, rows, cols);


    char** whatPlayerTwoSees = new char* [rows];
    makeDynamicField(whatPlayerTwoSees, rows, cols);

    fillDynamicFieldWithDots(whatPlayerOneSees, rows, cols);
    fillDynamicFieldWithDots(whatPlayerTwoSees, rows, cols);

    bool hit = 0;

    while (true) {
        cout << "Player(1) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;
        shoot(fieldPlayerTwo, shootCoordinateX, shootCoordinateY, sunkShipsCounterPlayerTwo, rows, cols, hit);
        if (hit) {
            changeSeeFieldHit(whatPlayerOneSees, shootCoordinateX, shootCoordinateY);
        }
        else {
            changeSeeFieldMiss(whatPlayerOneSees, shootCoordinateX, shootCoordinateY);
        }
        printField(whatPlayerOneSees, rows, cols);

        if (sunkShipsCounterPlayerTwo == shipsCount) {
            cout <<" - Player(1) wins!!! - "<< endl;
            break;
        }


        cout << "Player(2) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;
        shoot(fieldPlayerOne, shootCoordinateX, shootCoordinateY, sunkShipsCounterPlayerOne, rows, cols, hit);
        if (hit) {
            changeSeeFieldHit(whatPlayerTwoSees, shootCoordinateX, shootCoordinateY);
        }
        else {
            changeSeeFieldMiss(whatPlayerTwoSees, shootCoordinateX, shootCoordinateY);
        }
        printField(whatPlayerTwoSees, rows, cols);

        if (sunkShipsCounterPlayerOne == shipsCount) {
            cout << " - Player(2) wins!!! - " << endl;
            break;
        }

    }

}

void playGame() {
    int rows, cols;
    cout << "Board size (rows / columns): ";
    cin >> rows;
    cin >> cols;
    if (boardSizeValidation(rows, cols)) {
        cout << "Invalid board size" << endl;
        return;
    }

    int shipsCount;
    cout << "Ships count: ";
    cin >> shipsCount;
    if (shipsCountValidation(shipsCount)) {
        cout << "Invalid ships count" << endl;
        return;
    }

    char** fieldPlayerOne = new char* [rows];
    makeDynamicField(fieldPlayerOne, rows, cols);

    char** fieldPlayerTwo = new char* [rows];
    makeDynamicField(fieldPlayerTwo, rows, cols);

    fillDynamicFieldWithDots(fieldPlayerOne, rows, cols);
    fillDynamicFieldWithDots(fieldPlayerTwo, rows, cols);

    cout << "Player(1) places ships: " << endl;
    placeShipsInField(fieldPlayerOne, rows, cols, shipsCount);
   

    cout << "Player(2) places ships: " << endl;
    placeShipsInField(fieldPlayerTwo, rows, cols, shipsCount);


    cout <<endl<< "Player(1)'s field: ";
    printField(fieldPlayerOne, rows, cols);

    cout << "Player(2)'s field: " << endl;
    printField(fieldPlayerTwo, rows, cols);
    int shootCoordinateX = 0, shootCoordinateY = 0;

    result(shootCoordinateX,shootCoordinateY, fieldPlayerOne,fieldPlayerTwo, rows, cols, shipsCount);
}

int main()
{
    playGame();
    
    return 0;
}