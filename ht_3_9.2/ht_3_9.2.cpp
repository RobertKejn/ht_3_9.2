#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class big_integer {
private:
	std::vector<int> v;

	std::vector<int>summ(std::vector<int>& v1, std::vector<int>&& v2) {
		std::vector<int> res;
		std::vector<int>& sub = v2;

		if (v1.size() > v2.size()) {
			res = v1;
		}
		else {
			res = v2;
			sub = v1;
		}
		int summ = 0;
		for (int i = 0; i < res.size(); ++i) {
			summ = summ + res[i] + (i < sub.size() ? sub[i] : 0);
			res[i] = summ % 10;
			summ = summ / 10;
		}
		if (summ > 0)res.push_back(summ);

		return res;
	}

	std::vector<int> multiply(int vector_digit, int vector_power, int digit, int power) {
		int res_power = vector_power + power;
		int res_digit = vector_digit * digit;
		std::vector<int> res_vector;
		for (int i = 0; i < res_power; ++i) res_vector.push_back(0);
		while (res_digit > 0) {
			res_vector.push_back(res_digit % 10);
			res_digit = res_digit / 10;
		}
		return res_vector;
	}

public:
	big_integer() {};

	big_integer(big_integer&& b) : v(std::exchange(v, b.v)) { }

	big_integer(std::string s) {
		for (int i = s.length() - 1; i >= 0; i--) {
			char c = s[i];
			v.push_back(std::stoi(&c));
		}
	};

	big_integer(const big_integer& b) : v(b.v) {}

	big_integer(std::vector<int> v) {
		this->v = v;
	}

	big_integer operator+(big_integer& b) {
		std::vector<int> res;
		std::vector<int>& sub = b.v;

		if (this->v.size() > b.v.size()) {
			res = this->v;
		}
		else {
			res = b.v;
			sub = this->v;
		}
		int summ = 0;
		for (int i = 0; i < res.size(); ++i) {
			summ = summ + res[i] + (i<sub.size() ? sub[i] : 0);
			res[i] = summ % 10;
			summ = summ / 10;
		}
		if (summ > 0)res.push_back(summ);

		big_integer b1;
		b1.v = res;
		return b1;
	}

	big_integer operator*(int&& c) {
		std::vector<int> res;
		
		for (int i = 0; i < this->v.size(); ++i) {
			int pow_count = 0;
			int pow = c;
			while (pow > 0) {
				res = summ(res, multiply(this->v[i], i, pow % 10, pow_count));
				pow = pow / 10;
				++pow_count;
			}
		}

		big_integer b(res);
		return b;
	}

	big_integer operator*(int& c) {
		std::vector<int> res;

		for (int i = 0; i < this->v.size(); ++i) {
			int pow_count = 0;
			int pow = c;
			while (pow > 0) {
				res = summ(res, multiply(this->v[i], i, pow % 10, pow_count));
				pow = pow / 10;
				++pow_count;
			}
		}
		big_integer b(res);
		return b;
	}

	big_integer operator*(big_integer& b) {
		std::vector<int> v = b.v;
		std::vector<int> res;
		for (int i = 0; i < this->v.size(); ++i) {
			for(int j = 0; j<v.size();++j){
				res = summ(res, multiply(this->v[i], i, v[j], j));
			}
		}

		big_integer b1(res);
		return b1;
	}

	big_integer& operator=(const big_integer& b) {
		this->v = b.v;
		return *this;

	}

	big_integer& operator=(big_integer&& b) noexcept {
		std::swap(v, b.v);
		return *this;
	}

	void str() {
		for (auto i = this->v.crbegin(); i != this->v.crend(); i++) {
			std::cout << *i;
		}
		std::cout << "\n";
	}
};

int main()
{
	auto b1 = big_integer("15");
	auto b2 = big_integer("15");

	big_integer b3(b1 + b2);
	big_integer b4(b1 * b2);

	b1.str();
	b2.str();
	b3.str();
}
