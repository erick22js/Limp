#ifndef limpextra_h
#define limpextra_h


#include <LimpExtra/bus_std.h>
#include <LimpExtra/peri_stdout.h>
#include <LimpExtra/peri_hd.h>


/**

	SLI => Standard Limp Interfacing
	
	@Periphericals
	
	* Every one must begin with a interruption
	* Every one must provide a standard code interface for indentification:
		0x10 => Type Peripherical: Returns
			1-Stdout; 2-Disk Drive; 3-Flash Drive; 4-Keyboard; 5-Mouse; 6-Controller;
			7-Monitor; 8-Sound Card; 9-Network Card
	
*/


#endif // limpextra_h
