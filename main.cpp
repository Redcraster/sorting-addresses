#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // для std::sort

// Класс для хранения информации об адресе
class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;

public:
    // Конструктор класса Address с параметрами
    Address(const std::string& city, const std::string& street, int houseNumber, int apartmentNumber) 
        : city(city), street(street), houseNumber(houseNumber), apartmentNumber(apartmentNumber) {}

    // Метод для получения строки формата адреса для вывода в файл
    std::string getOutputAddress() const {
        return city + ", " + street + ", " + std::to_string(houseNumber) + ", " + std::to_string(apartmentNumber);
    }

    // Метод для получения названия города (используется для сортировки)
    std::string getCity() const {
        return city;
    }
};

// Функция сортировки адресов по названию города
void sortAddresses(std::vector<Address>& addresses) {
    std::sort(addresses.begin(), addresses.end(), [](const Address& a, const Address& b) {
        return a.getCity() < b.getCity(); // Сравниваем названия городов
    });
}

int main() {
    std::ifstream inFile("in.txt");
    if (!inFile) {
        std::cerr << "Не удалось открыть файл in.txt" << std::endl;
        return 1;
    } else {
        std::cout << "Файл in.txt открыт успешно." << std::endl;  // Отладочный вывод
    }

    int numAddresses;
    inFile >> numAddresses;
    inFile.ignore(); // Игнорируем оставшийся символ новой строки
    std::cout << "Количество адресов: " << numAddresses << std::endl;  // Отладочный вывод

    std::vector<Address> addresses;

    // Считываем адреса из файла
    for (int i = 0; i < numAddresses; ++i) {
        std::string city, street;
        int houseNumber, apartmentNumber;
        
        std::getline(inFile, city);
        std::getline(inFile, street);
        inFile >> houseNumber >> apartmentNumber;
        inFile.ignore(); // Игнорируем оставшийся символ новой строки

        addresses.push_back(Address(city, street, houseNumber, apartmentNumber));
        std::cout << "Прочитали адрес: " << city << ", " << street << ", " << houseNumber << ", " << apartmentNumber << std::endl;  // Отладочный вывод
    }

    inFile.close();

    // Сортируем адреса по названию города
    sortAddresses(addresses);
    std::cout << "Адреса отсортированы." << std::endl;  // Отладочный вывод

    std::ofstream outFile("out.txt");
    if (!outFile) {
        std::cerr << "Не удалось открыть файл out.txt" << std::endl;
        return 1;
    } else {
        std::cout << "Файл out.txt открыт успешно." << std::endl;  // Отладочный вывод
    }

    outFile << numAddresses << std::endl;

    // Записываем отсортированные адреса в файл
    for (const auto& address : addresses) {
        outFile << address.getOutputAddress() << std::endl;
        std::cout << "Записали адрес: " << address.getOutputAddress() << std::endl;  // Отладочный вывод
    }

    outFile.close();
    std::cout << "Запись в файл завершена." << std::endl;  // Отладочный вывод

    return 0;
}