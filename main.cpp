#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>

using namespace std;

// класс MaintenanceRecord (журнал техобслуживания)
class MaintenanceRecord {
protected:
    string record;

public:
    MaintenanceRecord(){
        record = "";
    }
    MaintenanceRecord(const string &record) {
        this->record = record;
    }

    ~MaintenanceRecord() {
    }

    // функции logAction для фиксирования выполненных действий
    void logAction(const string &action) {
        record += "Выполнено действие: " + action + "\n";
    }
    void logAction(const string &action, int cost) {
        record += "Выполнено действие: " + action + ", Стоимость: " + to_string(cost) + "\n";
    }

    void printRecord() const {
        cout << "Журнал техобслуживания:\n" << record << "\n";
    }
};

// класс транспорта (наследуется от журнала техобслуживания)
class Vehicle : public MaintenanceRecord {
protected:              // переменные (поля) будут доступны только для класса и его наследников
    string brand;       // марка
    string model;       // модель
    int year;           // год выпуска
    string regNumber;   // регистрационный номер

public:                 // будут доступны извне
    // конструктор по умолчанию (если ничего не передается при создании)
    Vehicle(){
        brand = "";
        model = "";
        year = 0;
        regNumber = "";
    }

    // конструктор с параметрами
    // пишем const string &*имя*, чтобы ссылаться на строку и не менять ее
    Vehicle(const string &brand, const string &model, int year, const string &regNumber){
        this->brand = brand;            // this указывает на объект данного класса
        this->model = model;
        this->year = year;
        this->regNumber = regNumber;
    }

    // виртуальный деструктор (значит, что можно переопределить в наследниках)
    virtual ~Vehicle() {}

    // сеттеры (чтобы установить новые значения) и геттеры (чтобы получить текущие значения)
    void setBrand(const string &brand) { this->brand = brand; }
    void setModel(const string &model) { this->model = model; }
    void setYear(int year) { this->year = year; }
    void setRegNumber(const string &regNumber) { this->regNumber = regNumber; }

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    string getRegNumber() const { return regNumber; }

    // виртуальные функции (их переопределяют наследники)
    virtual void service(const string &action) {
        cout << "Обслуживание транспорта: "<< brand << " " << model << "\n";
        logAction(action);
    }
    virtual void rent() const {
        cout << "Аренда транспорта: " << brand << " " << model << "\n";
    }
};

// класс-наследник Vehicle Car
// публичное наследование, то есть публичные члены Vehicle будут публичными и в Car
class Car : public Vehicle {
private:        // доступ только внутри класса Car
    int doors;  // количество дверей

public:
    Car() : Vehicle(), doors(4) {}
    Car(const string &brand, const string &model, int year, const string &regNumber, int doors)
        : Vehicle(brand, model, year, regNumber) {
        this->doors = doors;
    }

    // при удалении Car вызывается этот деструктор
    virtual ~Car() {}

    void setDoors(int doors) { this->doors = doors; }
    int getDoors() const { return doors; }

    // переопределённые функции
    void service(const string &action) override {
        cout << "Обслуживание машины: "<< brand << " " << model << ", дверей: " << doors << "\n";
        logAction(action);
    }

    void rent() const override {
        cout << "Аренда машины: "<< brand << " " << model << ", дверей: " << doors << "\n";
    }
};

// класс-наследник Truck (грузовик)
class Truck : public Vehicle {
private:
    double loadCapacity; // грузоподъёмность в тоннах

public:
    Truck() : Vehicle(), loadCapacity(0.0) {}
    Truck(const string &brand, const string &model, int year, const string &regNumber, double loadCapacity)
        : Vehicle(brand, model, year, regNumber) {
        this->loadCapacity = loadCapacity;
    }

    virtual ~Truck() {}

    void setLoadCapacity(double loadCapacity) { this->loadCapacity = loadCapacity; }
    double getLoadCapacity() const { return loadCapacity; }

    void service(const string &action) override {
        cout << "Обслуживание грузовика: "<< brand << " " << model << ", грузоподъёмность: " << loadCapacity << " тонн\n";
        logAction(action);
    }

    void rent() const override {
        cout << "Аренда грузовика: "<< brand << " " << model << ", грузоподъёмность: " << loadCapacity << " тонн\n";
    }
};


// класс-наследник Motorcycle (мотоцикл)
class Motorcycle : public Vehicle {
private:
    bool hasSidecar; // есть ли коляска

public:
    Motorcycle() : Vehicle(), hasSidecar(false) {}
    Motorcycle(const string &brand, const string &model, int year, const string &regNumber, bool hasSidecar)
        : Vehicle(brand, model, year, regNumber) {
        this->hasSidecar = hasSidecar;
    }

    virtual ~Motorcycle() {}

    void setSidecar(bool hasSidecar) { this->hasSidecar = hasSidecar; }
    bool getSidecar() const { return hasSidecar; }

    void service(const string &action) override {
        cout << "Обслуживание мотоцикла: " << brand << " " << model;
        if (hasSidecar) {
            cout << " (с коляской)";
        }
        logAction(action);
        cout << "\n";
    }

    void rent() const override {
        cout << "Аренда мотоцикла: " << brand << " " << model;
        if (hasSidecar) {
            cout << " (с коляской)";
        }
        cout << "\n";
    }
};




// Класс Customer (клиент)
class Customer {
private:
    string name;
    string rentalHistory;       // история аренды

public:
    Customer(){
        name = "";
        rentalHistory = "";
    }
    Customer(const string &name){
        this->name = name;
        rentalHistory = "";
    }
    Customer(const string &name, const string &rentalHistory) {
        this->name = name;
        this->rentalHistory = rentalHistory;
    }

    ~Customer() {
    }

    void setName(const string &name) { this->name = name; }
    string getName() const { return name; }
    string getRentalHistory() const { return rentalHistory; }

    // перегрузка оператора "+=" для добавления записи в историю
    Customer& operator+=(const string &history) {
        rentalHistory += history + "\n";
        return *this;
    }
};


int main() {

    SetConsoleOutputCP(CP_UTF8); // Устанавливает кодировку UTF-8 для консоли
    #endif

    Vehicle* vehicles[3];
    Customer customers[3];

    vehicles[0] = new Car("Toyota", "Corolla", 2011, "A123BC", 4);
    vehicles[1] = new Truck("Volvo", "FH", 2018, "Q333OP", 15.0);
    vehicles[2] = new Motorcycle("Dodge", "Tomahawk", 2022, "P001PP", false);

    customers[0] = Customer("Иван Иванов");
    customers[1] = Customer("Олеся Иванченко", "Вернула машину\n");

    for (int i = 0; i < 3; i++) {
        vehicles[i]->service("Замена масла");
        vehicles[i]->rent();
        cout << endl;
    }

    vehicles[0]->printRecord();

    customers[0] += "Вернул машину";
    cout << customers[0].getName() << "\n" << customers[0].getRentalHistory() << "\n";

    return 0;
}
