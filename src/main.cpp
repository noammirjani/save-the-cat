//------------------------------------------
// CIRCLE THE CAT - EX4
//
// Wroten by Noam Mirjani and 
//		     Efrat Ilouz
// 
//
//------------------------------------------

#include "Controller.h"

int main()
{
	srand(time(NULL));

	try { Controller().run(); }
	catch (std::exception&) {}

	return EXIT_SUCCESS;
}
