#include <iostream>
using namespace std;

constexpr int MAX = 128;

const char SHIP_TYPE_BOAT = 'B';
const char SHIP_TYPE_SUBMARINE = 'S';
const char SHIP_TYPE_DESTROYER = 'D';
const char SHIP_TYPE_AIRCRAFT = 'A';

const int SHIP_SIZE_BOAT = 2;
const int SHIP_SIZE_SUBMARINE = 3;
const int SHIP_SIZE_DESTROYER = 4;
const int SHIP_SIZE_AIRCRAFT = 5;

const char ORIENTATION_HORIZONTAL = 'H';
const char ORIENTATION_VERTICAL = 'V';

const int MIN_ROWS = 2;
const int MIN_COLS = 2;
const int MAX_ROWS = 128;
const int MAX_COLS = 128;

const char SYMBOL_SEA = '.';

const char SYMBOL_HIT = '#';
const char SYMBOL_MISS = '0';

bool isShipTypeValid(char type) {
    if (type != SHIP_TYPE_BOAT && type != SHIP_TYPE_SUBMARINE && type != SHIP_TYPE_DESTROYER && type != SHIP_TYPE_AIRCRAFT) {
        return true;
    }

    return false;
}

bool isOriåntationValid(char orientation) {
    if (orientation != ORIENTATION_HORIZONTAL && orientation != ORIENTATION_VERTICAL) {
        return true;
    }

    return false;
}

bool isBoardSizeValid(int rows, int cols) {
    if (rows < MIN_ROWS || cols < MIN_COLS || rows > MAX_ROWS || cols > MAX_COLS) {
        return true;
    }

    return false;
}

bool isShipsCountValid(int shipsCount) {
    if (shipsCount < 0) {
        return true;
    }

    return false;
}

bool isCapitalLetter(char letter) {
    return letter >= 'A' && letter <= 'Z';
}

void initDynamicField(char** field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        field[i] = new char[cols];
    }
}

void fillDefaultField(char** field, int rows, int cols) {
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            field[i][j] = SYMBOL_SEA;
        }
    }
}

void printField(char** field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << field[i][j] << ' ';
        }

        cout << endl;
    }
}

bool canShipBePlaced(char** field, int firstCellX, int firstCellY, char orientation, int sizeOfShip, int fieldRows, int fieldCols) {

    if (firstCellX < 0 || firstCellX >= fieldRows) {
        return false;
    }

    if (firstCellY < 0 || firstCellX >= fieldCols) {
        return false;
    }

    if (orientation == ORIENTATION_VERTICAL) {
        int j = firstCellY;
        if (firstCellX + sizeOfShip - 1 >= fieldRows) {
            return false;
        }

        for (int i = firstCellX; i < firstCellX + sizeOfShip;i++) {
            if (isCapitalLetter(field[i][j])) {
                return false;
            }
        }
    }

    if (orientation == ORIENTATION_HORIZONTAL) {
        int k = firstCellX;
        if (firstCellY + sizeOfShip - 1 >= fieldCols) {
            return false;
        }

        for (int l = firstCellY; l < firstCellY + sizeOfShip;l++) {
            if (isCapitalLetter(field[k][l])) {
                return false;
            }
        }
    }

    return true;
}

void placeShip(char** field, int firstCellX, int firstCellY, int orientation, int sizeOfShip, int rows, int cols, int shipsCount, char currentShipSymbol) {
    if (orientation == ORIENTATION_HORIZONTAL) {
        int i = firstCellX;
        for (int j = firstCellY; j < firstCellY + sizeOfShip;j++) {
            field[i][j] = currentShipSymbol;
        }
    }

    if (orientation == ORIENTATION_VERTICAL) {
        int j = firstCellY;
        for (int i = firstCellX; i < firstCellX + sizeOfShip;i++) {
            field[i][j] = currentShipSymbol;
        }
    }
}

