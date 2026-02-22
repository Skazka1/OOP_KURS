#include "set.h"
#include <vector>
#include <memory>
#include <locale>

std::vector<BaseSet*> sets;
std::vector<BaseSet*> multiSets;

void printAllSets() {
    std::cout << "\n=== ТЕКУЩИЕ МНОЖЕСТВА ===" << std::endl;
    for (size_t i = 0; i < sets.size(); ++i) {
        std::cout << i + 1 << ". ";
        sets[i]->Print();
    }

    std::cout << "\n=== ТЕКУЩИЕ МУЛЬТИМНОЖЕСТВА ===" << std::endl;
    for (size_t i = 0; i < multiSets.size(); ++i) {
        std::cout << i + 1 << ". ";
        multiSets[i]->Print();
    }
}

void operationsMenu(BaseSet* set1) {
    int choice;
    do {
        std::cout << "\n=== ОПЕРАЦИИ НАД МНОЖЕСТВАМИ ===" << std::endl;
        std::cout << "1. Объединение с другим множеством" << std::endl;
        std::cout << "2. Пересечение с другим множеством" << std::endl;
        std::cout << "3. Разность с другим множеством" << std::endl;
        std::cout << "4. Симметрическая разность с другим множеством" << std::endl;
        std::cout << "5. Сравнение с другим множеством" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        if (choice == 0) break;

        printAllSets();

        int typeChoice, index;
        BaseSet* set2 = nullptr;

        std::cout << "\nВыберите тип второго множества:" << std::endl;
        std::cout << "1. Обычное множество" << std::endl;
        std::cout << "2. Мультимножество" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> typeChoice;

        if (typeChoice == 1) {
            if (sets.empty()) {
                std::cout << "Нет созданных множеств!" << std::endl;
                continue;
            }
            std::cout << "Выберите множество (1-" << sets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)sets.size()) {
                set2 = sets[index - 1];
            }
        }
        else {
            if (multiSets.empty()) {
                std::cout << "Нет созданных мультимножеств!" << std::endl;
                continue;
            }
            std::cout << "Выберите мультимножество (1-" << multiSets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)multiSets.size()) {
                set2 = multiSets[index - 1];
            }
        }

        if (!set2) {
            std::cout << "Неверный выбор!" << std::endl;
            continue;
        }

        BaseSet* result = nullptr;

        switch (choice) {
        case 1:
            result = set1->Union(set2);
            std::cout << "\nРезультат объединения:" << std::endl;
            result->Print();
            break;
        case 2:
            result = set1->Intersection(set2);
            std::cout << "\nРезультат пересечения:" << std::endl;
            result->Print();
            break;
        case 3:
            result = set1->Difference(set2);
            std::cout << "\nРезультат разности:" << std::endl;
            result->Print();
            break;
        case 4:
            result = set1->SymmetricDifference(set2);
            std::cout << "\nРезультат симметрической разности:" << std::endl;
            result->Print();
            break;
        case 5:
            if (*set1 == *set2) {
                std::cout << "Множества равны" << std::endl;
            }
            else {
                std::cout << "Множества не равны" << std::endl;
            }
            break;
        }

        if (result && choice >= 1 && choice <= 4) {
            std::cout << "\nСохранить результат?" << std::endl;
            std::cout << "1. Да, как обычное множество" << std::endl;
            std::cout << "2. Да, как мультимножество" << std::endl;
            std::cout << "0. Нет" << std::endl;
            std::cout << "Выбор: ";
            int saveChoice;
            std::cin >> saveChoice;

            if (saveChoice == 1) {
                Set* setResult = result->ToSet();
                if (result != setResult) {
                    delete result;
                }
                sets.push_back(setResult);
                std::cout << "Результат сохранен как множество #" << sets.size() << std::endl;
            }
            else if (saveChoice == 2) {
                MultiSet* multiResult = result->ToMultiSet();
                if (result != multiResult) {
                    delete result;
                }
                multiSets.push_back(multiResult);
                std::cout << "Результат сохранен как мультимножество #" << multiSets.size() << std::endl;
            }
            else {
                delete result;
            }
        }

    } while (choice != 0);
}

void menuSet(BaseSet* set) {
    int choice;
    do {
        std::cout << "\n=== РАБОТА С МНОЖЕСТВОМ ===" << std::endl;
        std::cout << "1. Добавить элемент" << std::endl;
        std::cout << "2. Удалить элемент" << std::endl;
        std::cout << "3. Проверить наличие элемента" << std::endl;
        std::cout << "4. Показать множество" << std::endl;
        std::cout << "5. Операции с другими множествами" << std::endl;
        std::cout << "6. Преобразовать в мультимножество" << std::endl;
        std::cout << "7. Клонировать множество" << std::endl;
        std::cout << "8. Очистить множество" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Введите значение: ";
            std::cin >> value;
            set->Add(value);
            break;
        }
        case 2: {
            int value;
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            set->Delete(value);
            break;
        }
        case 3: {
            int value;
            std::cout << "Введите значение для проверки: ";
            std::cin >> value;
            std::cout << (set->Exist(value) ? "Присутствует" : "Отсутствует") << std::endl;
            break;
        }
        case 4:
            set->Print();
            break;
        case 5:
            operationsMenu(set);
            break;
        case 6: {
            MultiSet* multiSet = set->ToMultiSet();
            multiSets.push_back(multiSet);
            std::cout << "Создано мультимножество #" << multiSets.size() << std::endl;
            multiSet->Print();
            break;
        }
        case 7: {
            BaseSet* clone = set->Clone();
            sets.push_back(clone);
            std::cout << "Создана копия как множество #" << sets.size() << std::endl;
            break;
        }
        case 8:
            set->Clear();
            std::cout << "Множество очищено" << std::endl;
            break;
        }
    } while (choice != 0);
}

