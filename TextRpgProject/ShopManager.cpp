#include "ShopManager.h"
#include "Character.h"
#include <limits>

void ShopManager::initializeInventory() {
    inventory.clear();
    ItemManager::GetInstance()->initializeItems();
    for (const auto& item : ItemManager::GetInstance()->getAllItems()) {
        inventory[item] = 10;
    }
}

void ShopManager::DisplayItems() const {
    std::cout << "\n===== ���� ������ ��� =====\n";
    int index = 1;
    for (const auto& pair : inventory) {
        const auto& item = pair.first;
        std::cout << index++ << ". " << item->GetName()
            << " (ü�� +" << item->GetHealthBoost()
            << ", ���ݷ� +" << item->GetAttackBoost()
            << ") - ���Ű�: " << item->GetBuyPrice()
            << " ���, �ǸŰ�: " << item->GetSellPrice() << " ���\n";
    }
}

bool ShopManager::buyItem(int index, Character& player) {
    if (index < 1 || index > inventory.size()) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    auto it = std::next(inventory.begin(), index - 1);
    const auto& item = it->first;
    int& stock = it->second;

    if (stock <= 0) {
        std::cout << "�ش� �������� ��� �����ϴ�.\n";
        return false;
    }

    if (player.GetGold() < item->GetBuyPrice()) {
        std::cout << "������ ��尡 �����Ͽ� ������ �� �����ϴ�. �ʿ��� ���: " << item->GetBuyPrice()
            << ", ���� ���: " << player.GetGold() << "\n";
        return false;
    }

    player.AddItem(item);
    player.SpendGold(item->GetBuyPrice());
    stock--;

    std::cout << "\n";
    std::cout << item->GetName() << "��(��) " << item->GetBuyPrice() << " ��忡 �����߽��ϴ�.\n";
    std::cout << item->GetName() << "��(��) �κ��丮�� �߰��Ǿ����ϴ�.\n";
    std::cout << item->GetBuyPrice() << " ��尡 �κ��丮���� �����Ǿ����ϴ�. (���� ���: " << player.GetGold() << ")\n";
    return true;
}

bool ShopManager::sellItem(int index, Character& player) {
    auto item = player.GetItem(index);
    if (!item) {
        std::cout << "�߸��� ������ ��ȣ�Դϴ�.\n";
        return false;
    }

    player.EarnGold(item->GetSellPrice());
    std::cout << "\n";
    std::cout << item->GetName() << "��(��) " << item->GetSellPrice() << " ��忡 �Ǹ��Ͽ����ϴ�.\n";
    std::cout << item->GetName() << "��(��) �κ��丮���� �����Ǿ����ϴ�.\n";
    std::cout << item->GetSellPrice() << " ��尡 �κ��丮�� �߰��Ǿ����ϴ�. (���� ���: " << player.GetGold() << ")\n";
    player.RemoveItem(item);

    for (auto& pair : inventory) {
        if (pair.first->GetName() == item->GetName()) {
            pair.second++;
            break;
        }
    }

    return true;
}

size_t ShopManager::itemCount() const {
    return std::distance(inventory.begin(), inventory.end());
}

void ShopManager::manageInventory(Character& player) const {
    player.DisplayStatus();
    player.DisplayItemList();

    if (!player.HasItems()) {
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

void ShopManager::VisitShop(Character& player) {
    std::cout << "\n*** ���� �湮�� ȯ���մϴ�! ***\n";

    initializeInventory();

    char choice;
    bool shouldDisplayItems = true;
    do {
        if (shouldDisplayItems) {
            DisplayItems();
            // player.DisplayInventory(); �� ����
            shouldDisplayItems = false;
        }

        std::cout << "\n������ �Ͻðڽ��ϱ�? (B: ����, S: �Ǹ�, I: �κ��丮 ����, Q: ������): ";
        std::cin >> choice;

        switch (toupper(choice)) {
        case 'B': {
            std::cout << "���� ���� ���: " << player.GetGold() << "\n";
            int itemIndex;
            do {
                std::cout << "������ ������ ��ȣ�� �Է��ϼ��� (0: ���): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "���Ÿ� ����մϴ�.\n";
                    break;
                }
                if (itemIndex < 1 || itemIndex > this->itemCount()) {
                    std::cout << "�߸��� ������ ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n";
                }
                else {
                    this->buyItem(itemIndex, player);
                    break;
                }
            } while (true);
            break;
        }
        case 'S': {
            if (!player.HasItems()) {
                std::cout << "�Ǹ��� �������� �����ϴ�.\n";
                break;
            }
            player.PrintItemList();
            int itemIndex;
            do {
                std::cout << "�Ǹ��� ������ ��ȣ�� �Է��ϼ��� (0: ���): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "�ǸŸ� ����մϴ�.\n";
                    break;
                }
                if(itemIndex < 1 || itemIndex > this->itemCount()) {
                    std::cout << "�߸��� ������ ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n";
                }
                else {
                    this->sellItem(itemIndex, player);
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
            std::cout << "\n";
            std::cout << "�������� �����ϴ�.\n";
            break;
        default:
            std::cout << "�߸� �Է��ϼ̽��ϴ�. B, S, I, Q �� �ϳ��� �Է����ּ���.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (toupper(choice) != 'Q');
}

