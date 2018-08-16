#include "stdafx.h"
#include "jsBindFunctions.h"
#include "base_functions.h"
#include "global.h"


jsValue JS_CALL findWindow(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	std::string g_Class(jsToTempString(es, val0));
	std::string g_Title(UTF8ToGBK(jsToTempString(es, val1)));
	HWND hWnd = FindWindow(g_Class.c_str(), g_Title.c_str());
	return jsInt((int)hWnd);
}

jsValue JS_CALL openProcess(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	char ProcessName[100] = { NULL };
	sprintf_s(ProcessName, "%s", UTF8ToGBK(jsToString(es, val0)).c_str());
	g_dwProcessId = getProcessIdByProcessName(ProcessName);
	g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, g_dwProcessId);
	return jsInt((int)g_hProcess);
}

jsValue JS_CALL getOpenedProcessID(jsExecState es)
{
	return jsInt((int)g_dwProcessId);
}

jsValue JS_CALL readByte(jsExecState es)
{
	BYTE buffer = NULL;
	jsValue val0 = jsArg(es, 0);
	if (val0)
		ReadProcessMemory(g_hProcess, (LPCVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	return jsInt(buffer);
}

jsValue JS_CALL readShort(jsExecState es)
{
	short buffer = NULL;
	jsValue val0 = jsArg(es, 0);
	if (val0)
		ReadProcessMemory(g_hProcess, (LPCVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	return jsInt(buffer);
}

jsValue JS_CALL readInteger(jsExecState es)
{
	int buffer = NULL;
	jsValue val0 = jsArg(es, 0);
	if(val0)
		ReadProcessMemory(g_hProcess,(LPCVOID)jsToInt(es, val0),&buffer,sizeof(buffer),NULL);
	return jsInt(buffer);
}

jsValue JS_CALL readFloat(jsExecState es)
{
	float buffer = NULL;
	jsValue val0 = jsArg(es, 0);
	if (val0)
		ReadProcessMemory(g_hProcess, (LPCVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	return jsFloat(buffer);
}

jsValue JS_CALL readDouble(jsExecState es)
{
	double buffer = NULL;
	jsValue val0 = jsArg(es, 0);
	if (val0)
		ReadProcessMemory(g_hProcess, (LPCVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	return jsDouble(buffer);
}

jsValue JS_CALL writeByte(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0 && val1) {
		BYTE buffer = (BYTE)jsToInt(es, val1);
		result = WriteProcessMemory(g_hProcess, (LPVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	}
	return jsBoolean(result);
}

jsValue JS_CALL writeShort(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0 && val1) {
		short buffer = (short)jsToInt(es, val1);
		result = WriteProcessMemory(g_hProcess, (LPVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	}
	return jsBoolean(result);
}

jsValue JS_CALL writeInteger(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0 && val1) {
		int buffer = (int)jsToInt(es, val1);
		result = WriteProcessMemory(g_hProcess, (LPVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	}
	return jsBoolean(result);
}

jsValue JS_CALL writeFloat(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0 && val1) {
		float buffer = (float)jsToInt(es, val1);
		result = WriteProcessMemory(g_hProcess, (LPVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	}
	return jsBoolean(result);
}

jsValue JS_CALL writeDouble(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0 && val1) {
		double buffer = (double)jsToInt(es, val1);
		result = WriteProcessMemory(g_hProcess, (LPVOID)jsToInt(es, val0), &buffer, sizeof(buffer), NULL);
	}
	return jsBoolean(result);
}

jsValue JS_CALL mb_AutoAssemble(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	jsValue val1 = jsArg(es, 1);
	BOOL result;
	if (val0)
	{
		
		int toggle = 1;
		if (jsIsNull(val1))
		{
			toggle = jsToInt(es, val1);
		}
		std::string script(jsToTempString(es, val0));
		MessageBox(NULL, (char*)script.c_str(),"aa",MB_OK);
		result = autoAssemble(g_hProcess, (char*)script.c_str(), toggle);
	}
	return jsBoolean(result);
}


jsValue JS_CALL mb_GetAddress(jsExecState es)
{
	jsValue val0 = jsArg(es, 0);
	int result;
	if (val0)
	{
		std::string expression(jsToTempString(es, val0));
		result = getAddress(g_hProcess, (char*)expression.c_str());
	}
	return jsInt(result);
}




VOID jsBindFunctions() 
{
	jsBindFunction("findWindow", findWindow, 2);
	jsBindFunction("openProcess", openProcess, 1);
	jsBindFunction("getOpenedProcessID", getOpenedProcessID, 0);
	// ¶Á
	jsBindFunction("readByte", readByte, 1);
	jsBindFunction("readShort", readShort, 1);
	jsBindFunction("readInteger", readInteger, 1);
	jsBindFunction("readFloat", readFloat, 1);
	jsBindFunction("readDouble", readDouble, 1);
	// Ð´
	jsBindFunction("writeByte", writeByte, 2);
	jsBindFunction("writeShort", writeShort, 2);
	jsBindFunction("writeInteger", writeInteger, 2);
	jsBindFunction("writeFloat", writeFloat, 2);
	jsBindFunction("writeDouble", writeDouble, 2);

	jsBindFunction("autoAssemble", mb_AutoAssemble, 2);
	jsBindFunction("getAddress", mb_GetAddress, 1);



}