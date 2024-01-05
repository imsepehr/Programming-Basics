#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>
#pragma warning(disable: 4996)
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
using namespace std;

struct USER
{
    char Username[20];
    char Password[20];
   
};

struct GAME
{
    int minefield[30][30];                                      //This 2-D array contains all of the mines, numbers and blank spaces
    int blank_minefield[30][30];                                //This contains the minefield full of '|-|' characters
    int final_minefield[30][30];

};

struct GameInfo
{
    char dificulty_name[20];
    time_t t;
    int row;
    int coulmn;
    
};

void MenuMain();
void Login();
void SignUp();
void MenuGame();
void EditPass();
void load();
void save(GameInfo gmi);
void difficulty(void);
void beginner(void);
void intermediate(void);
void expert(void);
void custom(void);
void minefield_generator(void);
void print_minefield(void);
void guess(void);
void boom(void);
void print_final_minefield(void);
void win(void);
void play_again(void);


int x, y;
int M, N;
float diff;
int total_mines = 0;
int mines = 0;
USER user;
GAME game;
GameInfo gameinfo;
//int minefield[30][30];                                      //This 2-D array contains all of the mines, numbers and blank spaces
//int blank_minefield[30][30];                                //This contains the minefield full of '|-|' characters
//int final_minefield[30][30];

int main()
{
    
    MenuMain();
    //difficulty();
    
    return 0;
}

void MenuMain()
{
	puts("\t\t\t\t---------------------------------------------------------------");

	printf(ANSI_COLOR_YELLOW "\t\t\t\t|\t     \" W    E    L    C    O    M    E \"\t      |\n\n\t\t\t\t|\t\t     T  O      M  Y\t\t\t      |\n\n\t\t\t\t|\t         \" P  R  O  G  R  A  M  M \"\t\t      |\n" ANSI_COLOR_RESET);

	puts("\t\t\t\t---------------------------------------------------------------\n");
	puts("\n");

	printf(ANSI_COLOR_BLUE "%50s%52s%60s", "\t\t\t1.login\n\n", "\t\t\t2.sign up\n\n", "\t\t3.Exit\n\n" ANSI_COLOR_RESET);

    while (true)
    {
        int menumain;
        cout << "? : ";
        cin >> menumain;

        switch (menumain)
        {
        case 1:
            Login();
            break;
        case 2:
            SignUp();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Just Enter (1) OR (2) OR (3)";
            break;
        }
    }
}

void Login()
{
    char filepath[] = "Userinfo.bin";
    FILE* fp = fopen(filepath, "rb");
    //USER user;
    
    cout << "Username : " << endl;
    cin >> user.Username;
    cout << "Password : " << endl;
    cin >> user.Password;
    
    bool flag = false;
    USER fuser;
    while (!feof(fp))
    {
        fread(&fuser, sizeof(fuser), 1, fp);
        if (strcmp(fuser.Username, user.Username) == 0 && strcmp(fuser.Password, user.Password) == 0)
        {
            flag = true;
            break;
        }
    }

    if (flag == false)
        Login();
    else
        MenuGame();
    
    
}

void SignUp()
{
    char filepath[] = "Userinfo.bin";
    FILE* fp = fopen(filepath, "ab");
    //USER user;

	cout << "Username : " << endl;
    cin >> user.Username;
	cout << "Password : " << endl;
    cin >> user.Password;

    fwrite(&user, sizeof(user), 1, fp);
    fclose(fp);

    MenuGame();

}