void menuMultiSet(BaseSet* multiSet) {
    int choice;

    do {
        std::cout << "\n=== РАБОТА С МУЛЬТИМНОЖЕСТВОМ ===" << std::endl;
        std::cout << "1. Добавить элемент" << std::endl;
        std::cout << "2. Добавить несколько одинаковых элементов" << std::endl;
        std::cout << "3. Удалить один экземпляр элемента" << std::endl;
        std::cout << "4. Удалить все экземпляры элемента" << std::endl;
        std::cout << "5. Проверить наличие элемента" << std::endl;
        std::cout << "6. Получить количество экземпляров элемента" << std::endl;
        std::cout << "7. Показать мультимножество" << std::endl;
        std::cout << "8. Операции с другими множествами" << std::endl;
        std::cout << "9. Преобразовать в обычное множество" << std::endl;
        std::cout << "10. Клонировать мультимножество" << std::endl;
        std::cout << "11. Очистить мультимножество" << std::endl;
        std::cout << "0. Назад" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Введите значение: ";
            std::cin >> value;
            multiSet->Add(value);
            break;
        }
        case 2: {
            int value, count;
            std::cout << "Введите значение: ";
            std::cin >> value;
            std::cout << "Введите количество: ";
            std::cin >> count;
            for (int i = 0; i < count; ++i) {
                multiSet->Add(value);
            }
            break;
        }
        case 3: {
            int value;
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            multiSet->Delete(value);
            break;
        }
        case 4: {
            int value;
            std::cout << "Введите значение: ";
            std::cin >> value;
            while (multiSet->Exist(value)) {
                multiSet->Delete(value);
            }
            break;
        }
        case 5: {
            int value;
            std::cout << "Введите значение для проверки: ";
            std::cin >> value;
            std::cout << (multiSet->Exist(value) ? "Присутствует" : "Отсутствует") << std::endl;
            break;
        }
        case 6: {
            int value;
            std::cout << "Введите значение: ";
            std::cin >> value;
            std::cout << "Количество: " << multiSet->GetMultiplicity(value) << std::endl;
            break;
        }
        case 7:
            multiSet->Print();
            break;
        case 8:
            operationsMenu(multiSet);
            break;
        case 9: {
            Set* set = multiSet->ToSet();
            sets.push_back(set);
            std::cout << "Создано множество #" << sets.size() << std::endl;
            set->Print();
            break;
        }
        case 10: {
            BaseSet* clone = multiSet->Clone();
            multiSets.push_back(clone);
            std::cout << "Создана копия как мультимножество #" << multiSets.size() << std::endl;
            break;
        }
        case 11:
            multiSet->Clear();
            std::cout << "Мультимножество очищено" << std::endl;
            break;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int choice;

    do {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1. Создать новое множество" << std::endl;
        std::cout << "2. Создать новое мультимножество" << std::endl;
        std::cout << "3. Работать с существующим множеством" << std::endl;
        std::cout << "4. Работать с существующим мультимножеством" << std::endl;
        std::cout << "5. Показать все множества и мультимножества" << std::endl;
        std::cout << "6. Удалить множество" << std::endl;
        std::cout << "7. Удалить мультимножество" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Set* newSet = new Set();
            sets.push_back(newSet);
            std::cout << "Создано множество #" << sets.size() << std::endl;
            break;
        }
        case 2: {
            MultiSet* newMultiSet = new MultiSet();
            multiSets.push_back(newMultiSet);
            std::cout << "Создано мультимножество #" << multiSets.size() << std::endl;
            break;
        }
        case 3: {
            if (sets.empty()) {
                std::cout << "Нет созданных множеств!" << std::endl;
                break;
            }
            printAllSets();
            int index;
            std::cout << "Выберите множество (1-" << sets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)sets.size()) {
                menuSet(sets[index - 1]);
            }
            else {
                std::cout << "Неверный выбор!" << std::endl;
            }
            break;
        }
        case 4: {
            if (multiSets.empty()) {
                std::cout << "Нет созданных мультимножеств!" << std::endl;
                break;
            }
            printAllSets();
            int index;
            std::cout << "Выберите мультимножество (1-" << multiSets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)multiSets.size()) {
                menuMultiSet(multiSets[index - 1]);
            }
            else {
                std::cout << "Неверный выбор!" << std::endl;
            }
            break;
        }
        case 5:
            printAllSets();
            break;
        case 6: {
            if (sets.empty()) {
                std::cout << "Нет созданных множеств!" << std::endl;
                break;
            }
            printAllSets();
            int index;
            std::cout << "Выберите множество для удаления (1-" << sets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)sets.size()) {
                delete sets[index - 1];
                sets.erase(sets.begin() + index - 1);
                std::cout << "Множество удалено" << std::endl;
            }
            else {
                std::cout << "Неверный выбор!" << std::endl;
            }
            break;
        }
        case 7: {
            if (multiSets.empty()) {
                std::cout << "Нет созданных мультимножеств!" << std::endl;
                break;
            }
            printAllSets();
            int index;
            std::cout << "Выберите мультимножество для удаления (1-" << multiSets.size() << "): ";
            std::cin >> index;
            if (index >= 1 && index <= (int)multiSets.size()) {
                delete multiSets[index - 1];
                multiSets.erase(multiSets.begin() + index - 1);
                std::cout << "Мультимножество удалено" << std::endl;
            }
            else {
                std::cout << "Неверный выбор!" << std::endl;
            }
            break;
        }
        }
    } while (choice != 0);

    for (auto set : sets) delete set;
    for (auto multiSet : multiSets) delete multiSet;

    return 0;
}