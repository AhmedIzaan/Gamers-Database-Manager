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
        cout << "Games played:\n";
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
        left = nullptr;
        right = nullptr;
    }
    void printGameInfo()
    {
        cout << "Game ID: " << Game_ID << endl;
        cout << "Name: " << Name << endl;
        cout << "Developer: " << Developer << endl;
        cout << "Publisher: " << Publisher << endl;
        cout << "File Size: " << File_Size_in_GBs << " GBs" << endl;
        cout << "Downloads: " << Downloads << endl;
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

    Player *searchPlayer(const string &playerID)
    {
        return findPlayer(root, playerID);
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
    void deletePlayer(const string &playerID)
    {
        root = deletePlayerNode(root, playerID);
    }
    Player *deletePlayerNode(Player *node, const string &playerID)
    {
        if (node == nullptr)
            return nullptr;

        if (playerID < node->Player_ID)
        {
            node->left = deletePlayerNode(node->left, playerID);
        }
        else if (playerID > node->Player_ID)
        {
            node->right = deletePlayerNode(node->right, playerID);
        }
        else
        {

            if (node->left == nullptr)
            {
                Player *temp = node->right;
                deletePlayerGames(node);
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Player *temp = node->left;
                deletePlayerGames(node);
                delete node;
                return temp;
            }

            Player *temp = findMinPlayer(node->right);
            node->Player_ID = temp->Player_ID;
            node->Name = temp->Name;
            node->Phone_Number = temp->Phone_Number;
            node->Email = temp->Email;
            node->Password = temp->Password;

            node->games_played = temp->games_played;
            temp->games_played = nullptr;
            node->right = deletePlayerNode(node->right, temp->Player_ID);
        }
        return node;
    }
    Player *findMinPlayer(Player *node)
    {
        Player *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    void deletePlayerGames(Player *player)
    {
        Games_Played_class *currentGame = player->games_played;
        while (currentGame)
        {
            Games_Played_class *nextGame = currentGame->next;
            delete currentGame;
            currentGame = nextGame;
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

    Game *searchGame(const string &gameID)
    {
        return findGame(root, gameID);
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
    void deleteGame(const string &gameID)
    {
        root = deleteGameNode(root, gameID);
    }
    Game *deleteGameNode(Game *node, const string &gameID)
    {
        if (node == nullptr)
            return nullptr;

        if (gameID < node->Game_ID)
        {
            node->left = deleteGameNode(node->left, gameID);
        }
        else if (gameID > node->Game_ID)
        {
            node->right = deleteGameNode(node->right, gameID);
        }
        else
        {
            if (node->left == nullptr)
            {
                Game *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Game *temp = node->left;
                delete node;
                return temp;
            }

            Game *temp = findMinGame(node->right);
            node->Game_ID = temp->Game_ID;
            node->Name = temp->Name;
            node->Developer = temp->Developer;
            node->Publisher = temp->Publisher;
            node->File_Size_in_GBs = temp->File_Size_in_GBs;
            node->Downloads = temp->Downloads;

            node->right = deleteGameNode(node->right, temp->Game_ID);
        }
        return node;
    }

    Game *findMinGame(Game *node)
    {
        Game *current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    void printGames(Game *node)
    {
        if (node != nullptr)
        {
            printGames(node->left);
            cout << "Game ID: " << node->Game_ID << ", Name: " << node->Name << ", Developer: " << node->Developer << ", Publisher: " << node->Publisher << ", File Size: " << node->File_Size_in_GBs << " GBs, Downloads: " << node->Downloads << endl;
            printGames(node->right);
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
void searchAndPrint(playerBST &playerTree, GameBST &gameTree)
{
    string searchPlayerID;
    cout << "Enter Player ID to search: ";
    cin >> searchPlayerID;
    Player *foundPlayer = playerTree.searchPlayer(searchPlayerID);
    if (foundPlayer != nullptr)
    {
        cout << "Player found:\n";
        foundPlayer->printPlayerInfo();
    }
    else
    {
        cout << "Player with ID " << searchPlayerID << " not found.\n";
    }

    string searchGameID;
    cout << "Enter Game ID to search: ";
    cin >> searchGameID;
    Game *foundGame = gameTree.searchGame(searchGameID);
    if (foundGame != nullptr)
    {
        cout << "Game found:\n";
        foundGame->printGameInfo();
    }
    else
    {
        cout << "Game with ID " << searchGameID << " not found.\n";
    }
}
void deletePlayerAndGame(playerBST &playerTree, GameBST &gameTree)
{
    string deletePlayerID;
    cout << "Enter Player ID to delete: ";
    cin >> deletePlayerID;
    playerTree.deletePlayer(deletePlayerID);
    cout << "Player with ID " << deletePlayerID << " deleted.\n";

    string deleteGameID;
    cout << "Enter Game ID to delete: ";
    cin >> deleteGameID;
    gameTree.deleteGame(deleteGameID);
    cout << "Game with ID " << deleteGameID << " deleted.\n";
}
int main()
{
    playerBST playerTree;
    GameBST gameTree;

    readingDataFromPlayerData("Players.txt", playerTree);
    readingDataFromGameData("Games.txt", gameTree);

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "0. Exit\n";
        cout << "1. Search Player and Game\n";
        cout << "2.Delete Player and Game\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Exiting...\n";
            break;
        case 1:
            searchAndPrint(playerTree, gameTree);
            break;
        case 2:
            deletePlayerAndGame(playerTree, gameTree);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}