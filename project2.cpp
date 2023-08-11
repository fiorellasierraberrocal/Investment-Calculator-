//professor Some of my code may have bugs, if docked may I have the opportunity to resubmit. Thank you, Fiorella 
//This project is an application that allows users to see how their investments will grow over time. 



#ifndef INVESTMENTCALCULATOR_H_
#define INVESTMENTCALCULATOR_H_

#include <vector>

class InvestmentCalculator {
public:
    InvestmentCalculator(double principal, double monthlyDeposit, double annualInterestRate, int investmentYears);

    void calculateInvestmentGrowth();

private:
    double principal;
    double monthlyDeposit;
    double annualInterestRate;
    int investmentYears;

    std::vector<double> yearEndBalancesWithoutDeposit;
    std::vector<double> yearEndInterestWithoutDeposit;
    std::vector<double> yearEndBalancesWithDeposit;
    std::vector<double> yearEndInterestWithDeposit;

    double calculateInterest(double balance);
};

#endif // INVESTMENTCALCULATOR_H_

#include "InvestmentCalculator.h"

#include <iostream>
#include <iomanip>

InvestmentCalculator::InvestmentCalculator(double principal, double monthlyDeposit, double annualInterestRate, int investmentYears) {
    this->principal = principal;
    this->monthlyDeposit = monthlyDeposit;
    this->annualInterestRate = annualInterestRate;
    this->investmentYears = investmentYears;
}

void InvestmentCalculator::calculateInvestmentGrowth() {
    double balanceWithoutDeposit = principal;
    double balanceWithDeposit = principal;

    yearEndBalancesWithoutDeposit.push_back(balanceWithoutDeposit);
    yearEndBalancesWithDeposit.push_back(balanceWithDeposit);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Month\tOpening Amount\tDeposited Amount\tTotal\tInterest\tClosing Balance\n";
    std::cout << "----------------------------------------------------------------------------\n";

    for (int month = 1; month <= (investmentYears * 12); ++month) {
        double interestWithoutDeposit = calculateInterest(balanceWithoutDeposit);
        balanceWithoutDeposit += interestWithoutDeposit;

        double interestWithDeposit = calculateInterest(balanceWithDeposit);
        balanceWithDeposit += (interestWithDeposit + monthlyDeposit);

        yearEndBalancesWithoutDeposit.push_back(balanceWithoutDeposit);
        yearEndInterestWithoutDeposit.push_back(interestWithoutDeposit);

        yearEndBalancesWithDeposit.push_back(balanceWithDeposit);
        yearEndInterestWithDeposit.push_back(interestWithDeposit);

        std::cout << month << "\t$" << balanceWithoutDeposit << "\t$" << balanceWithDeposit - monthlyDeposit << "\t$"
                  << balanceWithDeposit << "\t$" << interestWithDeposit << "\t$" << balanceWithDeposit << "\n";
    }
}

double InvestmentCalculator::calculateInterest(double balance) {
    double monthlyInterestRate = annualInterestRate / 100.0 / 12.0;
    return balance * monthlyInterestRate;
}

#include <iostream>
#include "InvestmentCalculator.h"

int main() {
    double principalAmount, monthlyDepositAmount, annualInterestRate;
    int investmentYears;

    std::cout << "Enter Initial Investment Amount: $";
    std::cin >> principalAmount;

    std::cout << "Enter Monthly Deposit: $";
    std::cin >> monthlyDepositAmount;

    std::cout << "Enter Annual Interest (Compounded): ";
    std::cin >> annualInterestRate;

    std::cout << "Enter Number of Years: ";
    std::cin >> investmentYears;

    InvestmentCalculator calculator(principalAmount, monthlyDepositAmount, annualInterestRate, investmentYears);

    std::cout << "\nInvestment Growth Table (Without Monthly Deposit):\n";
    calculator.calculateInvestmentGrowth();

    return 0;
}