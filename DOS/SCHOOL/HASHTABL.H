
typedef long Key;
enum Boolean { False, True };

struct TCell;


class THashTable
{
public:
	THashTable( int size );
	virtual ~THashTable();

	virtual Boolean Insert( Key key, int data );
	virtual Boolean Find( Key key, int &data );
	virtual Boolean Delete( Key key );

	float GetLoadRatio();

private:
	virtual int FindAddress( Key key );

	virtual int CalculateHome( Key key );
	virtual int CalculateStep( Key key );

	int fSize;
	TCell *fTable;
	int fCount;
};
