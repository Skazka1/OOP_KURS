#include "set.h"

// Реализация методов класса Set
void Set::Add(int value) {
    if (!Exist(value)) {
        items.push_back(Item(value, 1));
    }
}

void Set::Delete(int value) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->GetValue() == value) {
            items.erase(it);
            break;
        }
    }
}

bool Set::Exist(int value) const {
    for (const auto& item : items) {
        if (item.GetValue() == value) {
            return true;
        }
    }
    return false;
}

int Set::Power() const {
    return items.size();
}

int Set::Unic() const {
    return items.size();
}

int Set::GetMultiplicity(int value) const {
    return Exist(value) ? 1 : 0;
}

BaseSet* Set::Union(const BaseSet* other) const {
    // Если другой операнд - мультимножество, результат должен быть мультимножеством
    if (other->getType() == SetType::MULTISET) {
        MultiSet* result = new MultiSet();

        // Добавляем элементы из текущего множества (с кратностью 1)
        for (const auto& item : items) {
            result->Add(item.GetValue(), 1);
        }

        // Добавляем элементы из другого мультимножества
        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            int currentCount = result->GetMultiplicity(item.GetValue());
            int otherCount = other->GetMultiplicity(item.GetValue());
            if (otherCount > currentCount) {
                if (currentCount > 0) {
                    result->Delete(item.GetValue(), currentCount);
                }
                result->Add(item.GetValue(), otherCount);
            }
        }

        return result;
    }
    else {
        // Оба операнда - обычные множества
        Set* result = new Set();

        // Добавляем элементы из текущего множества
        for (const auto& item : items) {
            result->Add(item.GetValue());
        }

        // Добавляем элементы из другого множества
        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            result->Add(item.GetValue());
        }

        return result;
    }
}

BaseSet* Set::Intersection(const BaseSet* other) const {
    // Если другой операнд - мультимножество, результат должен быть множеством
    // (так как пересечение с мультимножеством дает уникальные значения)
    Set* result = new Set();

    for (const auto& item : items) {
        if (other->Exist(item.GetValue())) {
            result->Add(item.GetValue());
        }
    }

    return result;
}

BaseSet* Set::Difference(const BaseSet* other) const {
    // Разность всегда дает множество
    Set* result = new Set();

    for (const auto& item : items) {
        if (!other->Exist(item.GetValue())) {
            result->Add(item.GetValue());
        }
    }

    return result;
}

BaseSet* Set::SymmetricDifference(const BaseSet* other) const {
    // Если другой операнд - мультимножество, результат должен быть мультимножеством
    if (other->getType() == SetType::MULTISET) {
        MultiSet* result = new MultiSet();

        // Элементы из текущего множества, которых нет в другом
        for (const auto& item : items) {
            if (!other->Exist(item.GetValue())) {
                result->Add(item.GetValue(), 1);
            }
        }

        // Элементы из другого мультимножества, которых нет в текущем
        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            if (!Exist(item.GetValue())) {
                result->Add(item.GetValue(), item.GetCount());
            }
        }

        return result;
    }
    else {
        // Оба операнда - обычные множества
        Set* result = new Set();

        // Элементы из текущего, которых нет в другом
        for (const auto& item : items) {
            if (!other->Exist(item.GetValue())) {
                result->Add(item.GetValue());
            }
        }

        // Элементы из другого, которых нет в текущем
        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            if (!Exist(item.GetValue())) {
                result->Add(item.GetValue());
            }
        }

        return result;
    }
}

BaseSet* Set::Clone() const {
    return new Set(*this);
}

void Set::Print() const {
    std::cout << "Множество: { ";
    if (items.empty()) {
        std::cout << "пусто";
    }
    else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << items[i].GetValue();
            if (i < items.size() - 1) std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;
    std::cout << "Мощность: " << Power() << std::endl;
    std::cout << "Уникальных: " << Unic() << std::endl;
}

MultiSet* Set::ToMultiSet() {
    MultiSet* multiSet = new MultiSet();
    for (const auto& item : items) {
        multiSet->Add(item.GetValue(), 1);
    }
    return multiSet;
}

// Реализация методов класса MultiSet
void MultiSet::Add(int value) {
    Add(value, 1);
}

