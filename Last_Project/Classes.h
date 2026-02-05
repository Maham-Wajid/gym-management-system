#pragma warning(disable : 4996)
#include "iostream"
#include "string"
#include "ctime"
#include "fstream"

class GYM {
protected:
    std::string Name;
    int ID;
 
public:
    GYM();
    void setName(std::string);
    std::string getName();
    int getID();
    bool isValidName(std::string);
    virtual void Input();
    virtual void Output();
};


GYM::GYM() {
    Name = "NULL";
    ID = 0;
}

void GYM::setName(std::string iName) {
    Name = iName;
}

std::string GYM::getName() {
    return Name;
}

int GYM::getID() {
    return ID;
}

bool GYM::isValidName(std::string Name) {
    for (size_t index = 0; index < Name.length(); index++) {
        if (!isalpha(Name[index]) && !isblank(Name[index])) {
            return false;
        }
    }
    return true;
}

void GYM::Input() {
NAMEERROR:
    std::cout << "Enter Name: ";
    fflush(stdin);
    std::cin.ignore();
    getline(std::cin, Name);
    if (!isValidName(Name)) {
        std::cerr << "ERROR: Invalid Name!" << '\n';
        goto NAMEERROR;
    }
    std::cout << "Enter ID: ";
    while (!(std::cin >> ID)) {
        std::cerr << "ERROR: Wrong Input!" << '\n';
        std::cout << "Enter ID: ";
        std::cin.clear();
        std::cin.ignore(1024, '\n');
    }
}

void GYM::Output() {
    std::cout << "Name: " << Name << '\n';
    std::cout << "ID: " << ID << '\n';
}

class customers : public GYM {
private:
    std::string Address;
    std::string Phone;
    std::string Email;
    int CustomerStartTime;
    int Assigned_Trainer_Id;

public:
    customers();
    void Input();
    void Output();
    void AddCustomers();
    void EditCustomers();
    void deleteCustomers();
    bool isValidPhone(std::string);
    int getCustomerStartTime();
    void setAssignedTrainerID(int);
    void Input_Time();
    int getAssignedTrainerID();
    void SaveCustomerData();
};

customers::customers() :GYM() {
    Address = "NULL";
    Phone = "NULL";
    Email = "NULL";
    CustomerStartTime = 0;
}

void customers::Input() {
    GYM::Input();
    std::cout << "Enter Address: ";
    std::cin >> Address;
PHONEERROR:
    std::cout << "Enter Phone: ";
    std::cin >> Phone;
    if (!isValidPhone(Phone)) {
        std::cerr << "ERROR: Invalid Phone Number!" << '\n';
        goto PHONEERROR;
    }
    std::cout << "Enter Email: ";
    std::cin >> Email;
TIMEERROR:
    std::cout << "Enter your Starting Time(hour): ";
    std::cin >> CustomerStartTime;
    if (!(CustomerStartTime >= 0 && CustomerStartTime <= 24)) {
        std::cerr << "Error: Invalid Time! " << '\n';
        system("cls");
        goto TIMEERROR;
    }
}

void customers::Output() {
    GYM::Output();
    std::cout << "Address: " << Address << '\n';
    std::cout << "Phone: " << Phone << '\n';
    std::cout << "Email: " << Email << '\n';
}

void customers::Input_Time() {
    std::cout << "Enter your Starting Time (hour): ";
    std::cin >> CustomerStartTime;
}

int customers::getCustomerStartTime() {
    return CustomerStartTime;
}

void customers::setAssignedTrainerID(int Id) {
    Assigned_Trainer_Id = Id;
}

int customers::getAssignedTrainerID() {
    return Assigned_Trainer_Id;
}

bool customers::isValidPhone(std::string Phone) {
    if (Phone.length() > 11 || Phone.length() < 11) {
        return false;
    }
    for (size_t index = 0; index < Phone.length(); index++) {
        if (!isdigit(Phone[index])) {
            return false;
        }
    }
    return true;
}

