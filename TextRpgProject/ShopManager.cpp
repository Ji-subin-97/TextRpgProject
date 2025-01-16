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
    std::cout << "\n===== 상점 아이템 목록 =====\n";
    int index = 1;
    for (const auto& pair : inventory) {
        const auto& item = pair.first;
        std::cout << index++ << ". " << item->GetName()
            << " (체력 +" << item->GetHealthBoost()
            << ", 공격력 +" << item->GetAttackBoost()
            << ") - 구매가: " << item->GetBuyPrice()
            << " 골드, 판매가: " << item->GetSellPrice() << " 골드\n";
    }
}

bool ShopManager::buyItem(int index, Character& player) {
    if (index < 1 || index > inventory.size()) {
        std::cout << "잘못된 아이템 번호입니다.\n";
        return false;
    }

    auto it = std::next(inventory.begin(), index - 1);
    const auto& item = it->first;
    int& stock = it->second;

    if (stock <= 0) {
        std::cout << "해당 아이템의 재고가 없습니다.\n";
        return false;
    }

    if (player.GetGold() < item->GetBuyPrice()) {
        std::cout << "소지한 골드가 부족하여 구매할 수 없습니다. 필요한 골드: " << item->GetBuyPrice()
            << ", 보유 골드: " << player.GetGold() << "\n";
        return false;
    }

    player.AddItem(item);
    player.SpendGold(item->GetBuyPrice());
    stock--;

    std::cout << "\n";
    std::cout << item->GetName() << "을(를) " << item->GetBuyPrice() << " 골드에 구매했습니다.\n";
    std::cout << item->GetName() << "이(가) 인벤토리에 추가되었습니다.\n";
    std::cout << item->GetBuyPrice() << " 골드가 인벤토리에서 차감되었습니다. (남은 골드: " << player.GetGold() << ")\n";
    return true;
}

bool ShopManager::sellItem(int index, Character& player) {
    auto item = player.GetItem(index);
    if (!item) {
        std::cout << "잘못된 아이템 번호입니다.\n";
        return false;
    }

    player.EarnGold(item->GetSellPrice());
    std::cout << "\n";
    std::cout << item->GetName() << "을(를) " << item->GetSellPrice() << " 골드에 판매하였습니다.\n";
    std::cout << item->GetName() << "이(가) 인벤토리에서 차감되었습니다.\n";
    std::cout << item->GetSellPrice() << " 골드가 인벤토리에 추가되었습니다. (현재 골드: " << player.GetGold() << ")\n";
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

void ShopManager::VisitShop(Character& player) {
    std::cout << "\n*** 상점 방문을 환영합니다! ***\n";

    initializeInventory();

    char choice;
    bool shouldDisplayItems = true;
    do {
        if (shouldDisplayItems) {
            DisplayItems();
            // player.DisplayInventory(); 를 제거
            shouldDisplayItems = false;
        }

        std::cout << "\n무엇을 하시겠습니까? (B: 구매, S: 판매, I: 인벤토리 관리, Q: 나가기): ";
        std::cin >> choice;

        switch (toupper(choice)) {
        case 'B': {
            std::cout << "현재 보유 골드: " << player.GetGold() << "\n";
            int itemIndex;
            do {
                std::cout << "구매할 아이템 번호를 입력하세요 (0: 취소): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "구매를 취소합니다.\n";
                    break;
                }
                if (itemIndex < 1 || itemIndex > this->itemCount()) {
                    std::cout << "잘못된 아이템 번호입니다. 다시 입력해주세요.\n";
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
                std::cout << "판매할 아이템이 없습니다.\n";
                break;
            }
            player.PrintItemList();
            int itemIndex;
            do {
                std::cout << "판매할 아이템 번호를 입력하세요 (0: 취소): ";
                std::cin >> itemIndex;
                if (itemIndex == 0) {
                    std::cout << "판매를 취소합니다.\n";
                    break;
                }
                if(itemIndex < 1 || itemIndex > this->itemCount()) {
                    std::cout << "잘못된 아이템 번호입니다. 다시 입력해주세요.\n";
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
            std::cout << "상점에서 나갑니다.\n";
            break;
        default:
            std::cout << "잘못 입력하셨습니다. B, S, I, Q 중 하나를 입력해주세요.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (toupper(choice) != 'Q');
}

