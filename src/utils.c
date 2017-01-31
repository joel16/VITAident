#include "graphics.h"
#include "utils.h"

void setColor(Color color)
{
	psvDebugScreenSetFgColor(color);
}

int printStr(bool printStar, Color color, char message[250], char *info, ...)
{
	char buf[512];

	va_list opt;
	va_start(opt, info);
	
	if (printStar == true)
	{
		setColor(color); 
		printf("* "); 
	}
	
	setColor(WHITE); 
	printf("%s", message); 
	
	setColor(color); 
	int ret = vsnprintf(buf, sizeof(buf), info, opt);
	printTextScreen(buf);
	va_end(opt);
	
	return ret;
}

void getSizeString(char *string, uint64_t size) //Thanks TheOfficialFloW
{
	double double_size = (double)size;

	int i = 0;
	static char *units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	while (double_size >= 1024.0f) {
		double_size /= 1024.0f;
		i++;
	}

	sprintf(string, "%.*f %s", (i == 0) ? 0 : 2, double_size, units[i]);
}

const char * concat(char* s1, char* s2)
{
    char *ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}