#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>



struct Board {
    std::vector<std::vector<char>> grid;
};


struct boardScore {
    Board board;
    int score;
};


std::unordered_map<std::string,std::pair<std::string,int >> dp;


void DrawBoard(Board board) {

    int rows = board.grid.size();
    int cols = board.grid[0].size();

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
                    std::cout << board.grid[i/2-1][j/2-1];
                }
            }
        }
        std::cout << std::endl;
    }
}

char BoardState(Board board,int win_count) {
    int rows = board.grid.size();
    int cols = board.grid[0].size();
    std::string target_x ="";
    std::string target_o = "";
    for (int i = 0; i < win_count ; i ++) {
        target_x += 'x';
        target_o += 'o';
    }
    for (int i = 0; i < rows;i ++ ) {
        std::string row = "";
        for (int j = 0; j <cols; j ++) {
            row += board.grid[i][j];
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
            col += board.grid[i][j];
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
            diag1 += board.grid[ti][j];
            ti--;
            j ++;
        }

        ti = i;
        j = cols-1;
        while (ti>-1&&j>-1) {
            diag2 += board.grid[ti][j];
            ti--;
            j--;
        }
        
        ti = i;
        j = 0;
        while (ti<rows&&j<cols){
            diag3 += board.grid[ti][j];
            ti++;
            j++;
        }
        ti = i;
        j =0;
        while (ti<rows&&j>-1) {
            diag4+=board.grid[ti][j];
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
            if (board.grid[i][j] == ' ') {
                return 'p';
            }
        }
    }

    return 'd';
}


std::string boardToString(Board board) {
    std::string result = "";
    for (int i = 0; i < board.grid.size(); i ++ ){
        for (int j = 0; j < board.grid[0].size(); j ++) {
            result += board.grid[i][j];
        }
    }

    return result;
}

Board stringToBoard(std::string board,int rows , int cols) {
    Board result;
    for (int i = 0; i < rows; i++) {
        std::vector<char> row;
        for (int j = 0; j < cols; j ++ ){
            row.push_back(board[i * cols + j]);
        }
        result.grid.push_back(row);
    }    
    return result;
}


boardScore minimax(Board board, int depth , int win_count , char player ,char turn ,int DEPTH) {
    
    char board_state = BoardState(board,win_count);
    int rows = board.grid.size();
    int cols = board.grid[0].size();

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
        boardScore result;
        result.board = board;
        result.score = value;

        return result;
    }
    
    
    std::vector<Board> moves;
    std::vector<int> scores;
    for (int i = 0; i < board.grid.size(); i ++ ) {
        for (int j = 0; j < board.grid[0].size(); j ++) {
            if (board.grid[i][j] == ' ') {
                boardScore ans;
                if (turn == 'x') {
                    board.grid[i][j] = 'x';
                    std::string stringBoard = boardToString(board);
                    if (dp.find(stringBoard)!=dp.end()){
                        
                        ans.board=stringToBoard(dp[stringBoard].first,rows,cols);
                        ans.score= dp[stringBoard].second;
                        
                    }
                    else{
                        ans =  minimax(board,depth-1,win_count,player,'o',DEPTH);
                        std::pair<std::string,int> pair_ans;
                        pair_ans.first=boardToString(ans.board);
                        pair_ans.second=ans.score;
                        dp[stringBoard]= pair_ans;
                        
                    }
                    board.grid[i][j] = ' ';
                    
                }
                if (turn == 'o') {
                    board.grid[i][j]='o';
                    std::string stringBoard = boardToString(board);
                    if (dp.find(stringBoard)!=dp.end()){
                        ans.board=stringToBoard(dp[stringBoard].first,rows,cols);
                        ans.score= dp[stringBoard].second;
                    }
                    else {
                        ans = minimax(board,depth-1,win_count,player,'x',DEPTH);
                        std::pair<std::string,int> pair_ans;
                        pair_ans.first=boardToString(ans.board);
                        pair_ans.second=ans.score;
                        dp[stringBoard]= pair_ans;
                    }
                    
                    board.grid[i][j] = ' ';
                }
                moves.push_back(ans.board);
                scores.push_back(ans.score);
            }
        }
    }
    boardScore RESULT;
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
            RESULT.board = moves[index];
            RESULT.score = scores[index];
        }
        else {
            RESULT.board = board;
            RESULT.score = scores[index];
            
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
        RESULT.board = moves[index];
        RESULT.score = scores[index];
    }else{
        //std::cout << scores.size() << std::endl;
        //std::cout << scores[0] << std::endl;
        RESULT.board = board;
        RESULT.score = scores[index];
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

    Board BOARD;


    for (int i = 0; i < rows; i ++) {
        std::vector<char> row;
        for (int j = 0; j < cols; j ++) {
            row.push_back(' ');
        }
        BOARD.grid.push_back(row);
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
            BOARD.grid[i][j] = turn;
            
        }

        if (turn != player) {
            boardScore move = minimax(BOARD,25,win_count,turn,turn,25);
            dp.clear();
            BOARD = move.board;
        }
        if (turn =='o') turn = 'x';
        else if (turn == 'x') turn = 'o';
        
    }
}