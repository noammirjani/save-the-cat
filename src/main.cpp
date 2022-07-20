//------------------------------------------
// CIRCLE THE CAT - EX4
//
// Wroten by Noam Mirjani 315216515 and 
//		     Efrat Ilouz 211357395
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
