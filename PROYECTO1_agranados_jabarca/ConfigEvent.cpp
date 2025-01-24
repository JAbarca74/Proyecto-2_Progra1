#include "ConfigEvent.h"

void ConfigEvent::printSeparatorIdeas()
{
	cout << endl << BRIGHT_CYAN << separatorIdeas << RESET << endl << endl;
}

void ConfigEvent::printInicializeEventData()
{
	cout << YELLOW << "INFORMACION DEL EVENTO: " << RESET << endl << endl
		<< "Nombre del evento    |   " << BRIGHT_CYAN << nameEvent << RESET << endl
		<< "Fecha del evento     |   " << BRIGHT_CYAN << dateEvent << RESET << endl
		<< "Numero de segmentos  |   " << BRIGHT_CYAN << segmentsEvent << RESET << endl
		<< "Numero de asientos   |   " << BRIGHT_CYAN << calculateTotalSeats() << RESET << endl;
}

void ConfigEvent::confirmSegment()
{
	while (segmentsEvent < 1)
	{
		cout << RED << "Numero de segmentos invalido. Intente nuevamente." << RESET << endl
			<< GREEN << "Ingrese el numero de segmentos (mayor a 0): " << RESET;
		cin >> segmentsEvent;
		printSeparatorIdeas();

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			segmentsEvent = 0;
		}
	}
}

int ConfigEvent::getSizeSegmentsSpace()
{
	return sizeSegmentsSpace;
}

int ConfigEvent::calculateTotalSeats()
{
	int totalSeats = 0;
	Node<Segment>* currentNode = segmentsSpace.getHead();
	while (currentNode != nullptr) {
		Segment& segment = currentNode->getElement();
		totalSeats += (segment.getNumberSeatingColumns() * segment.getNumberSeatingRows());
		currentNode = currentNode->getNext();
	}
	return totalSeats;
}

void ConfigEvent::resizeSegmentsSpace(int newSize)
{
	while (segmentsSpace.getHead() != nullptr) {
		segmentsSpace.deleteNode(0);
	}

	// Add new segments
	for (int i = 0; i < newSize; i++) {
		segmentsSpace.addNewNode(Segment());
	}
	sizeSegmentsSpace = newSize;
}

void ConfigEvent::prepareEventData()
{
	int temporalRows = 0;
	int temporalColumns = 0;
	float temporalPrice = 0;
	printInicializeEventData();
	captureEventData(temporalRows, temporalColumns, temporalPrice);
	system("cls");
	printInicializeEventData();
	cout << endl;
	system("pause");
}

void ConfigEvent::printExportCurrentEvent()
{
	system("cls");
	printInicializeEventData();
	cout << endl;
	system("pause");
}


void ConfigEvent::deleteEvent()
{
	while (segmentsSpace.getHead() != nullptr) {
		segmentsSpace.deleteNode(0);
	}

	// Clear discountCodes
	while (discountCodes.getHead() != nullptr) {
		discountCodes.deleteNode(0);
	}

	// Reset event details
	nameEvent = "-";
	dateEvent = "-";
	segmentsEvent = 0;
	sizeSegmentsSpace = 0;
	codes = 0;
	acountWithDiscount = 0;
	discount = 0.0f;

	cout << GREEN << "El evento ha sido eliminado completamente." << RESET << endl;
	system("pause");
}

void ConfigEvent::configureMatrixDimensions(int segmentNumber)
{
	segmentNumber--;
	Node<Segment>* currentNode = segmentsSpace.getHead();
	for (int i = 0; i < segmentNumber && currentNode != nullptr; i++) {
		currentNode = currentNode->getNext();
	}

	if (currentNode != nullptr) {
		totalRows = currentNode->getElement().getNumberSeatingRows();
		totalColumns = currentNode->getElement().getNumberSeatingColumns();
	}
}

void ConfigEvent::inicializateSeatsSpace(int segmentNumber)
{
	while (availableSeats.getHead() != nullptr) {
		delete availableSeats.getHead()->getElement();
		availableSeats.deleteNode(0);
	}

	// Get segment dimensions
	Segment* selectedSegment = getSegment(segmentNumber - 1);
	totalRows = selectedSegment->getNumberSeatingRows();
	totalColumns = selectedSegment->getNumberSeatingColumns();

	// Create new available seats list
	for (int i = 0; i < totalRows; i++) {
		List<string>* rowList = new List<string>();
		for (int j = 0; j < totalColumns; j++) {
			rowList->addNewNode("");
		}
		availableSeats.addNewNode(rowList);
	}
}

