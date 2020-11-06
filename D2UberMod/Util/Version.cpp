#include "Version.h"
#include "..\framework.h"

std::string D2Version(short major, short minor, short rev, short subrev) { 
    if (major != 1) return "Unknown";
    if (minor == 0 && rev == 7 && subrev == 0) return "1.07";
    if (minor == 0 && rev == 8 && subrev == 28) return "1.08";
    if (minor == 0 && rev == 9 && subrev == 19) return "1.09";
    if (minor == 0 && rev == 9 && subrev == 20) return "1.09b";
    if (minor == 0 && rev == 9 && subrev == 22) return "1.09d";
    if (minor == 0 && rev == 10 && subrev == 39) return "1.10";
    if (minor == 0 && rev == 11 && subrev == 45) return "1.11";
    if (minor == 0 && rev == 11 && subrev == 46) return "1.11b";
    if (minor == 0 && rev == 12 && subrev == 49) return "1.12";
    if (minor == 0 && rev == 13 && subrev == 60) return "1.13c";
    if (minor == 0 && rev == 13 && subrev == 64) return "1.13d";
    if (minor == 14 && rev == 0 && subrev == 64) return "1.14a";
    if (minor == 14 && rev == 1 && subrev == 68) return "1.14b";
    if (minor == 14 && rev == 2 && subrev == 70) return "1.14c";
    if (minor == 14 && rev == 3 && subrev == 71) return "1.14d";
    return "Unknown";
}

std::string Version::GetVersionString() {
    std::string name = "Game.exe";
    LPSTR szVersionFile = name.data();
    DWORD  verHandle = 0;
    UINT   size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD  verSize = GetFileVersionInfoSizeA(szVersionFile, &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfoA(szVersionFile, 0, verSize, verData))
        {
            if (VerQueryValueA(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size))
            {
                if (size)
                {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        return D2Version(
                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
                            (verInfo->dwFileVersionMS >> 0) & 0xffff,
                            (verInfo->dwFileVersionLS >> 16) & 0xffff,
                            (verInfo->dwFileVersionLS >> 0) & 0xffff
                        );
                    }
                }
            }
        }
        delete[] verData;
    }
    return "Unknown";
}