void customers::SaveCustomerData() {
    std::ofstream save;
    save.open("Customers.txt", std::ios::app);
    save << ID << '\t' << Name << '\t' << Address << '\t' << Phone << '\t' << Email << '\n';
    save.close();
}


class ExcercisePlans {
public:
    ExcercisePlans();
    void Input();
    void Output();
    void setPlanID();
    void setTrainerID(int);
    void setEquipmentID(int);
    void setDuration(int);
    int getPlanID();
    int getTrainerID();
    int getEquipmentID();
    int getDuration();
    void SaveExercisePlanData();

private:
    int ID;
    int TrainerID;
    int EquipmentID;
    int Duration;
    static int StaticID;
};

int ExcercisePlans::StaticID = 0;

ExcercisePlans::ExcercisePlans() {
  ID = 0;
  TrainerID = 0;
  EquipmentID = 0;
  Duration = 0;
}

void ExcercisePlans::setPlanID(){
  ID = ++StaticID;
}
void ExcercisePlans::setTrainerID(int TrainID){
  TrainerID = TrainID;
}
void ExcercisePlans::setEquipmentID(int EquipID){
  EquipmentID = EquipID;
}
void ExcercisePlans::setDuration(int Dur){
  Duration = Dur;
}
int ExcercisePlans::getPlanID(){
  return ID;
}
int ExcercisePlans::getTrainerID(){
  return TrainerID;
}
int ExcercisePlans::getEquipmentID(){
  return EquipmentID;
}
int ExcercisePlans::getDuration(){
  return Duration;
}

void ExcercisePlans::Input() {
  std::cout << "Enter Equipment ID: ";
  std::cin >> EquipmentID;
  std::cout << "Enter Duration: ";
  std::cin >> Duration;
}

void ExcercisePlans::Output() {
  std::cout << "Plan ID: " << ID << '\n';
  std::cout << "Trainer ID: " << TrainerID << '\n';
  std::cout << "Equipment ID: " << EquipmentID << '\n';
  std::cout << "Duration: " << Duration << '\n';
}

void ExcercisePlans::SaveExercisePlanData() {
  std::ofstream save;
  save.open("ExcercisePlans.txt", std::ios::app);
  save << getPlanID() << '\t' << getTrainerID() << '\t' << '\t' << getEquipmentID() << '\t' << '\t' << getDuration() << '\n';
  save.close();
}

class Trainers : public GYM {
private:
    int StartTime;
    int EndTime;
    int NoOfCustomersAssigned;
    ExcercisePlans Plan;
public:
    int getStartTime();
    int getEndTime();
    void Input();
    int WhichTrainerAvailable(int);
    void InputPlan(int EquipmentID, int Duration);
    void ShowPlan();
    void SavePlans();
    int getExerciseID();
    Trainers();
};

Trainers::Trainers() :GYM() {
    StartTime = 0;
    EndTime = 0;
    NoOfCustomersAssigned = 0;
}

void Trainers::Input() {
    GYM::Input();
SHIFTERROR:
    std::cout << "Enter The Starting time(Hour) of the shift: ";
    std::cin >> StartTime;
    std::cout << "Enter The Ending time(Hour) of the shift: ";
    std::cin >> EndTime;
    if ((StartTime >= 0 && StartTime <= 24) && (EndTime >= 0 && EndTime <= 24)) {
        if (EndTime - StartTime != 8) {
            system("cls"); 
            std::cerr << "Trainer\'s shift must be of 8 hours!" << '\n';
            goto SHIFTERROR;
        }
    }
    else {
        system("cls");
        std::cerr << "ERROR: Invalid Time!" << '\n';
        goto SHIFTERROR;
    }
}

int Trainers::WhichTrainerAvailable(int CustomerStartTime) {
    if ((CustomerStartTime >= StartTime) && (CustomerStartTime < EndTime) && NoOfCustomersAssigned < 3) {
        NoOfCustomersAssigned++;
        return ID;
    }
    else {
        return 0;
    }
}

