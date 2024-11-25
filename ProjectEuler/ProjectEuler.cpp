// ProjectEuler.cpp : Defines the entry point for the application.
//

#include "ProjectEuler.h"
//#include "Problem1.h"
//#include "Problem2.h"
//#include "Problem3.h"
//#include "Problem4.h"
//#include "Problem5.h"
//#include "Problem6.h"
//#include "Problem7.h"
//#include "Problem8.h"
//#include "Problem9.h"
//#include "Problem10.h"
#include "Timer.h"

#include <map>

using namespace std;



int main()
{
	int lines;
	cin >> lines;
	for (int i = 0; i < lines; i++)
	{
		long long nb;
		cin >> nb;
		//cout << Problem3::Solve(nb) << endl;

		Timer::TimeAndOutput([nb]() {		
			//cout << Solve(nb) << endl;
		});
	}
	
	return 0;
}
