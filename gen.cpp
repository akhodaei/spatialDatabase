#include <iostream.h>
#include <stdlib.h>

const int CNum = 10;

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x < y ? y : x)

void GenerateConstraints(void);

int nNumPoint;
double dPointX[CNum];
double dPointY[CNum];

void main()
{
	cout << "Input Number of Points :\n";
	cin >> nNumPoint;

	if (nNumPoint > CNum || nNumPoint < 2)
	{
		cout << "Limit : 2 - ";
		cout << CNum;
		return;
	}

	for (int i=0; i<nNumPoint; i++)
	{
		cout << "Point ";
		cout << i;
		cout << "\n";

		cin >> dPointX[i];
		cin >> dPointY[i];

		cout << "\n";
	}

	GenerateConstraints();

	cout << "done.\n";
}

void GenLine(double& dX, double& dY, double& dConst, double x1, double y1, double x2, double y2)
{
	dX = y2 - y1;
	dY = x1 - x2;
	dConst = x1*(y2-y1) + y1*(x1-x2);
}

void GenerateConstraints(void)
{
	double dX, dY, dConst;

	if (nNumPoint == 2)
	{
		GenLine(dX, dY, dConst, dPointX[0], dPointY[0], dPointX[1], dPointY[1]);
		cout << dX << " x " << dY << " y " << "<= " << dConst << "\n";
		cout << dX << " x " << dY << " y " << ">= " << dConst << "\n";
		if (dPointX[0] != dPointX[1])
		{
			cout << "x >= " << min(dPointX[0], dPointX[1]) << "\n";
			cout << "x <= " << max(dPointX[0], dPointX[1]) << "\n";
		}
		else
		{
			cout << "y >= " << min(dPointY[0], dPointY[1]) << "\n";
			cout << "y <= " << max(dPointY[0], dPointY[1]) << "\n";
		}
	}
	else
	{
		for (int i=0; i<nNumPoint; i++)
		{
			bool bGreater;
			double dNextX, dNextY;
			GenLine(dX, dY, dConst, dPointX[i], dPointY[i], 
					dPointX[(i+1) % nNumPoint], dPointY[(i+1) % nNumPoint]);
			dNextX = dPointX[(i+2) % nNumPoint];
			dNextY = dPointY[(i+2) % nNumPoint];

			double dTemp = dX * dNextX + dY * dNextY;
			if (dTemp > dConst)
				bGreater = true;
			else if (dTemp < dConst)
				bGreater = false;
			else
			{
				cout << "\n Error : Same Line\n";
				exit(0);
			}

			if (dX != 0)
			{
				cout << (dX>0? "+" : "-");
				if (dX>0)
				{
					if (dX!=1)
						cout << dX;
				}
				else
				{
					if (dX!=-1)
						cout << -dX;
				}
				cout << " x ";
			}
			if (dY != 0)
			{
				cout << (dY>0? "+" : "-");
				if (dY>0)
				{
					if (dY!=1)
						cout << dY;
				}
				else
				{
					if (dY!=-1)
						cout << -dY;
				}
				cout << " y ";
			}
			cout << (bGreater? ">= " : "<= ") << dConst << "\n";
		}
	}
}

void PrintPoints(void)
{
	for (int i=0; i < nNumPoint; i++)
	{
		cout << dPointX[i];
		cout << "  ";
		cout << dPointY[i];
		cout << "\n";
	}

}

