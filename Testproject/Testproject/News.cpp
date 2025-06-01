// News.cpp
#include "News.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

//īī��43000,�Ｚ56000,����27��,����23��,�׽���49��,�Ƹ���28��,����Ǽ�6��3õ,SK���̴н�20��
News::News() : round(0) {
    companies.emplace_back("īī��", 43000.0);
    companies.emplace_back("�Ｚ", 56000.0);
    companies.emplace_back("Apple", 270000.0);
    companies.emplace_back("Google", 230000.0);
    companies.emplace_back("�׽���", 490000.0);
    companies.emplace_back("Amazon", 280000.0);
    companies.emplace_back("����Ǽ�", 63000.0);
    companies.emplace_back("SK���̴н�", 200000.0);
    

    newsHints["īī��"] = {
        {"īī���� �ű���� ���� ���Դϴ�.", "īī���� �ű�� ���߿� �����߽��ϴ�!", "īī���� �ű�� ������ ����Ǿ����ϴ�.", 85, 0.15, 0.10},
        {"īī���� ��Ը� ���ڸ� ��ġ�߽��ϴ�.", "īī���� ���� ��ġ�� �����߽��ϴ�!", "īī���� ���� ��ġ�� �����߽��ϴ�.", 75, 0.10, 0.05},
        {"īī���� �ؿ� ���忡 �����ϰ� �ֽ��ϴ�.", "īī���� �ؿ� ���� ���⿡ �����߽��ϴ�!", "īī���� �ؿ� ���� ������ �����߽��ϴ�.", 60, 0.20, 0.15}
    };
    newsHints["�Ｚ"] = {
        {"�Ｚ�� �Ҽۿ� �ָ��Ƚ��ϴ�.", "�Ｚ�� �Ҽۿ��� �¼��߽��ϴ�!", "�Ｚ�� �Ҽۿ��� �м��߽��ϴ�.", 40, 0.05, 0.20},
        {"�Ｚ�� �ֿ� �λ縦 ��ü�߽��ϴ�.", "�Ｚ�� �� �λ簡 ȸ�縦 �������׽��ϴ�!", "�Ｚ�� ������ ��ȭ�� ȥ���� �ʷ��߽��ϴ�.", 55, 0.08, 0.12},
        {"�Ｚ�� ���ο� ��ǰ�� ��ǥ�߽��ϴ�.", "�Ｚ�� ����ǰ�� ���忡�� ȣ���� �޾ҽ��ϴ�!", "�Ｚ�� ����ǰ�� ���������� �򰡹޾ҽ��ϴ�.", 65, 0.12, 0.08}
    };
    newsHints["Apple"] = {
        {"Apple�� ���� ������ �����ϰ� �ֽ��ϴ�.", "Apple�� ���� ������ �����߽��ϴ�!", "Apple�� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
        {"Apple�� �۷ι� ����� ���� ���Դϴ�.", "Apple�� ������ ���� ������ �̾������ϴ�!", "Apple�� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
        {"Apple�� ������ �ս��� �����߽��ϴ�.", "Apple�� �ս� ȸ�� ������ �����߽��ϴ�!", "Apple�� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };
    newsHints["Google"] = {
       {"Google�� ���� ������ �����ϰ� �ֽ��ϴ�.", "Google�� ���� ������ �����߽��ϴ�!", "Google�� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
       {"Google�� �۷ι� ����� ���� ���Դϴ�.", "Google�� ������ ���� ������ �̾������ϴ�!", "Google�� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
       {"Google�� ������ �ս��� �����߽��ϴ�.", "Google�� �ս� ȸ�� ������ �����߽��ϴ�!", "Google�� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };

    newsHints["�׽���"] = {
       {"�׽��� ���� ������ �����ϰ� �ֽ��ϴ�.", "�׽��� ���� ������ �����߽��ϴ�!", "�׽����� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
       {"�׽��� �۷ι� ����� ���� ���Դϴ�.", "�׽����� ������ ���� ������ �̾������ϴ�!", "�׽����� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
       {"�׽��� ������ �ս��� �����߽��ϴ�.", "�׽����� �ս� ȸ�� ������ �����߽��ϴ�!", "�׽���� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };

    newsHints["Amazon"] = {
       {"Amazon�� ���� ������ �����ϰ� �ֽ��ϴ�.", "Amazon�� ���� ������ �����߽��ϴ�!", "Amazon�� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
       {"Amazon�� �۷ι� ����� ���� ���Դϴ�.", "Amazon�� ������ ���� ������ �̾������ϴ�!", "Amazon�� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
       {"Amazon�� ������ �ս��� �����߽��ϴ�.", "Amazon�� �ս� ȸ�� ������ �����߽��ϴ�!", "Amazon�� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };

    newsHints["����Ǽ�"] = {
       {"����Ǽ��� ���� ������ �����ϰ� �ֽ��ϴ�.", "����Ǽ��� ���� ������ �����߽��ϴ�!", "����Ǽ��� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
       {"����Ǽ��� �۷ι� ����� ���� ���Դϴ�.", "����Ǽ��� ������ ���� ������ �̾������ϴ�!", "����Ǽ��� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
       {"����Ǽ��� ������ �ս��� �����߽��ϴ�.", "����Ǽ��� �ս� ȸ�� ������ �����߽��ϴ�!", "����Ǽ��� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };
    newsHints["SK���̴н�"] = {
       {"SK���̴н��� ���� ������ �����ϰ� �ֽ��ϴ�.", "SK���̴н��� ���� ������ �����߽��ϴ�!", "SK���̴н��� ���� ������ ������ �߻��߽��ϴ�.", 70, 0.10, 0.05},
       {"SK���̴н��� �۷ι� ����� ���� ���Դϴ�.", "SK���̴н��� ������ ���� ������ �̾������ϴ�!", "SK���̴н��� ������ ����Ǿ����ϴ�.", 60, 0.18, 0.12},
       {"SK���̴н��� ������ �ս��� �����߽��ϴ�.", "SK���̴н��� �ս� ȸ�� ������ �����߽��ϴ�!", "SK���̴н��� �߰� �ս��� �߻��߽��ϴ�.", 30, 0.08, 0.25}
    };



    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void News::nextRound() {
    round++;
    generateNews();
    applyNewsResults();
}

int News::getCurrentRound() const {
    return round;
}

void News::generateNews() {
    int numNews = 1 + rand() % 3;
    std::vector<int> indices(companies.size());
    for (int i = 0; i < companies.size(); ++i) {
        indices[i] = i;
    }
    std::random_shuffle(indices.begin(), indices.end());

    std::cout << "\n[���� " << round << " - ���� �߻�]\n";

    for (int i = 0; i < numNews && i < indices.size(); ++i) {
        Company& company = companies[indices[i]];
        std::string cname = company.getName();
        auto& pool = newsHints[cname];

        std::vector<std::tuple<std::string, std::string, std::string, int, double, double>> availableHints;
        for (const auto& entry : pool) {
            if (activeHintTexts.find(std::get<0>(entry)) == activeHintTexts.end()) {
                availableHints.push_back(entry);
            }
        }

        if (availableHints.empty()) continue;

        auto& entry = availableHints[rand() % availableHints.size()];

        NewsEvent event{
            cname,
            std::get<0>(entry), std::get<1>(entry), std::get<2>(entry),
            std::get<3>(entry), std::get<4>(entry), std::get<5>(entry),
            round, false
        };
        pendingResults.push_back(event);
        activeHintTexts.insert(event.hintText);

        std::cout << " - " << event.hintText << "\n";
    }
}

void News::applyNewsResults() {
    std::cout << "\n[���� ��� �ݿ�]\n";
    for (auto& event : pendingResults) {
        if (!event.resolved && round - event.createdRound >= 3) {
            int roll = rand() % 100;
            for (auto& company : companies) {
                if (company.getName() == event.companyName) {
                    double rate = 0.0;
                    if (roll < event.successChance) {
                        rate = event.successRate;
                        company.setPrice(company.getPrice() * (1.0 + rate));
                        std::cout << " - (" << event.companyName << ") " << event.successText
                            << " [�ְ� ���: " << std::fixed << std::setprecision(0) << rate * 100 << "%]\n";
                    }
                    else {
                        rate = event.failureRate;
                        company.setPrice(company.getPrice() * (1.0 - rate));
                        std::cout << " - (" << event.companyName << ") " << event.failureText
                            << " [�ְ� �϶�: " << std::fixed << std::setprecision(0) << rate * 100 << "%]\n";
                    }
                    break;
                }
            }
            event.resolved = true;
            activeHintTexts.erase(event.hintText);
        }
    }
}

void News::showCompanyStatus() const {
    std::cout << "\n[ȸ�� �ֽ� ���� ��Ȳ]\n";
    for (const auto& company : companies) {
        std::cout << " - " << company.getName() << ": " << company.getPrice() << " ��\n";
    }
}

std::vector<Company>& News::getCompanies() {
    return companies;
}