int Trainers::getStartTime() {
    return StartTime;
}

int Trainers::getEndTime() {
    return EndTime;
}

void Trainers::InputPlan(int EquipmentID, int Duration) {
  Plan.setTrainerID(ID);
  Plan.setPlanID();
  Plan.setEquipmentID(EquipmentID);
  Plan.setDuration(Duration);
}

void Trainers::ShowPlan(){
  Plan.Output();
}

void Trainers::SavePlans() {
  Plan.SaveExercisePlanData();
}

int Trainers::getExerciseID() {
    return Plan.getPlanID();
}

class Equipments : public GYM {
private:
public:
    Equipments();
    void Input();
};


Equipments::Equipments() :GYM() {}

void Equipments::Input() {
    GYM::Input();
}


Trainers* IncreaseTrainers(Trainers* TrainerArray, int& NoOfTrainers);
Trainers* DecreaseTrainers(Trainers* TrainerArray, int& NoOfTrainers);
Equipments* IncreaseEquipments(Equipments* EquipmentArray, int& NoOfEquipments);
Equipments* DecreaseEquipments(Equipments* EquipmentArray, int& NoOfEquipments);

class GYMHall : public GYM {
private:
    Equipments* EquipmentArray;
    Trainers* TrainerArray;
    int NoOfEquipments;
    int NoOfTrainers;
    int OpeningHour;
    int ClosingHour;

public:
    GYMHall();
    void Input();
    void AddTrainer();
    bool EditTrainer();
    bool DeleteTrainer();
    void AddEquipment();
    bool EditEquipment();
    bool DeleteEquipment();
    void DisplayHallSchedule();
    bool DisplayTrainerSchedule(int);
    void DisplayTrainerPlans();
    void Output();
    int getTrainerId(int);
    void SaveTrainerData();
    void SaveEquipmentData();
    void SaveTrainerPlans();
    int getTrainerExcerciseID(int);
    ~GYMHall();
};

GYMHall::GYMHall() : GYM() {
    NoOfEquipments = 0;
    NoOfTrainers = 0;
    EquipmentArray = NULL;
    TrainerArray = NULL;
    OpeningHour = 0;
    ClosingHour = 0;
}

void GYMHall::Input() {
    int TempEquipmentID = 0;
    GYM::Input();
HALLTIMEERROR:
    std::cout << "Enter Opening Hour of this Hall: ";
    std::cin >> OpeningHour;
    std::cout << "Enter Closing Hour of this Hall: ";
    std::cin >> ClosingHour;
    if ((OpeningHour >= 0 && OpeningHour <= 24) && (ClosingHour >= 0 && ClosingHour <= 24)) {
        if (ClosingHour - OpeningHour != 12) {
            system("cls");
            std::cerr << "ERROR: Hall must be opened for 12 hours!" << '\n';
            goto HALLTIMEERROR;
        }
    }
    else {
        system("cls");
        std::cerr << "ERROR: Invalid Time!" << '\n';
        goto HALLTIMEERROR;
    }
EQUIPMENTERROR:
    std::cout << "Enter Number of Equipments for this Hall: ";
    std::cin >> NoOfEquipments;
    if (NoOfEquipments <= 0) {
        system("cls");
        std::cerr << "ERROR: Invalid Input!" << '\n';
        goto EQUIPMENTERROR;
    }
    EquipmentArray = new Equipments[NoOfEquipments];
    for (size_t index = 0; index < NoOfEquipments; index++) {
        std::cout << "Enter Information about Equipment " << index + 1 << ':' << '\n';
        EquipmentArray[index].Input();
    }
TRAINERERROR:
    std::cout << "Enter Number of Trainers for this Hall: ";
    std::cin >> NoOfTrainers;
    if (NoOfTrainers <= 0) {
        system("cls");
        std::cerr << "ERROR: Invalid Input!" << '\n';
        goto TRAINERERROR;
    }
    TrainerArray = new Trainers[NoOfTrainers];
    for (size_t index = 0; index < NoOfTrainers; index++) {
        std::cout << "Enter Information about Trainer " << index + 1 << ':' << '\n';
        TrainerArray[index].Input();
        std::cout << "Enter Duration of Plan: " ;
        int Duration = 0;
        std::cin >> Duration;
        PLANERROR:
        std::cout << "Enter Equipment ID for Plan: ";
        std::cin >> TempEquipmentID;
        for (size_t index2 = 0; index2 < NoOfEquipments; index2++) {
          if (EquipmentArray[index2].getID() == TempEquipmentID) {
            TrainerArray[index].InputPlan(TempEquipmentID, Duration);
            TempEquipmentID = 0;
            break;
          }
        }
        if (TempEquipmentID) {
          system("cls");
          std::cerr << "ERROR: No ID Matches any Equipment!" << '\n';
          goto PLANERROR;
        }
    }
}

