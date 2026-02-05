#include "iostream"
#include "Classes.h"

using namespace std;

void Menu();
bool isValidCustomerId(int id);
customers* IncreaseCustomers(customers* CustomerArray, int& size);
customers* DecreaseCustomers(customers* CustomerArray, int& size);
Subscription* IncreaseSubscription(Subscription* SubscriptionArray, int& NoOfSubscriptions);

int main(int argc, char const* argv[]) {
    int NoOfHalls = 0;
    int TempHallID = 0;
    int choice = 0;
    int NoOfCustomers = 1;
    int NoOfSubscriptions = 1;
    int TempCustomerID = 0;
    int TempTrainerID = 0;
    bool FirstCustomer = true;
    customers* CustomerArray = new customers[NoOfCustomers];
    Subscription* SubscriptionArray = new Subscription[NoOfSubscriptions];
HALLERROR:
    std::cout << "How Many Halls Your GYM Have? ";
    std::cin >> NoOfHalls;
    if (NoOfHalls <= 0) {
        system("cls");
        std::cerr << "ERROR:Invalid Input!" << '\n';
        goto HALLERROR;
    }
    GYMHall* GYMArray = new GYMHall[NoOfHalls];
    for (size_t index = 0; index < NoOfHalls; index++) {
        std::cout << "Enter Information about Hall No. " << index + 1 << ':' << '\n';
        GYMArray[index].Input();
    }
    system("cls");
menu:
    Menu();
    while (!(std::cin >> choice)) {
        std::cerr << "ERROR: Wrong Input!" << '\n';
        std::cout << "Choose Again: ";
        std::cin.clear();
        std::cin.ignore(1024, '\n');
    }
    switch (choice) {
    case 1:
        if (!FirstCustomer) {
            goto DONTSKIP;
        }
        else {
            goto SKIP;
        }
    DONTSKIP:
        CustomerArray = IncreaseCustomers(CustomerArray, NoOfCustomers);
        SubscriptionArray = IncreaseSubscription(SubscriptionArray, NoOfSubscriptions);
    SKIP:
        CustomerArray[NoOfCustomers - 1].Input();
        std::cout << "Customer Added Successfully!" << '\n';
        FirstCustomer = false;
    LOOP:
        for (size_t index = 0; index < NoOfHalls; index++) {
            CustomerArray[NoOfCustomers - 1].setAssignedTrainerID(GYMArray[index].getTrainerId(CustomerArray[NoOfCustomers - 1].getCustomerStartTime()));
            if (!CustomerArray[NoOfCustomers - 1].getAssignedTrainerID()) {
                continue;
            }
            else {
                break;
            }
        }
        if (!CustomerArray[NoOfCustomers - 1].getAssignedTrainerID()) {
            std::cout << "Trainer not available at this time! Choose another time:" << '\n';
            CustomerArray[NoOfCustomers - 1].Input_Time();
            goto LOOP;
        }
        else {
            std::cout << "Trainer Assigned to this customer is: " << CustomerArray[NoOfCustomers - 1].getAssignedTrainerID() << '\n';
        }
        SubscriptionArray[NoOfSubscriptions - 1].setID();
        SubscriptionArray[NoOfSubscriptions - 1].setCustomerID(CustomerArray[NoOfSubscriptions - 1].getID());
        SubscriptionArray[NoOfSubscriptions - 1].setTrainerID(CustomerArray[NoOfSubscriptions - 1].getAssignedTrainerID());
        TempTrainerID = CustomerArray[NoOfSubscriptions - 1].getAssignedTrainerID();
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getTrainerExcerciseID(TempTrainerID)) {
                SubscriptionArray[NoOfSubscriptions - 1].setExerciseID(GYMArray[index].getTrainerExcerciseID(TempTrainerID));
                system("cls");
                goto menu;
            }
        }
        goto menu;
    case 2:
        std::cout << "Enter the customer ID to edit : " << '\n';
        std::cin >> TempCustomerID;
        for (size_t index = 0; index < NoOfCustomers; index++) {
            if (CustomerArray[index].getID() == TempCustomerID) {
                CustomerArray[index].Input();
                system("cls");
                std::cout << "Customer Edited Successfully!" << '\n';
                goto menu;
            }
        }
        std::cerr << "Error: Id does not exist!" << '\n';
        goto menu;
    case 3:
        std::cout << "Enter the customer ID to delete : " << '\n';
        std::cin >> TempCustomerID;
        for (size_t index = 0; index < NoOfCustomers; index++) {
            if (CustomerArray[index].getID() == TempCustomerID) {
                for (size_t index2 = index; index2 < NoOfCustomers - 1; index2++) {
                    CustomerArray[index2] = CustomerArray[index2 + 1];
                }
                DecreaseCustomers(CustomerArray, NoOfCustomers);
                system("cls");
                std::cout << "Customer Deleted Successfully!" << '\n';
                goto menu;
            }
        }
        std::cerr << "Error: Id does not exist!" << '\n';
        goto menu;
    case 4:
        std::cout << "Enter Hall ID to Edit: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                GYMArray[index].Input();
                system("cls");
                std::cout << "Hall Edited Successfully!" << '\n';
                goto menu;
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does not Match Any Hall!" << '\n';
        goto menu;
    case 5:
        std::cout << "Enter Hall ID in which you want to Add Trainer: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                GYMArray[index].AddTrainer();
                system("cls");
                std::cout << "Trainer Added Successfully!" << '\n';
                goto menu;
            }
        }
        system("cls");
        std::cerr << "ERROR: ID does Not Match Any Hall!" << '\n';
        goto menu;
    case 6:
        std::cout << "Enter Hall ID in which you want to Edit Trainer: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                if (GYMArray[index].EditTrainer()) {
                    system("cls");
                    std::cout << "Trainer Edited Successfully!" << '\n';
                    goto menu;
                }
                else {
                    system("cls");
                    std::cerr << "ERROR: ID Does Not Match Any Trainer!" << '\n';
                    goto menu;
                }
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does Not Match Any Hall!" << '\n';
        goto menu;
    case 7:
        std::cout << "Enter Hall ID in which you want to Delete Trainer: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                if (GYMArray[index].DeleteTrainer()) {
                    system("cls");
                    std::cout << "Trainer Deleted Successfully!" << '\n';
                    goto menu;
                }
                else {
                    system("cls");
                    std::cerr << "ERROR: ID Does Not Match Any Trainer!" << '\n';
                    goto menu;
                }
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does Not Match Any Hall!" << '\n';
        goto menu;
    case 8:
        std::cout << "Enter Hall ID in which you want to Add Equipment: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                GYMArray[index].AddEquipment();
                system("cls");
                std::cout << "Equipment Added Successfully!" << '\n';
                goto menu;
            }
        }
        system("cls");
        std::cerr << "ERROR: ID does Not Match Any Hall!" << '\n';
        goto menu;
    case 9:
        std::cout << "Enter Hall ID in which you want to Edit Equipment: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                if (GYMArray[index].EditEquipment()) {
                    system("cls");
                    std::cout << "Equipment Edited Successfully!" << '\n';
                    goto menu;
                }
                else {
                    system("cls");
                    std::cerr << "ERROR: ID Does Not Match Any Equipment!" << '\n';
                    goto menu;
                }
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does Not Match Any Hall!" << '\n';
        goto menu;
    case 10:
        std::cout << "Enter Hall ID in which you want to Delete Equipment: ";
        std::cin >> TempHallID;
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].getID() == TempHallID) {
                if (GYMArray[index].DeleteEquipment()) {
                    system("cls");
                    std::cout << "Equipment Deleted Successfully!" << '\n';
                    goto menu;
                }
                else {
                    system("cls");
                    std::cerr << "ERROR: ID Does Not Match Any Equipment!" << '\n';
                    goto menu;
                }
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does Not Match Any Hall!" << '\n';
        goto menu;
    case 11:
        for (size_t index = 0; index < NoOfHalls; index++) {
            GYMArray[index].SaveTrainerPlans();
        }
        system("cls");
        std::cout << "Excercise Plan Data Saved in ExcercisePlans.txt" << '\n';
        goto menu;
    case 12:
        for (size_t index = 0; index < NoOfHalls; index++) {
            GYMArray[index].SaveTrainerData();
        }
        system("cls");
        std::cout << "Trainer Data Saved in Trainers.txt" << '\n';
        goto menu;
    case 13:
        for (size_t index = 0; index < NoOfHalls; index++) {
            GYMArray[index].SaveEquipmentData();
        }
        system("cls");
        std::cout << "Equipment Data Saved in Equipments.txt" << '\n';
        goto menu;
    case 14:
        for (size_t index = 0; index < NoOfCustomers; index++) {
            CustomerArray[index].SaveCustomerData();
        }
        system("cls");
        std::cout << "Customer Data saved in Customers.txt" << '\n';
        goto menu;
    case 15:
        for (size_t index = 0; index < NoOfCustomers; index++) {
            SubscriptionArray[index].SaveSubscriptionsData();
        }
        system("cls");
        std::cout << "Subscription Data is saved in Subscriptions.txt" << '\n';
        goto menu;
    case 16:
        system("cls");
        for (size_t index = 0; index < NoOfCustomers; index++) {
            CustomerArray[index].Output();
        }
        goto menu;
    case 17:
        system("cls");
        for (size_t index = 0; index < NoOfHalls; index++) {
            GYMArray[index].Output();
        }
        goto menu;
    case 18:
        system("cls");
        for (size_t index = 0; index < NoOfHalls; index++) {
            std::cout << "Schedule of Hall " << GYMArray[index].getID() << '\n';
            GYMArray[index].DisplayHallSchedule();
        }
        goto menu;
    case 19:
        std::cout << "Enter Trainer ID for Schedule" << '\n';
        std::cin >> TempTrainerID;
        system("cls");
        for (size_t index = 0; index < NoOfHalls; index++) {
            if (GYMArray[index].DisplayTrainerSchedule(TempTrainerID)) {
                goto menu;
            }
        }
        system("cls");
        std::cerr << "ERROR: ID Does Not Match Any Trainer!" << '\n';
        goto menu;
    case 20:
        system("cls");
        for (size_t index = 0; index < NoOfSubscriptions; index++) {
            std::cout << "Subscription ID: " << SubscriptionArray[index].getID() << "\n";
            std::cout << "Customer ID: " << SubscriptionArray[index].getCustomerID() << "\n";
            std::cout << "Trainer ID: " << SubscriptionArray[index].getTrainerID() << "\n";
            std::cout << "Exercise ID: " << SubscriptionArray[index].getExerciseID() <<'\n';
            std::cout << "Date:  " << SubscriptionArray[index].getDay() << "/" << SubscriptionArray[index].getMonth() << "/" << SubscriptionArray[index].getyear() << "\n";

        }
        goto menu;
    case 21:
    system("cls");
    for (size_t index = 0; index < NoOfHalls; index++) {
      GYMArray[index].DisplayTrainerPlans();
    }
    goto menu;
    case 0:
        system("cls");
        std::cout << "Thanks For using!" << '\n';
        break;
    default:
        system("cls");
        std::cerr << "ERROR: Invalid Choice!" << '\n';
        goto menu;
    }
    delete[] GYMArray;
    delete[] CustomerArray;
    return EXIT_SUCCESS;
}