void MenuGame()
{
    printf("\n\t\t\t---------------------------------------------------\n"
        "\t\t\t|\t\t1.New\t\t\t\t  |\n"
        "\t\t\t|\t\t2.Load\t\t\t\t  |\n"
        "\t\t\t|\t\t3.Edit Password\t\t\t  |\n"
        "\t\t\t|\t\t4.Exit\t\t\t\t  |\n"
        "\t\t\t---------------------------------------------------\n\n");


    while (true)
    {
        int menugame;
        cout << "\n? : ";
        cin >> menugame;

        switch (menugame)
        {
        case 1:
            time(&gameinfo.t);
            difficulty();
            break;
        case 2:
            load();
            break;
        case 3:
            EditPass();
            break;
        case 4:
            MenuMain();
            break;
        default:
            cout << "Choose correct number (1) or (2) or (3) or (4)";
            break;
        }
    }
}

void EditPass()
{
    char filepath[] = "Userinfo.bin";
    FILE* fp = fopen(filepath, "rb");
    
    USER userlist[100];
    int i = 0;
    while (!feof(fp))
    {
        fread(&userlist[i], sizeof(userlist[i]), 1, fp);
        i++;
    }
    fclose(fp);
    char new_username[20], new_password[20];

    cout << "1-Username : " << user.Username << "\n";
    cout << "2-Password : " << user.Password << "\n";
    cout << "3-Save" << "\n";
    cout << "4-Return " << "\n\n";
    

    while (true)
    {
        int editpass;
        cout << "? : ";
        cin >> editpass;

        switch (editpass)
        {
        case 1:
            cout << "New Username : ";
            cin >> new_username;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(userlist[j].Username, user.Username) == 0 )
                {
                    strcpy(userlist[j].Username, new_username);
                    break;
                }
            }
            strcpy(user.Username, new_username);
            break;
        case 2:
            cout << "New Password : ";
            cin >> new_password;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(userlist[j].Password, user.Password) == 0)
                {
                    strcpy(userlist[j].Password, new_password);
                    break;
                }
            }
            strcpy(user.Password, new_password);
            break;
        case 3:
            cout << "New Info Saved :)" << endl;
            fp = fopen(filepath, "wb");
            for (int j = 0; j < i; j++)
            {
                fwrite(&userlist[j], sizeof(userlist[j]), 1, fp);
            }
            fclose(fp);
            break;
        case 4:
            MenuGame();
            break;
        default:
            cout << "Enter (1) or (2) or (3)" << endl;
            break;
        }
    }
}









void difficulty(void)                                     //Function for choosing the difficulty level
{
    diff = 0;
    while ((diff != 1) && (diff != 2) && (diff != 3) && (diff != 4))
    {
        printf("\t\tChoose a difficulty level(1-3) or 4 for a custom game:");
        scanf("%f", &diff);
        
        if ((diff != 1) && (diff != 2) && (diff != 3) && (diff != 4))
        {
            printf("\t\tPlease enter either 1, 2, 3 or 4\n");
        }
    }

    if (diff == 1)                                         //If, else if and else statements that each go to the respective difficulty
    {
        beginner();
        strcpy(gameinfo.dificulty_name, "beginner");

    }
    else if (diff == 2)
    {
        intermediate();
        strcpy(gameinfo.dificulty_name, "intermediate");

    }
    else if (diff == 3)
    {
        expert();
        strcpy(gameinfo.dificulty_name, "expert");

    }
    else if (diff == 4)
    {
        custom();
        strcpy(gameinfo.dificulty_name, "custom");

    }
}

void beginner(void)                                       //Gives the minefield the 'beginner' grid and mines
{
    M = 9;
    N = 9;
    total_mines = 10;
    minefield_generator();
    guess();
}

void intermediate(void)                                   //Gives the minefield the 'intermediate' grid and mines
{
    M = 16;
    N = 16;
    total_mines = 40;
    minefield_generator();
    guess();
}

void expert(void)                                         //Gives the minefield the 'expert' grid size and mines
{
    M = 16;
    N = 30;
    total_mines = 99;
    minefield_generator();
    guess();
}

void custom(void)
{
    M = 0;
    N = 0;
    total_mines = 0;
    printf("\t\tPlease enter the size of the dimensions you want\n");
    printf("\t\tFirst value:\n");
    scanf("%d", &M);
    printf("\t\tSecond value:\n");
    scanf("%d", &N);
    printf("\t\tNumber of mines you want to assign to the board:\n");
    scanf("%d", &total_mines);
    minefield_generator();
    guess();
}

