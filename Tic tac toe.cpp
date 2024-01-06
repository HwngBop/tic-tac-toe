#include <iostream>
#include <vector>

const int boardSize = 10;
const char emptyCell = ' ';
std::vector<std::vector<char>> board(boardSize, std::vector<char>(boardSize, emptyCell));

bool isValidMove(int row, int col) {
    return row >= 0 && row < boardSize && col >= 0 && col < boardSize && board[row][col] == emptyCell;
}

bool checkWin(int row, int col, char player) {
    // Kiểm tra hàng ngang
    int count = 0;
    for (int i = col - 4; i <= col + 4; ++i) {
        if (i >= 0 && i < boardSize && board[row][i] == player) {
            count++;
            if (count == 5) return true;
        }
        else {
            count = 0;
        }
    }

    // Kiểm tra hàng dọc
    count = 0;
    for (int i = row - 4; i <= row + 4; ++i) {
        if (i >= 0 && i < boardSize && board[i][col] == player) {
            count++;
            if (count == 5) return true;
        }
        else {
            count = 0;
        }
    }

    // Kiểm tra theo hàng chéo từ trái xuống phải
    count = 0;
    for (int i = -4; i <= 4; ++i) {
        int r = row + i;
        int c = col + i;
        if (r >= 0 && r < boardSize && c >= 0 && c < boardSize && board[r][c] == player) {
            count++;
            if (count == 5) return true;
        }
        else {
            count = 0;
        }
    }

    // Kiểm tra theo hàng chéo từ phải xuống trái
    count = 0;
    for (int i = -4; i <= 4; ++i) {
        int r = row + i;
        int c = col - i;
        if (r >= 0 && r < boardSize && c >= 0 && c < boardSize && board[r][c] == player) {
            count++;
            if (count == 5) return true;
        }
        else {
            count = 0;
        }
    }

    return false;
}

void printBoard() {
    std::cout << "   ";
    for (int i = 0; i < boardSize; ++i) {
        std::cout << "  " << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < boardSize; ++i) {
        std::cout << " " << i << " ";
        for (int j = 0; j < boardSize; ++j) {
            std::cout << " " << board[i][j] << " ";
            if (j < boardSize - 1) {
                std::cout << "|";
            }
        }
        std::cout << '\n';
        if (i < boardSize - 1) {
            std::cout << "   ";
            for (int j = 0; j < boardSize - 1; ++j) {
                std::cout << "---|";
            }
            std::cout << "---\n";
        }
    }
}
void displayRules() {
    std::cout << "Rules:\n";
    // Thêm hướng dẫn và luật chơi ở đây
    std::cout << "Each player takes turns to place their symbol ('X' or 'O') on the board.\n";
    std::cout << "The first player to get 5 in a row horizontally, vertically, or diagonally wins.\n";
    std::cout << "To make a move, enter the row and column numbers separated by a space.\n";
    std::cout << "For example, to place your symbol in the top-left corner, enter '0 0'.\n";
    std::cout << "Press 'q' to quit the game at any time.\n";
    std::cout << "Press 'p' to display the board again.\n";
    std::cout << "Press 'r' to display the rules again.\n";
}


int main() {
    char action;
    bool rulesRead = false;
    bool namesEntered = false;

    std::string playerNames[2];  // Chuyển playerNames thành biến toàn cục

    while (true) {
        std::cout << "Press 'r' to read the rules, 'p' to play, or 'q' to quit: ";
        std::cin >> action;

        if (action == 'q') {
            std::cout << "Quitting the game. Goodbye!" << std::endl;
            return 0;
        }
        else if (action == 'r') {
            displayRules();
            rulesRead = true;
        }
        else if (action == 'p') {
            if (!rulesRead) {
                std::cout << "Please read the rules first by pressing 'r'." << std::endl;
                continue;
            }

            if (!namesEntered) {
                const char players[2] = { 'X', 'O' };

                for (int i = 0; i < 2; ++i) {
                    std::cout << "Enter Player " << players[i] << "'s name: ";
                    std::cin >> playerNames[i];
                }

                namesEntered = true;
            }

            break;  // Bắt đầu chơi khi đã đọc luật và nhập tên người chơi
        }
        else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    int currentPlayerIndex = 0;
    int row, col;

    printBoard();

    while (true) {
        std::cout << "Player " << playerNames[currentPlayerIndex] << ", enter your move (row and column): ";
        std::cin >> row >> col;

        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != emptyCell) {
            std::cout << "Invalid move. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        board[row][col] = (currentPlayerIndex == 0) ? 'X' : 'O';

        printBoard();

        if (checkWin(row, col, (currentPlayerIndex == 0) ? 'X' : 'O')) {
            std::cout << "Player " << playerNames[currentPlayerIndex] << " wins!" << std::endl;
            break;
        }

        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
    }

    return 0;
}


