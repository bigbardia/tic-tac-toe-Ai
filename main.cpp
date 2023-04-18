#include <iostream>
#include <vector>
#include <utility>



void DrawBoard(std::vector<std::vector<char>> board) {
    int rows = board.size();
    int cols = board[0].size();

    for (int i = 0; i < rows * 2 + 2; i ++) {
        for (int j = 0; j < cols * 2 + 2; j ++) {
            if (i == 0 ){
                if ( j== 0){
                    std::cout << " ";
                }
                else if (j % 2 ==1 ) {
                    std::cout << "|";
                }
                else {
                    std::cout << j/2 - 1;
                }
            }
            else {
                if (i % 2 == 1) {
                    std::cout << "-" ;
                }
                else if (j % 2== 1) {
                    std::cout << "|";
                }
                else if (j == 0) {
                    std::cout << i/2-1;
                }
                else {
                    std::cout << board[i/2-1][j/2-1];
                }
            }
        }
        std::cout << std::endl;
    }
}

char BoardState(std::vector<std::vector<char>> board,int win_count) {
    int rows = board.size();
    int cols = board[0].size();
    std::string target_x ="";
    std::string target_o = "";
    for (int i = 0; i < win_count ; i ++) {
        target_x += 'x';
        target_o += 'o';
    }
    for (int i = 0; i < rows;i ++ ) {
        std::string row = "";
        for (int j = 0; j <cols; j ++) {
            row += board[i][j];
        }
        if (row.find(target_x)!=std::string::npos){
            return 'x';
        }
        if (row.find(target_o) != std::string::npos) {
            return 'o';
        }
    }
    for (int j = 0; j < cols; j ++) {
        std::string col = "";
        for (int i = 0; i < rows;i ++) {
            col += board[i][j];
        }
        if (col.find(target_x)!=std::string::npos) {
            return 'x';
        }
        if (col.find(target_o)!=std::string::npos) {
            return 'o';
        }
    }

    for (int i = 0; i < rows; i ++) {
        std::string diag1 = "";
        std::string diag2 = "";
        std::string diag3 = "";
        std::string diag4 = "";


        int j = 0;
        int ti = i;
        while (ti > -1 && j < cols) {
            diag1 += board[ti][j];
            ti--;
            j ++;
        }

        ti = i;
        j = cols-1;
        while (ti>-1&&j>-1) {
            diag2 += board[ti][j];
            ti--;
            j--;
        }
        
        ti = i;
        j = 0;
        while (ti<rows&&j<cols){
            diag3 += board[ti][j];
            ti++;
            j++;
        }
        ti = i;
        j =0;
        while (ti<rows&&j>-1) {
            diag4+=board[ti][j];
            ti ++;
            j --;
        }


        if (diag1.find(target_x)!=std::string::npos || diag2.find(target_x)!=std::string::npos||diag3.find(target_x)!=std::string::npos||diag4.find(target_x)!=std::string::npos) {
            return 'x';
        }
        if (diag1.find(target_o)!=std::string::npos || diag2.find(target_o)!=std::string::npos||diag3.find(target_o)!=std::string::npos||diag4.find(target_o)!=std::string::npos) {
            return 'o';
        }
    }

    for (int i = 0; i < rows;i ++ ){
        for (int j = 0; j < cols; j ++ ){
            if (board[i][j] == ' ') {
                return 'p';
            }
        }
    }


    return 'd';
}


std::pair<std::vector<std::vector<char>>,int> minimax(std::vector<std::vector<char>> board, int depth , int win_count , char player ,char turn ,int DEPTH) {
    
    char board_state = BoardState(board,win_count);

    if (depth == 0 || board_state != 'p'){ 




        int value;
        if (board_state == player) {
            value=1;
        }
        else if (board_state!='d') {
            value=-1;
        }
        else {
            value=0;
        }
        std::pair< std::vector<std::vector<char>>, int> result;
        result.first = board;
        result.second = value;

        return result;
    }
    
    
    std::vector<std::vector<std::vector<char>>> moves;
    std::vector<int> scores;
    for (int i = 0; i < board.size(); i ++ ) {
        for (int j = 0; j < board[0].size(); j ++) {
            if (board[i][j] == ' ') {
                std::pair<std::vector<std::vector<char>>,int> ans;
                if (turn == 'x') {
                    board[i][j] = 'x';
                    ans = minimax(board,depth-1,win_count,player,'o',DEPTH);
                    board[i][j] = ' ';
                }
                if (turn == 'o') {
                    board[i][j] = 'o';
                    ans = minimax(board,depth-1,win_count,player,'x',DEPTH);
                    board[i][j] = ' ';
                }
                moves.push_back(ans.first);
                scores.push_back(ans.second);
            }
        }
    }
    std::pair<std::vector<std::vector<char>>,int> RESULT;
    if (turn == player) {
        int maximum = -2;
        int index;
        for (int i = 0; i < scores.size(); i ++ ){
            if (scores[i]>maximum) {
                maximum=scores[i];
                index = i;
            }
        }

        if (depth == DEPTH) {
            RESULT.first = moves[index];
            RESULT.second = scores[index];
        }
        else {
            RESULT.first = board;
            RESULT.second = scores[index];
        }

        return RESULT;
    }

    int minimum = 3;
    int index;
    for (int i = 0; i < scores.size(); i ++ ){
        if (scores[i]<minimum) {
            minimum=scores[i];
            index = i;
        }
    }
    if (depth == DEPTH){
        RESULT.first = moves[index];
        RESULT.second = scores[index];
    }else{
        RESULT.first = board;
        RESULT.second = scores[index];
    }
    return RESULT;    
}

int main() {


    int rows ;
    int cols ;
    int win_count ;

    std::cout << "enter [rows,cols,win_count] :";
    std::cin >> rows >> cols >> win_count;
    std::cout << std::endl;

    std::vector<std::vector<char>> BOARD;

    for (int i = 0; i < rows; i ++) {
        std::vector<char> row;
        for (int j = 0; j < cols; j ++) {
            row.push_back(' ');
        }
        BOARD.push_back(row);
    }
    char player;
    std::cout << "do you want to be x or o? [x,o] :";
    std::cin >> player;
    std::cout << std::endl;

    char turn ='x';

    while (true) {
        std::cout << "-------------------------------------------" << std::endl;
        DrawBoard(BOARD);
        if (BoardState(BOARD,win_count) == 'x') {
            std::cout << "x won!" << std::endl;
            break;
        }
        if (BoardState(BOARD,win_count) == 'o') {
            std::cout << "o won!" << std::endl;
            break;
        }
        if (BoardState(BOARD,win_count) == 'd') {
            std::cout << "DRAW!" << std::endl;
            break;
        }

        if (turn == player) {
            int i,j;
            std::cout << "enter row number and col number [row col] : ";
            std::cin >> i >> j;
            std::cout << std::endl;
            BOARD[i][j] = turn;
            
        }

        if (turn != player) {
            std::pair<std::vector<std::vector<char>> , int> move;
            move = minimax(BOARD,9,win_count,turn,turn,9);
            BOARD=move.first;
        }
        if (turn =='o') turn = 'x';
        else if (turn == 'x') turn = 'o';
        
    }
}