void minefield_generator(void)                            //Function that generates the minefield
{
    int i = 0, j = 0;

    srand(time(NULL));                                  //Starts the random no. generator

    while (j < N)                                          //Nested loop for making the blank minefield and final minefield
    {
        while (i < M)
        {
            game.minefield[i][j] = '-';
            game.blank_minefield[i][j] = game.minefield[i][j];
            game.final_minefield[i][j] = game.minefield[i][j];
            i++;
        }
        i = 0;
        j++;
    }
    mines = 0;
    while (mines < total_mines)                            //Randomly generates the mines into the minefield
    {
        i = rand() % (M);
        j = rand() % (N);
        if (game.minefield[i][j] != '*')                         //If statement that checks if there is a mine already there and doesn't place a mine if there is
        {
            game.minefield[i][j] = '*';
            game.final_minefield[i][j] = game.minefield[i][j];
            mines++;
        }
    }
    i = 0;
    j = 0;

    while (j < N)                                          //While loop that generates the numbers for any adjacent mines
    {
        while (i < M)
        {
            if (game.minefield[i][j] != '*')
            {
                game.minefield[i][j] = 0;
            }
            if ((game.minefield[i - 1][j - 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i - 1][j] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i][j - 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i - 1][j + 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i + 1][j - 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i + 1][j] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i][j + 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            if ((game.minefield[i + 1][j + 1] == '*') && (game.minefield[i][j] != '*'))
            {
                game.minefield[i][j]++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    i = 0;
    j = 0;

}

void print_minefield(void)                                  // This function prints the minefield
{
    int i = 0, j = 0, z = 0;
    while (z < M)                                          // This while loop prints out the line of co-ordinates along the x axis of the minefield
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N)                                          // Loop that prints out each character in the minefield                         
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            if (game.blank_minefield[i][j] == '-')
            {
                printf("|%c|\t", game.blank_minefield[i][j]);

            }
            else if (game.minefield[i][j] == 0)                 // This changes any spaces with values of zero to the character 'B'
            {
                game.blank_minefield[i][j] = 'B';
                printf("|%c|\t", game.blank_minefield[i][j]);
            }
            else
            {
                printf("|%d|\t", game.blank_minefield[i][j]);

            }
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}


void guess(void)
{
    int q = 0, i = 0, j = 0, match = 0;
    print_minefield();
    while (j < N)                                          // While loop for testing whether or not the user has cleared the minefield
    {
        while (i < M)
        {
            if (game.minefield[i][j] == game.blank_minefield[i][j])
            {
                match++;
            }
            i++;
        }
        i = 0;
        j++;
    }
    if (match == ((M * N) - total_mines))                 // If the user has cleared the minefield, the win() function is run
    {
        win();

    }
    printf("\nEnter the x value, then a space, then the y value:");
    scanf("%d %d", &x, &y);                                 // Reading in the co-ordinates for the guess
    
    if ((x >= M) || (x < 0) || (y < 0) || (y >= N))
    {
        printf("\nPlease enter a value inside the grid\n");
        guess();
    }
    if (game.minefield[x][y] == '*')                            // Runs the boom() function if the user selects a mine
    {
        boom();
    }
    if (game.blank_minefield[x][y] != '-')
    {
        printf("\nPlease enter a value that has not already been entered\n");
        guess();
    }

    else                                                // Checks if the adjacent spaces are blank, then changes the values in the blank_minefield array. Because they are changed, they will now print out in the print_minefield function
    {
        game.blank_minefield[x][y] = game.minefield[x][y];
        if (game.minefield[x][y] == 0)
        {
            if (game.minefield[x - 1][y - 1] == 0)
            {
                game.blank_minefield[x - 1][y] = game.minefield[x - 1][y];
            }
            if (game.minefield[x - 1][y] == 0)
            {
                game.blank_minefield[x - 1][y] = game.minefield[x - 1][y];
            }
            if (game.minefield[x][y - 1] == 0)
            {
                game.blank_minefield[x][y - 1] = game.minefield[x][y - 1];
            }
            if (game.minefield[x - 1][y + 1] == 0)
            {
                game.blank_minefield[x - 1][y + 1] = game.minefield[x - 1][y + 1];
            }
            if (game.minefield[x + 1][y - 1] == 0)
            {
                game.blank_minefield[x + 1][y - 1] = game.minefield[x + 1][y - 1];
            }
            if (game.minefield[x + 1][y] == 0)
            {
                game.blank_minefield[x + 1][y] = game.minefield[x + 1][y];
            }
            if (game.minefield[x][y + 1] == 0)
            {
                game.blank_minefield[x][y + 1] = game.minefield[x][y + 1];
            }
            if (game.minefield[x + 1][y + 1] == 0)
            {
                game.blank_minefield[x + 1][y + 1] = game.minefield[x + 1][y + 1];
            }
        }
        guess();
    }
}

void boom(void)                                       // Runs the print_final_minefield function, then the play_again function                    
{
    print_final_minefield();
    printf("\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
    gameinfo.coulmn = x;
    gameinfo.row = y;
    save(gameinfo);
    play_again();
}

void print_final_minefield(void)                      // Prints the minefield, showing where all of the mines are placed
{
    int i = 0, j = 0, z = 0;
    while (z < M)
    {
        if (z == 0)
        {
            printf("\t");
        }
        printf("|%d|\t", z);
        z++;
    }
    printf("\n\n");

    while (j < N)
    {
        printf("|%d|\t", j);
        while (i < M)
        {
            printf("|%c|\t", game.final_minefield[i][j]);
            i++;
        }
        printf("\n");
        i = 0;
        j++;
    }
}

void win(void)                                        // Runs the play_again function
{
    printf("\n\n\n\t\t\tYOU WIN!!!!!\n\n\n");
    gameinfo.coulmn = -1;
    gameinfo.row = -1;
    save(gameinfo);
    play_again();
}

void play_again(void)                                 // Gives the user the option to play again
{
    char option[2];
    printf("\n\t\tWould you like to Return GameMenu(Y/N)?:");
    scanf("%c", &option[0]);
    
    if ((option[0] == 'Y') || (option[0] == 'y'))        // Restarts the program from after the welcome message
    {
        MenuGame();
    }
    else if ((option[0] == 'N') || (option[0] == 'n'))
    {
        MenuMain();
    }
    else
    {
        printf("Please enter either Y or N");
        play_again();
    }
}

void save(GameInfo gmi)
{
    char filepath[30] = "";
    strcat(filepath, user.Username);
    strcat(filepath, ".bin");
    FILE* fp = fopen(filepath, "ab");
    fwrite(&gmi, sizeof(gmi), 1, fp);
    fclose(fp);
}

void load()
{
    char filepath[30] = "";
    strcat(filepath, user.Username);
    strcat(filepath, ".bin");
    FILE* fp = fopen(filepath, "rb");
    int i = 0;
    GameInfo gmi;

    while (!feof(fp))
    {
        fread(&gmi, sizeof(gmi), 1, fp);
        printf("%s : %s  Hit the mine at (%d,%d)\n", gmi.dificulty_name, ctime(&gmi.t), gmi.coulmn, gmi.row);
    }
    fclose(fp);

    /*for (int j = 0; j < i; j++)
    {
        printf("%s : %s --> Hit the mine in location (%d,%d)\n", gmi[j].dificulty_name, ctime(&gmi[j].t), gmi[j].coulmn, gmi[j].row);
    }*/
    
    cout << "Press any key to return" << endl;
    getch();
    
    MenuGame();
    
    
}