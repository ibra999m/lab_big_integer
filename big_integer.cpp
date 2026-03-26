#include "big_integer.h"
#include <algorithm>
#include <stdexcept>
#include <utility>
long long BigInteger::mod(long long a, long long b) const{
    return ((a % b) + b) % b;
}
BigInteger::BigInteger(): negative_(0){
    digits_.push_back(0);
}
BigInteger::BigInteger(int value): negative_(value < 0){
    long long val = std::abs(static_cast<long long>(value));
    do {
        digits_.push_back(mod(val, 10));
        val /= 10;
    } while (val > 0);
}
BigInteger::BigInteger(long long value): negative_(value < 0){
    value = std::abs(value);
    do {
        digits_.push_back(mod(value, 10));
        value /= 10;
    } while (value > 0);
}
BigInteger::BigInteger(const std::string& str): negative_(false) {
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+'){
        negative_ = (str[0] == '-');
        start = 1;
    }
    while (start + 1 < str.size() && str[start] == '0'){
        ++start;
    }
    for (size_t i = str.size(); i > start; --i){
        digits_.push_back(str[i - 1] - '0');
    }
}
bool BigInteger::is_negative() const{
    return negative_;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& value){
    if (value.is_negative() && !value.is_zero()){
        os << '-';
    }
    for (int i = value.digits_.size() - 1; i > -1; --i){
        os << value.digits_[i];
    }
    return os;
}
std::istream& operator>>(std::istream& is, BigInteger& value){
    value.digits_.clear();
    std::string res;
    size_t start = 0;
    if (!(is >> res)) return is;
    if (res[0] == '-') {
        value.negative_ = true;
        ++start;
    } else if (res[0] == '+') {
        ++start;
    }
    while (start < res.size() - 1 && res[start] == '0') {
        ++start;
    }
    for (size_t i = res.size(); i > start; --i) {
        value.digits_.push_back(res[i - 1] - '0');
    }
    return is;
}
BigInteger BigInteger::operator-() const{
    BigInteger a = *this;
    if (!a.is_zero()) a.negative_ = !a.negative_;
    return a;
}
bool BigInteger::operator<(const BigInteger& rhs) const{
    if (is_zero() && rhs.is_zero()) return 0;
    if (is_negative() && !rhs.is_negative()){
        return 1;
    }
    if (!is_negative() && rhs.is_negative()){
        return 0;
    }
    if (digits_.size() < rhs.digits_.size()){
        return !is_negative();
    }
    if (digits_.size() > rhs.digits_.size()){
        return is_negative();
    }
    for (int i = digits_.size() - 1; i > -1; --i){
        if (digits_[i] < rhs.digits_[i]) return !is_negative();
        if (digits_[i] > rhs.digits_[i]) return is_negative();
    }
    return 0;
}
bool BigInteger::operator<=(const BigInteger& rhs) const{
    return !(rhs < *this);
}
bool BigInteger::operator>(const BigInteger& rhs) const{
    return (rhs < *this);
}
... (осталось: 196 строк)
