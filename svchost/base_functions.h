#pragma once

std::string GBKToUTF8(const char * strGBK);

std::string UTF8ToGBK(const char * strUTF8);

DWORD getProcessIdByProcessName(const char * processName);
