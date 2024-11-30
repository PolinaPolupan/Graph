#pragma once

#include <iostream> 

template <typename T>
class StandardVertex {

public:
    StandardVertex() = default;

    StandardVertex(const T& data) : data(data) {}

    void setData(const T& data) {
        this->data = data;
    }

    inline const T& getData() const { return data; }

    // Comparison operator overloads for comparing data
    bool operator==(const StandardVertex& other) const {
        return this->data == other.data;
    }

    bool operator!=(const StandardVertex& other) const {
        return !(*this == other);
    }

    bool operator<(const StandardVertex& other) const {
        return this->data < other.data;
    }

    bool operator>(const StandardVertex& other) const {
        return other < *this;  // Reuse operator<
    }

    // Stream insertion operator for printing data
    friend std::ostream& operator<<(std::ostream& os, const StandardVertex& vertex) {
        os << vertex.data;
        return os;
    }

protected:

    T data;
};

template <typename T, typename K>
class MarkedVertex : public StandardVertex<T> {

public:
    MarkedVertex() = default;

    MarkedVertex(const T& data) : StandardVertex<T>(data) {}

    MarkedVertex(const T& data, const K& mark) : StandardVertex<T>(data), mark(mark) {}

    void setMark(const K& mark) {
        this->mark = mark;
    }

    K getMark() const {
        return mark;
    }

    // Comparison operator overloads for comparing data in MarkedVertex
    bool operator==(const MarkedVertex& other) const {
        return this->data == other.data;
    }

    bool operator!=(const MarkedVertex& other) const {
        return !(*this == other);
    }

    bool operator<(const MarkedVertex& other) const {
        return this->data < other.data;
    }

    bool operator>(const MarkedVertex& other) const {
        return other < *this;  // Reuse operator<
    }

private:

    K mark;
};
