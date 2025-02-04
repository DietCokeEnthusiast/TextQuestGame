#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to roll dice
int rollDie(int sides) {
    return rand() % sides + 1;
}

// Function to add a pause
void pause() {
    cout << "\nPress 1 to continue...";
    int choice;
    do {
        cin >> choice;
    } while (choice != 1);
}

// Base class for Hero
class Hero {
protected:
    string name;
    string race;
    string heroClass;
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    int strength;
    int arcana;
    int ac;
    string weapon;
    string armor;
    int weaponBonus;
    int gold;
    bool isBlocking;
    int healthPotions; // Track health potions

public:
    Hero(string name, string race) : name(name), race(race), health(10), maxHealth(10), mana(10), maxMana(10), strength(1), arcana(1), gold(100), weaponBonus(0), isBlocking(false), healthPotions(0) {
        weapon = "None";
        armor = "None";
        ac = 10;
    }

    string getName() { return name; }
    int getMaxHealth() { return maxHealth; }
    int getMaxMana() { return maxMana; }
    int getStrength() { return strength; }
    int getArcana() { return arcana; }
    int getHealth() { return health; }
    int getMana() { return mana; }
    int getGold() { return gold; }
    int getAC() { return ac; }
    int getWeaponBonus() { return weaponBonus; }
    string getWeapon() { return weapon; }
    string getArmor() { return armor; }
    int getHealthPotions() { return healthPotions; }

    void setMaxHealth(int newMaxHealth) { maxHealth = newMaxHealth; health = maxHealth; }
    void setMaxMana(int newMaxMana) { maxMana = newMaxMana; mana = maxMana; }
    void setStrength(int newStrength) { strength = newStrength; }
    void setArcana(int newArcana) { arcana = newArcana; }
    void setHealth(int h) { health = h; }
    void setMana(int m) { mana = m; }
    void addGold(int amount) { gold += amount; }
    void spendGold(int amount) { gold -= amount; }
    void setWeapon(string newWeapon, int bonus) { weapon = newWeapon; weaponBonus = bonus; }
    void setArmor(string newArmor, int armorBonus) { armor = newArmor; ac += armorBonus; }
    void addHealthPotion() { healthPotions += 1; }
    void useHealthPotion() {
        if (healthPotions > 0) {
            health = maxHealth;
            healthPotions -= 1;
            cout << "You used a health potion! Health is fully restored.\n";
        }
        else {
            cout << "You don't have any health potions!\n";
        }
    }

    void showInventory() {
        cout << "\n--- Inventory ---\n";
        cout << "Hero: " << name << endl;
        cout << "Class: " << heroClass << " | Race: " << race << endl;
        cout << "Health: " << health << " / " << maxHealth << " | Mana: " << mana << " / " << maxMana << endl;
        cout << "Strength: " << strength << " | Arcana: " << arcana << endl;
        cout << "AC: " << ac << endl;
        cout << "Weapon: " << weapon << " (+ " << weaponBonus << " to attack)\n";
        cout << "Armor: " << armor << endl;
        cout << "Gold: " << gold << "g\n";
        cout << "Health Potions: " << healthPotions << endl;
    }

    virtual void attack() = 0;

    virtual void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            cout << name << " has died!\n";
        }
    }

    void restoreHealth() {
        health = maxHealth;
        cout << "Health restored to " << maxHealth << "!\n";
    }

    void restoreMana() {
        mana = maxMana;
        cout << "Mana restored to " << maxMana << "!\n";
    }

    void block() {
        isBlocking = true;
        ac += 5;
        cout << name << " is blocking, AC increased to " << ac << "!\n";
    }

    void endBlock() {
        if (isBlocking) {
            ac -= 5;
            isBlocking = false;
            cout << name << "'s block ends, AC returns to " << ac << ".\n";
        }
    }
};

// Derived class for Warrior
class Warrior : public Hero {
public:
    Warrior(string name, string race) : Hero(name, race) {
        heroClass = "Warrior";
        weapon = "Sword (1d8)";
        armor = "Chainmail";
        ac = 16;
    }

    void attack() override {
        int damage = rollDie(8) + strength + weaponBonus;
        cout << name << " swings the sword for " << damage << " damage!\n";
    }
};

// Derived class for Mage
class Mage : public Hero {
public:
    Mage(string name, string race) : Hero(name, race) {
        heroClass = "Mage";
        weapon = "Firebolt (1d20)";
        armor = "Robes";
        ac = 12;
    }

    void attack() override {
        int damage = rollDie(20) + arcana + weaponBonus;
        mana -= 1;
        cout << name << " casts Firebolt for " << damage << " damage!\n";
    }
};

// Enemy class
class Enemy {
public:
    string type;
    int health;
    int ac;
    int damageDie;