void ConfigEvent::createdSegmentSeats()
{
	Node<List<string>*>* rowNode = availableSeats.getHead();
	for (int letter = 0; letter < totalRows; letter++) {
		Node<string>* columnNode = rowNode->getElement()->getHead();
		for (int number = 0; number < totalColumns; number++) {
			string seatLabel;
			if (letter < 26) {
				seatLabel = string(1, 'A' + letter);
			}
			else {
				char firstLetter = 'A' + (letter / 26) - 1;
				char secondLetter = 'A' + (letter % 26);
				seatLabel = string(1, firstLetter) + string(1, secondLetter);
			}

			columnNode->setElement(seatLabel + to_string(number + 1));
			columnNode = columnNode->getNext();
		}
		rowNode = rowNode->getNext();
	}
}

void ConfigEvent::printSegment()
{
	Node<Segment>* segmentNode = segmentsSpace.getHead();
	for (int i = 0; i < sizeSegmentsSpace; i++)
	{
		Segment& currentSegment = segmentNode->getElement();
		int rows = currentSegment.getNumberSeatingRows();
		int columns = currentSegment.getNumberSeatingColumns();

		Node<List<string>*>* rowNode = availableSeats.getHead();
		for (int letter = 0; letter < rows; letter++)
		{
			Node<string>* columnNode = rowNode->getElement()->getHead();
			for (int number = 0; number < columns; number++)
			{
				cout << "[ |_" << columnNode->getElement() << "_| ] ";
				columnNode = columnNode->getNext();
			}
			cout << endl;
			rowNode = rowNode->getNext();
		}
		cout << endl;

		segmentNode = segmentNode->getNext();
	}
}

void ConfigEvent::getReserveSeat(string& reserveSeats)
{
	Node<List<string>*>* rowNode = availableSeats.getHead();
	for (int letter = 0; letter < totalRows; letter++)
	{
		Node<string>* columnNode = rowNode->getElement()->getHead();
		for (int number = 0; number < totalColumns; number++)
		{
			if (columnNode->getElement() == reserveSeats)
			{
				columnNode->setElement("XX");
				return;
			}
			columnNode = columnNode->getNext();
		}
		rowNode = rowNode->getNext();
	}
}

void ConfigEvent::showAvaibleSeats()
{
	printSegment();
}

void ConfigEvent::createVectorDiscounts(int size)
{
	while (discountCodes.getHead() != nullptr) {
		discountCodes.deleteNode(0);
	}
	for (int i = 0; i < size; i++) {
		discountCodes.addNewNode("");
	}
}


void ConfigEvent::generateDiscountCodes()
{
	int length = 6;
	char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	Node<string>* currentNode = discountCodes.getHead();
	for (int i = 0; i < acountWithDiscount; i++) {
		string code = "";
		for (int j = 0; j < length; j++) {
			int randomIndex = rand() % 36;
			code += alphanum[randomIndex];
		}

		if (currentNode) {
			currentNode->setElement(code);
			currentNode = currentNode->getNext();
		}
	}
}

void ConfigEvent::printCodes()
{
	Node<string>* currentNode = discountCodes.getHead();
	cout << BRIGHT_CYAN << "-------------Codigos Disponibles-------------" << RESET << endl;

	int codeCount = 0;
	while (currentNode != nullptr && codeCount < codes) {
		cout << GREEN << currentNode->getElement() << " || ";
		currentNode = currentNode->getNext();
		codeCount++;
	}

	cout << '\n';
	cout << YELLOW << "Elige la cantidad de codigos que necesites." << endl << LIGHT_PURPLE
		<< "(Cada codigo es valido unicamente para una entrada.)" << RESET;
	cout << endl << endl;
	system("pause");
	system("cls");
}


void ConfigEvent::deleteCode(string aCode)
{
	Node<string>* currentNode = discountCodes.getHead();
	Node<string>* prevNode = nullptr;
	int index = 0;

	while (currentNode != nullptr) {
		if (currentNode->getElement() == aCode) {
			// Remove the node
			if (prevNode == nullptr) {
				// If it's the first node
				discountCodes.deleteNode(0);
			}
			else {
				// Find the index and delete
				discountCodes.deleteNode(index);
			}
			codes--;
			return;
		}
		prevNode = currentNode;
		currentNode = currentNode->getNext();
		index++;
	}
}

