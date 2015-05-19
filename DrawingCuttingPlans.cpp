
#include "stdafx.h"
#include <string>
#include <vector>

#ifdef __linux__
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#endif

#include <stdio.h>
#include <wchar.h>
#include "include/CImg.h"
#include "include/pugixml.hpp"

#include "DrawingCuttingPlans.h"
#include "headers/Geometry.h"
#include "src/Detail.cpp"
#include "src/GenericArc.cpp"
#include "src/EuroGrooveArc.cpp"
#include "src/CurveSawsArc.cpp"
#include "src/GenericLine.cpp"
#include "src/CurveSawsLine.cpp"
#include "src/EuroGrooveLine.cpp"

#define TIME_LEN 34
#define PI 3.141592653589793238463
#define BASE_ERRNO     7

static wchar_t *g_PropNames[] = { L"Height", L"Weight", L"Depth", L"Spectrum", L"TempDir" };
static wchar_t *g_MethodNames[] = { L"DrawCuttingPlan" };

static wchar_t *g_PropNamesRu[] = { L"Высота", L"Ширина", L"Глубина", L"Спектр", L"ВременнаяДиректория" };
static wchar_t *g_MethodNamesRu[] = { L"НарисоватьЭскиз" };


static const wchar_t g_kClassNames[] = L"CDrawingCuttingPlans"; //"|OtherClass1|OtherClass2";
static IAddInDefBase *pAsyncEvent = NULL;

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len = 0);
uint32_t getLenShortWcharStr(const WCHAR_T* Source);

//---------------------------------------------------------------------------//
long GetClassObject(const WCHAR_T* wsName, IComponentBase** pInterface)
{
	if (!*pInterface)
	{
		*pInterface = new CDrawingCuttingPlans;
		return (long)*pInterface;
	}
	return 0;
}
//---------------------------------------------------------------------------//
long DestroyObject(IComponentBase** pIntf)
{
	if (!*pIntf)
		return -1;

	delete *pIntf;
	*pIntf = 0;
	return 0;
}
//---------------------------------------------------------------------------//
const WCHAR_T* GetClassNames()
{
	static WCHAR_T* names = 0;
	if (!names)
		::convToShortWchar(&names, g_kClassNames);
	return names;
}
//---------------------------------------------------------------------------//
#ifndef __linux__
VOID CALLBACK MyTimerProc(
	HWND hwnd, // handle of window for timer messages
	UINT uMsg, // WM_TIMER message
	UINT idEvent, // timer identifier
	DWORD dwTime // current system time
	);
#else
static void MyTimerProc(int sig);
#endif //__linux__