void Menu() {
    std::cout << "Choose the option : " << '\n';
    std::cout << "1.  Add Customer" << '\n';
    std::cout << "2.  Edit Customer" << '\n';
    std::cout << "3.  Delete Customer" << '\n';
    std::cout << "4.  Edit Hall " << '\n';
    std::cout << "5.  Add Trainer" << '\n';
    std::cout << "6.  Edit Trainer" << '\n';
    std::cout << "7.  Delete Trainer" << '\n';
    std::cout << "8.  Add Equipment" << '\n';
    std::cout << "9.  Edit Equipment" << '\n';
    std::cout << "10. Delete Equipment" << '\n';
    std::cout << "11. Save Excercise Plans" << '\n';
    std::cout << "12. Save Trainers Data" << '\n';
    std::cout << "13. Save Equipment Data" << '\n';
    std::cout << "14. Save Customer Data" << '\n';
    std::cout << "15. Save Subsciption Data" << '\n';
    std::cout << "16. Display Customer Data" << '\n';
    std::cout << "17. Display Hall Data" << '\n';
    std::cout << "18. Display Hall Schedule" << '\n';
    std::cout << "19. Display Trainer Schedule" << '\n';
    std::cout << "20. Display Subscription Data" << '\n';
    std::cout << "21. Display Excercise Plans" << '\n';
    std::cout << "0. Exit" << '\n';
}

