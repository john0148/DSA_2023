#include<iostream>

struct PhanSo {
    int tuSo;
    int mauSo;

    // Overload toán tử "=" thành viên
    PhanSo& operator=(const PhanSo& other) {
        if (this != &other) {  // Kiểm tra tránh gán cho chính nó
            tuSo = other.tuSo;
            mauSo = other.mauSo;
        }
        return *this;
    }

    // Overload toán tử "<" cho struct PhanSo
    bool operator<(const PhanSo& other) const {
        // So sánh phân số
        return (tuSo * other.mauSo < other.tuSo * mauSo);
    }

    // Hàm toán tử ">"
    bool operator>(const PhanSo& other) const {
        // So sánh phân số
        return (tuSo * other.mauSo > other.tuSo * mauSo);
    }
};


/*
    // Overload toán tử "=" global
    PhanSo operator=(const PhanSo& lhs, const PhanSo& rhs) {
        PhanSo result;
        result.tuSo = rhs.tuSo;
        result.mauSo = rhs.mauSo;
        return result;
    }
*/

