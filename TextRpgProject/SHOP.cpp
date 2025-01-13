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
        std::cout << "\n===== " << name << "의 인벤토리 =====\n";
        for (const auto& pair : inventory) {
            const auto& item = pair.second;
            std::cout << pair.first << ". " << item.name
                << " (체력 +" << item.healthBoost
                << ", 공격력 +" << item.attackBoost << ")\n";
        }
        std::cout << "보유 골드: " << gold << "\n";
    }

    const Item* getItem(int index) const {
        auto it = inventory.find(index);
        return it != inventory.end() ? &it->second : nullptr;
    }

    void displayStatus() const {
        std::cout << "\n===== " << name << "의 상태 =====\n";
        std::cout << "체력: " << currentHealth << "/" << maxHealth << "\n";
        std::cout << "공격력: " << attack << "\n";
        std::cout << "골드: " << gold << "\n";
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
        items.push_back(Item("체력 포션", 50, 0, 10));
        items.push_back(Item("공격력 버프 포션", 0, 10, 15));
    }

    void displayItems() const {
        std::cout << "\n===== 상점 아이템 목록 =====\n";
        for (size_t i = 0; i < items.size(); ++i) {
            const auto& item = items[i];
            std::cout << i + 1 << ". " << item.name
                << " (체력 +" << item.healthBoost
                << ", 공격력 +" << item.attackBoost
                << ") - 구매가: " << item.buyPrice
                << " 골드, 판매가: " << item.sellPrice << " 골드\n";
        }
    }

    bool buyItem(int index, Character& player) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            std::cout << "잘못된 아이템 번호입니다.\n";
            return false;
        }

        const Item& item = items[index];
        if (player.getGold() < item.buyPrice) {
            std::cout << "소지한 골드가 부족하여 구매할 수 없습니다. 필요한 골드: " << item.buyPrice
                << ", 보유 골드: " << player.getGold() << "\n";
            return false;
        }

        player.addItem(index + 1, item);
        player.spendGold(item.buyPrice);
        std::cout << "\n";
        std::cout << item.name << "을(를) " << item.buyPrice << " 골드에 구매했습니다.\n";
        std::cout << item.name << "이(가) 인벤토리에 추가되었습니다.\n";
        std::cout << item.buyPrice << " 골드가 인벤토리에서 차감되었습니다. (남은 골드: " << player.getGold() << ")\n";
        return true;
    }

    bool sellItem(int index, Character& player) {
        const Item* item = player.getItem(index);
        if (!item) {
            std::cout << "잘못된 아이템 번호입니다.\n";
            return false;
        }

        player.earnGold(item->sellPrice);
        std::cout << "\n";
        std::cout << item->name << "을(를) " << item->sellPrice << " 골드에 판매하였습니다.\n";
        std::cout << item->name << "이(가) 인벤토리에서 차감되었습니다.\n";
        std::cout << item->sellPrice << " 골드가 인벤토리에 추가되었습니다. (현재 골드: " << player.getGold() << ")\n";
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
        std::cout << "인벤토리가 비어있습니다.\n";
    }

    char choice;
    do {
        std::cout << "\n";
        std::cout << "인벤토리를 확인했습니다. 상점으로 돌아가시겠습니까? (Y): ";
        std::cin >> choice;
        choice = toupper(choice);

        if (choice != 'Y') {
            std::cout << "잘못된 입력입니다. Y를 입력해주세요.\n";
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

        std::cout << "\n무엇을 하시겠습니까? (B: 구매, S: 판매, I: 인벤토리 관리, Q: 나가기): ";
        std::cin >> choice;

        switch (toupper(choice)) {
        case 'B': {
            int itemIndex;
            do {
                std::cout << "구매할 아이템 번호를 입력하세요 (0: 취소): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "구매를 취소합니다.\n";
                    break;
                }
                if (itemIndex < 1 || itemIndex > shop.itemCount()) {
                    std::cout << "잘못된 아이템 번호입니다. 다시 입력해주세요.\n";
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
                std::cout << "판매할 아이템이 없습니다.\n";
                break;
            }
            player.displayInventory();
            int itemIndex;
            do {
                std::cout << "판매할 아이템 번호를 입력하세요 (0: 취소): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "판매를 취소합니다.\n";
                    break;
                }
                if (player.getItem(itemIndex) == nullptr) {
                    std::cout << "잘못된 아이템 번호입니다. 다시 입력해주세요.\n";
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
            std::cout << "상점에서 나갑니다.\n";
            break;
        default:
            std::cout << "잘못 입력하셨습니다. B, S, I, Q 중 하나를 입력해주세요.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (toupper(choice) != 'Q');
}

int main() {
    Shop shop;
    Character player("Player");

    // 상점 방문을 환영하는 메시지 출력
    std::cout << "*** 상점 방문을 환영합니다! ***\n";

    visitShop(shop, player);

    return 0;
}