int getSizeOfShip(char shipType) {

    switch (shipType) {
        case (SHIP_TYPE_BOAT):
            return SHIP_SIZE_BOAT;
            break;

        case(SHIP_TYPE_SUBMARINE):
            return SHIP_SIZE_SUBMARINE;
            break;

        case(SHIP_TYPE_DESTROYER):
            return SHIP_SIZE_DESTROYER;
            break;

        case(SHIP_TYPE_AIRCRAFT):
            return SHIP_SIZE_AIRCRAFT;
            break;
    }
}

void placeShipsInField(char** field, int rows, int cols, int shipsCount) {
    char currentShipSymbol = 'A';

    for (int i = 0; i < shipsCount; i++) {
        char shipType;
        cout << "Enter ship type ('B'/'S'/'D'/'A'): ";
        cin >> shipType;

        if (isShipTypeValid(shipType)) {
            cout << "Invalid ship type" << endl;
            return;
        }
        int firstCellX, firstCellY;
        cout << "Enter ship coordinates for the first cell (X/Y): ";
        cin >> firstCellX >> firstCellY;

        char orientation;
        cout << "Enter ship orientation ('H'/'V'): ";
        cin >> orientation;

        if (isOriåntationValid(orientation)) {
            cout << "Invalid ship orientation" << endl;
            return;
        }

        int sizeOfShip = getSizeOfShip(shipType);

        currentShipSymbol += i;

        while (!canShipBePlaced(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols)) {
            cout << endl << "Can't place a ship there" << endl;
            cout << "Enter ship coordinates again (X/Y): ";
            cin >> firstCellX >> firstCellY;
        }

        placeShip(field, firstCellX, firstCellY, orientation, sizeOfShip, rows, cols, shipsCount, currentShipSymbol);

        cout << endl;
        printField(field, rows, cols);
        cout << endl;
    }
}

