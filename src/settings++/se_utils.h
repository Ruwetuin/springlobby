#ifndef SE_UTILS_H_
#define SE_UTILS_H_

#include <wx/string.h>

//#define _S(v) wxString(v.c_str(),wxConvUTF8)

void loadUnitsync();

int fromString(const wxString& s);

void openUrl(const wxString& url);


#endif /*SE_UTILS_H_*/