// CDrawingCuttingPlans
//---------------------------------------------------------------------------//
CDrawingCuttingPlans::CDrawingCuttingPlans()
{
	m_iMemory = 0;
	m_iConnect = 0;
}
//---------------------------------------------------------------------------//
CDrawingCuttingPlans::~CDrawingCuttingPlans()
{
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::Init(void* pConnection)
{
	m_iConnect = (IAddInDefBase*)pConnection;
	return m_iConnect != NULL;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::GetInfo()
{
	// Component should put supported component technology version 
	// This component supports 2.0 version
	return 2000;
}
//---------------------------------------------------------------------------//
void CDrawingCuttingPlans::Done()
{
}
/////////////////////////////////////////////////////////////////////////////
// ILanguageExtenderBase
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::RegisterExtensionAs(WCHAR_T** wsExtensionName)
{
	wchar_t *wsExtension = L"DrawingCuttingPlans";
	int iActualSize = ::wcslen(wsExtension) + 1;
	WCHAR_T* dest = 0;

	if (m_iMemory)
	{
		if (m_iMemory->AllocMemory((void**)wsExtensionName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(wsExtensionName, wsExtension, iActualSize);
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::GetNProps()
{
	// You may delete next lines and add your own implementation code here
	return ePropLast;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::FindProp(const WCHAR_T* wsPropName)
{
	long plPropNum = -1;
	wchar_t* propName = 0;

	::convFromShortWchar(&propName, wsPropName);
	plPropNum = findName(g_PropNames, propName, ePropLast);

	if (plPropNum == -1)
		plPropNum = findName(g_PropNamesRu, propName, ePropLast);

	delete[] propName;

	return plPropNum;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CDrawingCuttingPlans::GetPropName(long lPropNum, long lPropAlias)
{
	if (lPropNum >= ePropLast)
		return NULL;

	wchar_t *wsCurrentName = NULL;
	WCHAR_T *wsPropName = NULL;
	int iActualSize = 0;

	switch (lPropAlias)
	{
	case 0: // First language
		wsCurrentName = g_PropNames[lPropNum];
		break;
	case 1: // Second language
		wsCurrentName = g_PropNamesRu[lPropNum];
		break;
	default:
		return 0;
	}

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory && wsCurrentName)
	{
		if (m_iMemory->AllocMemory((void**)&wsPropName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(&wsPropName, wsCurrentName, iActualSize);
	}

	return wsPropName;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::GetPropVal(const long lPropNum, tVariant* pvarPropVal)
{
	switch (lPropNum)
	{
	case ePropHeight:
		TV_VT(pvarPropVal) = VTYPE_INT;
		TV_INT(pvarPropVal) = m_height;
		break;
	case ePropWidth:
		TV_VT(pvarPropVal) = VTYPE_INT;
		TV_INT(pvarPropVal) = m_width;
		break;
	case ePropDepth:
		TV_VT(pvarPropVal) = VTYPE_INT;
		TV_INT(pvarPropVal) = m_depth;
		break;
	case ePropSpectrum:
		TV_VT(pvarPropVal) = VTYPE_INT;
		TV_INT(pvarPropVal) = m_spectrum;
		break;
	case ePropTempDir:
		TV_VT(pvarPropVal) = VTYPE_INT;
		//pvarPropVal->pstrVal = m_tempDir;
		break;
	default:
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::SetPropVal(const long lPropNum, tVariant *varPropVal)
{
	switch (lPropNum)
	{
	case ePropHeight:
		if (TV_VT(varPropVal) != VTYPE_INT)
			return false;
		m_height = TV_INT(varPropVal);
		break;
	case ePropWidth:
		if (TV_VT(varPropVal) != VTYPE_INT)
			return false;
		m_width = TV_INT(varPropVal);
		break;
	case ePropDepth:
		if (TV_VT(varPropVal) != VTYPE_INT)
			return false;
		m_depth = TV_INT(varPropVal);
		break;
	case ePropSpectrum:
		if (TV_VT(varPropVal) != VTYPE_INT)
			return false;
		m_spectrum = TV_INT(varPropVal);
		break;
	case ePropTempDir:
		if (TV_VT(varPropVal) == VTYPE_PSTR)
			m_tempDir = varPropVal->pstrVal;
		else if (TV_VT(varPropVal) == VTYPE_PWSTR)
		{
			// Memory leak ??
			int size = 0;
			char *mbstr = 0;
			wchar_t* wsTmp = 0;
			::convFromShortWchar(&wsTmp, TV_WSTR(varPropVal));
			size = wcstombs(0, wsTmp, 0) + 1;
			if (size && m_iMemory->AllocMemory((void**)&mbstr, size))
			{
				memset(mbstr, 0, size);
				size = wcstombs(mbstr, wsTmp, getLenShortWcharStr(TV_WSTR(varPropVal)));
				m_tempDir = mbstr;
			}
		}
		break;
	default:
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::IsPropReadable(const long lPropNum)
{
	switch (lPropNum)
	{
	case ePropHeight:
	case ePropWidth:
	case ePropDepth:
	case ePropSpectrum:
	case ePropTempDir:
		return true;
	default:
		return false;
	}

	return false;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::IsPropWritable(const long lPropNum)
{
	switch (lPropNum)
	{
	case ePropHeight:
	case ePropWidth:
	case ePropDepth:
	case ePropSpectrum:
	case ePropTempDir:
		return true;
	default:
		return false;
	}

	return false;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::GetNMethods()
{
	return eMethLast;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::FindMethod(const WCHAR_T* wsMethodName)
{
	long plMethodNum = -1;
	wchar_t* name = 0;

	::convFromShortWchar(&name, wsMethodName);

	plMethodNum = findName(g_MethodNames, name, eMethLast);

	if (plMethodNum == -1)
		plMethodNum = findName(g_MethodNamesRu, name, eMethLast);

	return plMethodNum;
}
//---------------------------------------------------------------------------//
const WCHAR_T* CDrawingCuttingPlans::GetMethodName(const long lMethodNum, const long lMethodAlias)
{
	if (lMethodNum >= eMethLast)
		return NULL;

	wchar_t *wsCurrentName = NULL;
	WCHAR_T *wsMethodName = NULL;
	int iActualSize = 0;

	switch (lMethodAlias)
	{
	case 0: // First language
		wsCurrentName = g_MethodNames[lMethodNum];
		break;
	case 1: // Second language
		wsCurrentName = g_MethodNamesRu[lMethodNum];
		break;
	default:
		return 0;
	}

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory && wsCurrentName)
	{
		if (m_iMemory->AllocMemory((void**)&wsMethodName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(&wsMethodName, wsCurrentName, iActualSize);
	}

	return wsMethodName;
}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::GetNParams(const long lMethodNum)
{
	switch (lMethodNum)
	{
	case eMethDrawCuttingPlan:
		return 1;
	default:
		return 0;
	}

	return 0;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::GetParamDefValue(const long lMethodNum, const long lParamNum,
	tVariant *pvarParamDefValue)
{
	TV_VT(pvarParamDefValue) = VTYPE_EMPTY;

	switch (lMethodNum)
	{
	default:
		return false;
	}

	return false;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::HasRetVal(const long lMethodNum)
{
	switch (lMethodNum)
	{
	case eMethDrawCuttingPlan:
		return true;
	default:
		return false;
	}

	return false;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::CallAsProc(const long lMethodNum,
	tVariant* paParams, const long lSizeArray)
{
	switch (lMethodNum)
	{
	default:
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::CallAsFunc(const long lMethodNum,
	tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray)
{
	bool ret = false;
	FILE *file = 0;
	char *xml = 0;
	int size = 0;
	char *mbstr = 0;
	wchar_t* wsTmp = 0;

	switch (lMethodNum)
	{
	case eMethDrawCuttingPlan:
	{
								 if (!lSizeArray || !paParams)
									 return false;

								 switch (TV_VT(paParams))
								 {
								 case VTYPE_PSTR:
									 xml = paParams->pstrVal;
									 break;
								 case VTYPE_PWSTR:
									 ::convFromShortWchar(&wsTmp, TV_WSTR(paParams));
									 size = wcstombs(0, wsTmp, 0) + 1;
									 mbstr = new char[size];
									 memset(mbstr, 0, size);
									 size = wcstombs(mbstr, wsTmp, getLenShortWcharStr(TV_WSTR(paParams)));
									 xml = mbstr;
									 break;
								 default:
									 return false;
								 }
	}

		// If parameter is empty, throw error
		if (strlen(xml) == 0)
		{
			wchar_t* wsMsgBuf;
			uint32_t err = errno;
			xml = strerror(err);
			size = mbstowcs(0, xml, 0) + 1;
			wsMsgBuf = new wchar_t[size];
			memset(wsMsgBuf, 0, size * sizeof(wchar_t));
			size = mbstowcs(wsMsgBuf, xml, size);

			addError(ADDIN_E_VERY_IMPORTANT, L"DrawingCuttingPlans", wsMsgBuf, RESULT_FROM_ERRNO(err));
			delete[] wsMsgBuf;
			return false;
		}

		//std::vector<Part> parts = parseXml(xml);

		std::string guid = this->guid();
		std::string filePath = m_tempDir;
		if (filePath[filePath.length() - 1] != (char)"\\")
		{
			filePath.append("\\");
		}
		filePath.append(guid);
		filePath.append(".bmp");

		drawImage(xml, filePath.c_str());

		file = fopen(filePath.c_str(), "rb");

		fseek(file, 0, SEEK_END);
		size = ftell(file);

		if (size && m_iMemory->AllocMemory((void**)&pvarRetValue->pstrVal, size))
		{
			fseek(file, 0, SEEK_SET);
			size = fread(pvarRetValue->pstrVal, 1, size, file);
			pvarRetValue->strLen = size;
			TV_VT(pvarRetValue) = VTYPE_BLOB;

			ret = true;
		}
		if (file)
			fclose(file);

		break;
	}
	return ret;
}
//---------------------------------------------------------------------------//
// This code will work only on the client!
#ifndef __linux__
VOID CALLBACK MyTimerProc(
	HWND hwnd,    // handle of window for timer messages
	UINT uMsg,    // WM_TIMER message
	UINT idEvent, // timer identifier
	DWORD dwTime  // current system time
	)
{
	if (!pAsyncEvent)
		return;

	wchar_t *who = L"ComponentNative", *what = L"Timer";

	wchar_t *wstime = new wchar_t[TIME_LEN];
	if (wstime)
	{
		wmemset(wstime, 0, TIME_LEN);
		::_ultow(dwTime, wstime, 10);
		pAsyncEvent->ExternalEvent(who, what, wstime);
		delete[] wstime;
	}
}
#else
void MyTimerProc(int sig)
{
	if (pAsyncEvent)
		return;

	WCHAR_T *who = 0, *what = 0, *wdata = 0;
	wchar_t *data = 0;
	time_t dwTime = time(NULL);

	data = new wchar_t[TIME_LEN];

	if (data)
	{
		wmemset(data, 0, TIME_LEN);
		swprintf(data, TIME_LEN, L"%ul", dwTime);
		::convToShortWchar(&who, L"ComponentNative");
		::convToShortWchar(&what, L"Timer");
		::convToShortWchar(&wdata, data);

		pAsyncEvent->ExternalEvent(who, what, wdata);

		delete[] who;
		delete[] what;
		delete[] wdata;
		delete[] data;
	}
}
#endif
//---------------------------------------------------------------------------//
void CDrawingCuttingPlans::SetLocale(const WCHAR_T* loc)
{
#ifndef __linux__
	_wsetlocale(LC_ALL, loc);
#else
	//We convert in char* char_locale
	//also we establish locale
	//setlocale(LC_ALL, char_locale);
#endif
}
/////////////////////////////////////////////////////////////////////////////
// LocaleBase
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::setMemManager(void* mem)
{
	m_iMemory = (IMemoryManager*)mem;
	return m_iMemory != 0;
}
//---------------------------------------------------------------------------//
void CDrawingCuttingPlans::addError(uint32_t wcode, const wchar_t* source,
	const wchar_t* descriptor, long code)
{
	if (m_iConnect)
	{
		WCHAR_T *err = 0;
		WCHAR_T *descr = 0;

		::convToShortWchar(&err, source);
		::convToShortWchar(&descr, descriptor);

		m_iConnect->AddError(wcode, err, descr, code);
		delete[] err;
		delete[] descr;
	}
}
//---------------------------------------------------------------------------//
std::string CDrawingCuttingPlans::guid(){
	size_t i;
	const int BUFFER_SIZE = 100;
	char* guidChar = new char[BUFFER_SIZE];

	wchar_t *guidStr = 0x00;
	GUID *pguid = 0x00;
	pguid = new GUID;

	CoCreateGuid(pguid);

	// Convert the GUID to a string
	UuidToString(pguid, (RPC_WSTR*)&guidStr);

	wcstombs_s(&i, guidChar, (size_t)BUFFER_SIZE,
		guidStr, (size_t)BUFFER_SIZE);

	delete pguid;

	return (std::string)guidChar;
}
//---------------------------------------------------------------------------//
bool CDrawingCuttingPlans::removeFile(std::string file){
	int ret_code = std::remove(file.c_str());
	return ret_code == 0;
}
void CDrawingCuttingPlans::drawImage(char *xml, const char* file){

	unsigned char black[] = { 0, 0, 0 };

	std::vector<Drawable<char>*> elements;

	pugi::xml_document xml_doc;

	pugi::xml_parse_result result = xml_doc.load_string(xml);

	for (pugi::xml_node xml_page = xml_doc.first_child(); xml_page;)
	{
		pugi::xml_node xml_parts = xml_page.child("Parts");

		for (pugi::xml_node xml_part = xml_parts.first_child(); xml_part; xml_part = xml_part.next_sibling())
		{
			int x0 = xml_part.child("x0").text().as_int(), x1 = x0, x2 = x0;
			int y0 = xml_part.child("y0").text().as_int(), y1 = y0, y3 = y0;

			int width = xml_part.child("width").text().as_int();
			int height = xml_part.child("height").text().as_int();

			int y2 = y0 + height, y4 = y2;
			int x3 = x0 + width, x4 = x3;

			// LeftTop
			pugi::xml_node leftTop = xml_part.child("leftTop");

			if (leftTop.child("arc") != 0){
				int radius = leftTop.child("arc").child("radius").text().as_int();
				elements.push_back(new GenericArc<char>(Point(x0 + radius, y0 + radius), radius, PI, 3 * PI / 2, black));
				x1 = x0 + radius;
				y1 = y0 + radius;

				if (leftTop.child("arc").child("curveSaws") != 0){
					elements.push_back(new CurveSawsArc<char>(Point(x0 + radius, y0 + radius), radius, PI, 3 * PI / 2, black));
				}

				if (leftTop.child("arc").child("euroGroove") != 0){
					elements.push_back(new EuroGrooveArc<char>(Point(x0 + radius, y0 + radius), radius - 10, PI, 3 * PI / 2, black));
				}

			}
			else if (leftTop.child("curve") != 0){

				if (leftTop.child("curveSaws") != 0){

				}

				if (leftTop.child("euroGroove") != 0){

				}
			}

			// leftBottom
			pugi::xml_node leftBottom = xml_part.child("leftBottom");

			if (leftBottom.child("arc") != 0){
				int radius = leftBottom.child("arc").child("radius").text().as_int();
				elements.push_back(new GenericArc<char>(Point(x0 + radius, y0 + height - radius), radius, PI / 2, PI, black));
				x2 = x0 + radius;
				y2 = y0 + height - radius;

				if (leftBottom.child("arc").child("curveSaws") != 0){
					elements.push_back(new CurveSawsArc<char>(Point(x0 + radius, y0 + height - radius), radius, PI / 2, PI, black));
				}

				if (leftBottom.child("arc").child("euroGroove") != 0){
					elements.push_back(new EuroGrooveArc<char>(Point(x0 + radius, y0 + height - radius), radius - 10, PI / 2, PI, black));
				}

			}
			else if (leftBottom.child("curve") != 0){

				if (leftBottom.child("curveSaws") != 0){

				}

				if (leftTop.child("euroGroove") != 0){

				}
			}

			// left
			pugi::xml_node left = xml_part.child("left");
			elements.push_back(new GenericLine<char>(Point(x0, y1), Point(x0, y2), 1, black));

			if (left.child("line").child("curveSaws") != 0){
				elements.push_back(new CurveSawsLine<char>(Point(x0, y1), Point(x0, y2), 1, black));
			}

			if (left.child("line").child("euroGroove") != 0){
				elements.push_back(new EuroGrooveLine<char>(Point(x0, y1), Point(x0, y2), 1, black));
			}

			// rightTop
			pugi::xml_node rightTop = xml_part.child("rightTop");

			if (rightTop.child("arc") != 0){
				int radius = rightTop.child("arc").child("radius").text().as_int();
				elements.push_back(new GenericArc<char>(Point(x0 + width - radius, y0 + radius), radius, 3 * PI / 2, 2 * PI, black));
				x3 = x0 + width - radius;
				y3 = y0 + radius;

				if (rightTop.child("arc").child("curveSaws") != 0){
					elements.push_back(new CurveSawsArc<char>(Point(x0 + width - radius, y0 + radius), radius, 3 * PI / 2, 2 * PI, black));
				}

				if (rightTop.child("arc").child("euroGroove") != 0){
					elements.push_back(new EuroGrooveArc<char>(Point(x0 + width - radius, y0 + radius), radius - 10, 3 * PI / 2, 2 * PI, black));
				}

			}
			else if (rightTop.child("curve") != 0){

				if (rightTop.child("curveSaws") != 0){

				}

				if (rightTop.child("euroGroove") != 0){

				}
			}

			// Top
			pugi::xml_node top = xml_part.child("top");
			elements.push_back(new GenericLine<char>(Point(x1, y0), Point(x3, y0), 1, black));

			if (top.child("line").child("curveSaws") != 0){
				elements.push_back(new CurveSawsLine<char>(Point(x1, y0), Point(x3, y0), 1, black));
			}

			if (top.child("line").child("euroGroove") != 0){
				elements.push_back(new EuroGrooveLine<char>(Point(x1, y0), Point(x3, y0), 1, black));
			}

			//rightBottom
			pugi::xml_node rightBottom = xml_part.child("rightBottom");

			if (rightBottom.child("arc") != 0){
				int radius = rightBottom.child("arc").child("radius").text().as_int();
				elements.push_back(new GenericArc<char>(Point(x0 + width - radius, y0 + height - radius), radius, 0, PI / 2, black));
				x4 = x0 + width - radius;
				y4 = y0 + height - radius;

				if (rightBottom.child("arc").child("curveSaws") != 0){
					elements.push_back(new CurveSawsArc<char>(Point(x0 + width - radius, y0 + height - radius), radius, 0, PI / 2, black));
				}

				if (rightBottom.child("arc").child("euroGroove") != 0){
					elements.push_back(new EuroGrooveArc<char>(Point(x0 + width - radius, y0 + height - radius), radius - 10, 0, PI / 2, black));
				}

			}
			else if (rightBottom.child("curve") != 0){

				if (rightBottom.child("curveSaws") != 0){

				}

				if (rightBottom.child("euroGroove") != 0){

				}
			}

			// Right
			pugi::xml_node right = xml_part.child("right");
			elements.push_back(new GenericLine<char>(Point(x0 + width, y3), Point(x0 + width, y4), 0, black));

			if (right.child("line").child("curveSaws") != 0){
				elements.push_back(new CurveSawsLine<char>(Point(x0 + width, y3), Point(x0 + width, y4), 0, black));
			}

			if (right.child("line").child("euroGroove") != 0){
				elements.push_back(new EuroGrooveLine<char>(Point(x0 + width, y3), Point(x0 + width, y4), 0, black));
			}

			// Bottom
			pugi::xml_node bottom = xml_part.child("bottom");
			elements.push_back(new GenericLine<char>(Point(x2, y0 + height), Point(x4, y0 + height), 0, black));

			if (bottom.child("line").child("curveSaws") != 0){
				elements.push_back(new CurveSawsLine<char>(Point(x2, y0 + height), Point(x4, y0 + height), 0, black));
			}

			if (bottom.child("line").child("euroGroove") != 0){
				elements.push_back(new EuroGrooveLine<char>(Point(x2, y0 + height), Point(x4, y0 + height), 0, black));
			}

			std::cout << "x0 : " << x0 << " y0 : " << y0 << " width : " << width << " height : " << height << std::endl;
		}
		xml_page = xml_page.next_sibling();
	}

	int size = m_height * m_width * m_depth * m_spectrum;
	char *values = new char[size];
	cimg_library::CImg<char> img(values, m_height, m_width, m_depth, m_spectrum, true);
	img.fill(255);

	Detail<char> dt;
	dt
		.Add(elements)
		.Draw(img);

	/*
	for (std::vector<Part>::const_iterator part = parts.begin(); part != parts.end(); ++part){
		img.draw_rectangle((*part).x0, (*part).y0, (*part).x0 + (*part).width, (*part).y0 + (*part).height, black, 1, -1);
		img.draw_text((*part).width + (*part).x0  - (*part).comment.length() * 3, (*part).height + (*part).y0 - 10, (*part).comment.c_str(), purple);
	}*/

	img.save(file);
}
//---------------------------------------------------------------------------//
/*std::vector<Part> CDrawingCuttingPlans::parseXml(char* xml){
	pugi::xml_document xml_doc;
	std::vector<Part> parts;

	pugi::xml_parse_result result = xml_doc.load_string(xml);

	for (pugi::xml_node xml_page = xml_doc.first_child(); xml_page;)
	{
		pugi::xml_node xml_parts = xml_page.child("Parts");

		for (pugi::xml_node xml_part = xml_parts.first_child(); xml_part; xml_part = xml_part.next_sibling())
		{
			int x0 = xml_part.child("x0").text().as_int();
			int y0 = xml_part.child("y0").text().as_int();
			int width = xml_part.child("width").text().as_int();
			int height = xml_part.child("height").text().as_int();
			std::string comment = xml_part.child("comment").text().get();

			parts.push_back(Part(x0, y0, width, height, comment));
		}
		xml_page = xml_page.next_sibling();
	}
	return parts;
}*/
//---------------------------------------------------------------------------//
void saveImage(std::string file){

}
//---------------------------------------------------------------------------//
long CDrawingCuttingPlans::findName(wchar_t* names[], const wchar_t* name,
	const uint32_t size) const
{
	long ret = -1;
	for (uint32_t i = 0; i < size; i++)
	{
		if (!wcscmp(names[i], name))
		{
			ret = i;
			break;
		}
	}
	return ret;
}
//---------------------------------------------------------------------------//
uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len)
{
	if (!len)
		len = ::wcslen(Source) + 1;

	if (!*Dest)
		*Dest = new WCHAR_T[len];

	WCHAR_T* tmpShort = *Dest;
	wchar_t* tmpWChar = (wchar_t*)Source;
	uint32_t res = 0;

	::memset(*Dest, 0, len*sizeof(WCHAR_T));
	do
	{
		*tmpShort++ = (WCHAR_T)*tmpWChar++;
		++res;
	} while (len-- && *tmpWChar);

	return res;
}
//---------------------------------------------------------------------------//
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len)
{
	if (!len)
		len = getLenShortWcharStr(Source) + 1;

	if (!*Dest)
		*Dest = new wchar_t[len];

	wchar_t* tmpWChar = *Dest;
	WCHAR_T* tmpShort = (WCHAR_T*)Source;
	uint32_t res = 0;

	::memset(*Dest, 0, len*sizeof(wchar_t));
	do
	{
		*tmpWChar++ = (wchar_t)*tmpShort++;
		++res;
	} while (len-- && *tmpShort);

	return res;
}
//---------------------------------------------------------------------------//
uint32_t getLenShortWcharStr(const WCHAR_T* Source)
{
	uint32_t res = 0;
	WCHAR_T *tmpShort = (WCHAR_T*)Source;

	while (*tmpShort++)
		++res;

	return res;
}
//---------------------------------------------------------------------------//