float ConfigEvent::applyCodeDiscount(Segment* spaceSegment)
{
	float price = spaceSegment->getPrice();
	float priceWithDiscount = price - (price * discount / 100);
	return priceWithDiscount;
}


void ConfigEvent::processPurchase(int seatsPurchased, string& numberReserveSeats)
{
	int temporalSegment = 0, totalSeatsPurchase = 0, option = 0;
	string seleccionAsiento, auxCode = "";
	float temporalTotal = 0.0f, temporalDiscount = 0.0f, aux = 0.0f;

	client.collectAllInformation();
	do {
		cout << endl << "Digite la cantidad de asientos que desea comprar: ";
		cin >> aux;
		totalSeatsPurchase = static_cast <int>(aux);

		if (totalSeatsPurchase > 5 || totalSeatsPurchase > freeSeats)
		{
			cout << RED << "ERROR. El maximo son 5 asientos / No hay asientos suficientes. Intente de nuevo: " << endl;
		}
	} while (totalSeatsPurchase > 5 || totalSeatsPurchase > freeSeats);

	system("pause");
	system("cls");
	while (seatsPurchased < totalSeatsPurchase)
	{
		cout << "Estado actual de los segmentos disponibles: " << endl;
		showStatusOfEvent();
		if (sizeSegmentsSpace == 0)
		{
			return;
		}
		cout << "Digite el segmento en el que desea comprar (1 - " << sizeSegmentsSpace << "): ";
		cin >> aux;
		temporalSegment = static_cast <int>(aux);
		if (temporalSegment < 1 || temporalSegment > sizeSegmentsSpace || cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << RED << "Segmento invalido. Por favor, intente de nuevo." << RESET << endl;
			system("pause");
			system("cls");
			continue;
		}
		if (codes > 0)
		{
			cout << "Posee un codigo de descuento? " << endl <<
				"1. " << GREEN << "SI" << RESET << endl <<
				"2. " << RED << "NO" << RESET << endl <<
				"Opcion: ";
			cin >> option;
			if (option == 1)
			{
				cout << "Digite su codigo de descuento: ";
				cin >> auxCode;
				if (isCodeExist(auxCode))
				{
					cout << GREEN << "Codigo encontrado" << RESET << endl;
					deleteCode(auxCode);
				}
				else
				{
					while (!isCodeExist(auxCode))
					{
						cout << RED << "Error....No se encontro el codigo de descuento." << RESET << endl << endl;
						auxCode = "";
						cout << "Digite nuevamente el codigo: ";
						cin >> auxCode;
					}
					cout << GREEN << "Codigo encontrado" << RESET << endl;
					deleteCode(auxCode);
				}
			}
		}
		bool asientoReservado;
		do
		{
			cout << "Introduce el asiento (por ejemplo, A1): ";
			cin >> seleccionAsiento;

			asientoReservado = segmentsSpace[temporalSegment - 1].reserveSeat(seleccionAsiento);
			if (!asientoReservado)
			{
				cout << RED << "El asiento " << seleccionAsiento << " no existe o ya esta reservado." << RESET << endl;
			}
		} while (!asientoReservado);

		client.addReservedSeat(seleccionAsiento);
		seatsPurchased++;
		numberReserveSeats += seleccionAsiento + " ";
		cout << "Asiento " << seleccionAsiento << " reservado correctamente." << endl;
		freeSeats--;
		if (auxCode != "")
		{
			float precioConDescuento = applyCodeDiscount(getSegment(temporalSegment - 1));
			float precioOriginal = getSegment(temporalSegment - 1)->getPrice();
			temporalTotal += precioConDescuento;
			temporalDiscount += (precioOriginal - precioConDescuento);
		}
		else
		{
			temporalTotal += getSegment(temporalSegment - 1)->getPrice();
		}
		auxCode = "";
		int aux = 0;
		system("pause");
		system("cls");
	}
	printInvoice(totalSeatsPurchase, temporalDiscount, temporalTotal + temporalDiscount, temporalTotal);
	cout << endl;
	system("pause");
	system("cls");
}

void ConfigEvent::numberOfSeatsPurchase()
{
	int seatsPurchased = 0;
	string numberReserveSeats = "";
	processPurchase(seatsPurchased, numberReserveSeats);
	cout << "Haz comprado estos asientos: " << numberReserveSeats << endl;
}

void ConfigEvent::controlTicketSoldEvent()
{
	numberOfSeatsPurchase();
	system("pause");
	system("cls");
}

