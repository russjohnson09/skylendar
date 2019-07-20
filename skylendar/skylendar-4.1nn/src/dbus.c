#include <processthreadsapi.h>

STARTUPINFO Startup;
PROCESS_INFORMATION ProcessInfo;

void main()
{
		char buf[200];
		/*start /B */
		strcpy(buf, "dbus-daemon --config-file=\"");
		strcat(buf, SKYPATH);
		strcat(buf, "/session.conf\"");
		if(CreateProcessA(NULL, LPSTR(buf), NULL, NULL, TRUE, DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &Startup, &ProcessInfo) == 0);
}
