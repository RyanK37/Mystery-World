#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Room {                                                   //Room class
    public:

    bool is_empty(char matrix1[10][10], int row, int column){   //check whether the place is empty or not
        return matrix1[row][column] == '.';
    }

    // --------------------------------------------------------------------------------

    void display_room(char matrix1[10][10]){                    //display the current room 
        cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
        for (int i=0; i<10; i++){
            cout << i << " " ;
            for (int j=0; j<10; j++){
                cout << matrix1[i][j] << " " ;
            }
            cout << endl;
        }
    }

    // --------------------------------------------------------------------------------

    bool wanna_continue(){                                     //to ask the user whether he/she wants to contiue the game or not
        while (true){
            string option1;
            cout << "\nDo you want to continue playing the game?(Type Yes or No)  >> ";
            cin  >> option1;
            if (option1 == "No" || option1 == "no"){
                cout << "\nThank you for playing our game!";
                return false;
            }
            else if (option1 == "Yes" || option1 == "yes"){
                return true;
            }
            else {
                cout << "\nInvalid input!!\nPlease type Yes or No!!\n";
            }
        }
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Inanimate : public Room {                               //Inanimate class and it inherient Room class directly
    public:
    int random_row;                                           //declare the variables random_row and random_column to use for inanimate entiies 
    int random_column;      
};

// ==================================================================================== //

class Stone : public Inanimate {                            //Stone class (inherient directly from Inanimate class and undirectly from Room class)
    public:
    void place_stone(char matrix2[10][10]){                   //The function to randomly place the stones at the start
        for (int i=0; i<2; ){
            random_row = rand() % 10;
            random_column = rand() % 10;
            if (is_empty(matrix2 , random_row , random_column)){
                matrix2[random_row][random_column] = 'S';
                i++;
            }
        }
    }

    // --------------------------------------------------------------------------------

    void display_stone_info(){                              //The function to display the informations of the stones
        cout << "Entity properties:\n";
        cout << "Type : Stone\n";
    }
};

// ==================================================================================== //

class Hole : public Inanimate {                             //The Hole class (inherient directly from Inanimate class and undirectly from Room class)
    public:
    int depth;                                              
    vector<tuple<int , int , int>>hole_info;                //Vector of tuple with "hole_info" as variable name to store the informations of the holes
    
    void place_hole(char matrix3[10][10]){                    //The function to randomly place the holes at the start and store their datas (depth, row, column) into "hole_info"
        for (int i=0; i<2; ){
            depth = rand() % 21;
            random_row = rand() % 10;
            random_column = rand() % 10;
            if (is_empty(matrix3 , random_row , random_column)){
                matrix3[random_row][random_column] = 'O';
                hole_info.emplace_back(depth, random_row, random_column);
                i++;
            }
        }
        
    }

    // --------------------------------------------------------------------------------

    void display_hole_info(int row, int column){            //The function to display the informations/properties of the holes
        for (auto info : hole_info){
            int dp = get<0>(info);
            int r = get<1>(info);
            int cl = get<2>(info);
            if (r == row && cl == column){
                cout << "Entity properties:\n";
                cout << "Type : Hole\n";
                cout << "Depth : " << dp << endl;
            }
        }
    }
};

// ==================================================================================== //
// ==================================================================================== //

class Animate : public Room {                               //The animate class inherient directly from Room
    public:
    int health = 100;                                       //Delcare some variables and initialize health value as "100" since it is true for every animate entities
    int random_row;
    int random_column;
};

// ==================================================================================== //

class Human : public Animate {                              //Human class (inherient directly from Animate and undirectly from Room)
    public:
    string name[3] = {"Harlod" , "David", "Clare"};         //Assign some names according to the task and store in a string array "name"
    vector<tuple<string, int, int, int>>human_info;

    void place_human(char matrix4[10][10]){                   //The function to randomly place the humans at the start and store their datas (name, helath, row, column) into "human_info" 
        for (int i=0; i<3;) {                               //For loop for 3 humans
            random_row    = rand() % 10;                    //random_row
            random_column = rand() % 10;                    //random_column
            if (is_empty(matrix4, random_row , random_column)){         //if the palce is empty, place "@" which represent "@"
                matrix4[random_row][random_column] = '@';
                human_info.emplace_back(name[i], health, random_row, random_column);  //Store name, health, row and column of each human into human_info
                i++;
            }
        }
    }

    // --------------------------------------------------------------------------------

    void human_move(char matrix4[10][10]){                        //The funciton to move human entities 
        for (auto &position : human_info){                      //Use Reference "&" so that values of human_info can be updated easily
            int row = get<2>(position);                         //fetch row
            int column = get<3>(position);                      //fetch column
            vector<pair<int,int>> valid_moves;                  //To store the possible moves of human entities

            if(column < 9 && matrix4[row][column+1] == '.'){    //To move right (which is the first option for humans) and store in "valid_moves"
                valid_moves.push_back({row, column+1});
            }

            if (valid_moves.empty()){                           //If right is not possible to move, check all possible adjecents and store in "valid_moves"
                if(row > 0 && matrix4[row-1][column] == '.'){   //To move up
                    valid_moves.push_back({row-1, column});
                }

                if(row < 9 && matrix4[row+1][column] == '.'){   //To move down
                    valid_moves.push_back({row+1, column});
                }

                if(column > 0 && matrix4[row][column-1] == '.'){ //To move left
                    valid_moves.push_back({row, column-1});
                }
            }

            if (!valid_moves.empty()){                           //If the "valid_moves" is not empty, randomly pick the place to move  
                int index = rand() % valid_moves.size();    
                pair <int , int > move = valid_moves[index];    
                matrix4[move.first][move.second] = matrix4[row][column];
                matrix4[row][column] = '.';
                get<2>(position) = move.first;                  //Update the new row of human
                get<3>(position) = move.second;                 //Update the new column of human
                get<1>(position) = get<1>(position)-1;          //Health is reduced by 1
            }

            if (get<1>(position) <= 0){                         //If the health reached 0 or less than 0 the entity is cleared and replaced '.' as empty space
                matrix4[get<2>(position)][get<3>(position)] = '.';
            }
        }
    }

    // --------------------------------------------------------------------------------

    void display_human_info(int row, int column){               //The funciton to display human informations using row and column as parametes
        for (auto info : human_info){                           //To check every row and column of each human (since there are only three)
            string n    = get<0>(info);         
            int hp      = get<1>(info);
            int r       = get<2>(info);
            int cl      = get<3>(info);
            if (r == row && cl == column ){                     //If row and column is same, display that one human's properties.If not check another human according to "for loop"
                cout << "Entity properties:\n";
                cout << "Type : Human\n";
                cout << "Name : " << n << "\n";
                cout << "Health : " << hp << "%\n";
            }
        }
    }

};
// ==================================================================================== //

class Dragon : public Animate {                                     //The dragon class (inherient directly from Animate and undirectly from Room)
    public: 
    vector<tuple<int, int, int>>dragon_info;                        //To store informations of dragons (health, row, column)

    void place_dragon(char matrix5[10][10]){                          //The function to place dragon and store their info
        for (int i=0; i<2;){                                        //Two dragons
            random_row    = rand() % 10;                            //random_row
            random_column = rand() % 10;                            //random_column
            if (is_empty(matrix5, random_row , random_column)){     //If loop to check empty place and place the dragons "#" and store info of each dragon into dragon_info
                matrix5[random_row][random_column] = '#';
                dragon_info.emplace_back(health, random_row, random_column);
                i++;                                                //next dragon
            }
        }
    }
    
    //--------------------------------------------------------------------------------

    void dragon_move(char matrix5[10][10]){                           //The function to move dragons 
        for (auto &position : dragon_info) {                        //Use Reference "&" so that values of dragon_info can be updated easily
            int row    = get<1>(position);                          //fetch row
            int column = get<2>(position);                          //fetch column
            vector<pair<int , int>> valid_moves;                    //To store the possible moves of dragon entities

            if(row > 0 && matrix5[row-1][column] == '.'){           //To move up
                valid_moves.push_back({row-1, column});
            }
            if(row < 9 && matrix5[row+1][column] == '.'){           //To move down
                valid_moves.push_back({row+1, column});
            }
            if(column > 0 && matrix5[row][column-1] == '.'){        //To move left
                valid_moves.push_back({row, column-1});
            }
            if(column < 9 && matrix5[row][column+1] == '.'){        //To move right
                valid_moves.push_back({row, column+1});
            }

            if (!valid_moves.empty()){                              //If the valid_moves is not empty, randomly choose an adjcent and move
                int index = rand() % valid_moves.size();            //Same concept from human_move
                pair <int, int>move = valid_moves[index];
                matrix5[move.first][move.second] = matrix5[row][column];
                matrix5[row][column] = '.';
                get<1>(position) = move.first;
                get<2>(position) = move.second;               
                get<0>(position) = get<0>(position) - (rand()% 6);  //Reduced health by random between 0 and 5 (inclusive)
            }

            if (get<0>(position) <= 0){                             //If the health reached 0 or less than 0 the entity is cleared and replaced '.' as empty space
                matrix5[get<1>(position)][get<2>(position)] = '.';
            }
        }
    }
    // --------------------------------------------------------------------------------

    void display_dragon_info(int row, int column){                 //The funciton to display dragon informations using row and column as parametes
        for (auto info : dragon_info){                             //Same concept from display_human_info
            int hp = get<0>(info);
            int r  = get<1>(info);
            int cl = get<2>(info);
            if (r == row && cl == column){
                cout << "Entity properties:\n";
                cout << "Type : Dragon\n";
                cout << "Health : " << hp << "%\n";
            }
        }
    }

};

// ==================================================================================== //

class Monster : public Animate {                                    //The monster class (inherient directly from Animate and undirectly from Room)
    public:
    int random_strength;                                            //declare "random_strenth" variable 
    vector<tuple<int, int, int, int>>monster_info;                  //To store informations of monsters (health, strenth, row, column)

    void place_monster(char matrix6[10][10]){                         //The function to place monsters and store their info into "monster_info"
        for (int i=0; i<3;) {                                       //Same conecpt with "place_human" and "place_dragon"
            random_strength = rand() % 5 + 1;                       //To random the strength of monsters between "1" and "5"(inclusive) ("0" was excluded because of movement)
            random_row      = rand() % 10;
            random_column   = rand() % 10;
            if (is_empty(matrix6, random_row , random_column)){
                matrix6[random_row][random_column] = '*';
                monster_info.emplace_back(health, random_strength, random_row, random_column);
                i++;
            }
        }
    }

    // --------------------------------------------------------------------------------

    void monster_move(char matrix6[10][10]){                                          //The funciton to move monsters
        for (auto &position : monster_info){                                        //Same fectching datas concept with "human" and "dragon"
            int row      = get<2>(position);            
            int column   = get<3>(position);
            int strength = get<1>(position);
            vector<pair<int, int>> valid_moves;

            if (row-strength >= 0 && matrix6[row - strength][column] == '.'){       //To move up  
                valid_moves.emplace_back(row-strength , column);    
            }
            if (row+strength < 10 && matrix6[row + strength][column] == '.'){       //To move down
                valid_moves.emplace_back(row+strength , column);
            }
            if (column-strength >= 0 && matrix6[row][column - strength] == '.'){    //To move left
                valid_moves.emplace_back(row , column-strength);
            }
            if (column+strength < 10 && matrix6[row][column + strength] == '.'){    //To move right
                valid_moves.emplace_back(row , column+strength);
            }

            
            if (!valid_moves.empty()){                                              //If normal monster movement are possible, random one and go to that place(using same logic with "human" and "dragon")
                int index = rand() % valid_moves.size();
                pair <int , int > move = valid_moves[index];
                matrix6[move.first][move.second] = matrix6[row][column];
                matrix6[row][column] = '.';
                get<2>(position) = move.first;
                get<3>(position) = move.second;
            }
            else {                                                                  //If normal movements are not possible, move to a random adjecent place (Same concept with "dragon")
                vector<pair<int , int>> valid_moves_1;
                                                                                    
                if(row > 0 && matrix6[row-1][column] == '.'){                       //To move up
                    valid_moves_1.push_back({row-1, column});
                }
                if(row < 9 && matrix6[row+1][column] == '.'){                       //To move down
                    valid_moves_1.push_back({row+1, column});
                }
                if(column > 0 && matrix6[row][column-1] == '.'){                    //To move left
                    valid_moves_1.push_back({row, column-1});
                }
                if(column < 9 && matrix6[row][column+1] == '.'){                    //To move right
                    valid_moves_1.push_back({row, column+1});
                }
                if (!valid_moves_1.empty()){                                        //Same concept with 
                    int index = rand() % valid_moves_1.size();
                    pair <int, int>move1 = valid_moves_1[index];
                    matrix6[move1.first][move1.second] = matrix6[row][column];
                    matrix6[row][column] = '.';
                    get<2>(position) = move1.first;
                    get<3>(position) = move1.second;               
                }
            }
            get<0>(position) = get<0>(position) - get<1>(position);

            if (get<0>(position) <= 0){
                matrix6[get<2>(position)][get<3>(position)] = '.';
            }
        }
    }

    // --------------------------------------------------------------------------------

    void display_monster_info(int row, int column){                         //The funciton to display monsters' informations
        for (auto info : monster_info){                                     //Same concept with "human" and "dragon"
            int hp = get<0>(info);
            int st = get<1>(info);
            int r  = get<2>(info);
            int cl = get<3>(info);
            if (r == row && cl == column ){
                cout << "Entity properties:\n";
                cout << "Type : Monster\n";
                cout << "Strength : " << st << "\n";
                cout << "Health : " << hp << "%\n";
            }
        }
    }
};


// ==================================================================================== //
// ==================================================================================== //

int main(){
    srand(time(NULL));                                                  //Since we are using rand() to random, we need to use srand() to initialize
    char grid[10][10] = {                                               //Intialzie the empty room with character array "grid"
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        {'.','.','.','.','.','.','.','.','.','.'},
                        };

    Room room;                                                         //Create object for "Room" class
    Stone stone;                                                       //Create object for "Stone" class
    Hole hole;                                                         //Create object for "Hole" class
    Human human;                                                       //Create object for "Human" class
    Dragon dragon;                                                     //Create object for "Dragon" class        
    Monster monster;                                                   //Create object for "Monster" class

    stone.place_stone(grid);                                           //Place "stone"  
    hole.place_hole(grid);                                             //Place "hole" 
    human.place_human(grid);                                           //Place "human" 
    dragon.place_dragon(grid);                                         //Place "dragon"         
    monster.place_monster(grid);                                       //Place "monster" 
    // --------------------------------------------------------------------------------

    cout << "Hello! Welcome from Mystery World!\n";
    room.display_room(grid);
    while (true){
        int instruction;
                                                                        //The options menu
        cout << "\nAvaialabe options.\n";
        cout << "1. Display Room\n2. Move all the animated entites\n3. Display the entity state by coordinates\n4. Reset the room\n5. Finish\n";
        cout << "Your option(in number 1 to 5) >>> ";
        cin  >> instruction;
        cout << endl;
        // --------------------------------------------------------------------------------
        if (instruction == 1) {                                        //Display the current state fo the room
            room.display_room(grid);
            if (!room.wanna_continue()){                               //Ask the user whether want to continue the game or not?
                break;
            }   
        }

        // --------------------------------------------------------------------------------

        else if (instruction == 2) {                                  //Move all animate entites and display the room
            human.human_move(grid); 
            dragon.dragon_move(grid);
            monster.monster_move(grid);
            string input;
            cout << "The entities are moved successfully.\nDo you want to display the current room (Yes or No) : ";  //ask user wanna see current room or not
            cin  >>  input;
            if (input == "Yes" || input == "yes"){
                room.display_room(grid); 
            }                    
            if (!room.wanna_continue()){                              //Ask the user whether want to continue the game or not?
                break;
            }   
        }

        // --------------------------------------------------------------------------------

        else if (instruction == 3) {                                           //Display the properties according to user input (row and column)
            int row, column;
            while (true){
                cout << "Row coordinate(number on left 0 to 9) : ";
                cin >> row; 
                if (row < 0 || row > 9) {                                      //valid row or not
                    cout << "Invaid input!\nPlease choose from 0 to 9!!\n";
                    continue;
                }

                cout << "Column coordinate(number at the top 0 to 9) : ";
                cin >> column;
                cout << endl;
                if (column < 0 || column > 9) {                               //valid column or not
                    cout << "Invaid input!\nPlease choose from 0 to 9!!\n";
                    continue;
                }

                if (grid[row][column] == 'S'){                                //Display stone's properties
                    stone.display_stone_info();
                }
                else if (grid[row][column] == 'O'){                           //Display hole's properties  
                    hole.display_hole_info(row, column);
                }
                else if (grid[row][column] == '@'){                           //Display human's properties   
                    human.display_human_info(row, column);
                }
                else if (grid[row][column] == '#'){                           //Display dragon's properties  
                    dragon.display_dragon_info(row, column);
                }
                else if (grid[row][column] == '*'){                           //Display moster's properites  
                    monster.display_monster_info(row, column);
                }
                else {                                                        //Display no entity      
                    cout << "There is no entity in that coordinate!!\n";
                }
                break;                                                          
            }

            if (!room.wanna_continue()){                                      //Ask the user whether want to continue the game or not?
                break;
            }   

        }

        // --------------------------------------------------------------------------------

        else if (instruction == 4) {                                        //Reset the room
            for(int i = 0; i < 10; ++i){                                    //Reititialize the room as an empty room
                for(int j = 0; j < 10; ++j){
                    grid[i][j] = '.';
                }
            }   
            
            stone.place_stone(grid);                                        //Place "stone"
            hole.place_hole(grid);                                          //Place "hole"
            human.place_human(grid);                                        //Place "human"
            dragon.place_dragon(grid);                                      //Place "dragon"
            monster.place_monster(grid);                                    //Place "monster"
            string input;
            cout << "The room is reset successfully.\nDo you want to display the current room (Yes or No) : ";  //ask user wanna see current room or not
            cin  >>  input;
            if (input == "Yes" || input == "yes"){
                room.display_room(grid); 
            }

            if (!room.wanna_continue()){                                    //Ask the user whether want to continue the game or not?
                break;
            }
        }

        // --------------------------------------------------------------------------------

        else if (instruction == 5) {                                        //Exit the program
            cout << "Thank you for playing our game!\n";
            break;
        }

        // --------------------------------------------------------------------------------

        else {                                                              //Invalid input and ask again
            cout << "\nInvalid Option!!\nPlease input from 1 to 5!!\n" ;
        }
    }  
}

// ==================================================================================== //
// ==================================================================================== //