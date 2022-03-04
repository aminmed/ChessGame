#include <iostream>
#include <chrono>
#include "Game.h"
#include "PGNio.h"

using namespace std; 
Game* CreateGame();
int gameMenu(); 
int main() {
    Game* game =NULL; 
    int option = 0;
    string filePath = ""; 
    PGNio* pgn = NULL;   
    Clock * cl = NULL; 
    string n = ""; 
    Player* p1 = NULL; 
    Player* p2 = NULL; 
    while(option != 7) {
        option = gameMenu(); 
        switch (option)
        {
        case 1:
            game = CreateGame();
            game->playGame();
            break;
        case 2:
           // game = CreateGame();
           if(game != NULL) game->playGame();
           else cout<<"No current game !"<<std::endl; 
            break;
        case 3:
            cout<<"Please type configuration file `.txt` :";
            getline(cin >> ws,filePath);
            cout<<"|..... Now you need to create a game that will start with given configuration.....|"<<endl;
            cout<<"Type any thing to continue ! "; 
            char c;  
            cin>>c; 
            game = CreateGame();  
            
            game->getBoard()->readConfiguration(filePath); 
            game->playGame(); 
            break; 
        case 4:
            cout<<"Current game history will be lost if you don't save It"<<endl; 
            cout<<"Please type PGN file `.pgn`(Q to exit) :"; 
            getline(cin >> ws,filePath); 
            if(filePath != "Q"){
                pgn = new PGNio(filePath,false);
                Player* p1 = new Player(false,pgn->getWhitePlayerName()); 
                Player* p2 = new Player(true,pgn->getBlackPlayerName()); 
                Clock *c = new Clock("BLITZ",chrono::seconds(10*60),chrono::seconds(10*60),chrono::seconds(2)); 
                game = new Game(p2,p1,filePath,c);
                game->startGame(filePath,0); 
                game->playGame(); 
            }   

            break;
        case 5:
            cout<<"Current game history will be lost if you don't save It"<<endl; 
            cout<<"Please type PGN file `.pgn`(Q to exit) :"; 
            getline(cin >> ws,filePath); 
            if(filePath != "Q"){
                pgn = new PGNio(filePath,true);
                Board *b =pgn->readMovesFromPGN(0); 
            }
        break; 
        case 6: 
            p1 = new Player(false,"player");
            p2 = new Player(true, "MinMax");
            cl = new Clock("BLITZ",chrono::seconds(10*60),chrono::seconds(10*60),chrono::seconds(2)); 
            game = new Game(p2,p1,"",cl); 
            game->playAgainstAgent(); 
        break; 
        default:
            break;
        }
    }
    return 0; 

}