void ConfigEvent::reserveSeatInSegment(int segmentIndex, const string& seatCode)
{
	if (segmentIndex < 0 || segmentIndex >= sizeSegmentsSpace)
	{
		cout << "Segmento invalido." << endl;
		return;
	}
	if (segmentsSpace[segmentIndex].reserveSeat(seatCode))
	{
		cout << "Asiento " << seatCode << " reservado correctamente." << endl;
	}
	else
	{
		cout << "El asiento " << seatCode << " no está disponible o no existe." << endl;
	}
}

void ConfigEvent::showStatusOfEvent()
{
	if (sizeSegmentsSpace <= 0) {
		cout << RED << "ERROR. Configure un evento. " << RESET << endl << endl;
		return;
	}

	if (isFullEvent()) {
		cout << RED << "EL EVENTO ESTA LLENO" << RESET << endl << endl;
		return;
	}

	Node<Segment>* currentNode = segmentsSpace.getHead();
	for (int i = 0; currentNode != nullptr; i++) {
		cout << "Segmento " << i + 1 << ":\n";
		currentNode->getElement().printSeats();
		currentNode = currentNode->getNext();
	}
}

Segment* ConfigEvent::getSegment(int pos)
{
	Node<Segment>* currentNode = segmentsSpace.getHead();
	for (int i = 0; i < pos; i++) {
		if (currentNode == nullptr) return nullptr;
		currentNode = currentNode->getNext();
	}
	return &(currentNode->getElement());
}

bool ConfigEvent::isSegmentExist()
{
	if (getSizeSegmentsSpace() == 0)
	{
		return false;
	}
	return true;
}

bool ConfigEvent::isDiscountNumExist()
{
	if (acountWithDiscount == 0)
	{
		return false;
	}
	return true;
}

bool ConfigEvent::isCodeExist(string code) 
{
	Node<string>* currentNode = discountCodes.getHead();
	while (currentNode != nullptr) 
	{
		if (currentNode->getElement() == code) 
		{
			return true;
		}
		currentNode = currentNode->getNext();
	}
	return false;
}

bool ConfigEvent::isSeatAvailable(string& reserveSeats)
{
	for (int letter = 0; letter < totalRows; letter++)
	{
		for (int number = 0; number < totalColumns; number++)
		{
			if (availableSeats[letter][number] == reserveSeats)
			{
				return true;
			}
		}
	}
	return false;
}

bool ConfigEvent::isFullEvent()
{
	Node<Segment>* currentNode = segmentsSpace.getHead();
	while (currentNode != nullptr) {
		if (!currentNode->getElement().isFullTheEvent()) {
			return false;
		}
		currentNode = currentNode->getNext();
	}
	return true;
}

void ConfigEvent::captureEventData(int& temporalRows, int& temporalColumns, float temporalPrice)
{
	float aux = 0.0;
	cout << endl << BRIGHT_WHITE << "Ingrese el nombre del evento: " << RESET;
	cin.ignore();
	getline(cin, nameEvent);
	while (nameEvent.empty()) {
		cout << RED << "ERROR. " << RESET << "Ingrese un nombre verdadero de evento: ";
		getline(cin, nameEvent);
	}

	cout << BRIGHT_WHITE << "Ingrese la fecha del evento (formato DD/MM/YYYY): " << RESET;
	getline(cin, dateEvent);
	while (dateEvent.empty()) {
		cout << RED << "ERROR. " << RESET << "Ingrese una fecha verdadera de evento: ";
		getline(cin, dateEvent);
	}
	dateProcessorTool.confirmDateEvent(dateEvent);
	printSeparatorIdeas();

	cout << BRIGHT_WHITE << "Ingrese el numero de segmentos (mayor a 0): " << RESET;
	cin >> aux;
	segmentsEvent = static_cast<int>(aux);
	printSeparatorIdeas();
	confirmSegment();
	resizeSegmentsSpace(segmentsEvent);

	cout << BRIGHT_WHITE << "Ingrese la cantidad de entradas que desea que posean descuento: " << RESET;
	cin >> aux;
	acountWithDiscount = static_cast<int>(aux);
	codes = acountWithDiscount;
	createVectorDiscounts(acountWithDiscount);
	generateDiscountCodes();

	cout << BRIGHT_WHITE << "Ingrese el porcentaje de descuento deseado: " << RESET;
	cin >> aux;
	discount = static_cast<float>(aux);
	printSeparatorIdeas();

	for (int i = 0; i < sizeSegmentsSpace; i++) {
		cout << BRIGHT_WHITE << "Ingrese el numero de filas del segmento " << RESET << i + 1 << ": ";
		cin >> aux;
		temporalRows = static_cast<int>(aux);
		cout << BRIGHT_WHITE << "Ingrese el numero de columnas del segmento " << RESET << i + 1 << ": ";
		cin >> aux;
		temporalColumns = static_cast<int>(aux);
		cout << BRIGHT_WHITE << "Ingrese el precio de cada asiento del segmento " << RESET << i + 1 << ": ";
		cin >> temporalPrice;
		printSeparatorIdeas();

		// Update segment data
		Node<Segment>* currentNode = segmentsSpace.getHead();
		for (int j = 0; j < i; j++) {
			currentNode = currentNode->getNext();
		}
		currentNode->getElement().updateData(temporalRows, temporalColumns, temporalPrice);
	}
	freeSeats = calculateTotalSeats();
}

