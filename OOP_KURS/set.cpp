#include "set.h"
#include <algorithm>

void Set::Add(int value) {
    if (!Exist(value)) {
        items.push_back(value);
    }
}

void Set::Delete(int value) {
    auto it = std::find(items.begin(), items.end(), value);
    if (it != items.end()) {
        items.erase(it);
    }
}

bool Set::Exist(int value) const {
    return std::find(items.begin(), items.end(), value) != items.end();
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
    if (other->getType() == SetType::MULTISET) {
        MultiSet* result = new MultiSet();

        for (const auto& item : items) {
            result->Add(item);
        }

        const auto& otherItems = other->GetItems();
        std::vector<int> processed;

        for (const auto& item : otherItems) {
            if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
                int currentCount = result->GetMultiplicity(item);
                int otherCount = other->GetMultiplicity(item);

                if (otherCount > currentCount) {
                    for (int i = 0; i < otherCount - currentCount; ++i) {
                        result->Add(item);
                    }
                }
                processed.push_back(item);
            }
        }

        return result;
    }
    else {
        Set* result = new Set();

        for (const auto& item : items) {
            result->Add(item);
        }

        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            result->Add(item);
        }

        return result;
    }
}

BaseSet* Set::Intersection(const BaseSet* other) const {
    Set* result = new Set();

    for (const auto& item : items) {
        if (other->Exist(item)) {
            result->Add(item);
        }
    }

    return result;
}

BaseSet* Set::Difference(const BaseSet* other) const {
    Set* result = new Set();

    for (const auto& item : items) {
        if (!other->Exist(item)) {
            result->Add(item);
        }
    }

    return result;
}

BaseSet* Set::SymmetricDifference(const BaseSet* other) const {
    if (other->getType() == SetType::MULTISET) {
        MultiSet* result = new MultiSet();

        for (const auto& item : items) {
            if (!other->Exist(item)) {
                result->Add(item);
            }
        }

        const auto& otherItems = other->GetItems();
        std::vector<int> processed;

        for (const auto& item : otherItems) {
            if (!Exist(item) &&
                std::find(processed.begin(), processed.end(), item) == processed.end()) {
                int otherCount = other->GetMultiplicity(item);
                for (int i = 0; i < otherCount; ++i) {
                    result->Add(item);
                }
                processed.push_back(item);
            }
        }

        return result;
    }
    else {
        Set* result = new Set();

        for (const auto& item : items) {
            if (!other->Exist(item)) {
                result->Add(item);
            }
        }

        const auto& otherItems = other->GetItems();
        for (const auto& item : otherItems) {
            if (!Exist(item)) {
                result->Add(item);
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
            std::cout << items[i];
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
        multiSet->Add(item);
    }
    return multiSet;
}

void MultiSet::Add(int value) {
    items.push_back(value);
}

void MultiSet::Delete(int value) {
    auto it = std::find(items.rbegin(), items.rend(), value);
    if (it != items.rend()) {
        items.erase(std::next(it).base());
    }
}

bool MultiSet::Exist(int value) const {
    return std::find(items.begin(), items.end(), value) != items.end();
}

int MultiSet::Power() const {
    return items.size();
}

int MultiSet::Unic() const {
    std::vector<int> uniqueItems;
    for (const auto& item : items) {
        if (std::find(uniqueItems.begin(), uniqueItems.end(), item) == uniqueItems.end()) {
            uniqueItems.push_back(item);
        }
    }
    return uniqueItems.size();
}

int MultiSet::GetMultiplicity(int value) const {
    return std::count(items.begin(), items.end(), value);
}

BaseSet* MultiSet::Union(const BaseSet* other) const {
    MultiSet* result = new MultiSet();

    for (const auto& item : items) {
        result->Add(item);
    }

    const auto& otherItems = other->GetItems();
    std::vector<int> processed;

    for (const auto& item : otherItems) {
        if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
            int currentCount = result->GetMultiplicity(item);
            int otherCount = other->GetMultiplicity(item);

            if (otherCount > currentCount) {
                for (int i = 0; i < otherCount - currentCount; ++i) {
                    result->Add(item);
                }
            }
            processed.push_back(item);
        }
    }

    return result;
}

BaseSet* MultiSet::Intersection(const BaseSet* other) const {
    if (other->getType() == SetType::SET) {
        Set* result = new Set();

        std::vector<int> processed;
        for (const auto& item : items) {
            if (other->Exist(item) &&
                std::find(processed.begin(), processed.end(), item) == processed.end()) {
                result->Add(item);
                processed.push_back(item);
            }
        }

        return result;
    }
    else {
        MultiSet* result = new MultiSet();

        std::vector<int> processed;
        for (const auto& item : items) {
            if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
                int currentCount = GetMultiplicity(item);
                int otherCount = other->GetMultiplicity(item);

                if (otherCount > 0) {
                    int minCount = std::min(currentCount, otherCount);
                    for (int i = 0; i < minCount; ++i) {
                        result->Add(item);
                    }
                }
                processed.push_back(item);
            }
        }

        return result;
    }
}

BaseSet* MultiSet::Difference(const BaseSet* other) const {
    MultiSet* result = new MultiSet();

    std::vector<int> processed;
    for (const auto& item : items) {
        if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
            int currentCount = GetMultiplicity(item);
            int otherCount = other->GetMultiplicity(item);
            int diffCount = currentCount - otherCount;

            if (diffCount > 0) {
                for (int i = 0; i < diffCount; ++i) {
                    result->Add(item);
                }
            }
            processed.push_back(item);
        }
    }

    return result;
}

BaseSet* MultiSet::SymmetricDifference(const BaseSet* other) const {
    MultiSet* result = new MultiSet();
    std::vector<int> processed;

    for (const auto& item : items) {
        if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
            int currentCount = GetMultiplicity(item);
            int otherCount = other->GetMultiplicity(item);

            if (otherCount == 0) {
                for (int i = 0; i < currentCount; ++i) {
                    result->Add(item);
                }
            }
            else if (currentCount != otherCount) {
                int diffCount = std::abs(currentCount - otherCount);
                for (int i = 0; i < diffCount; ++i) {
                    result->Add(item);
                }
            }
            processed.push_back(item);
        }
    }

    const auto& otherItems = other->GetItems();
    for (const auto& item : otherItems) {
        int currentCount = GetMultiplicity(item);
        if (currentCount == 0) {
            if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
                int otherCount = other->GetMultiplicity(item);
                for (int i = 0; i < otherCount; ++i) {
                    result->Add(item);
                }
                processed.push_back(item);
            }
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
        std::vector<int> processed;
        bool first = true;

        for (const auto& item : items) {
            if (std::find(processed.begin(), processed.end(), item) == processed.end()) {
                if (!first) {
                    std::cout << ", ";
                }
                int count = GetMultiplicity(item);
                std::cout << item << "(" << count << ")";
                processed.push_back(item);
                first = false;
            }
        }
    }
    std::cout << " }" << std::endl;
    std::cout << "Мощность: " << Power() << std::endl;
    std::cout << "Уникальных: " << Unic() << std::endl;
}

Set* MultiSet::ToSet() {
    Set* set = new Set();
    std::vector<int> added;

    for (const auto& item : items) {
        if (std::find(added.begin(), added.end(), item) == added.end()) {
            set->Add(item);
            added.push_back(item);
        }
    }
    return set;
}