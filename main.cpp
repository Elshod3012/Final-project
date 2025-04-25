#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int SIZE = 6;
const char WATER = '~';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

struct Player {
    string name;
    char board[SIZE][SIZE];
};

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 1; i < SIZE; i++)
        for (int j = 1; j < SIZE; j++)
            board[i][j] = WATER;
}

void printBoard(const char board[SIZE][SIZE]) {
    cout << "  ";
    for (int j = 1; j < SIZE; j++) cout << j << " ";
    cout << endl;

    for (int i = 1; i < SIZE; i++) {
        cout << char('A' + i - 1) << " ";
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] == SHIP)
                cout << WATER << " ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int getRowFromChar(char c) {
    c = toupper(c);
    if (c >= 'A' && c <= 'E')
        return c - 'A' + 1;
    return -1;
}

void placeShips(Player& player, int shipCount = 5) {
    cout << player.name << ", place your " << shipCount << " ships." << endl;
    char rowChar;
    int col;

    for (int i = 0; i < shipCount; i++) {
        while (true) {
            cout << "Enter coordinates for ship " << (i + 1) << " (e.g. B 3): ";
            cin >> rowChar >> col;


            int row = getRowFromChar(rowChar);
            if (row >= 1 && row <= 5 && col >= 1 && col <= 5 && player.board[row][col] == WATER) {
                player.board[row][col] = SHIP;
                break;
            } else {
                cout << "You can't place ships here or you've already done." << endl;
            }
        }
    }
    cout << "Ships placed!\n";
}

bool attack(Player& attacker, Player& defender) {
    char rowChar;
    int col;
    cout << attacker.name << ", enter attack coordinates (example A 5): ";
    cin >> rowChar >> col;
    int row = getRowFromChar(rowChar);

    if (row < 1 ||  row >= SIZE || col < 1 || col >= SIZE) {
        cout << "It is a 5x5 map, are you blind?!?" << endl;
        return false;
    }

    if (defender.board[row][col] == HIT || defender.board[row][col] == MISS) {
        cout << "You already tried this spot!" << endl;
        return false;
    }

    if (defender.board[row][col] == SHIP) {
        cout << "Hit!" << endl;

        defender.board[row][col] = HIT;
    } else if (defender.board[row][col] != SHIP)  {

        cout << "Miss!" << endl;

        defender.board[row][col] = MISS;

    }
    return true;
}

bool hasShipsLeft(const Player& player) {
    for (int i = 1; i < SIZE; i++)
        for (int j = 1; j < SIZE; j++)
            if (player.board[i][j] == SHIP)
                return true;
    return false;
}

int main() {
    Player player1, player2;
    cout<<"WELCOME TO 'SEA BATTLE' GAME, COMMANDER!"
          "\nRules:"
          "\nGrid size: 5x5 (Rows A–E, Columns 1–5)."
          "\nEach player places 3 ships (1 cell each)."
          "\nTake turns guessing coordinates (e.g., B 3).\nHit = X, Miss = O."
          "\nFirst to sink all enemy ships wins."<<endl;
    cout << "Enter name for Player 1: ";
    cin >> player1.name;
    cout << "Enter name for Player 2: ";
    cin >> player2.name;

    initializeBoard(player1.board);
    initializeBoard(player2.board);

    placeShips(player1);
    placeShips(player2);

    Player* current = &player1;
    Player* opponent = &player2;

    while (true) {
        cout << "\n" << current->name << "'s turn.\n";

        cout << opponent->name << "'s board:\n";
        printBoard(opponent->board);

        if (!attack(*current, *opponent))
            continue;

        if (!hasShipsLeft(*opponent)) {
            cout << current->name << " wins! All ships destroyed.\n";
            break;
        }

        swap(current, opponent);
    }

    return 0;
}
