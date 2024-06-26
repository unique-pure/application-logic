#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class RationalNumber {
public:
    RationalNumber(int numerator, int denominator, int symbol = 1) : num(numerator), den(denominator), symbol(symbol) {}

    // Function to simplify the rational number
    RationalNumber simplify() {
        int gcdVal = gcd(num, den);
        int new_num = num / gcdVal;
        int new_den = den / gcdVal;
        return RationalNumber(new_num, new_den);
    }

    // Function to get the next rational number
    RationalNumber next() const {
        if (num < den) {
            return RationalNumber(num + 1, den);
        } else {
            return RationalNumber(1, den + 1);
        }
    }

    // Overloading the < operator for comparing rational numbers
    bool operator<(const RationalNumber& other) const {
        return symbol * num * other.den < other.symbol * other.num * den;
    }

    // Overloading the == operator for checking equality of rational numbers
    bool operator==(const RationalNumber& other) const {
        return symbol * num * other.den == other.symbol * other.num * den;
    }

    // Overloading the << operator for printing
    friend ostream& operator<<(ostream& os, const RationalNumber& rational) {
        if (rational.symbol == -1) os << "-";
        os << rational.num << "/" << rational.den;
        return os;
    }

    void set_symbol(int s) {
        symbol = s;
    }

private:
    int num;    // numerator
    int den;    // denominator, den != 0
    int symbol; // 1 for positive, -1 for negative

    // Function to calculate the greatest common divisor
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

// use the set to remove redundant rationals
set<RationalNumber> generateRationals(int N) {
    set<RationalNumber> rationals;
    RationalNumber cur = RationalNumber(0, 1);
    rationals.insert(cur.simplify());
    while (rationals.size() < N) {
        cur = cur.next();
        RationalNumber temp = cur.simplify();
        rationals.insert(temp);

        if (rationals.size() >= N) break;

        // get its opposite
        temp.set_symbol(-1);
        rationals.insert(temp);
    }
    return rationals;
}

int main(int argc, char* argv[]) {
    if (argc > 2 || (argc == 2 && atoi(argv[1]) <= 0)) {
        cout << "Usage: " << argv[0] << " [number_of_rationals]" << endl;
        return 1;
    }
    int N = argc == 2 ? atoi(argv[1]) : 20; // default 20 rationals

    set<RationalNumber> rationals = generateRationals(N);
    cout << "First " << N << " rationals: [ ";
    for (auto rational : rationals) {
        cout << rational << ", ";
    }
    cout << "\b\b ]" << endl;
    return 0;
}