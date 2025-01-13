#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 몬스터 아이디
enum PawnId {
    SLIME = 1,
    TROLL = 2,
    ORC = 3,
    GOBLIN = 4,
    HUMAN = 5
};

struct BaseAbility {
    int health;
    int attack;
};

class Item {
private:
    string name;
    int value;

public:
    Item(string _name, int _value) : name(_name), value(_value) {}

    string GetName() const {
        return name;
    }

    int GetValue() const {
        return value;
    }
};

class Entity {
private:
    string name;

public:
    Entity() : name("Unknown") {}
    virtual ~Entity() {}

    void SetName(string _name) {
        name = _name;
    }

    string GetName() const {
        return name;
    }
};

class Pawn : public Entity {
private:
    int level;
    int health;
    int attack;
    int gold;
    int experience;
    vector<Item*> inventory;

public:
    Pawn() : level(1), health(100), attack(10), gold(0), experience(0) {}

    void SetLevel(int _level) { level = _level; }
    int GetLevel() const { return level; }

    void SetHealth(int _health) { health = _health; }
    int GetHealth() const { return health; }

    void SetAttack(int _attack) { attack = _attack; }
    int GetAttack() const { return attack; }

    void SetGold(int _gold) { gold = _gold; }
    int GetGold() const { return gold; }

    void SetExperience(int _experience) { experience = _experience; }
    int GetExperience() const { return experience; }

    void AddItemToInventory(Item* item) { inventory.push_back(item); }
    Item* DropItem() {
        if (inventory.empty()) {
            cout << "No items to drop!" << endl;
            return nullptr;
        }
        Item* itemToDrop = inventory.back();
        inventory.pop_back();
        cout << "Dropped item: " << itemToDrop->GetName() << endl;
        return itemToDrop;
    }

    void ShowInventory() const {
        cout << "Inventory: ";
        for (const auto& item : inventory) {
            cout << item->GetName() << " ";
        }
        cout << endl;
    }
};

class IMonster {
public:
    virtual void Attack() = 0;
    virtual void TakeDamage(int damage) = 0;
    virtual void Die() = 0;
    virtual ~IMonster() {}
};

class Player {
private:
    string name;
    int coins;

public:
    Player(string _name, int _coins) : name(_name), coins(_coins) {}

    void SetCoins(int _coins) { coins = _coins; }
    int GetCoins() const { return coins; }

    void LoseCoins(int amount) {
        if (coins >= amount) {
            coins -= amount;
            cout << name << " loses " << amount << " coins! Remaining coins: " << coins << endl;
        }
        else {
            cout << name << " doesn't have enough coins to lose!" << endl;
        }
    }
};

class Slime : public Pawn, public IMonster {
private:
    int id = PawnId::SLIME;
    string name = "슬라임";
    BaseAbility ba = { 50, 5 };

public:
    Slime(int _level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    void Attack() override {
        cout << GetName() << " 슬라임은 흐물거리며 당신에게 돌진한다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << GetName() << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << GetName() << " 슬라임은 흘러내려 형체를 알아볼수 없게 되었다." << endl;
    }
};

class Troll : public Pawn, public IMonster {
private:
    int id = PawnId::TROLL;
    string name = "트롤";
    BaseAbility ba = { 120, 20 };

public:
    Troll(int _level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    void Attack() override {
        cout << GetName() << " 트롤은 괴상한 소리를 내며 방망이로 공격한다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << GetName() << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << GetName() << " 트롤은 더이상 소리내지 않는다." << endl;
    }
};

class Goblin : public Pawn, public IMonster {
private:
    int id = PawnId::GOBLIN;
    string name = "고블린";
    BaseAbility ba = { 100, 15 };

public:
    Goblin(int _level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    void Attack() override {
        cout << GetName() << " 고블린은 단검을 들고 당신을향해 뛰어온다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << GetName() << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << GetName() << " 고블린은 더이상 숨쉬지 않는다." << endl;
    }
};

class Orc : public Pawn, public IMonster {
private:
    int id = PawnId::ORC;
    string name = "오크";
    BaseAbility ba = { 150, 25 };

public:
    Orc(int _level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    void Attack() override {
        cout << GetName() << " 오크는 거대한 몸뚱이를 이끌고 당신을 짓밟으려 한다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << GetName() << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << GetName() << " 그의 거대한 몸뚱이는 더이상 움직이지 못한다." << endl;
    }
};

class Human : public Pawn, public IMonster {
private:
    int id = PawnId::HUMAN;
    string name = "인간";
    BaseAbility ba = { 120, 20 };

public:
    Human(int _level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    void Attack() override {
        cout << GetName() << " 적대적으로 보이는 인간이 당신에게 검을 휘두른다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << GetName() << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << GetName() << " 그는 죽었다." << endl;
    }
};

class GoldenGoblin : public Goblin {
private:
    int id = PawnId::GOBLIN;
    string name = "황금 고블린";
    BaseAbility ba = { 200, 30 };