void GYMHall::AddTrainer() {
    int TempEquipmentID = 0;
    TrainerArray = IncreaseTrainers(TrainerArray, NoOfTrainers);
    TrainerArray[NoOfTrainers - 1].Input();
    std::cout << "Enter Duration of Plan: " ;
    int Duration = 0;
    std::cin >> Duration;
    PLANERROR:
    std::cout << "Enter Equipment ID for Plan: ";
    std::cin >> TempEquipmentID;
    for (size_t index2 = 0; index2 < NoOfEquipments; index2++) {
      if (EquipmentArray[index2].getID() == TempEquipmentID) {
        TrainerArray[NoOfTrainers - 1].InputPlan(TempEquipmentID, Duration);
        TempEquipmentID = 0;
        break;
      }
    }
    if (TempEquipmentID) {
      system("cls");
      std::cerr << "ERROR: No ID MAtches any Equipment!" << '\n';
      goto PLANERROR;
    }
}

bool GYMHall::EditTrainer() {
    int TempTrainerID = 0;
    std::cout << "Enter Trainer ID to Edit: ";
    std::cin >> TempTrainerID;
    for (size_t index = 0; index < NoOfTrainers; index++) {
        if (TrainerArray[index].getID() == TempTrainerID) {
            TrainerArray[index].Input();
            return true;
        }
    }
    return false;
}

bool GYMHall::DeleteTrainer() {
    int TempTrainerID = 0;
    std::cout << "Enter Trainer ID to Delete: ";
    std::cin >> TempTrainerID;
    for (size_t index = 0; index < NoOfTrainers; index++) {
        if (TrainerArray[index].getID() == TempTrainerID) {
            for (size_t index2 = index; index2 < NoOfTrainers - 1; index2++) {
                TrainerArray[index2] = TrainerArray[index2 + 1];
            }
            TrainerArray = DecreaseTrainers(TrainerArray, NoOfTrainers);
            return true;
        }
    }
    return false;
}

int GYMHall::getTrainerId(int CustomerStartTime) {
    for (size_t index = 0; index < NoOfTrainers; index++) {
        int TempID = TrainerArray[index].WhichTrainerAvailable(CustomerStartTime);
        if (TempID == 0) {
            if (index == NoOfTrainers - 1) {
                return 0;
            }
            continue;
        }
        else  
            return TempID;
    }
    return 0;
}
//Function that return Trainer's Excercise ID
int GYMHall::getTrainerExcerciseID(int TrainerID) {
    for (size_t index = 0; index < NoOfTrainers; index++) {
        if (TrainerArray[index].getID() == TrainerID) {
            return TrainerArray[index].getExerciseID();
        }
    }
    return 0;
}
void GYMHall::AddEquipment() {
    EquipmentArray = IncreaseEquipments(EquipmentArray, NoOfEquipments);
    EquipmentArray[NoOfEquipments - 1].Input();
}