void shoot(char**field, int shootCellX, int shootCellY, int& sunkShipsCount, int fieldRows, int fieldCols, bool& hitResult) {
    if (shootCellX < 0 || shootCellY < 0 || shootCellX > fieldRows - 1 || shootCellY > fieldCols - 1) {
        cout << "Invalid shooting coordinates! You lost your turn." << endl;
        return;
    }

    if (isCapitalLetter(field[shootCellX][shootCellY]) || field[shootCellX][shootCellY] == SYMBOL_HIT) {
        cout << "Hit!" << endl;

        if (shootCellX > 0 && shootCellY > 0 && shootCellX < fieldRows - 1 && shootCellY < fieldCols - 1) {
            if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY - 1]) && (field[shootCellX][shootCellY] != field[shootCellX + 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                cout << "You sunk a ship!" << endl;
                sunkShipsCount++;
            }
        }
        else {
            if (shootCellX == 0 && shootCellY == 0) {
                if ((field[shootCellX][shootCellY] != field[shootCellX + 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

            else if (shootCellX == 0) {
                if ((field[shootCellX][shootCellY] != field[shootCellX][shootCellY - 1]) && (field[shootCellX][shootCellY] != field[shootCellX + 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

            if (shootCellX == fieldRows - 1 && shootCellY == 0) {
                if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                    cout << "You sunk a shipppp!" << endl;
                    sunkShipsCount++;
                }
            }

            else if (shootCellY == 0) {
                if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX + 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

            else if (shootCellX == fieldRows - 1 && shootCellY == fieldCols - 1) {
                if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY - 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

            else if (shootCellX == fieldRows - 1) {
                if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY - 1]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY + 1])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

            else if (shootCellY == fieldCols - 1) {
                if ((field[shootCellX][shootCellY] != field[shootCellX - 1][shootCellY]) && (field[shootCellX][shootCellY] != field[shootCellX][shootCellY - 1]) && (field[shootCellX][shootCellY] != field[shootCellX + 1][shootCellY])) {
                    cout << "You sunk a ship!" << endl;
                    sunkShipsCount++;
                }
            }

        }
        field[shootCellX][shootCellY] = '#';
        hitResult = 1;
    }
    else {
        cout << "Miss!" << endl;
        hitResult = 0;
    }
}

void changeFieldCellHit(char** field, int x, int y) {
    field[x][y] = SYMBOL_HIT;
}

void changeFieldCellMiss(char** field, int x, int y, int rows, int cols) {
    if (x < 0 || y < 0 || x > rows - 1 || y > cols - 1) {
        return;
    }

    field[x][y] = SYMBOL_MISS;
}

void startShootingPhase(int shootCoordinateX, int shootCoordinateY,char** fieldPlayerOne, char** fieldPlayerTwo, int rows, int cols, int shipsCount) {
    int sunkShipsCountPlayerOne = 0;
    int sunkShipsCountPlayerTwo = 0;

    char** playerOneUIField = new char* [rows];
    initDynamicField(playerOneUIField, rows, cols);


    char** playerTwoUIField = new char* [rows];
    initDynamicField(playerTwoUIField, rows, cols);

    fillDefaultField(playerOneUIField, rows, cols);
    fillDefaultField(playerTwoUIField, rows, cols);

    bool hit = false;

    while (true) {
        cout << "Player(1) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;

        shoot(fieldPlayerTwo, shootCoordinateX, shootCoordinateY, sunkShipsCountPlayerTwo, rows, cols, hit);

        if (hit) {
            changeFieldCellHit(playerOneUIField, shootCoordinateX, shootCoordinateY);
        }
        else {
            changeFieldCellMiss(playerOneUIField, shootCoordinateX, shootCoordinateY, rows ,cols);
        }

        cout << endl;
        printField(playerOneUIField, rows, cols);

        if (sunkShipsCountPlayerTwo == shipsCount) {
            cout <<" - Player(1) wins!!! - "<< endl;
            break;
        }

        cout << "Player(2) shoots at (X/Y): ";
        cin >> shootCoordinateX >> shootCoordinateY;

        shoot(fieldPlayerOne, shootCoordinateX, shootCoordinateY, sunkShipsCountPlayerOne, rows, cols, hit);

        if (hit) {
            changeFieldCellHit(playerTwoUIField, shootCoordinateX, shootCoordinateY);
        }
        else {
            changeFieldCellMiss(playerTwoUIField, shootCoordinateX, shootCoordinateY, rows, cols);
        }

        cout << endl;
        printField(playerTwoUIField, rows, cols);

        if (sunkShipsCountPlayerOne == shipsCount) {
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
    if (isBoardSizeValid(rows, cols)) {
        cout << "Invalid board size" << endl;
        return;
    }

    int shipsCount;
    cout << "Ships count: ";
    cin >> shipsCount;
    if (isShipsCountValid(shipsCount)) {
        cout << "Invalid ships count" << endl;
        return;
    }

    char** fieldPlayerOne = new char* [rows];
    initDynamicField(fieldPlayerOne, rows, cols);

    char** fieldPlayerTwo = new char* [rows];
    initDynamicField(fieldPlayerTwo, rows, cols);

    fillDefaultField(fieldPlayerOne, rows, cols);
    fillDefaultField(fieldPlayerTwo, rows, cols);

    cout << "Player(1) turn to place ships: " << endl;
    placeShipsInField(fieldPlayerOne, rows, cols, shipsCount);
   
    cout << "Player(2) turn to place ships: " << endl;
    placeShipsInField(fieldPlayerTwo, rows, cols, shipsCount);

    cout << endl << "Player(1)'s field: " << endl;
    printField(fieldPlayerOne, rows, cols);

    cout << "Player(2)'s field: " << endl;
    printField(fieldPlayerTwo, rows, cols);

    int shootCoordinateX = 0, shootCoordinateY = 0;
    startShootingPhase(shootCoordinateX,shootCoordinateY, fieldPlayerOne,fieldPlayerTwo, rows, cols, shipsCount);
}

int main() {
    playGame();

    return 0;
}