#include <iostream>
#include <fstream>
#include <sstream>
#include "queue.cpp"

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
    void savePlayerData(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << filename << " for writing." << endl;
            return;
        }
        savePlayerDataPreorder(root, file);
        file.close();
    }
    void savePlayerDataPreorder(Player *node, ofstream &file)
    {
        if (node == nullptr)
            return;

        file << node->Player_ID << ',' << node->Name << ',' << node->Phone_Number << ','
             << node->Email << ',' << node->Password;

        Games_Played_class *currentGame = node->games_played;
        while (currentGame)
        {
            file << ',' << currentGame->Game_ID << ',' << currentGame->Hours_Played << ','
                 << currentGame->Achievements_Unlocked;
            currentGame = currentGame->next;
        }
        file << '\n';

        savePlayerDataPreorder(node->left, file);
        savePlayerDataPreorder(node->right, file);
    }
    int getQueueSize(Queue<Player *> &q)
    {
        int count = 0;
        Queue<Player *> tempQueue;

        while (!q.isEmpty())
        {
            Player *node = q.dequeue();
            tempQueue.enqueue(node);
            count++;
        }

        while (!tempQueue.isEmpty())
        {
            q.enqueue(tempQueue.dequeue());
        }

        return count;
    }
    void showLayers(int N)
    {
        if (root == nullptr)
        {
            cout << "The tree is empty." << endl;
            return;
        }

        Queue<Player *> q;
        q.enqueue(root);
        int currentLayer = 1;

        while (!q.isEmpty() && currentLayer <= N)
        {
            int layerSize = getQueueSize(q);

            cout << "Layer " << currentLayer << ": ";
            for (int i = 0; i < layerSize; ++i)
            {
                Player *node = q.dequeue();

                cout << node->Player_ID << " (" << node->Name << ") ";

                if (node->left != nullptr)
                    q.enqueue(node->left);
                if (node->right != nullptr)
                    q.enqueue(node->right);
            }
            cout << endl;

            currentLayer++;
        }

        if (currentLayer <= N)
        {
            cout << "Layer Limit was Reached, can't go further" << endl;
        }
    }
    int getPlayerLayer(const string &playerID)
    {
        if (root == nullptr)
        {
            cout << "The tree is empty." << endl;
            return -1;
        }

        Queue<Player *> q;
        q.enqueue(root);
        int currentLayer = 1;

        while (!q.isEmpty())
        {
            int layerSize = getQueueSize(q);

            for (int i = 0; i < layerSize; ++i)
            {
                Player *node = q.dequeue();
                if (node->Player_ID == playerID)
                {
                    return currentLayer;
                }

                if (node->left != nullptr)
                    q.enqueue(node->left);
                if (node->right != nullptr)
                    q.enqueue(node->right);
            }
            currentLayer++;
        }

        cout << "Player with ID " << playerID << " not found in the tree." << endl;
        return -1;
    }
    bool showPlayerPath(Player *node, const string &playerID)
    {
        if (node == nullptr)
            return false;

        cout << node->Player_ID << " ";

        if (node->Player_ID == playerID)
        {
            cout << endl;
            return true;
        }

        if (playerID < node->Player_ID)
        {
            return showPlayerPath(node->left, playerID);
        }
        else
        {
            return showPlayerPath(node->right, playerID);
        }
    }

    void printPlayerPath(const string &playerID)
    {
        cout << "Preorder Traversal Path to find Player ID " << playerID << ": ";
        if (!showPlayerPath(root, playerID))
        {
            cout << "\nPlayer with ID " << playerID << " not found." << endl;
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
    void saveGameData(const string &filename)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << filename << " for writing." << endl;
            return;
        }
        saveGameDataPreorder(root, file);
        file.close();
    }
    void saveGameDataPreorder(Game *node, ofstream &file)
    {
        if (node == nullptr)
            return;

        file << node->Game_ID << ',' << node->Name << ',' << node->Developer << ','
             << node->Publisher << ',' << node->File_Size_in_GBs << ',' << node->Downloads << '\n';

        saveGameDataPreorder(node->left, file);
        saveGameDataPreorder(node->right, file);
    }
    int getQueueSize(Queue<Game *> &q)
    {
        int count = 0;
        Queue<Game *> tempQueue;

        while (!q.isEmpty())
        {
            Game *node = q.dequeue();
            tempQueue.enqueue(node);
            count++;
        }

        while (!tempQueue.isEmpty())
        {
            q.enqueue(tempQueue.dequeue());
        }

        return count;
    }
    void showLayers(int N)
    {
        if (root == nullptr)
        {
            cout << "The tree is empty." << endl;
            return;
        }

        Queue<Game *> q;
        q.enqueue(root);
        int currentLayer = 1;

        while (!q.isEmpty() && currentLayer <= N)
        {
            int layerSize = getQueueSize(q);

            cout << "Layer " << currentLayer << ": ";
            for (int i = 0; i < layerSize; ++i)
            {
                Game *node = q.dequeue();

                cout << node->Game_ID << " (" << node->Name << ") ";

                if (node->left != nullptr)
                {
                    q.enqueue(node->left);
                }
                if (node->right != nullptr)
                {
                    q.enqueue(node->right);
                }
            }
            cout << endl;

            currentLayer++;
        }

        if (currentLayer <= N)
        {
            cout << "Layer Limit was Reached, can't go further" << endl;
        }
    }
    int getGameLayer(const string &gameID)
    {
        if (root == nullptr)
        {
            cout << "The tree is empty." << endl;
            return -1;
        }

        Queue<Game *> q;
        q.enqueue(root);
        int currentLayer = 1;

        while (!q.isEmpty())
        {
            int layerSize = getQueueSize(q);

            for (int i = 0; i < layerSize; ++i)
            {
                Game *node = q.dequeue();
                if (node->Game_ID == gameID)
                {
                    return currentLayer;
                }

                if (node->left != nullptr)
                    q.enqueue(node->left);
                if (node->right != nullptr)
                    q.enqueue(node->right);
            }
            currentLayer++;
        }

        cout << "Game with ID " << gameID << " not found in the tree." << endl;
        return -1;
    }
    bool showGamePath(Game *node, const string &gameID)
    {
        if (node == nullptr)
            return false;

        cout << node->Game_ID << " ";

        if (node->Game_ID == gameID)
        {
            cout << endl;
            return true;
        }

        if (gameID < node->Game_ID)
        {
            return showGamePath(node->left, gameID);
        }
        else
        {
            return showGamePath(node->right, gameID);
        }
    }

    void printGamePath(const string &gameID)
    {
        cout << "Preorder Traversal Path to find Game ID " << gameID << ": ";
        if (!showGamePath(root, gameID))
        {
            cout << "\nGame with ID " << gameID << " not found." << endl;
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
void editPlayerEntry(playerBST &playerTree, const string &oldPlayerID)
{

    Player *player = playerTree.searchPlayer(oldPlayerID);
    if (player == nullptr)
    {
        cout << "Player with ID " << oldPlayerID << " not found.\n";
        return;
    }

    cout << "Current Player Info:\n";
    player->printPlayerInfo();

    string newPlayerID, name, phone, email, password;
    cout << "\nEnter new Player ID (or press Enter to keep current ID): ";
    cin.ignore();
    getline(cin, newPlayerID);
    cout << "Enter new Name: ";
    getline(cin, name);
    cout << "Enter new Phone Number: ";
    getline(cin, phone);
    cout << "Enter new Email: ";
    getline(cin, email);
    cout << "Enter new Password: ";
    getline(cin, password);

    if (!newPlayerID.empty() && newPlayerID != oldPlayerID)
    {

        playerTree.deletePlayer(oldPlayerID);

        Player *newPlayer = new Player(newPlayerID, name, phone, email, password);
        newPlayer->games_played = player->games_played;

        playerTree.insertPlayer(newPlayer);
        cout << "Player ID changed. Repositioned in the tree.\n";
    }
    else
    {

        player->Name = name;
        player->Phone_Number = phone;
        player->Email = email;
        player->Password = password;
        cout << "Player details updated.\n";
    }
}
void editGameEntry(GameBST &gameTree, const string &oldGameID)
{

    Game *game = gameTree.searchGame(oldGameID);
    if (game == nullptr)
    {
        cout << "Game with ID " << oldGameID << " not found.\n";
        return;
    }

    cout << "Current Game Info:\n";
    game->printGameInfo();

    string newGameID, name, developer, publisher;
    float fileSize;
    int downloads;
    cout << "\nEnter new Game ID (or press Enter to keep current ID): ";
    cin.ignore();
    getline(cin, newGameID);
    cout << "Enter new Name: ";
    getline(cin, name);
    cout << "Enter new Developer: ";
    getline(cin, developer);
    cout << "Enter new Publisher: ";
    getline(cin, publisher);
    cout << "Enter new File Size in GBs: ";
    cin >> fileSize;
    cout << "Enter new Downloads: ";
    cin >> downloads;

    if (!newGameID.empty() && newGameID != oldGameID)
    {

        gameTree.deleteGame(oldGameID);

        Game *newGame = new Game(newGameID, name, developer, publisher, fileSize, downloads);

        gameTree.insertGame(newGame);
        cout << "Game ID changed. Repositioned in the tree.\n";
    }
    else
    {

        game->Name = name;
        game->Developer = developer;
        game->Publisher = publisher;
        game->File_Size_in_GBs = fileSize;
        game->Downloads = downloads;
        cout << "Game details updated.\n";
    }
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
        cout << "2. Delete Player and Game\n";
        cout << "3. save Player and Game data\n";
        cout << "4. Show player layers\n";
        cout << "5. Show game layers\n";
        cout << "6. Get player layer and Game layer according to their ids\n";
        cout << "7. Show search path of players and games\n";
        cout << "8. Edit Player Entry\n";
        cout << "9. Edit Game Entry\n";
        cout << "Enter your choice: \n";
        cin >> choice;

        switch (choice)
        {
        case 0:
        {

            cout << "Exiting...\n";
            break;
        }
        case 1:
        {
            searchAndPrint(playerTree, gameTree);
            break;
        }

        case 2:
        {
            deletePlayerAndGame(playerTree, gameTree);
            break;
        }

        case 3:
        {
            playerTree.savePlayerData("PlayersBackup.csv");
            gameTree.saveGameData("GamesBackup.csv");
            cout << "Data saved to PlayersBackup.csv and GamesBackup.csv successfully." << endl;
        }

        case 4:
        {
            int layers;
            cout << "Enter the number of layers to display for the player tree: ";
            cin >> layers;
            playerTree.showLayers(layers);
            break;
        }

        case 5:
        {
            int layers;
            cout << "Enter the number of layers to display for the game tree: ";
            cin >> layers;
            gameTree.showLayers(layers);
            break;
        }
        case 6:
        {
            string playerID;
            cout << "Enter Player ID to find layer number: ";
            cin >> playerID;
            int playerLayer = playerTree.getPlayerLayer(playerID);
            if (playerLayer != -1)
            {
                cout << "Player with ID " << playerID << " is in layer " << playerLayer << "." << endl;
            }

            string gameID;
            cout << "Enter Game ID to find layer number: ";
            cin >> gameID;
            int gameLayer = gameTree.getGameLayer(gameID);
            if (gameLayer != -1)
            {
                cout << "Game with ID " << gameID << " is in layer " << gameLayer << "." << endl;
            }
            break;
        }
        case 7:
        {
            string playerID;
            cout << "Enter Player ID to show search path: ";
            cin >> playerID;
            playerTree.printPlayerPath(playerID);

            string gameID;
            cout << "Enter Game ID to show search path: ";
            cin >> gameID;
            gameTree.printGamePath(gameID);
            break;
        }
        case 8:
        {
            string playerID;
            cout << "Enter Player ID to edit: ";
            cin >> playerID;
            editPlayerEntry(playerTree, playerID);
            break;
        }
        case 9:
        {
            string gameID;
            cout << "Enter Game ID to edit: ";
            cin >> gameID;
            editGameEntry(gameTree, gameID);
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}