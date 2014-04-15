/*----------------------------------------------*/
/*                                  			*/
/*		PV 1.0   				    			*/
/*		Configuration Include File		    	*/
/*												*/
/*----------------------------------------------*/

#ifndef CONFIG
#define CONFIG


const printer = 0;
const encoder = 1;


class TConfiguration : private TObject, private TStreamable
{
public:
	TConfiguration();

	void dlgPrinterPort();

	void getPrinterPortName( char *rec );
	void getEncoderPortName( char *rec );

	Boolean passThrough();

private:
	ushort ports[2];


public:
	TConfiguration( StreamableInit )
		{ }

	static const char *const name;
	static TStreamable *build();

protected:
	virtual void write( opstream& );
	virtual void *read( ipstream& );

private:
	virtual const char *streamableName() const
		{ return name; }
};


inline ipstream& operator >> ( ipstream& is, TConfiguration& cl )
	{ return is >> (TStreamable&) cl; }
inline ipstream& operator >> ( ipstream& is, TConfiguration*& cl )
	{ return is >> (void *&) cl; }

inline opstream& operator << ( opstream& os, TConfiguration& cl )
	{ return os << (TStreamable&) cl; }
inline opstream& operator << ( opstream& os, TConfiguration* cl )
	{ return os << (TStreamable *) cl; }


extern TConfiguration *config;


#endif