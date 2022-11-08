#include "idirectoryaccess.h"
class DirectoryAccess : public IDirectoryAccess
{
public:
	State getCurState();
	QString getErrorString();

private: 
	State curState;
	QString errorString;

};