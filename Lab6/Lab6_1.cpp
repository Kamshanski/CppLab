#include "../utilities.cpp"
using namespace std;
/*
Составить программу, выводящую на экран ведомость начисленной
заработной платы (Ф.И.О., должность, год и дата рождения, заработная плата). Вывести
фамилию сотрудника с самой маленькой зарплатой.
 */
enum Post { SAILOR, CAPTAIN, ENGINEER };

struct Worker {
    string firstName;
    string lastName;
    string fathersName;
    Post post;
    int year;
    int month;
    int day;
    int wage;

    string toString() const {
        ostringstream o;
        o << lastName << " ";
        o << firstName << " ";
        o << fathersName << " ";
        switch (post) {
            case CAPTAIN: o << "CAPTAIN"; break;
            case ENGINEER: o << "ENGINEER"; break;
            case SAILOR: o << "SAILOR"; break;
        }
        o << " ";
        o << year << "." << month << "." << day << " ";
        o << wage << "$";
        return o.str();
    }
};

int main() {
    Worker workers[] = {
            {"Anton", "Sergeevich", "Kirov", SAILOR, 1963, 11,9,8924},
            {"Pavel", "Viktorovna", "Ruban", SAILOR, 1987, 1,10,7896},
            {"Nikita", "Vladimirovna", "Eryomkin", ENGINEER, 1977, 22,9,9875},
            {"Marina", "Pavlovna", "Nosov", CAPTAIN, 1968, 9,8,7567},
            {"Anna", "Semyonovna", "Pavlov", ENGINEER, 2000, 4,9,8289},
    };
    int n = sizeof(workers) / sizeof(workers[0]);

    sort(workers, workers + n,
         [](const Worker& a, const Worker& b) -> bool {
             return (a.wage < b.wage);
         });

    cout << workers[0].toString() << endl;

    return 0;
}