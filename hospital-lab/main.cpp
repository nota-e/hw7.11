#include <iostream>
#include <string>
#include <vector>

enum class Department {
    Therapy,    // Терапия
    Surgery,    // Хирургия
    Cardiology, // Кардиология
    Unknown
};

enum class PatientState {
    InQueue,     // В очереди
    InTreatment, // Лечится
    Discharged   // Выписан
};

std::string department_to_string(Department d) {
    switch(d) {
        case Department::Therapy: return "Терапия";
        case Department::Surgery: return "Хирургия";
        case Department::Cardiology: return "Кардиология";
        default: return "Неизвестно";
    }
} 

std::string PatientState_to_string(PatientState p) {
    switch(p) {
        case PatientState::InQueue: return "В очереди";
        case PatientState::InTreatment: return "Лечится";
        case PatientState::Discharged: return "Выписан";
        default: return "Неизвестно";
    }
} 

class Patient {
private:
    std::string name;
    int age;
    Department department;
    PatientState state;

public:
    Patient(std::string patientName, int patientAge, Department dept) 
        : name(std::move(patientName)), age(patientAge), department(dept), state(PatientState::InQueue) {}

    // Геттеры
    std::string getName() const { return name; }
    int getAge() const { return age; }
    Department getDepartment() const { return department; }
    PatientState getState() const { return state; }

    // Сеттеры
    void setAge(int newAge) {
        if (newAge > 0) {
            age = newAge;
        } else {
            std::cerr << "Ошибка: возраст должен быть больше 0.\n";
        }
    }

    void setState(PatientState s) {
        state = s;
    }

    virtual std::string getDescription() const {
        return "Пациент: " + name + 
               ", возраст: " + std::to_string(age) + 
               ", отделение: " + department_to_string(department) + 
               ", состояние: " + PatientState_to_string(state);
    }

    virtual ~Patient() = default;
};

class ChildPatient : public Patient {
private:
    std::string parentName;
public:
    // Конструктор должен вызывать базовый класс и ОБЯЗАТЕЛЬНО заканчиваться фигурными скобками {}
    ChildPatient(std::string name, int age, Department dept, std::string parentName) 
        : Patient(std::move(name), age, dept), parentName(std::move(parentName)) {}

    // Теперь метод скомпилируется без предупреждений и ошибок
    std::string getDescription() const override {
        return "Ребёнок: " + getName() + 
               ", возраст: " + std::to_string(getAge()) + 
               ", отделение: " + department_to_string(getDepartment()) + 
               ", состояние: " + PatientState_to_string(getState()) + 
               ", родитель: " + parentName;
    }
}; // Не забудьте точку с запятой в самом конце класса



int main() {
    // 1. Создаёт обычного пациента и ребёнка
    Patient adult("Иван Петров", 35, Department::Surgery);
    ChildPatient child("Маша Иванова", 8, Department::Therapy, "Ольга Иванова");

    // 2. Выводит их описания
    std::cout << adult.getDescription() << "\n";
    std::cout << child.getDescription() << "\n";

    // 3. Меняет состояние одного пациента через setState
    adult.setState(PatientState::InTreatment);

    // 4. Снова выводит описание
    std::cout << adult.getDescription() << "\n";

    return 0;
}
