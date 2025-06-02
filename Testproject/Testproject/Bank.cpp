#include "Bank.h"

double Bank::getLoanAmount() const {
    return loan;
}

double Bank::calculateInterest() const {
    return loan * interestRate;
}

void Bank::applyInterest() {
    double interest = loan * interestRate;
    loan += interest;
}

void Bank::takeLoan(double money) {
    if (money <= 0) {
        std::cout << "[���� ����] �ݾ��� 0�� �����Դϴ�.\n";
        return;
    }
    if (loan + money > maxLoanLimit) {
        std::cout << "[���� ����] �ִ� ���� �ѵ�(" << maxLoanLimit
            << " ��)�� �ʰ��� �� �����ϴ�.\n";
        return;
    }
    loan += money;
    std::cout << "[���� �Ϸ�] ���� �����: " << loan << " ��\n";
}

void Bank::repayLoan(double money) {
    if (money <= 0) {
        std::cout << "[��ȯ ����] �ݾ��� 0�� �����Դϴ�.\n";
        return;
    }
    if (money > loan) money = loan;
    loan -= money;
    std::cout << "[��ȯ �Ϸ�] ���� �����: " << loan << " ��\n";
}

void Bank::showStatus() const {
    std::cout << "�����: " << loan << " ��\n";
}