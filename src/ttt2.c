#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

typedef struct tree{
    char b[3][3];
    char s[3][3];
    struct tree *right;
    struct tree *left;
}Tree;

struct Move
{
    int row, col;
};

char human = 'X', computer = 'O';
int ply=0;
int com=0;
int draw=0;

Tree *root=NULL, *traverse = NULL, *traverse2=NULL, *traverse3=NULL;

int AddNode(char board[3][3]){
    Tree *newchild =(Tree*) malloc (sizeof(Tree));
    newchild->left = newchild->right = NULL;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            newchild->b[i][j]=board[i][j];
    if(traverse2->left == NULL){  //if the level of tree has no nodes
        traverse2->left= newchild;
        traverse = newchild;
        printf("Added at the start\n");
    }
    else{                       // if the level of tree has existing nodes
        traverse3->right = newchild;
        traverse = newchild;
        printf("Added at the end\n");
    }
    return 0;
}

int TreeSearch(char board[3][3]){
    traverse3 = traverse;
    traverse2 = traverse;
    traverse=traverse->left;
    //Search for the board
    while(traverse!=NULL){
        int flag=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(traverse->b[i][j]!=board[i][j])
                    flag=1;
        if(flag==0){
            // If found
            return 1;
        }
        else
        {
            //if not found
            traverse3 = traverse;
            traverse=traverse->right;
        }
    }
    return AddNode(board); //Calls function to Add new node in the tree
}


void displayBoard(char board[3][3]){
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n",board[0][0],board[0][1],board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n",board[1][0],board[1][1],board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n",board[2][0],board[2][1],board[2][2]);
    printf("     |     |     \n");
}
void clearBoard(char board[3][3]){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j]=' ';
}
int validMove(char board[3][3],int x,int y){
    if(board[x][y]==' ')
        return 1;
    else
        printf("Invalid Move, Try another position.\n");
        return 0;
}
int checkResult(char state[3][3]){
    char win_state[9][3] = {
        {state[0][0], state[0][1], state[0][2]},
        {state[1][0], state[1][1], state[1][2]},
        {state[2][0], state[2][1], state[2][2]},
        {state[0][0], state[1][0], state[2][0]},
        {state[0][1], state[1][1], state[2][1]},
        {state[0][2], state[1][2], state[2][2]},
        {state[0][0], state[1][1], state[2][2]},
        {state[2][0], state[1][1], state[0][2]},
    };
    for(int i=0;i<9;i++){
        if(win_state[i][0]==win_state[i][1] && win_state[i][1]==win_state[i][2] ){
                if(win_state[i][2]==human){
                    printf("Game Over Human wins\n");
                    ply++;
                    return 0;
                }
                else if(win_state[i][2]==computer){
                    printf("Game Over Computer wins\n");
                    com++;
                    return 0;
                }
        }
    }
}
bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==' ')
                return true;
    return false;
}
int evaluate(char b[3][3])
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==computer)
                return +10;
            else if (b[row][0]==human)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==computer)
                return +10;

            else if (b[0][col]==human)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==computer)
            return +10;
        else if (b[0][0]==human)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==computer)
            return +10;
        else if (b[0][2]==human)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}
int minimax(char board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    if (score == 10)
        return score;

    if (score == -10)
        return score;

    if (isMovesLeft(board)==false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==' ')
                {
                    // Make the move
                    board[i][j] = computer;

                    best = max( best, minimax(board, depth+1, !isMax) );

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==' ')
                {
                    // Make the move
                    board[i][j] = human;

                    best = min(best,minimax(board, depth+1, !isMax));

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// This will return the best possible move for the player
struct Move findBestMove(char board[3][3])
{
    int bestVal = -1000;
    struct Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;


    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]==' ')
            {
                // Make the move
                board[i][j] = computer;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = ' ';

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
void main(){
    root = (Tree*) malloc (sizeof(Tree));
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            root->b[i][j]=' ';
    root->left=NULL;
    root->right=NULL;
    int x;
    double t,start,finish;
    char board[3][3];
    int moves[9][2]={{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    int count=1;
    int n,m,choice;
    printf("Welcome to the Unbeatable TIC TAC TOE Game....\nTry your luck and try to beat the Computer...\n\n");
    while(1){
        printf("1]New Game\n2]Exit\n\n");
        printf("Enter your choice:\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                t = 0.0;
                clearBoard(board);
                count=1;
                traverse = root;
                while(count<=9){
                    printf("Enter the no.:");
                    scanf("%d",&n);
                    if(validMove(board,moves[n-1][0],moves[n-1][1]))
                    {
                        board[moves[n-1][0]][moves[n-1][1]]=human;
                        //displayBoard(board);
                        printf("\n\n");
                        count=count+1;
                        if(!checkResult(board))
                           break;
                        clock_t begin = clock();
                        start=(double) begin / CLOCKS_PER_SEC;
                        //printf("start time: %.10f\n",start);
                        //sleep(1);
                        m=TreeSearch(board);
                        if(m==1){
                            printf("Using Tree\n");
                            memcpy(board,traverse->s,sizeof board);
                        }
                        else{
                            printf("Using MinMax\n");
                            struct Move bestMove = findBestMove(board);
                            board[bestMove.row][bestMove.col]=computer;
                            memcpy(traverse->s,board,sizeof board);
                        }
                        clock_t end = clock();
                        finish=(double) end / CLOCKS_PER_SEC;
                        //printf("end time: %.10f\n",finish);
                        t += finish-start;
                        displayBoard(board);
                        printf("total tiem: %lf\n",t);
                        count=count+1;
                        if(!checkResult(board))
                           break;
                    }
                }
                if(!isMovesLeft(board)){
                    draw++;
                    printf("Game Over Its a Draw\n\n\n");
                }
                break;
            case 2:
                exit(0);
            default:
                printf("\nEnter valid choice.\n");
        }
        printf("Score Board:\n\n");
        printf("Computer: %d\n",com);
        printf("Human: %d\n",ply);
        printf("Draw: %d\n\n",draw);
        printf("Time: %f\n\n\n",t);
    }

}
