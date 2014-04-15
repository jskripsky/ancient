#ifndef KONASAPP
#define KONASAPP


class Form;
class PersonList;

// Ausserdem etabliert diese Klasse den Zugriff auf die Datenbank
// (oder - in der ersten Konas-Version - alle wichtigen Dateien).
// Anschliessend l„sst es alle Anpassungs-Daten laden (wonach das Form-Objekt
// existiert).
// Dann folgt das Einlesen der Personenliste. Diese, oder deren Eintr„ge
// mssen nun mit der ListBox verbunden werden.
// Die Initialisierung ist abgeschlossen.

// Sollen die Daten einer Person ge„ndert werden, wird diese mit dem
// Form-Objekt verbunden und dessen Anzeige-Objekt sichtbar gemacht.

class KonasApp
{
public:
	//=== constructors and destructor =====
	KonasApp();
	virtual ~KonasApp();

protected:
        Form *form;
        PersonList *personList;
};


#endif