void ConfigEvent::printInvoice(int seatsPurchased, float anApplyDiscount, float aTotalPrice, float anFinalPrice)
{
	cout << endl << BRIGHT_CYAN << "\t     Factura" << endl
		<< " ----------------------------------" << endl << YELLOW << " | "
		<< " | Nombre del evento: " << nameEvent << endl << " | Fecha del evento: " << dateEvent << endl
		<< " ----------------------------------" << endl << LIGHT_PURPLE << " |\t Informacion personal." << endl
		<< " | " << endl << " | Nombre del Usuario:" << client.getPersonName() << endl
		<< " | Numero de Identificacion: " << client.getIdentification() << endl
		<< " | Fecha de nacimiento: " << client.getBirthdayDate() << endl
		<< " | " << endl << BRIGHT_YELLOW << " |\t Informacion de compra." << endl << " |" << endl
		<< " | Cantidad de Asientos adquiridos: " << seatsPurchased << endl << GREEN
		<< " | Precio total (sin descuento): " << aTotalPrice << endl << RED
		<< " | Cantidad del descuento aplicado: " << anApplyDiscount << endl
		<< " | " << endl << YELLOW << " |   Precio total a cancelar: " << anFinalPrice << endl
		<< " | " << endl << " ----------------------------------" << endl << BRIGHT_CYAN
		<< " | Gracias por adquirir cu entrada |" << endl << " |    con nosotros esperamos su    | "
		<< endl << " |     disfrute en este Evento     | " << endl
		<< " -----------------------------------" << endl << RESET;
}

void ConfigEvent::aboutUs()
{
	cout << BRIGHT_CYAN << "\t\t\t\t\t       ABOUT US:" << endl
	<< GREEN << "\t\t\t\t    _    ____  ____  ___    _    _   _ " << endl
	<< "\t\t\t\t   / \\  |  _ \\|  _ \\|_ _|  / \\  | \\ | |" << endl
	<< "\t\t\t\t  / _ \\ | | | | |_) || |  / _ \\ |  \\| |" << endl
	<< "\t\t\t\t / ___ \\| |_| |  _ < | | / ___ \\| |\\  |" << endl
    << "\t\t\t\t/_/   \\_\\____/|_| \\_\\___/_/   \\_\\_| \\_|" << endl
    << endl
	<< YELLOW "\t\t\t\t\t\t__   __" << endl
	<< "\t\t\t\t\t\t\\ \\ / /" << endl
	<< "\t\t\t\t\t\t \\ V / " << endl
	<< "\t\t\t\t\t\t  | |  " << endl
	<< "\t\t\t\t\t\t  |_|  " << endl
	<< endl
	<< RED << "\t\t\t\t       _ _____ _____ _____ ______  " << endl
	<< "\t\t\t\t      | | ____|  ___|  ___|  ___/ " << endl
	<< "\t\t\t\t   _  | |  _| | |_  | |_  |  _|   " << endl
	<< "\t\t\t\t  | |_| | |___|  _| |  _| | |___  " << endl
	<< "\t\t\t\t   \\___/|_____|_|   |_|   |_____|" << "" << endl
	<< BRIGHT_CYAN << "\t\t\t\t     Aspirantes a Ing.Sistemas." << RESET;
}

ConfigEvent::~ConfigEvent()
{
	Node<List<string>*>* currentRowNode = availableSeats.getHead();
	while (currentRowNode != nullptr) {
		delete currentRowNode->getElement();
		currentRowNode = currentRowNode->getNext();
	}
}