    int turnCount = 0;

public:
    GoldenGoblin(int _level) : Goblin(_level) {
        SetLevel(_level);
        SetHealth(ba.health);
        SetAttack(ba.attack);
        SetName(name);
    }

    bool Escape(Player& player) {
        if (turnCount >= 3) {
            cout << name << " 황금고블린은 원하는것을 얻었다." << endl;
            int coinLoss = rand() % 20 + 1;
            player.LoseCoins(coinLoss);
            return true;
        }
        return false;
    }

    void Attack() override {
        cout << name << " 황금고블린은 당신을 약탈하려 한다!" << endl;
    }

    void TakeDamage(int damage) override {
        SetHealth(GetHealth() - damage);
        cout << name << " takes " << damage << " damage. Health: " << GetHealth() << endl;
        if (GetHealth() <= 0) {
            Die();
        }
    }

    void Die() override {
        cout << name << " 황금고블린과의 악연은 끝이다." << endl;
    }

    void IncreaseTurn() {
        turnCount++;
    }
};

class MonsterFactory {
public:
    static IMonster* CreateMonster(const string& type, int level) {
        if (type == "Slime") {
            return new Slime(level);
        }
        else if (type == "Troll") {
            return new Troll(level);
        }
        else if (type == "Goblin") {
            return new Goblin(level);
        }
        else if (type == "Orc") {
            return new Orc(level);
        }
        else if (type == "Human") {
            return new Human(level);
        }
        else if (type == "GoldenGoblin") { // GoldenGoblin 추가
            return new GoldenGoblin(level);
        }
        else {
            cout << "Unknown monster type: " << type << endl;
            return nullptr;
        }
    }
};

int main() {
    Player player("Player1", 100);

    IMonster* slime = MonsterFactory::CreateMonster("Slime", 3);
    IMonster* troll = MonsterFactory::CreateMonster("Troll", 5);
    IMonster* goblin = MonsterFactory::CreateMonster("Goblin", 4);
    IMonster* orc = MonsterFactory::CreateMonster("Orc", 6);
    IMonster* human = MonsterFactory::CreateMonster("Human", 10);

    srand(time(0));
    if (rand() % 100 < 8) {
        IMonster* goldenGoblin = MonsterFactory::CreateMonster("GoldenGoblin", 6);
        GoldenGoblin* gg = dynamic_cast<GoldenGoblin*>(goldenGoblin);

        if (gg) {
            cout << "A wild Golden Goblin appears!" << endl;
            gg->Attack();
            gg->TakeDamage(30);
            gg->IncreaseTurn(); 
            gg->TakeDamage(50);
            gg->IncreaseTurn();
            gg->TakeDamage(70);
            gg->IncreaseTurn();
           
            if (gg->Escape(player)) {
                delete gg;
            }
        }
    }


    cout << "- 슬라임 인페 -" << endl;
    if (slime) {
        slime->Attack();
        slime->TakeDamage(30);
        slime->TakeDamage(80);
        delete slime;
    }

    cout << "\n- 트롤 인페 -" << endl;
    if (troll) {
        troll->Attack();
        troll->TakeDamage(30);
        troll->TakeDamage(80);
        delete troll;
    }

    cout << "\n- 고블린 인페 -" << endl;
    if (goblin) {
        goblin->Attack();
        goblin->TakeDamage(30);
        goblin->TakeDamage(50);
        delete goblin;
    }

    cout << "\n- 오크 인페 -" << endl;
    if (orc) {
        orc->Attack();
        orc->TakeDamage(30);
        orc->TakeDamage(50);
        delete orc;
    }

    cout << "\n- 인간 인페 -" << endl;
    if (human) {
        human->Attack();
        human->TakeDamage(30);
        human->TakeDamage(50);
        delete human;
    }

    return 0;
}
