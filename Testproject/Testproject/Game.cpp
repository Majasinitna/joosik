#include "Game.h"
#include <iostream>

Game::Game(int goalAssets) : player(5), news(), bank(), round(0), goalAssets(goalAssets) {}

void Game::start() {
    while (round < maxRound && !checkEndCondition()) {
        playRound();  // �� ���� ���� ��, ����ڰ� �Է��� ��ٸ�
        std::cout << "Enter to continue to the next round...\n";
        std::cin.get();  // ���� Ű�� ������ ���� ����� �Ѿ�ϴ�
    }
    std::cout << "���� ����! ���� �ڻ�: " << player.getFunds() << std::endl;
}


void Game::playRound() {
    std::cout << "\nRound " << round + 1 << " ����!\n";

    // ���� ��Ʈ ���
    news.generateHintNews();

    bool roundContinues = true;
    while (roundContinues) {
        std::cout << "\n--- �����ϼ��� ---\n";
        std::cout << "1. �ֽ� �ż�\n";
        std::cout << "2. �ֽ� �ŵ�\n";
        std::cout << "3. ��Ʈ������ Ȯ��\n";
        std::cout << "4. ���� ��û\n";
        std::cout << "5. ���� ����\n";
        std::cout << "���� �Է�: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            const auto& companies = news.getCompanies();

            std::cout << "\n[�ֽ� ��� �� ���� ����]\n";
            for (size_t i = 0; i < companies.size(); ++i) {
                std::cout << i + 1 << ". " << companies[i].getName() << " - ����: " << companies[i].getPrice() << " ��\n";
            }

            std::cout << "���� �ڱ�: " << player.getFunds() << " ��\n";

            int selection;
            std::cout << "�ż��� ȸ�� ��ȣ �Է�: ";
            std::cin >> selection;

            if (selection < 1 || selection > companies.size()) {
                std::cout << "�߸��� ��ȣ�Դϴ�.\n";
                break;
            }

            int quantity;
            std::cout << "�ż��� ���� �Է�: ";
            std::cin >> quantity;

            if (quantity <= 0) {
                std::cout << "�߸��� �����Դϴ�.\n";
                break;
            }

            Company& selectedCompany = news.getCompanies()[selection - 1];
            double totalCost = selectedCompany.getPrice() * quantity;

            if (player.getFunds() < totalCost) {
                std::cout << "�ڱ��� �����մϴ�.\n";
                break;
            }

            // ���� �ż� ����
            for (int i = 0; i < quantity; ++i) {
                player.buyStock(selectedCompany.getName(), news.getCompanies());
            }

            std::cout << selectedCompany.getName() << " �ֽ� " << quantity << "���� �ż��߽��ϴ�.\n";
            break;
        }
        case 2: {
            std::cout << "\n[���� �ֽ� ���]\n";
            const auto& companies = news.getCompanies();
            bool hasHoldings = false;

            for (size_t i = 0; i < companies.size(); ++i) {
                const std::string& companyName = companies[i].getName();
                int quantity = player.getHoldingQuantity(companyName);
                if (quantity > 0) {
                    hasHoldings = true;
                    std::cout << i + 1 << ". " << companyName
                        << " - ���� ����: " << quantity
                        << ", ���簡: " << companies[i].getPrice() << " ��\n";
                }
            }

            if (!hasHoldings) {
                std::cout << "������ �ֽ��� �����ϴ�.\n";
                break;
            }

            std::cout << "���� �ڱ�: " << player.getFunds() << " ��\n";

            int selection;
            std::cout << "�ŵ��� ȸ�� ��ȣ �Է�: ";
            std::cin >> selection;

            if (selection < 1 || selection > companies.size()) {
                std::cout << "�߸��� ��ȣ�Դϴ�.\n";
                break;
            }

            const std::string& sellCompany = companies[selection - 1].getName();
            int owned = player.getHoldingQuantity(sellCompany);

            if (owned <= 0) {
                std::cout << "�ش� ȸ�� �ֽ��� �����ϰ� ���� �ʽ��ϴ�.\n";
                break;
            }

            int quantity;
            std::cout << "�ŵ��� ���� �Է� (����: " << owned << "): ";
            std::cin >> quantity;

            if (quantity <= 0 || quantity > owned) {
                std::cout << "�߸��� �����Դϴ�.\n";
                break;
            }

            for (int i = 0; i < quantity; ++i) {
                player.sellStock(sellCompany, news.getCompanies());
            }

            std::cout << sellCompany << " �ֽ� " << quantity << "���� �ŵ��߽��ϴ�.\n";
            break;
        }
        case 3: {
            std::cout << "\n[��Ʈ������ ����]\n";
            player.showStatus(news.getCompanies(), bank);
            //bank.showStatus();
            break;
        }
        case 4: {
            double amount;
            std::cout << "������ �ݾ� �Է�: ";
            std::cin >> amount;
            bank.takeLoan(amount);
            break;
        }
        case 5: {
            roundContinues = false;
            break;
        }
        default:
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n";
        }
    }

    // ���� ���� �� ���� ��� �ݿ� �� ȸ�� ���� ���
    news.applyResultNews();

    std::cout << "\n[ȸ�� �ֽ� ���� ��Ȳ]\n";
    news.showCompanyStatus();

    std::cout << "\n[�÷��̾� ���� ���]\n";
    player.showStatus(news.getCompanies(), bank);
    bank.showStatus();

    std::cout << "\n���� ����� �����Ϸ��� Enter Ű�� ��������...";
    std::cin.ignore(); // ���� �Է� ���� Ŭ����
    std::cin.get();    // Enter Ű �Է� ���
}




bool Game::checkEndCondition() const {
    return player.getFunds() >= goalAssets;
}