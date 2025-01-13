#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <limits>


class Item {
public:
    std::string name;
    int healthBoost;
    int attackBoost;
    int buyPrice;
    int sellPrice;

    Item() : name(""), healthBoost(0), attackBoost(0), buyPrice(0), sellPrice(0) {}

    Item(std::string n, int h, int a, int bp)
        : name(n), healthBoost(h), attackBoost(a), buyPrice(bp) {
        sellPrice = static_cast<int>(buyPrice * 0.6);
    }
};

class Character {
private:
    std::string name;
    int gold;
    std::map<int, Item> inventory;
    int maxHealth;
    int currentHealth;
    int attack;

public:
    Character(std::string n) : name(n), gold(50), maxHealth(100), currentHealth(100), attack(10) {}

    void addItem(int index, const Item& item) {
        inventory[index] = item;
    }

    bool removeItem(int index) {
        auto it = inventory.find(index);
        if (it != inventory.end()) {
            inventory.erase(it);
            return true;
        }
        return false;
    }

    void spendGold(int amount) {
        gold -= amount;
    }

    void earnGold(int amount) {
        gold += amount;
    }

    int getGold() const {
        return gold;
    }

    void displayInventory() const {
        std::cout << "\n===== " << name << "�� �κ��丮 =====\n";
        for (const auto& pair : inventory) {
            const auto& item = pair.second;
            std::cout << pair.first << ". " << item.name
                << " (ü�� +" << item.healthBoost
                << ", ���ݷ� +" << item.attackBoost << ")\n";
        }
        std::cout << "���� ���: " << gold << "\n";
    }

    const Item* getItem(int index) const {
        auto it = inventory.find(index);
        return it != inventory.end() ? &it->second : nullptr;
    }

    void displayStatus() const {
        std::cout << "\n===== " << name << "�� ���� =====\n";
        std::cout << "ü��: " << currentHealth << "/" << maxHealth << "\n";
        std::cout << "���ݷ�: " << attack << "\n";
        std::cout << "���: " << gold << "\n";
    }

    bool hasItems() const {
        return !inventory.empty();
    }

    size_t inventorySize() const {
        return inventory.size();
    }
};

class Shop {
private:
    std::vector<Item> items;

public:
    Shop() {
        items.push_back(Item("ü�� ����", 50, 0, 10));
        items.push_back(Item("���ݷ� ���� ����", 0, 10, 15));
    }

    void displayItems() const {
        std::cout << "\n===== ���� ������ ��� =====\n";
        for (size_t i = 0; i < items.size(); ++i) {
            const auto& item = items[i];
            std::cout << i + 1 << ". " << item.name
                << " (ü�� +" << item.healthBoost
                << ", ���ݷ� +" << item.attackBoost
                << ") - ���Ű�: " << item.buyPrice
                << " ���, �ǸŰ�: " << item.sellPrice << " ���\n";
        }
    }

    bool buyItem(int index, Character& player) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
            return false;
        }

        const Item& item = items[index];
        if (player.getGold() < item.buyPrice) {
            std::cout << "������ ��尡 �����Ͽ� ������ �� �����ϴ�. �ʿ��� ���: " << item.buyPrice
                << ", ���� ���: " << player.getGold() << "\n";
            return false;
        }

        player.addItem(index + 1, item);
        player.spendGold(item.buyPrice);
        std::cout << "\n";
        std::cout << item.name << "��(��) " << item.buyPrice << " ��忡 �����߽��ϴ�.\n";
        std::cout << item.name << "��(��) �κ��丮�� �߰��Ǿ����ϴ�.\n";
        std::cout << item.buyPrice << " ��尡 �κ��丮���� �����Ǿ����ϴ�. (���� ���: " << player.getGold() << ")\n";
        return true;
    }

    bool sellItem(int index, Character& player) {
        const Item* item = player.getItem(index);
        if (!item) {
            std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
            return false;
        }

        player.earnGold(item->sellPrice);
        std::cout << "\n";
        std::cout << item->name << "��(��) " << item->sellPrice << " ��忡 �Ǹ��Ͽ����ϴ�.\n";
        std::cout << item->name << "��(��) �κ��丮���� �����Ǿ����ϴ�.\n";
        std::cout << item->sellPrice << " ��尡 �κ��丮�� �߰��Ǿ����ϴ�. (���� ���: " << player.getGold() << ")\n";
        player.removeItem(index);
        return true;
    }

    size_t itemCount() const {
        return items.size();
    }
};

void manageInventory(Character& player) {
    player.displayStatus();
    player.displayInventory();

    if (!player.hasItems()) {
        std::cout << "�κ��丮�� ����ֽ��ϴ�.\n";
    }

    char choice;
    do {
        std::cout << "\n";
        std::cout << "�κ��丮�� Ȯ���߽��ϴ�. �������� ���ư��ðڽ��ϱ�? (Y): ";
        std::cin >> choice;
        choice = toupper(choice);

        if (choice != 'Y') {
            std::cout << "�߸��� �Է��Դϴ�. Y�� �Է����ּ���.\n";
        }
    } while (choice != 'Y');
}

void visitShop(Shop& shop, Character& player) {
    char choice;
    bool shouldDisplayItems = true;
    do {
        if (shouldDisplayItems) {
            shop.displayItems();
            player.displayInventory();
            shouldDisplayItems = false;
        }

        std::cout << "\n������ �Ͻðڽ��ϱ�? (B: ����, S: �Ǹ�, I: �κ��丮 ����, Q: ������): ";
        std::cin >> choice;

        switch (toupper(choice)) {
        case 'B': {
            int itemIndex;
            do {
                std::cout << "������ ������ ��ȣ�� �Է��ϼ��� (0: ���): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "���Ÿ� ����մϴ�.\n";
                    break;
                }
                if (itemIndex < 1 || itemIndex > shop.itemCount()) {
                    std::cout << "�߸��� ������ ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n";
                }
                else {
                    shop.buyItem(itemIndex - 1, player);
                    break;
                }
            } while (true);
            break;
        }
        case 'S': {
            if (!player.hasItems()) {
                std::cout << "�Ǹ��� �������� �����ϴ�.\n";
                break;
            }
            player.displayInventory();
            int itemIndex;
            do {
                std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ��� (0: ���): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "�ǸŸ� ����մϴ�.\n";
                    break;
                }
                if (player.getItem(itemIndex) == nullptr) {
                    std::cout << "�߸��� ������ ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n";
                }
                else {
                    shop.sellItem(itemIndex, player);
                    break;
                }
            } while (true);
            break;
        }
        case 'I':
            manageInventory(player);
            shouldDisplayItems = true;
            break;
        case 'Q':
            std::cout << "�������� �����ϴ�.\n";
            break;
        default:
            std::cout << "�߸� �Է��ϼ̽��ϴ�. B, S, I, Q �� �ϳ��� �Է����ּ���.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (toupper(choice) != 'Q');
}

int main() {
    Shop shop;
    Character player("Player");

    // ���� �湮�� ȯ���ϴ� �޽��� ���
    std::cout << "*** ���� �湮�� ȯ���մϴ�! ***\n";

    visitShop(shop, player);

    return 0;
}