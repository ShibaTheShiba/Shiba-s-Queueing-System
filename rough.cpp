#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct FoodOrder {
    string name;
    string status;
};

class KitchenQueueSystem {
private:
    vector<FoodOrder> queue;

public:
    void displayMenu() const {
        cout << "\nMain Menu\n\n";
        cout << "1 - Order\n";
        cout << "2 - Update Order\n";
        cout << "3 - Check Queue\n";
        cout << "4 - Delete Order\n";
        cout << "5 - Exit\n\n";
    }

    void displayFoodMenu() const {
        cout << "\nFood Menu\n\n";
        cout << "C1 - Chicken Curry\n";
        cout << "C2 - Carbonara\n";
        cout << "C3 - Margherita Pizza\n";
        cout << "CS1 - Caesar Salad\n";
        cout << "L1 - Lasagna\n";
        cout << "L2 - Lasagna w/ Chicken\n\n";
    }

    void addToQueue(const string& foodName) {
        FoodOrder newOrder;
        newOrder.name = foodName;
        newOrder.status = "Pending";
        queue.push_back(newOrder);
        cout << "\nThe order is added to the queue.\n";
    }

    void updateOrderStatus(int orderIndex, const string& newStatus) {
        if (orderIndex >= 1 && static_cast<size_t>(orderIndex - 1) < queue.size()) {
            queue[static_cast<size_t>(orderIndex - 1)].status = newStatus;
            cout << "Order status updated.\n";
        }
        else {
            cout << "Invalid order index. Order status update denied.\n";
        }
    }

    void deleteOrder(int orderIndex) {
        if (orderIndex >= 1 && static_cast<size_t>(orderIndex - 1) < queue.size()) {
            queue.erase(queue.begin() + orderIndex - 1);
            cout << "Order deleted from the queue.\n";
        }
        else {
            cout << "Invalid order index. Deletion denied.\n";
        }
    }

    vector<FoodOrder> displayQueue() const {
        return queue;
    }

private:
    bool isValidFoodCode(const string& code) const {
        return !code.empty();
    }
};

int main() {

    cout << "================= SHIBA KITCHEN QUEUEING SYSTEM =================\n\n";

    KitchenQueueSystem kitchen;
    int choice;
    string userInput;

    do {
        kitchen.displayMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            kitchen.displayFoodMenu();
            cout << "\nPlace orders (enter 'done' to finish):\n\n";
            cin.ignore();
            while (true) {
                cout << "\nEnter food code (e.g., C1) or 'done' to finish: ";
                getline(cin, userInput);

                if (userInput == "done") {
                    break;
                }

                kitchen.addToQueue(userInput);
            }
            break;

        case 2:
            if (!kitchen.displayQueue().empty()) {
                int orderIndex;
                string newStatus;

                cout << "Enter the order index to update (1-" << kitchen.displayQueue().size() << "): ";
                cin >> orderIndex;
                cin.ignore();
                cout << "Enter the new status: ";
                getline(cin, newStatus);

                kitchen.updateOrderStatus(orderIndex, newStatus);
            }
            else {
                cout << "No orders in the queue to update.\n";
            }
            break;

        case 3:
        {
            int orderNumber = 1;
            cout << "\nCurrent Queue:\n";
            for (const auto& order : kitchen.displayQueue()) {
                cout << orderNumber << ". Food: " << order.name << ", Status: " << order.status << "\n";
                orderNumber++;
            }
            break;
        }

        case 4:
            if (!kitchen.displayQueue().empty()) {
                int orderIndex;
                cout << "Enter the order index to delete (1-" << kitchen.displayQueue().size() << "): ";
                cin >> orderIndex;

                kitchen.deleteOrder(orderIndex);
            }
            else {
                cout << "No orders in the queue to delete.\n";
            }
            break;

        case 5:
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            break;
        }

    } while (choice != 5);

    return 0;
}