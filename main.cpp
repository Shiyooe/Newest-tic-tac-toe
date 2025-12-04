#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char player;
    char bot;
    int difficulty; // 1=Mudah, 2=Sedang, 3=Sulit

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), player('X'), bot('O') {
        srand(time(0));
    }

    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << "  ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "  ---------\n";
        }
        cout << "\n";
    }

    void displayPositions() {
        cout << "\nPosisi papan (1-9):\n";
        cout << "  1 | 2 | 3\n";
        cout << "  ---------\n";
        cout << "  4 | 5 | 6\n";
        cout << "  ---------\n";
        cout << "  7 | 8 | 9\n\n";
    }

    bool isValidMove(int pos) {
        if (pos < 1 || pos > 9) return false;
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        return board[row][col] == ' ';
    }

    void makeMove(int pos, char symbol) {
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        board[row][col] = symbol;
    }

    char checkWinner() {
        // Cek baris
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return board[i][0];
        }
        
        // Cek kolom
        for (int i = 0; i < 3; i++) {
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return board[0][i];
        }
        
        // Cek diagonal
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return board[0][2];
        
        return ' ';
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    int minimax(bool isMaximizing) {
        char winner = checkWinner();
        
        if (winner == bot) return 10;
        if (winner == player) return -10;
        if (isBoardFull()) return 0;

        if (isMaximizing) {
            int bestScore = -1000;
            for (int i = 1; i <= 9; i++) {
                if (isValidMove(i)) {
                    makeMove(i, bot);
                    int score = minimax(false);
                    int row = (i - 1) / 3;
                    int col = (i - 1) % 3;
                    board[row][col] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 1; i <= 9; i++) {
                if (isValidMove(i)) {
                    makeMove(i, player);
                    int score = minimax(true);
                    int row = (i - 1) / 3;
                    int col = (i - 1) % 3;
                    board[row][col] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
            return bestScore;
        }
    }

    int getBotMove() {
        if (difficulty == 1) {
            // Mudah: Gerakan acak
            vector<int> validMoves;
            for (int i = 1; i <= 9; i++) {
                if (isValidMove(i)) validMoves.push_back(i);
            }
            return validMoves[rand() % validMoves.size()];
        } 
        else if (difficulty == 2) {
            // Sedang: 50% optimal, 50% acak
            if (rand() % 2 == 0) {
                vector<int> validMoves;
                for (int i = 1; i <= 9; i++) {
                    if (isValidMove(i)) validMoves.push_back(i);
                }
                return validMoves[rand() % validMoves.size()];
            }
        }
        
        // Sulit (atau 50% dari sedang): Minimax algorithm
        int bestMove = -1;
        int bestScore = -1000;
        
        for (int i = 1; i <= 9; i++) {
            if (isValidMove(i)) {
                makeMove(i, bot);
                int score = minimax(false);
                int row = (i - 1) / 3;
                int col = (i - 1) % 3;
                board[row][col] = ' ';
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }
        
        return bestMove;
    }

    void playVsPlayer() {
        cout << "\n=================================\n";
        cout << "   MODE: PLAYER VS PLAYER\n";
        cout << "=================================\n";
        cout << "Player 1 adalah 'X', Player 2 adalah 'O'\n";
        
        displayPositions();
        
        char currentPlayer = player;
        int playerNum = 1;
        
        while (true) {
            displayBoard();
            int move;
            cout << "Giliran Player " << playerNum << " (" << currentPlayer << ")! Masukkan posisi (1-9): ";
            cin >> move;
            
            while (!isValidMove(move)) {
                cout << "Gerakan tidak valid! Coba lagi (1-9): ";
                cin >> move;
            }
            
            makeMove(move, currentPlayer);
            
            char winner = checkWinner();
            if (winner != ' ') {
                displayBoard();
                cout << "🎉 SELAMAT! Player " << playerNum << " (" << winner << ") MENANG! 🎉\n";
                break;
            }
            
            if (isBoardFull()) {
                displayBoard();
                cout << "⚖️ SERI! Permainan berakhir imbang.\n";
                break;
            }
            
            // Ganti pemain
            currentPlayer = (currentPlayer == player) ? bot : player;
            playerNum = (playerNum == 1) ? 2 : 1;
        }
    }

    void playVsBot() {
        cout << "\n=================================\n";
        cout << "   MODE: PLAYER VS BOT\n";
        cout << "=================================\n";
        cout << "Pilih tingkat kesulitan:\n";
        cout << "1. Mudah\n";
        cout << "2. Sedang\n";
        cout << "3. Sulit\n";
        cout << "Pilihan (1-3): ";
        cin >> difficulty;
        
        while (difficulty < 1 || difficulty > 3) {
            cout << "Pilihan tidak valid! Masukkan 1-3: ";
            cin >> difficulty;
        }
        
        string level[] = {"", "MUDAH", "SEDANG", "SULIT"};
        cout << "\nAnda bermain melawan bot level " << level[difficulty] << "!\n";
        cout << "Anda adalah 'X', Bot adalah 'O'\n";
        
        displayPositions();
        
        while (true) {
            // Giliran pemain
            displayBoard();
            int move;
            cout << "Giliran Anda! Masukkan posisi (1-9): ";
            cin >> move;
            
            while (!isValidMove(move)) {
                cout << "Gerakan tidak valid! Coba lagi (1-9): ";
                cin >> move;
            }
            
            makeMove(move, player);
            
            char winner = checkWinner();
            if (winner == player) {
                displayBoard();
                cout << "🎉 SELAMAT! Anda MENANG! 🎉\n";
                break;
            }
            
            if (isBoardFull()) {
                displayBoard();
                cout << "⚖️ SERI! Permainan berakhir imbang.\n";
                break;
            }
            
            // Giliran bot
            cout << "Bot sedang berpikir...\n";
            int botMove = getBotMove();
            makeMove(botMove, bot);
            cout << "Bot memilih posisi: " << botMove << "\n";
            
            winner = checkWinner();
            if (winner == bot) {
                displayBoard();
                cout << "😢 Bot MENANG! Coba lagi!\n";
                break;
            }
            
            if (isBoardFull()) {
                displayBoard();
                cout << "⚖️ SERI! Permainan berakhir imbang.\n";
                break;
            }
        }
    }
};

int main() {
    char playAgain;
    
    do {
        TicTacToe game;
        
        cout << "\n=================================\n";
        cout << "   TIC-TAC-TOE GAME\n";
        cout << "=================================\n";
        cout << "Pilih mode permainan:\n";
        cout << "1. Player vs Bot\n";
        cout << "2. Player vs Player\n";
        cout << "Pilihan (1-2): ";
        
        int mode;
        cin >> mode;
        
        while (mode < 1 || mode > 2) {
            cout << "Pilihan tidak valid! Masukkan 1-2: ";
            cin >> mode;
        }
        
        if (mode == 1) {
            game.playVsBot();
        } else {
            game.playVsPlayer();
        }
        
        cout << "\nMain lagi? (y/n): ";
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "\nTerima kasih telah bermain!\n";
    
    return 0;
}