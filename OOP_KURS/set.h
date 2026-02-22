#ifndef SET_H
#define SET_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class Set;
class MultiSet;

enum class SetType { SET, MULTISET };

class BaseSet {
protected:
    std::vector<int> items;
public:
    virtual ~BaseSet() {}

    virtual void Add(int value) = 0;
    virtual void Delete(int value) = 0;
    virtual bool Exist(int value) const = 0;
    virtual int Power() const = 0;
    virtual int Unic() const = 0;
    virtual void Clear() = 0;

    virtual int GetMultiplicity(int value) const = 0;
    virtual SetType getType() const = 0;

    const std::vector<int>& GetItems() const { return items; }

    virtual BaseSet* Union(const BaseSet* other) const = 0;
    virtual BaseSet* Intersection(const BaseSet* other) const = 0;
    virtual BaseSet* Difference(const BaseSet* other) const = 0;
    virtual BaseSet* SymmetricDifference(const BaseSet* other) const = 0;

    virtual BaseSet* Clone() const = 0;
    virtual void Print() const = 0;

    virtual Set* ToSet() = 0;
    virtual MultiSet* ToMultiSet() = 0;

    bool operator==(const BaseSet& other) const {
        if (Power() != other.Power() || Unic() != other.Unic()) return false;

        for (const auto& item : items) {
            if (GetMultiplicity(item) != other.GetMultiplicity(item)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const BaseSet& other) const {
        return !(*this == other);
    }

    BaseSet& operator=(const BaseSet& other) {
        if (this != &other) {
            items = other.items;
        }
        return *this;
    }
};

class Set : public BaseSet {
public:
    Set() {}
    Set(const Set& other) {
        for (const auto& item : other.items) {
            Add(item);
        }
    }

    explicit Set(const std::vector<int>& values) {
        for (const auto& value : values) {
            Add(value);
        }
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            items.clear();
            for (const auto& item : other.items) {
                Add(item);
            }
        }
        return *this;
    }

    void Add(int value) override;
    void Delete(int value) override;
    bool Exist(int value) const override;
    int Power() const override;
    int Unic() const override;
    void Clear() override { items.clear(); }
    int GetMultiplicity(int value) const override;
    SetType getType() const override { return SetType::SET; }

    BaseSet* Union(const BaseSet* other) const override;
    BaseSet* Intersection(const BaseSet* other) const override;
    BaseSet* Difference(const BaseSet* other) const override;
    BaseSet* SymmetricDifference(const BaseSet* other) const override;

    BaseSet* Clone() const override;
    void Print() const override;

    Set* ToSet() override { return new Set(*this); }
    MultiSet* ToMultiSet() override;
};

class MultiSet : public BaseSet {
public:
    MultiSet() {}
    MultiSet(const MultiSet& other) {
        for (const auto& item : other.items) {
            Add(item);
        }
    }

    explicit MultiSet(const std::vector<int>& values) {
        for (const auto& value : values) {
            Add(value);
        }
    }

    MultiSet& operator=(const MultiSet& other) {
        if (this != &other) {
            items = other.items;
        }
        return *this;
    }

    void Add(int value) override;
    void Delete(int value) override;
    bool Exist(int value) const override;
    int Power() const override;
    int Unic() const override;
    void Clear() override { items.clear(); }
    int GetMultiplicity(int value) const override;
    SetType getType() const override { return SetType::MULTISET; }

    BaseSet* Union(const BaseSet* other) const override;
    BaseSet* Intersection(const BaseSet* other) const override;
    BaseSet* Difference(const BaseSet* other) const override;
    BaseSet* SymmetricDifference(const BaseSet* other) const override;

    BaseSet* Clone() const override;
    void Print() const override;

    Set* ToSet() override;
    MultiSet* ToMultiSet() override { return new MultiSet(*this); }
};

#endif