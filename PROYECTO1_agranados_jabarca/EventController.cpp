#include "EventController.h"

void EventController::printPrincipalMenu()
{
	cout << YELLOW << "MENU PRINCIPAL" << RESET << endl << endl
		<< BRIGHT_BLUE "1. " << RESET << "Configurar Evento." << endl << endl
		<< BRIGHT_BLUE "2. " << RESET << "Crear Codigo de Descuento." << RESET << endl << endl
		<< BRIGHT_BLUE "3. " << RESET << "Comprar Entrada." << RESET << endl << endl
		<< BRIGHT_BLUE "4. " << RESET << "Observar Disponibilidad de Asientos." << RESET << endl << endl
		<< BRIGHT_BLUE "5. " << RESET << "Acerca de." << RESET << endl << endl
		<< BRIGHT_BLUE "6. " << RESET << "Finalizar." << RESET << endl;
}

void EventController::printConfigMenu()
{
	cout << YELLOW << "CONFIGURACION DEL EVENTO " << RESET << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Crear un nuevo evento." << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Ver evento actual." << endl << endl
		<< BRIGHT_BLUE << "3. " << RESET << "Editar segmento." << endl << endl
		<< BRIGHT_BLUE << "4. " << RESET << "Finalizar evento." << endl << endl
		<< BRIGHT_BLUE << "5. " << RESET << "Volver." << endl;
}

void EventController::printConfigPriceDiscountMenu()
{
	cout << YELLOW << "CONFIGURACION DE DESCUENTOS " << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Obtener codigo de descuento " << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Volver. " << endl;
}

void EventController::printTicketSellMenu()
{
	cout << YELLOW << "TAQUILLA DE TIQUETES " << RESET << endl << endl
		<< BRIGHT_BLUE << "1. " << RESET << "Comprar tiquetes. " << endl << endl
		<< BRIGHT_BLUE << "2. " << RESET << "Visualizar disponibilidad asientos. " << endl << endl
		<< BRIGHT_BLUE << "3. " << RESET << "Volver. " << endl;
}

void EventController::printShowSegmentSeatsFlow(const int& segmentNumber)
{
	for (int i = 0; i < segmentNumber; i++)
	{
		cout << i + 1 << ". Segmento " << i + 1 << endl;
	}
}

void EventController::validateUserOption(int& userOption)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << endl << RED << "No se permiten letras, " << RESET
			<< "por favor vuelva a intentarlo: ";
		cin >> userOption;
	}
}

void EventController::captureMenuOption()
{
	cout << endl << endl << BRIGHT_CYAN << "Escoja una opcion: " << RESET;
	cin >> userOption;
	validateUserOption(userOption);
	system("cls");
}

void EventController::controlConfigMenuFlow()
{
	system("cls");
	printConfigMenu();
	captureMenuOption();
	if (userOption == 1)
	{
		configEvent.prepareEventData();
		system("cls");
	}
	else if (userOption == 2)
	{
		configEvent.printExportCurrentEvent();
		system("cls");
	}
	else if (userOption == 3)
	{
		
	}
	else if (userOption == 4)
	{
		configEvent.deleteEvent();
		system("cls");
	}
	else if (userOption == 5)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Numero de opcion no valido para este menu";
	}
}

void EventController::controlPriceDiscountMenuFlow()
{
	system("cls");
	printConfigPriceDiscountMenu();
	captureMenuOption();
	if (userOption == 1)
	{
		system("cls");
		if (!configEvent.isDiscountNumExist()) {
			cout << RED << "Error....No hay descuentos disponibles." << RESET << endl;
			cout << endl;
			system("pause");
			system("cls");
			return;
		}
		configEvent.printCodes();
	}
	else if (userOption == 2)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Numero de opcion no valido para este menu";
		system("pause");
		system("cls");
	}
}

void EventController::controlShowSegmentSeatsFlow()
{
	int segmentNumber = configEvent.getSizeSegmentsSpace();
	if (segmentNumber == 0) {
		system("cls");
		cout << "No se puede visualizar ningun segmento aun. Por favor configure un evento primero."
			<< endl << endl;
		system("pause");
		system("cls");
		return;
	}
	printShowSegmentSeatsFlow(segmentNumber);
	captureMenuOption();

	while ((userOption < 1 || userOption > segmentNumber) || cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		system("cls");
		cout << "Seleccione una opcion entre 1 y " << segmentNumber << endl << endl;
		printShowSegmentSeatsFlow(segmentNumber);
		captureMenuOption();
	}
	configEvent.inicializateSeatsSpace(userOption);
	configEvent.createdSegmentSeats();
	configEvent.printSegment();
	cout << endl;
	system("pause");
	system("cls");
}

void EventController::printAboutUs()
{
	system("cls");
	configEvent.aboutUs();
	cout << endl << endl;
	system("pause");
	system("cls");
}

void EventController::controlPrincipalMenuFlow()
{
	while (true)
	{
		printPrincipalMenu();
		captureMenuOption();
		if (userOption == 1)
		{
			controlConfigMenuFlow();
		}
		else if (userOption == 2)
		{
			controlPriceDiscountMenuFlow();
		}
		else if (userOption == 3)
		{
			controlTicketSellMenuFlow();
		}
		else if (userOption == 4)
		{
			configEvent.showStatusOfEvent();
			system("pause");
			system("cls");
		}
		else if (userOption == 5)
		{
			printAboutUs();
		}
		else if (userOption == 6)
		{
			cout << GREEN << "Saliendo del programa... " << RESET << endl;
			break;
		}
		else
		{
			cout << RED << "Numero de opcion no valido para este menu" << RESET << endl << endl;
		}
	}
}
void EventController::controlTicketSellMenuFlow()
{
	system("cls");
	if (!configEvent.isSegmentExist()) {
		cout << RED << "Error....No existen eventos." << RESET << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}
	printTicketSellMenu();
	captureMenuOption();

	if (userOption == 1)
	{
		configEvent.showStatusOfEvent();
		if (configEvent.isFullEvent())
		{
			system("pause");
			system("cls");
			return;
		}
		configEvent.controlTicketSoldEvent();
	}
	else if (userOption == 2)
	{
		configEvent.showStatusOfEvent();
		system("pause");
		system("cls");
	}
	else if (userOption == 3)
	{
		cout << GREEN << "Usted sera regresado al menu principal" << RESET << endl << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Numero de opcion no valido para este menu." << endl;
	}
}