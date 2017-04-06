// Braden Blackwell

// The logic for my code implements the rule set found here:
// http://media.wizards.com/2016/downloads/DND/PlayerBasicRulesV03.pdf
// https://media.wizards.com/2014/downloads/dnd/DMBasicRulesv.0.3.pdf

#include <iostream>
#include <vector>

struct dice
{
private:

public:
    // add more dice
    int rolld20();
};

struct sizeEntity
{
    /*
    Tiny <=2� by 2� ft.
    Small <=5 by 5 ft.
    Medium <=5 by 5 ft.
    Large <=10 by 10 ft.
    Huge <=15 by 15 ft.
    Gargantuan >=20 by 20 ft.
    */
public:
    enum sizestr {Tiny, Small, Medium, Large, Huge, Gargantuan};

    // in feet
    std::string sizeName;
    double height = 0;
    double width = 0;

    sizeEntity(std::string s)
    {
        sizeName = s;
        makeSizeStr(s, height, width);
    }
    sizeEntity(double h, double w)
    {
       height = h;
       width = w;
       makeSizeDem(sizeName, h, w);
    }

private:
    // only size given in a string
    // assume that height and width are equal
    void makeSizeStr(std::string s, double& h, double& w)
    {
        if(s == getString(Tiny))
            h = w = 2.5;
        else if(s == getString(Small))
            h = w = 5;
        else if(s == getString(Medium))
            h = w = 5;
        else if(s == getString(Large))
            h = w = 10;
        else if(s == getString(Huge))
            h = w = 15;
        else if(s == getString(Gargantuan))
            h = w = 20;

        // invalid string
        else
            throw "invalid string";
    }

    // only size given in a two doubles
    // decide the string name
    // might need parameter for small and medium
    void makeSizeDem(std::string& s, double h, double w)
    {
        // negative area
        if (h < 0 || w  < 0)
            throw "negative area";

        else if(h <= 2.5 && w <= 2.5)
            s = getString(Tiny);
        else if(h <= 5 && w <= 5)
            s = getString(Small);
        // same as small but depends on unit
        else if(h <= 5 && w <= 5)
            s = getString(Medium);
        else if(h <= 10 && w <= 10)
            s = getString(Large);
        else if(h <= 15 && w <= 15)
            s = getString(Huge);
        else
            s = getString(Gargantuan);
    }

    static constexpr char* enumStrings[] = { "Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"};
    const char* getString(sizestr id)
    {
      return enumStrings[id];
    }
};

class Entity
{
private:
    bool sex = true;

    std::string traits = "";
    std::string ideals = "";
    std::string bonds = "";
    std::string flaws = "";

    int mod(int ability)
    {
        return (ability / 2) - 5;
    }

    //change to a switch for now !!
    int proficiency(int level)
    {
        /*
        1-4 == +2
        5-8 == +3
        9-12 == +4
        13- 16 == +5
        17-20 == +6
        */

        if(level >= 1 && level <= 4)
            return 2;
        else if(level >= 5 && level <= 8)
            return 3;
        else if(level >= 9 && level <= 12)
            return 4;
        else if(level >= 13 && level <= 16)
            return 5;
        else if(level >= 17 && level <= 20)
            return 6;
    }

    // melee == roll + mod(strength) + proficiency(level) + class features + magic BS
    // ranged == roll + mod(dexterity) + proficiency(level) + class features + magic BS + ammo
    // spells cleric == roll + mod(wisdom) + proficiency(level) + class features + magic BS
    // spells wizard == roll + mod(intelligence) + proficiency(level) + class features + magic BS
    // this currently excludes finesse weapons
    // only get proficiency bonus if proficient in the weapon being used

    dice dice;

    int calcAttack(int roll, int ability)
    {
        return roll + mod(ability) + proficiency(level);
    }

    void toHit(bool& hit, bool& critHit, bool& critMiss, int ability, Entity& entity)
    {
        int attack = 0;
        int defense = 0;
        int roll = dice.rolld20();

        attack = calcAttack(roll, ability); //magic BS
        defense = entity.armorClass;

        if(roll == 20)
            critHit = true;
        else if(roll == 1)
            critMiss == true;

        if(attack > defense)
            hit = true;
        else
            hit = false;
    }

    void pickHit(bool& hit, bool& critHit, bool& critMiss, std::string attackType, std::string castAbility, Entity& entity)
    {
        if(attackType == "melee")
            toHit(hit, critHit, critMiss, strength, entity);
        else if(attackType == "ranged")
            toHit(hit, critHit, critMiss, dexterity, entity);
        else if(attackType == "spell")
        {
            if(castAbility == "intelligence")
                toHit(hit, critHit, critMiss, intelligence, entity);
            else if(castAbility == "wisdom")
                toHit(hit, critHit, critMiss, wisdom, entity);
        }
    }

    // melee == weaponRoll +  mod(strength) + class features + magicBS
    // ranged == weaponRoll + mod(dexterity) + class features + magicBS + ammo
    // spells cleric == spellRoll + class features + magicBS
    // spells wizard == spellRoll + class features + magicBS
    // this currently excludes sneak attack damage


public:
    int health = 0;
    int armorClass = 0;
    int level = 0;
    int experience = 0;

    double age = 0;

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





    // All possible alignments
    enum Aligment {LG, NG, CG, LN, TN,CN, LE, NE, CE};
    static constexpr char* enumStrings[9] = {"Lawful good", "Neutral good", "Chaotic good", "Lawful neutral", "True Neutral", "Chaotic neutral", "Lawful evil", "Neutral evil", "Chaotic evil"};
    const char* getAligment(Aligment id)
    {
      return enumStrings[id];
    }


    // speed
    int walk = 0;
    int burrow = 0;
    int climb = 0;
    int fly = 0;
    int swim = 0;


    //default constructor
    Entity()
    {

    }

    //move maybe??

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

    //between two entities
    std::string attack(Entity& entity)
    {

    }
};

class Monster : Entity
{
private:
    // maybe make class??
    std::string validType[14] = {"Aberration", "Beast", "Celestial", "Construct", "Dragon", "Elemental", "Fey", "Fiend", "Giant", "Humanoid", "Monstrosity", "Ooze", "Plant", "Undead"};
public:
    std::string type = "";
    bool legendary = true;
    double challenge = 0;
};

class PlayerChar : Entity
{
private:
    std::string validRace[4] = {"Dwarf", "Elf", "Halfling", "Human"}; // make class
    std::string validPlayerClass[4] = {"Cleric", "Fighter", "Rogue", "Wizard"};  // make class
    std::string validBackgrounds[6] = {"Acolyte", "Criminal", "Folk Hero", "Noble", "Sage", "Soldier"};  // make enum
public:
    std::string race = "";
    std::string playerClass = "";
    std::string backgrounds = "";
};

using namespace std;

int main()
{
    return 0;
}
