#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct NewspaperSubscription {
    std::string name;
    std::vector<double> prices;
};

void calculateSubscriptions(std::vector<NewspaperSubscription>& subscriptions, int budget, std::vector<std::vector<std::string>>& combinations, std::vector<std::string>& currentCombination, int day = 0);

void calculateSubscriptions(std::vector<NewspaperSubscription>& subscriptions, int budget, std::vector<std::vector<std::string>>& combinations, std::vector<std::string>& currentCombination, int day) {
    // Base case: reached the end of the week
    if (day >= subscriptions[0].prices.size()) {
        double totalCost = 0.0;
        // Calculate the total cost and print the current combination of subscriptions
        for (const auto& subscription : currentCombination) {
            // Find the subscription by name
            auto it = std::find_if(subscriptions.begin(), subscriptions.end(), [&](const NewspaperSubscription& sub) {
                return sub.name == subscription;
            });
            if (it != subscriptions.end()) {
                // Accumulate the price of each subscription in the combination
                totalCost += it->prices[day];
            }
        }
        // Check if the total cost is within the budget
        if (totalCost <= budget) {
            combinations.push_back(currentCombination);
        }
        return;
    }
    // Iterate over each subscription and try adding it to the current combination
    for (size_t i = 0; i < subscriptions.size(); ++i) {
        currentCombination.push_back(subscriptions[i].name);
        calculateSubscriptions(subscriptions, budget, combinations, currentCombination, day + 1);
        currentCombination.pop_back();
    }
}

int main() {
    std::vector<NewspaperSubscription> subscriptions = {
        {"TOI", {3, 3, 3, 3, 3, 5, 6}},
        {"Hindu", {2, 2, 2, 2, 2, 4, 4}},
        {"ET", {4, 4, 4, 4, 4, 4, 10}},
        {"BM", {1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5}},
        {"HT", {2, 2, 2, 2, 2, 4, 4}}
    };

    int budget;
    std::cout << "Enter the weekly budget: ";
    std::cin >> budget;

    std::vector<std::vector<std::string>> combinations;
    std::vector<std::string> currentCombination;

    calculateSubscriptions(subscriptions, budget, combinations, currentCombination);

    // Display the possible combinations
    std::cout << "Possible combinations of subscriptions within the budget:" << std::endl;
    for (const auto& combination : combinations) {
        double totalCost = 0.0;
        for (const auto& subscription : combination) {
            std::cout << subscription << " ";
            // Find the subscription by name
            auto it = std::find_if(subscriptions.begin(), subscriptions.end(), [&](const NewspaperSubscription& sub) {
                return sub.name == subscription;
            });
            if (it != subscriptions.end()) {
                // Accumulate the price of each subscription in the combination
                totalCost += it->prices[0]; // Assuming day 0 price is considered for the total cost
            }
        }
        if (totalCost <= budget) {
            std::cout << std::endl;
        } else {
            std::cout << "(Exceeds budget)" << std::endl;
        }
    }

    return 0;
}
