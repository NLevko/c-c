# include <iostream>

using namespace std;


int gcd (int a, int b, int &x, int &y){
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	int x_1 = 0;
	int y_1 = 0;
	int d = gcd (b%a, a, x_1, y_1);
	x = y_1 - (b/a)*x_1;
	y = x_1;
	return d;
}

bool first_solution(int a, int b, int n, int &x, int &y, int &g) {
	g = gcd (abs(a), abs(b), x, y);
	if (n % g != 0)
		return false;
	x *= n / g;
	y *= n / g;
	if (a < 0)   x *= -1;
	if (b < 0)   y *= -1;
	return true;
}

int Nod( int a, int b) {
    int c;
    while (b) {
        c = a % b;
        a = b;
        b = c;
    }
    return abs(a);
}


int main()
{
	int coef = 0;
	int a = 0;
	int b = 0;
	int n = 0;
	int x_0 = 0;
	int y_0 = 0;
	int g_0 = 0;
	int x = 0;
	int y = 0;
	cin >> a >> b >> n;
	
	if (b == 0){
		cout << "No";
		return 1;
	}
	cout << "nod = " << Nod(a, b) << endl;


	if (b<0) {
		a*=-1;
		b*=-1;
		n*=-1;
	}
	if (n == 0) { 
	}

	if (a == 0 && b == 0) {
		x = 1;
		y = n/b;
		cout << x << " ";
		cout << y << "\n";
		
	return 0;
	}

	if (b == 0 && (n%a) == 0) {
		if (n/a < 0) {
		cout<<"No";
		return 1;
		}
		x = n/a;
		y = 0;
		cout << x << " ";
		cout << y << "\n";
		
	return 0;
	}

	if (a == 0 && (n%b) == 0) {
		x = 1;
		y = n/b;
		cout << x << " ";
		cout << y << "\n";
		
	return 0;
	}


	if(n%Nod(a, b) != 0) {
		cout << "No";
		return 1;
	}


	if(!first_solution(a, b, n, x_0, y_0, g_0)) {
		cout << "No";
		return 1;
	}
	if (n == 0) {
		x = x_0 + b/g_0;
		y = y_0 - a/g_0;
		cout << x << " ";
		cout << y << "\n";
		return 0;
	}

	x = x_0;

	if (x_0 >= 0) {
		for (int i = 0; x > 0; i++) {
			coef = i;
			x = x_0 - i*b/g_0;
		}
		x = x_0 - (coef)*b/g_0;
		y = y_0 + (coef)*a/g_0;
		if(x <= 0) {
			x = x_0 - (coef - 1)*b/g_0;
			y = y_0 + (coef - 1)*a/g_0;
		}
	} 

	if(x_0 < 0) {
		x = x_0;
		for (int i = 0; x < 0; ++i) {	
			coef = i;
			x = x_0 + i*b/g_0;
		}
		x = x_0 + (coef)*b/g_0;
		y = y_0 - (coef)*a/g_0;
		if(x <= 0){
			x = x_0 + (coef + 1)*b/g_0;
			y = y_0 - (coef - 1)*a/g_0;
		}

	}

	cout << x << " ";
	cout << y << "\n";
	
	return 0;
}