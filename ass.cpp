#include <iostream>
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
    }
};
class BST
{
public:
    Player *root;

    BST() : root(nullptr) {}

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

    void insertPlayer(Player *newNode)
    {
        insert(root, newNode);
    }
};