Game* CreateGame(){
    int choice = 0;
    bool notValid = true;
    Clock *c = NULL; 
    chrono::seconds d; 
    chrono::seconds s; 
    system("clear"); 
    cout<<"###################"<<endl;
    cout<<"## New Game Menu   "<<endl;
    cout<<"###################"<<endl;
    cout<<" "<<endl;
    while(notValid) {
        notValid = false; 
        cout<<"#Choose the type of clock :"<<endl
        <<"|- - - - :1. FAST - BLITZ."<<endl 
        <<"|- - - - :2. FAST - RAPID."<<endl
        <<"|- - - - :3. FAST - BULLET."<<endl 
        <<"enter choosen option's number: "; 
        cin>>choice;
        if(choice<=0 ||choice>4) notValid = true; 
        if(notValid) std::cout<<"Not valid choice, please enter correct number  !"<<std::endl; 
        cout<<" "<<endl;
    } 
    switch (choice)
    {
    case 1: 
        cout<<"You have selected FAST - BLITZ, please choose a per-player time | incrementation:"<<endl
        <<"|- - - - :1. 5|5 ."<<endl 
        <<"|- - - - :2. 5|0 ."<<endl
        <<"|- - - - :3. 3|2 (default)."<<endl 
        <<"enter choosen option's number: "; 
        cin>>choice;
        if(choice >2 || choice <1) {
            d = chrono::seconds(3*60); 
            s = chrono::seconds(2);
        }
        if(choice == 1) {
            d = chrono::seconds(5*60); 
            s = chrono::seconds(5);            
        }
        if(choice == 2) {
            d = chrono::seconds(5*60); 
            s = chrono::seconds(0);            
        }
        c = new Clock("BLITZ", d,d,s); 
        break;        
    case 2: 
        cout<<"You have selected FAST - RAPID, please choose a per-player time | incrementation:"<<endl
        <<"|- - - - :1. 10|2 ."<<endl 
        <<"|- - - - :2. 30|0 ."<<endl
        <<"|- - - - :3. 15|10 (default)."<<endl 
        <<"enter choosen option's number: "; 
        cin>>choice;
        if(choice >2 || choice <1) {
            d = chrono::seconds(15*60); 
            s = chrono::seconds(10);
        }
        if(choice == 1) {
            d = chrono::seconds(10*60); 
            s = chrono::seconds(2);            
        }
        if(choice == 2) {
            d = chrono::seconds(30*60); 
            s = chrono::seconds(0);            
        }
        c = new Clock("RAPID", d,d,s); 
        break;
    case 3: 
        cout<<"You have selected FAST - BULLET, please choose a per-player time | incrementation:"<<endl
        <<"|- - - - :1. 2|1 ."<<endl 
        <<"|- - - - :2. 1|0 ."<<endl
        <<"|- - - - :3. 3|1 (default)."<<endl 
        <<"enter choosen option's number: "; 
        cin>>choice;
        if(choice >2 || choice <1) {
            d = chrono::seconds(3*60); 
            s = chrono::seconds(1);
        }
        if(choice == 1) {
            d = chrono::seconds(2*60); 
            s = chrono::seconds(1);            
        }
        if(choice == 2) {
            d = chrono::seconds(1*60); 
            s = chrono::seconds(0);            
        }
        c = new Clock("BULLET", d,d,s); 
        break;
    default:
        return NULL; 
        break;
    } 
    std::string name; 
    Player *whitePlayer=NULL; Player *blackPlayer=NULL; 
    bool unicode = true;  
    cout<<endl<<"Game Clock: "<<c->getClockType() <<"  "<< c->getRemainingSecondsForBlack().count() /60 <<"|"<<c->getClockInc().count()<<endl;
    cout<<"#Player's Name :"<<endl; 
    cout<<"Please Enter White player name : ";
    cin>>name; 
    cout<<endl; 
    whitePlayer = new Player(false,name);
    name =""; 
    cout<<"Please Enter Black player name : ";
    cin>>name;
    blackPlayer = new Player(true,name); 
    name = ""; 
    cout<<"#Chess board's pieces symboles :"<<endl;
    cout<<"Do you want unicode pieces (Y/n)? :";
    cin>>name; 
    if(name == "n") unicode = false; 
    cout<<"#File to store permenantly game history (PGN) :"<<endl;
    cout<<"File path :";
    cin>>name;
    Game * game = new Game(blackPlayer,whitePlayer, name,c); 
    game->getBoard()->setUnicode(unicode); 
    return game; 
}
int gameMenu(){
    int choice = 0;
    bool notValid = false; 
    while(choice==0) {
        system("clear"); 
        if(notValid) cout<<"Please choose a valid option !"<<endl; 
        notValid = false; 
        cout<<"1. Start a new game."<<endl
            <<"2. Resume current game."<<endl
            <<"3. Load a game from given configuration."<<endl
            <<"4. Load a game from given PGN file."<<endl
            <<"5. Play a game from given PGN file."<<endl
            <<"6. Play against MinMaxAgent."<<endl
            <<"7. Exit."<<endl
            <<"Enter chosen option's number : ";
        cin>>choice;
        if(choice>8 || choice <=0) {choice = 0; notValid = true; }
    }
    return choice; 
}