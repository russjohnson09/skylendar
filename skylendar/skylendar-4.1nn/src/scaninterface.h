#include "../config.h"
#include "astrostring.h"
#include "scanclientinterface.h"

class ScanInterface
#ifdef QT
            : public OrgSkylendarScanclientInterface
#endif
{
public:

    ScanInterface(AstroString service, AstroString path);

    /** Destructor */
    ~ScanInterface() {}
};
