#ifndef ASTROPERMS_H
#define ASTROPERMS_H

#include <astroresources.h>

extern const char *AccessModes[];

class AstroPerms
{
 public:

	inline AstroPerms() { Init(); }
	inline void Init() { Owner = Asr->DbUser; Access = Private; }
	inline bool CanRead() const { return Owner == Asr->DbUser || Access != Private; }
	inline bool CanWrite() const { return Owner == Asr->DbUser || Access == Shared; }
	inline const char* Mode() const { return AccessModes[Access]; }
	inline enum Access Mode(const AstroString& as) const
	{
		for(int i = 0; i < 3; i++)
			if(as == AccessModes[i])
	      return (enum Access)i;
		return Private;
	}

	AstroString Owner;
	enum Access Access;
};

#endif
