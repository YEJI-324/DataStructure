//c++로 쉽게풀어 쓴 자료구조
//Chapter 02 배열과 클래스
//프로그래밍 프로젝트 1

#include <cstdio>
#define MAX_DEGREE 80

class Polynomial {
	int degree;
	float coef[MAX_DEGREE];
public:
	Polynomial() { degree = 0; };

	void read() {
		printf("다항식의 최고 차수를 입력하시오 : ");
		scanf_s("%d", &degree);
		printf("각 항의 계수를 입력하시오 (총 %d개) : ", degree + 1);
		for (int i = 0; i <= degree; i++)
			scanf_s("%f", coef + i);
	}

	void display(char *str="Poly = ") {
		printf("\t%s", str);
		for (int i = 0; i < degree; i++) {
			if (coef[i] == 1)
				printf("x^%d + ", degree - 1);
			else if(coef[i]!=0)
				printf("%5.1f x^%d + ", coef[i], degree - i);
		}
		if(coef[degree]!= 0) printf("%4.1f\n", coef[degree]);
	}

	void add(Polynomial a, Polynomial b) {
		if (a.degree > b.degree) {
			*this = a;
			for (int i = 0; i <= b.degree; i++) {
				coef[i + (degree - b.degree)] += b.coef[i];
			}
		}
		else {
			*this = b;
			for (int i = 0; i <= a.degree; i++) {
				coef[i + (degree - a.degree)] += a.coef[i];
			}
		}
		trim();
	}

	void sub(Polynomial a, Polynomial b) {
		if (a.degree > b.degree) {
			*this = a;
			for (int i = 0; i <= degree; i++) {
				coef[i + (degree - b.degree)] -= b.coef[i];
			}
		}
		else {
			*this = b;
			for (int i = 0; i <= degree; i++) {
				coef[i + (degree - a.degree)] -= a.coef[i];
			}
			negate();
		}
		trim();
	}

	void mult(Polynomial a, Polynomial b) {
		*this = a;
		int temp = degree; // 기존 차수 저장
		degree += b.degree; // multiple polynomial degree;
		int *temporary = new int[degree + 1];
		for (int i = 0; i <= degree; i++)  temporary[i] = 0; //initialize

		for (int i = 0; i <= temp; i++) {
			for (int j = 0; j <= b.degree; j++) {
				temporary[i+j] += coef[i] * b.coef[j];
			}
		}
		for (int i = 0; i <= degree; i++) {
			coef[i] = temporary[i];
		}
		trim();
	}

	bool isZero() { return degree = 0; }
	void negate() {
		for (int i = 0; i <= degree; i++)
			coef[i] = -1 * coef[i];
	}

	void trim() {
		int count = 0;
		int i = 0;
		while (coef[i] == 0) {
			count++;
			i++;
		}
		if (count != 0) {
			int temp = degree;
			degree -= count;
			for (i = 0; i <= temp - count; i++) {
				coef[i] = coef[i + count];
			}
		}
	}
};

int main() {
	Polynomial a, b, c;
	a.read();
	b.read();

	a.display("A = ");
	b.display("B = ");
	c.add(a, b);
	c.display("add = ");
	c.sub(a, b);
	c.display("sub = ");
	c.mult(a, b);
	c.display("multiple = ");

	return 0;
}
