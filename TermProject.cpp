#include <iostream>
#include <vector>


class Entity
{
private:
    int health = 0;
    int armor_class = 0;

    // Ability Scores
    int strength = 0;
    int dexterity = 0;
    int constitution = 0;
    int intelligence = 0;
    int wisdom = 0;
    int charisma = 0;

    //Skills


    //Vulnerabilities, Resistances, and Immunities

    //Languages
    std::vector <bool> language;

    bool magic = true;

    bool equipment = true;
    // inventory


    /*
    Tiny 2½ by 2½ ft.
    Small 5 by 5 ft.
    Medium 5 by 5 ft.
    Large 10 by 10 ft.
    Huge 15 by 15 ft.
    Gargantuan 20 by 20 ft.
    */

    string size = "";
    string validSize[6] = ["Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"];
    double height = 0;
    double width = 0;

    string alignment = "";
    string validAligment[9] = ["Lawful good", "Neutral good", "Chaotic good", "Lawful neutral", "Neutral", "Chaotic neutral", "Lawful evil", "Neutral evil", "Chaotic evil"];

    // speed
    int burrow = 0
    int climb = 0
    int fly = 0
    int swim = 0;
public:

    void move()
    {

    }

    // between two entities
    bool communicate(Entity& entity)
    {
        for(int i = 0; i < entity.language.size(); i++)
        {
            if(entity.language[i] == language[i])
                return true;
        }
        return false;
    }


};

class Monster
{
    string type = "";
    string validType[14] = {"Aberration", "Beast", "Celestial", "Construct", "Dragon", "Elemental", "Fey", "Fiend", "Giant", "Humanoid", "Monstrosity", "Ooze", "Plant", "Undead"}

    bool legendary = true;
    double challenge = 0;
};

class PlayerChar
{
    age

    race

    class

};



using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}


