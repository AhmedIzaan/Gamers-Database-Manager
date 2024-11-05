#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Games_Played_class
{
public:
    string Game_ID;
    float Hours_Played;
    int Achievements_Unlocked;
    Games_Played_class *next;

    Games_Played_class(string gameID, float hours, int achievements)
    {
        Game_ID = gameID;
        Hours_Played = hours;
        Achievements_Unlocked = achievements;
        next = nullptr;
    }
};

class Player
{
public:
    string Player_ID;
    string Name;
    string Phone_Number;
    string Email;
    string Password;
    Games_Played_class *games_played;
    Player *left;
    Player *right;

    Player(string playerID, string name, string phone, string email, string password)
    {
        Player_ID = playerID;
        Name = name;
        Phone_Number = phone;
        Email = email;
        Password = password;
        games_played = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void addGame(string gameID, float hours, int achievements)
    {
        Games_Played_class *newGame = new Games_Played_class(gameID, hours, achievements);
        newGame->next = games_played;
        games_played = newGame;
    }
    void printPlayerInfo()
    {
        cout << "Player ID: " << Player_ID << endl;
        cout << "Name: " << Name << endl;
        cout << "Phone Number: " << Phone_Number << endl;
        cout << "Email: " << Email << endl;
        cout << "Password: " << Password << endl;

        Games_Played_class *currentGame = games_played;
        while (currentGame != nullptr)
        {
            cout << "  Game ID: " << currentGame->Game_ID << endl;
            cout << "  Hours Played: " << currentGame->Hours_Played << endl;
            cout << "  Achievements Unlocked: " << currentGame->Achievements_Unlocked << endl;
            currentGame = currentGame->next;
        }
    }
};
class Game
{
public:
    string Game_ID;
    string Name;
    string Developer;
    string Publisher;
    float File_Size_in_GBs;
    int Downloads;
    Game *left;
    Game *right;

    Game(string gameID, string name, string developer, string publisher, float fileSize, int downloads)
    {
        Game_ID = gameID;
        Name = name;
        Developer = developer;
        Publisher = publisher;
        File_Size_in_GBs = fileSize;
        Downloads = downloads;
        left=nullptr;
        right=nullptr;
    }
};
class playerBST
{

public:
    Player *root;

    playerBST() : root(nullptr) {}

    Player *findPlayer(Player *node, const string &playerID)
    {
        if (node == nullptr || node->Player_ID == playerID)
        {
            return node;
        }
        if (playerID < node->Player_ID)
        {
            return findPlayer(node->left, playerID);
        }
        return findPlayer(node->right, playerID);
    }

    void insertPlayer(Player *newNode)
    {
        if (findPlayer(root, newNode->Player_ID) != nullptr)
        {
            cout << "Error: Player with ID " << newNode->Player_ID << " already exists." << endl;
            delete newNode;
            return;
        }
        insert(root, newNode);
    }

    void insert(Player *&node, Player *newNode)
    {
        if (node == nullptr)
        {
            node = newNode;
        }
        else if (newNode->Player_ID < node->Player_ID)
        {
            insert(node->left, newNode);
        }
        else
        {
            insert(node->right, newNode);
        }
    }
};
class GameBST
{
public:
    Game *root;

    GameBST() : root(nullptr) {}

    Game *findGame(Game *node, const string &gameID)
    {
        if (node == nullptr || node->Game_ID == gameID)
        {
            return node;
        }
        if (gameID < node->Game_ID)
        {
            return findGame(node->left, gameID);
        }
        return findGame(node->right, gameID);
    }

    void insertGame(Game *newNode)
    {
        if (findGame(root, newNode->Game_ID) != nullptr)
        {
            cout << "Error: Game with ID " << newNode->Game_ID << " already exists." << endl;
            delete newNode;
            return;
        }
        insert(root, newNode);
    }

    void insert(Game *&node, Game *newNode)
    {
        if (node == nullptr)
        {
            node = newNode;
        }
        else if (newNode->Game_ID < node->Game_ID)
        {
            insert(node->left, newNode);
        }
        else
        {
            insert(node->right, newNode);
        }
    }
};

void readingDataFromPlayerData(const string &fileName, playerBST &playerTree)
{
    int rollNumber = 230015;
    int lastTwoDigits = rollNumber % 100;
    int seed = lastTwoDigits * 10 + 100;

    srand(time(0));

    ifstream playerFile(fileName);
    if (!playerFile.is_open())
    {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(playerFile, line))
    {
        int randomNumber = rand() % 1001;
        if (randomNumber < seed)
        {
            continue;
        }

        stringstream ss(line);
        string playerID, name, phone, email, password;

        getline(ss, playerID, ',');
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        Player *newPlayer = new Player(playerID, name, phone, email, password);

        
        string gameID, hoursStr, achievementsStr;
        while (getline(ss, gameID, ',') && getline(ss, hoursStr, ',') && getline(ss, achievementsStr, ','))
        {
            float hoursPlayed = stof(hoursStr);
            int achievementsUnlocked = stoi(achievementsStr);
            newPlayer->addGame(gameID, hoursPlayed, achievementsUnlocked);
        }

        playerTree.insertPlayer(newPlayer);
    }

    playerFile.close();
}

void readingDataFromGameData(const string &fileName, GameBST &gameTree)
{
    ifstream gameFile(fileName);
    if (!gameFile.is_open())
    {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(gameFile, line))
    {
        stringstream ss(line);
        string gameID, name, developer, publisher, fileSizeStr, downloadsStr;

        getline(ss, gameID, ',');
        getline(ss, name, ',');
        getline(ss, developer, ',');
        getline(ss, publisher, ',');
        getline(ss, fileSizeStr, ',');
        getline(ss, downloadsStr, ',');

        float fileSize = stof(fileSizeStr);
        int downloads = stoi(downloadsStr);

        Game *newGame = new Game(gameID, name, developer, publisher, fileSize, downloads);
        gameTree.insertGame(newGame);
    }

    gameFile.close();
}

int main()
{
    playerBST playerTree;
    GameBST gameTree;

    
    readingDataFromPlayerData("Players.txt", playerTree);
    readingDataFromGameData("Games.txt", gameTree);

    return 0;
}