bool GYMHall::EditEquipment() {
    int TempEquipmentID = 0;
    std::cout << "Enter Equipment ID to Edit: ";
    std::cin >> TempEquipmentID;
    for (size_t index = 0; index < NoOfEquipments; index++) {
        if (EquipmentArray[index].getID() == TempEquipmentID) {
            EquipmentArray[index].Input();
            return true;
        }
    }
    return false;
}

bool GYMHall::DeleteEquipment() {
    int TempEquipmentID = 0;
    std::cout << "Enter Equipment ID to Delete: ";
    std::cin >> TempEquipmentID;
    for (size_t index = 0; index < NoOfEquipments; index++) {
        if (EquipmentArray[index].getID() == TempEquipmentID) {
            for (size_t index2 = index; index2 < NoOfEquipments - 1; index2++) {
                EquipmentArray[index2] = EquipmentArray[index2 + 1];
            }
            EquipmentArray = DecreaseEquipments(EquipmentArray, NoOfEquipments);
            return true;
        }
    }
    return false;
}

void GYMHall::Output() {
    GYM::Output();
    std::cout << "Trainer Data in this Hall: " << '\n';
    for (size_t index = 0; index < NoOfTrainers; index++) {
        TrainerArray[index].Output();
    }
    std::cout << "Equipment Data in this Hall: " << '\n';
    for (size_t index = 0; index < NoOfEquipments; index++) {
        EquipmentArray[index].Output();
    }
}

void GYMHall::DisplayHallSchedule() {
    std::cout << "Hall opens at: " << OpeningHour << ":00" << '\n';
    std::cout << "Hall closes at: " << ClosingHour << ":00" << '\n';
}

bool GYMHall::DisplayTrainerSchedule(int TempID) {
    for (size_t index = 0; index < NoOfTrainers; index++) {
        if (TrainerArray[index].getID() == TempID) {
            std::cout << "Trainer available between " << TrainerArray[index].getStartTime() << ":00 and " << TrainerArray[index].getEndTime() << ":00" << '\n';
            return true;
        }
    }
    return false;
}

void GYMHall::SaveTrainerData() {
    std::ofstream save;
    save.open("Trainers.txt", std::ios::app);
    for (size_t index = 0; index < NoOfTrainers; index++) {
        save << TrainerArray[index].getID() << '\t' << TrainerArray[index].getName() << '\n';
    }
    save.close();
}

void GYMHall::SaveEquipmentData() {
    std::ofstream save;
    save.open("Equipments.txt", std::ios::app);
    for (size_t index = 0; index < NoOfEquipments; index++) {
        save << EquipmentArray[index].getID() << '\t' << EquipmentArray[index].getName() << '\n';
    }
    save.close();
}

void GYMHall::SaveTrainerPlans() {
  for (size_t index = 0; index < NoOfTrainers; index++) {
    TrainerArray[index].SavePlans();
  }
}

void GYMHall::DisplayTrainerPlans() {
  for (size_t index = 0; index < NoOfTrainers; index++) {
    TrainerArray[index].ShowPlan();
  }
}

GYMHall::~GYMHall() {
    delete[] EquipmentArray;
    delete[] TrainerArray;
}

class Subscription {
public:
    Subscription();
    int getyear();
    int getMonth();
    int getDay();
    void setID();
    int getID();
    void setCustomerID(int id);
    void setTrainerID(int id);
    void setExerciseID(int id);
    int getCustomerID();
    int getTrainerID();
    int getExerciseID();
    void SaveSubscriptionsData();
private:
    time_t now = time(0);
    tm* CustomerTime = localtime(&now);
    int CustomerID;
    int TrainerID;
    int ExerciseID;
    static int ID;
    int id;
};

int Subscription::ID = 1;

Subscription::Subscription() {
    CustomerID = 0;
    TrainerID = 0;
    ExerciseID = 0;
    id = 0;
}

int Subscription::getyear() {
    return 1900 + CustomerTime->tm_year;
}

int Subscription::getMonth() {
    return 1 + CustomerTime->tm_mon;
}

