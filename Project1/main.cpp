#include<iostream>
#include<stdio.h>
#include<math.h>

double func(double x, double y, double z, int num)
{
	switch (num)
	{
	case 0: 
		return (exp(x)*y - exp(-x * x) - z) / (x + 1);
	case 1:
		return z;
	default:
		return -99999999;
	}
}

double rungeAdditive(double *x, double *y, double *z, double h, int i, int num) //Разберись с системой выбора необходимого коэффициента. Вроде всё правильно написал, но проверь в любом случае.
{
	double k1 = func(x[i], y[i], z[i], num);
	double k2 = func(x[i] + h / 2, y[i] + h * k1 * num / 2, z[i] + h * k1 * (1 - num) / 2, num);
	double k3 = func(x[i] + h / 2, y[i] + h * k2 * num / 2, z[i] + h * k2 * (1 - num) / 2, num);
	double k4 = func(x[i] + h, y[i] + h * k3 * num, z[i] + h * k3 * (1 - num), num);
	return h*(k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void rungeFull(double *x, double *y, double *z, double h, int n)
{
	for (int i = n; i > 0; i--) // Обратить внимание! Из начальных условий взять вначале левую границу я не смог, поэтому Рунге считается в обратном порядке.
	{
		x[i - 1] = x[i] - h;
		z[i - 1] = z[i] - rungeAdditive(x, y, z, h, i, 0); // Порядок вычисления не важен, но на всякий оставлю так, как в системе.
		y[i - 1] = y[i] - rungeAdditive(x, y, z, h, i, 1);
	}
}


int main()
{
	double *x, *y, *z, h = 0.001, eps = 0.001;
	double alpha = 0; // Начальное условие. Лень проверять, думай сама, ок?
	int n = 1 / h;
	x = new double[n];
	y = new double[n];
	z = new double[n];
	/*do
	{  
		x[n - 1] = 1;
		y[n - 1] = alpha;
		z[n - 1] = -alpha / 2;
		rungeFull(x, y, z, h, n);
		// Здесь должно быть изменение альфы. Пока не знаю, как красиво сделать. Maybe alpha = z[0]. Need to think.
	} while (fabs(z[0]>eps));*/
	rungeFull(x, y, z, h, n);
	return 0;
}