void MultiSet::Add(int value, int count) {
    for (auto& item : items) {
        if (item.GetValue() == value) {
            item.AddCount(count);
            return;
        }
    }
    items.push_back(Item(value, count));
}

void MultiSet::Delete(int value) {
    Delete(value, 1);
}

void MultiSet::Delete(int value, int count) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->GetValue() == value) {
            if (it->GetCount() <= count) {
                items.erase(it);
            }
            else {
                it->SetCount(it->GetCount() - count);
            }
            break;
        }
    }
}

bool MultiSet::Exist(int value) const {
    return GetMultiplicity(value) > 0;
}

int MultiSet::Power() const {
    int total = 0;
    for (const auto& item : items) {
        total += item.GetCount();
    }
    return total;
}

int MultiSet::Unic() const {
    return items.size();
}

int MultiSet::GetMultiplicity(int value) const {
    for (const auto& item : items) {
        if (item.GetValue() == value) {
            return item.GetCount();
        }
    }
    return 0;
}

BaseSet* MultiSet::Union(const BaseSet* other) const {
    MultiSet* result = new MultiSet();

    // Копируем текущее мультимножество
    for (const auto& item : items) {
        result->Add(item.GetValue(), item.GetCount());
    }

    // Добавляем элементы из другого множества/мультимножества
    const auto& otherItems = other->GetItems();
    for (const auto& item : otherItems) {
        int currentCount = result->GetMultiplicity(item.GetValue());
        int otherCount = other->GetMultiplicity(item.GetValue());
        if (otherCount > currentCount) {
            if (currentCount > 0) {
                result->Delete(item.GetValue(), currentCount);
            }
            result->Add(item.GetValue(), otherCount);
        }
    }

    return result;
}

BaseSet* MultiSet::Intersection(const BaseSet* other) const {
    if (other->getType() == SetType::SET) {
        Set* result = new Set();

        for (const auto& item : items) {
            if (other->Exist(item.GetValue())) {
                result->Add(item.GetValue());
            }
        }

        return result;
    }
    else {
        MultiSet* result = new MultiSet();

        for (const auto& item : items) {
            int currentCount = item.GetCount();
            int otherCount = other->GetMultiplicity(item.GetValue());
            if (otherCount > 0) {
                result->Add(item.GetValue(), std::min(currentCount, otherCount));
            }
        }

        return result;
    }
}

BaseSet* MultiSet::Difference(const BaseSet* other) const {
    MultiSet* result = new MultiSet();

    for (const auto& item : items) {
        int currentCount = item.GetCount();
        int otherCount = other->GetMultiplicity(item.GetValue());
        int diffCount = currentCount - otherCount;
        if (diffCount > 0) {
            result->Add(item.GetValue(), diffCount);
        }
    }

    return result;
}

BaseSet* MultiSet::SymmetricDifference(const BaseSet* other) const {
    MultiSet* result = new MultiSet();

    for (const auto& item : items) {
        int currentCount = item.GetCount();
        int otherCount = other->GetMultiplicity(item.GetValue());
        if (otherCount == 0) {
            result->Add(item.GetValue(), currentCount);
        }
        else if (currentCount != otherCount) {
            result->Add(item.GetValue(), std::abs(currentCount - otherCount));
        }
    }

    const auto& otherItems = other->GetItems();
    for (const auto& item : otherItems) {
        int currentCount = GetMultiplicity(item.GetValue());
        if (currentCount == 0) {
            result->Add(item.GetValue(), item.GetCount());
        }
    }

    return result;
}

BaseSet* MultiSet::Clone() const {
    return new MultiSet(*this);
}

void MultiSet::Print() const {
    std::cout << "Мультимножество: { ";
    if (items.empty()) {
        std::cout << "пусто";
    }
    else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << items[i].GetValue() << "(" << items[i].GetCount() << ")";
            if (i < items.size() - 1) std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;
    std::cout << "Мощность: " << Power() << std::endl;
    std::cout << "Уникальных: " << Unic() << std::endl;
}

Set* MultiSet::ToSet() {
    Set* set = new Set();
    for (const auto& item : items) {
        set->Add(item.GetValue());
    }
    return set;
}