customers* IncreaseCustomers(customers* CustomerArray, int& size) {
    customers* TempCustomerArray = new customers[size];
    for (size_t index = 0; index < size; index++) {
        TempCustomerArray[index] = CustomerArray[index];
    }
    delete[] CustomerArray;
    CustomerArray = new customers[size + 1];
    for (size_t index = 0; index < size; index++) {
        CustomerArray[index] = TempCustomerArray[index];
    }
    delete[] TempCustomerArray;
    size++;
    return CustomerArray;
}

customers* DecreaseCustomers(customers* CustomerArray, int& size) {
    customers* TempCustomerArray = new customers[size];
    for (size_t index = 0; index < size; index++) {
        TempCustomerArray[index] = CustomerArray[index];
    }
    delete[] CustomerArray;
    if (size - 1 == 0) {
        CustomerArray = new customers[size];
        delete[] TempCustomerArray;
        return CustomerArray;
    }
    CustomerArray = new customers[--size];
    for (size_t index = 0; index < size; index++) {
        CustomerArray[index] = TempCustomerArray[index];
    }
    delete[] TempCustomerArray;
    return CustomerArray;
}

Subscription* IncreaseSubscription(Subscription* SubscriptionArray, int& NoOfSubscriptions) {
    Subscription* TempSubscriptionArray = new Subscription[NoOfSubscriptions];
    for (size_t index = 0; index < NoOfSubscriptions; index++) {
        TempSubscriptionArray[index] = SubscriptionArray[index];
    }
    delete[] SubscriptionArray;
    SubscriptionArray = new Subscription[NoOfSubscriptions + 1];
    for (size_t index = 0; index < NoOfSubscriptions; index++) {
        SubscriptionArray[index] = TempSubscriptionArray[index];
    }
    delete[] TempSubscriptionArray;
    NoOfSubscriptions++;
    return SubscriptionArray;
}
