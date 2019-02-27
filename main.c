#define POCET_PARAM			3		//kolik parametru pro volani programu musi byt zadano (bez nazvu aplikace)
#define PARAM_SOUBOR		1		//kolikaty parametr pro volani programu je nazev databazoveho souboru
#define PARAM_RADKU			2		//kolikaty parametr pro volani programu je pocet radku
#define PARAM_ODDELOVAC		3		//kolikaty parametr pro volani programu je oddelovaci znak
#define VYSTUP				stdout	//Filedescriptor vystupu (obrazovka ... stdout)
#define MEZERA				'\t'	//Oddìlovaci znak sloupcu na vystupu (mezeru mezi sloupci vytvoøit znakem tabulatoru)

#include <stdio.h>
#include <stdlib.h>

/* Prepisuje soubor na vystup, pricemz vsechny znaky zadane jako oddelovac nahradi znakem
 * tabulatoru a po prepsani zadaneho poctu radku nebo po prepsani celeho souboru skonci
 *
 * Pozn. konsole muze vyzadovat zadani oddelovaciho znaku napr. strednik nebo mezera do uvozovek,
 *	     jinak je ignorovan a zavola aplikaci pouze se 2 parametry, coz skonci chybou 4!
 *
 * Navratove hodnoty:
 * 0 - Vypis probehl uspesne
 * 1 - Nepodarilo se otevrit zadany soubor pro cteni
 * 2 - Nepodarilo se nacist parametr poctu radku
 * 3 - Nepodarilo se nacist parametr oddelovace
 * 4 - Chybny pocet vstupnich parametru
 */

int main(int argc, char *argv[])
	{
	FILE* Soubor;
	int radku;
	char oddelovac;

	//Kontrola, zda byl zadan spravny pocet parametru
	if(argc != (POCET_PARAM) +1)
		{
		fprintf(stderr, "Chybny pocet vstupnich parametru. Program bude ukoncen.\n");
		return(4);
		}

	//Pokus se nacist parametr poctu radku, jinak skonci
	if(sscanf(argv[PARAM_RADKU], "%d", &radku) != 1 || radku < 0)
		{
		fprintf(stderr, "Nepodarilo se nacist parametr poctu radku. Program bude ukoncen.\n");
		return(2);
		}

	//Pokus se nacist parametr oddelovace, jinak skonci
	if(sscanf(argv[PARAM_ODDELOVAC], "%c", &oddelovac) != 1)
		{
		fprintf(stderr, "Nepodarilo se nacist parametr oddelovace. Program bude ukoncen.\n");
		return(3);
		}

	//Pokud soubor uz existuje, nacti ho, jinak skonci
	if((Soubor = fopen(argv[PARAM_SOUBOR], "rt")) != NULL)
		{
		int znak;
		int ret_tisk = 1;
		int linka = 1;

		//nacti prvni znak
		znak = getc(Soubor);

		// Prepis zadany pocet radku nebo soubor az do konce, prip. do zaplneni vystupu
		while(linka <= radku && znak != EOF && ret_tisk != EOF)
			{
			// pocitadlo radku
			if(znak == '\n')
				++linka;

			// hledani oddelovace
			if(znak == oddelovac)
				ret_tisk = putc(MEZERA, VYSTUP);	// nahrad oddelovac definovanym znakem
			else
				ret_tisk = putc(znak, VYSTUP);		// vypis znak na vystup
			// nacti dalsi znak
			znak = getc(Soubor);
			}

		fclose(Soubor);
		}
	else
		{
		return(1);
		}

	return(0);
	}