    Enemy(string t, int h, int a, int d) : type(t), health(h), ac(a), damageDie(d) {}

    void attack() {
        int damage = rollDie(damageDie);
        cout << "The " << type << " attacks for " << damage << " damage!\n";
    }

    int getAC() { return ac; }
    int getHealth() { return health; }
    void takeDamage(int damage) { health -= damage; }
};

// Function to describe the enemy with detailed text and ASCII art
void describeEnemy(const Enemy& enemy) {
    cout << "\n--- Encounter ---\n";
    if (enemy.type == "Skeleton") {
        cout << "A decayed figure rises from the earth. Its bones creak as it stumbles towards you.\n";
        cout << "The empty eye sockets of the Skeleton seem to pierce into your soul as it raises its rusted sword.\n";
        cout << R"(
            ____
          /      \
         | ()  () |
          \  __  /
           \____/
        )" << endl;
    }
    else if (enemy.type == "Goblin") {
        cout << "A small, green-skinned creature approaches, grinning with malice.\n";
        cout << "The Goblin's sharp teeth gleam in the dim light as it clutches a jagged dagger in its hand.\n";
        cout << R"(
           ,      ,
          /(.-""-.)\
      |\  \/      \/  /|
      | \ / =.  .= \ / |
      \( \   o\/o   / )/
       \_, '-/  \-' ,_/
         /   \__/   \
         \ \__/\__/ /
         (_/ /  \ \_)
        )" << endl;
    }
    else if (enemy.type == "Dragon") {
        cout << "A monstrous creature looms above, scales shimmering in the darkness.\n";
        cout << "The Dragon’s fiery eyes lock onto you, and it lets out a terrifying roar, revealing rows of sharp teeth.\n";
        cout << R"(
                  __====-_  _-====__
             _--^^^#####//      \\#####^^^--_
          _-^##########// (    ) \\##########^-_
         -############//  |\^^/|  \\############-
       _/############//   (@::@)   \\############\_
      /#############((     \\//     ))#############\
     -###############\\    (oo)    //###############-
    -#################\\  / ** \  //#################-
   -###################\\/      \//###################-
  _#/|##########/\######(   /\   )######/\##########|\#_
 |/ |#/\#/\#/\/  /\#/\#   /\   /##\#/\/  /\#/\/  /\#/ \|)
 `  |/  |  \/    \/   \/    \/    \/  |  \/   \/    \|  '
        )" << endl;
    }
    else {
        cout << "A mysterious creature approaches.\n";
    }
    pause(); // Pause to allow the player to press 1 to proceed to combat
}

void levelUp(Hero* player) {
    if (player->getGold() < 50) {
        cout << "You don't have enough gold to level up! (50g required)\n";
        return;
    }

    cout << "\nThe shopkeeper grins as you hand over 50 gold.\n";
    player->spendGold(50);

    cout << "\"Alright, adventurer! What stat would ye like to improve?\"\n";
    cout << "1. Increase Max Health by 10\n";
    cout << "2. Increase Strength by 1\n";
    cout << "3. Increase Max Mana by 10\n";
    cout << "4. Increase Arcana by 1\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        player->setMaxHealth(player->getMaxHealth() + 10);
        cout << "Your Max Health increased by 10!\n";
        break;
    case 2:
        player->setStrength(player->getStrength() + 1);
        cout << "Your Strength increased by 1!\n";
        break;
    case 3:
        player->setMaxMana(player->getMaxMana() + 10);
        cout << "Your Max Mana increased by 10!\n";
        break;
    case 4:
        player->setArcana(player->getArcana() + 1);
        cout << "Your Arcana increased by 1!\n";
        break;
    default:
        cout << "Invalid choice. No changes made.\n";
    }
}

void enterShop(Hero* player) {
    cout << "\n--- The Dwarven Shop ---\n";
    cout << "A stout dwarf with a bushy beard and a monocle stands behind the counter, polishing a shining blade.\n";
    cout << "He peers at you through his monocle and gives a hearty chuckle.\n";
    cout << "\"Ah, a brave adventurer! Ye look like ye could use some better gear!\"\n";
    cout << R"(
      _____
     /     \
    | O  o  |  
    |  \_/  |  
     \_____/   
    ///|||\\\  
   /////|\\\\\
  //////|\\\\\\

    )" << endl;

    cout << "Would you like to enter the shop?\n1. Yes\n2. No\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int shopChoice;
        do {
            cout << "\nWelcome to the shop, " << player->getName() << "! What would you like to purchase?\n";
            cout << "1. Weapon Upgrade (+4 to attack, 150g)\n";
            cout << "2. Health Potion (restores health to full, 50g)\n";
            cout << "3. Exit\n";
            cout << "4. Talk with the dwarf shopkeeper\n";
            cout << "5. Level Up (Choose a stat bonus, 50g)\n";
            cin >> shopChoice;

            switch (shopChoice) {
            case 1:
                if (player->getGold() >= 150) {
                    player->spendGold(150);
                    player->setWeapon("Upgraded Weapon", player->getWeaponBonus() + 4);
                    cout << "You purchased a Weapon Upgrade! Your attack power increased by 4.\n";
                }
                else {
                    cout << "Not enough gold for the Weapon Upgrade.\n";
                }
                break;

            case 2:
                if (player->getGold() >= 50) {
                    player->spendGold(50);
                    player->addHealthPotion();
                    cout << "You purchased a Health Potion! It has been added to your inventory.\n";
                }
                else {
                    cout << "Not enough gold for a Health Potion.\n";
                }
                break;

            case 3:
                cout << "You exit the shop.\n";
                break;

            case 4: {
                int dialogueChoice;
                do {
                    cout << "\nWhat would you like to ask the shopkeeper?\n";
                    cout << "1. Where am I?\n";
                    cout << "2. Who am I?\n";
                    cout << "3. Why does everyone seem so afraid?\n";
                    cout << "4. Stop talking and return to the shop\n";

                    cin >> dialogueChoice;

                    switch (dialogueChoice) {
                    case 1:
                        cout << "\"Yer in the heart of the adventurer's hub! This here shop has been servin' brave souls like yerself for decades.\"\n";
                        break;

                    case 2:
                        cout << "\"Hah! Only ye can answer that, friend. But ye look like someone with a destiny bigger than a dragon's hoard.\"\n";
                        break;

                    case 3: {
                        cout << "\"Ah, the dark days are upon us, lad/lass. Rumors of a terrible evil spread like wildfire. Folks be lookin' over their shoulders and into the sky. We saw a winged beast in the sky just yesterday! It was a dragon I tell ye!\"\n";

                        int dragonChoice;
                        do {
                            cout << "\nWhat would you like to ask about the dragon?\n";
                            cout << "1. What direction did the dragon go?\n";
                            cout << "2. Which path should I take?\n";
                            cout << "3. Never mind.\n";
                            cin >> dragonChoice;

                            switch (dragonChoice) {
                            case 1:
                                cout << "\"The dragon flew eastward, toward the Misty Mountains and the Dark Forest.\"\n";
                                break;

                            case 2:
                                cout << "\"Both paths'll get ye to the dragon in the same amount of time, but both are filled with danger. The Misty Mountains be steep and treacherous, while the Dark Forest hides beasts that'll give ye nightmares. Choose wisely, adventurer.\"\n";
                                break;

                            case 3:
                                cout << "\"Alright, if ye don’t need my advice, let’s get back to business.\"\n";
                                break;

                            default:
                                cout << "\"Speak plainly, friend. I can't help if I don't understand.\"\n";
                            }
                        } while (dragonChoice != 3); // Exit dragon dialogue on choice 3
                        break;
                    }

                    case 4:
                        cout << "\"Alright, back to business! What'll it be?\"\n";
                        break;

                    default:
                        cout << "\"Speak plainly, friend. I can't help if I don't understand.\"\n";
                    }
                } while (dialogueChoice != 4); // Exit when player chooses to stop talking
                break;
            }
            case 5:
                levelUp(player);
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (shopChoice != 3); // Exit the shop when player selects 3
    }
    else {
        cout << "You decide to skip the shop and continue on your journey.\n";
    }
}




// Combat System with health, mana, and enemy display
bool combat(Hero* player, Enemy* enemy) {
    while (player->getHealth() > 0 && enemy->getHealth() > 0) {
        cout << "\n--- Combat Status ---\n";
        cout << "Your Health: " << player->getHealth() << " | Mana: " << player->getMana() << endl;
        cout << "Enemy: " << enemy->type << " | Health: " << enemy->getHealth() << endl;

        cout << "\nIt's your turn! Choose an action:\n";
        cout << "1. Attack\n";
        cout << "2. Block\n";
        cout << "i. Check Inventory\n";
        cout << "p. Use Health Potion\n";
        char choice;
        cin >> choice;

        if (choice == '1') {
            player->attack();
            int damage = rollDie(8) + player->getWeaponBonus();
            enemy->takeDamage(damage);
            cout << "You dealt " << damage << " damage to the " << enemy->type << "!\n";
            if (enemy->getHealth() <= 0) {
                cout << "You defeated the " << enemy->type << "!\n";
                int goldDrop = rollDie(10) + 5;
                player->addGold(goldDrop);
                cout << "You found " << goldDrop << " gold on the " << enemy->type << "!\n";
                pause(); // Pause after defeating an enemy
                return true;
            }
        }
        else if (choice == '2') {
            player->block();
        }
        else if (choice == 'i') {
            player->showInventory();
            continue;
        }
        else if (choice == 'p') {
            player->useHealthPotion();
        }
        else {
            cout << "Invalid choice, you lose your turn!\n";
        }

        cout << "\nEnemy's turn!\n";
        int roll = rollDie(20);
        cout << "The " << enemy->type << " rolls " << roll << " against your AC of " << player->getAC() << ".\n";
        if (roll >= player->getAC()) {
            int damage = rollDie(enemy->damageDie);
            cout << "The " << enemy->type << " hits you for " << damage << " damage!\n";
            player->takeDamage(damage);
        }
        else {
            cout << "The " << enemy->type << " missed!\n";
        }

        player->endBlock();

        if (player->getHealth() <= 0) {
            cout << "You have been slain.\n";
            return false;
        }
    }
    return false;
}

// Rest Area with Path Selection
void restArea(Hero* player) {
    cout << "\nYou reach a rest area. Your health and mana are restored.\n";
    player->restoreHealth();
    player->restoreMana();
    enterShop(player);

    cout << "\nChoose your path:\n1. Misty Mountains\n2. Dark Forest\n";
    int pathChoice;
    cin >> pathChoice;

    if (pathChoice == 1) {
        cout << "\nYou head towards the Misty Mountains.\n";
    }
    else {
        cout << "\nYou head towards the Dark Forest.\n";
    }
    pause(); // Pause after selecting a path
}

// Intro Story
void introStory() {
    cout << "\nYou awake in darkness. You push upward, feeling the weight of a lid above you. It creaks as you lift it, and a dull light floods in.\n";
    cout << "Climbing out, you realize you've stepped out of a coffin – your own. You have no memory of how you got here or why you awoke.\n";
    cout << "Before you can gather your thoughts, you hear another lid slide open nearby. A skeleton, holding a rusted sword, rises from its own coffin.\n";
    cout << "It turns toward you, hollow eyes gleaming, and lunges. Prepare yourself for combat!\n";
    pause(); // Pause after the introduction story
}

// Function to create a Hero with race bonuses directly applied
Hero* createHero() {
    string name, race;
    cout << "Welcome to Text Quest. What is the name of your hero?\n";
    cin >> name;

    cout << "Pick your class: 1. Warrior, 2. Mage\n";
    int classChoice;
    cin >> classChoice;
    Hero* hero;

    cout << "Pick your race: 1. Human (+10 Health), 2. Orc (+1 Strength), 3. Elf (+10 Mana), 4. Tiefling (+1 Arcana)\n";
    int raceChoice;
    cin >> raceChoice;

    switch (raceChoice) {
    case 1: race = "Human"; break;
    case 2: race = "Orc"; break;
    case 3: race = "Elf"; break;
    case 4: race = "Tiefling"; break;
    default: cout << "Invalid choice.\n"; race = "Human";
    }

    if (classChoice == 1) {
        hero = new Warrior(name, race);
    }
    else {
        hero = new Mage(name, race);
    }

    if (race == "Human") hero->setMaxHealth(hero->getMaxHealth() + 10);
    if (race == "Orc") hero->setStrength(hero->getStrength() + 1);
    if (race == "Elf") hero->setMaxMana(hero->getMaxMana() + 10);
    if (race == "Tiefling") hero->setArcana(hero->getArcana() + 1);

    return hero;
}

// Game Loop with Proper Progression
void gameLoop(Hero* player) {
    introStory();
    Enemy skeleton("Skeleton", 10, 10, 8);

    // Describe the enemy before combat
    describeEnemy(skeleton);
    if (combat(player, &skeleton)) {
        restArea(player);
        cout << "\nMoving on to the next area...\n";
        pause(); // Pause before moving to the next area

        Enemy goblin("Goblin", 15, 12, 6);

        // Describe the enemy before combat
        describeEnemy(goblin);
        if (combat(player, &goblin)) {
            restArea(player);

            cout << "\nYou approach the final boss...\n";
            pause(); // Pause before final boss fight

            Enemy boss("Dragon", 30, 16, 12);

            // Describe the enemy before combat
            describeEnemy(boss);
            if (combat(player, &boss)) {
                cout << "Congratulations! You defeated the Dragon and won Text Quest!\n";
            }
            else {
                cout << "You have died. Restarting...\n";
                player->setHealth(player->getMaxHealth());
                gameLoop(player);
            }
        }
        else {
            cout << "You have died. Restarting...\n";
            player->setHealth(player->getMaxHealth());
            gameLoop(player);
        }
    }
    else {
        cout << "You have died. Restarting...\n";
        player->setHealth(player->getMaxHealth());
        gameLoop(player);
    }
}

int main() {
    srand(time(0));
    Hero* player = createHero();
    player->showInventory();
    gameLoop(player);
    delete player;
    return 0;
}