int Subscription::getDay() {
    return CustomerTime->tm_mday;
}

int Subscription::getID() {
    return id;
}

void Subscription::setCustomerID(int id) {
    CustomerID = id;
}

void Subscription::setTrainerID(int id) {
    TrainerID = id;
}

void Subscription::setExerciseID(int id) {
    ExerciseID = id;
}

int Subscription::getCustomerID() {
    return CustomerID;
}

int Subscription::getTrainerID() {
    return TrainerID;
}

int Subscription::getExerciseID() {
    return ExerciseID;
}

void Subscription::setID() {
    id = ID++;
}

void Subscription::SaveSubscriptionsData() {
    std::ofstream save;
    save.open("Subscriptions.txt", std::ios::app);
    save << id << '\t' << getDay() << '/' << getMonth() << '/' << getyear() << '\t' << '\t' << getCustomerID() << '\t' << '\t' << getTrainerID() <<'\t' << '\t' << getExerciseID() << '\n';
    save.close();
}

Trainers* IncreaseTrainers(Trainers* TrainerArray, int& NoOfTrainers) {
    Trainers* TempTrainerArray = new Trainers[NoOfTrainers];
    for (size_t index = 0; index < NoOfTrainers; index++) {
        TempTrainerArray[index] = TrainerArray[index];
    }
    delete[] TrainerArray;
    TrainerArray = new Trainers[NoOfTrainers + 1];
    for (size_t index = 0; index < NoOfTrainers; index++) {
        TrainerArray[index] = TempTrainerArray[index];
    }
    NoOfTrainers++;
    delete[] TempTrainerArray;
    return TrainerArray;
}

Trainers* DecreaseTrainers(Trainers* TrainerArray, int& NoOfTrainers) {
    Trainers* TempTrainerArray = new Trainers[NoOfTrainers];
    for (size_t index = 0; index < NoOfTrainers; index++) {
        TempTrainerArray[index] = TrainerArray[index];
    }
    delete[] TrainerArray;
    if (NoOfTrainers - 1 == 0) {
        delete[] TempTrainerArray;
        TrainerArray = new Trainers[NoOfTrainers];
        return TrainerArray;
    }
    TrainerArray = new Trainers[--NoOfTrainers];
    for (size_t index = 0; index < NoOfTrainers; index++) {
        TrainerArray[index] = TempTrainerArray[index];
    }
    delete[] TempTrainerArray;
    return TrainerArray;
}

Equipments* IncreaseEquipments(Equipments* EquipmentArray, int& NoOfEquipments) {
    Equipments* TempEquipmentArray = new Equipments[NoOfEquipments];
    for (size_t index = 0; index < NoOfEquipments; index++) {
        TempEquipmentArray[index] = EquipmentArray[index];
    }
    delete[] EquipmentArray;
    EquipmentArray = new Equipments[NoOfEquipments + 1];
    for (size_t index = 0; index < NoOfEquipments; index++) {
        EquipmentArray[index] = TempEquipmentArray[index];
    }
    NoOfEquipments++;
    delete[] TempEquipmentArray;
    return EquipmentArray;
}

Equipments* DecreaseEquipments(Equipments* EquipmentArray, int& NoOfEquipments) {
    Equipments* TempEquipmentArray = new Equipments[NoOfEquipments];
    for (size_t index = 0; index < NoOfEquipments; index++) {
        TempEquipmentArray[index] = EquipmentArray[index];
    }
    delete[] EquipmentArray;
    if (NoOfEquipments - 1 == 0) {
        EquipmentArray = new Equipments[NoOfEquipments];
        delete[] TempEquipmentArray;
        return EquipmentArray;
    }
    EquipmentArray = new Equipments[--NoOfEquipments];
    for (size_t index = 0; index < NoOfEquipments; index++) {
        EquipmentArray[index] = TempEquipmentArray[index];
    }
    delete[] TempEquipmentArray;
    return EquipmentArray;
}
