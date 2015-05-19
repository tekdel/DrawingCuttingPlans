#ifndef __DrawingCuttingPlans_H__
#define __DrawingCuttingPlans_H__

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h""

///////////////////////////////////////////////////////////////////////////////
// class CDrawingCuttingPlans
class CDrawingCuttingPlans : public IComponentBase
{
public:
	enum Props
	{
		ePropHeight = 0,
		ePropWidth,
		ePropDepth,
		ePropSpectrum,
		ePropTempDir,
		ePropLast      // Always last
	};

	enum Methods
	{
		eMethDrawCuttingPlan = 0,
		eMethLast      // Always last
	};

	CDrawingCuttingPlans(void);
	virtual ~CDrawingCuttingPlans();
	// IInitDoneBase
	virtual bool ADDIN_API Init(void*);
	virtual bool ADDIN_API setMemManager(void* mem);
	virtual long ADDIN_API GetInfo();
	virtual void ADDIN_API Done();
	// ILanguageExtenderBase
	virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T**);
	virtual long ADDIN_API GetNProps();
	virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
	virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
	virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
	virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
	virtual bool ADDIN_API IsPropReadable(const long lPropNum);
	virtual bool ADDIN_API IsPropWritable(const long lPropNum);
	virtual long ADDIN_API GetNMethods();
	virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
	virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum,
		const long lMethodAlias);
	virtual long ADDIN_API GetNParams(const long lMethodNum);
	virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
		tVariant *pvarParamDefValue);
	virtual bool ADDIN_API HasRetVal(const long lMethodNum);
	virtual bool ADDIN_API CallAsProc(const long lMethodNum,
		tVariant* paParams, const long lSizeArray);
	virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
		tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
	// LocaleBase
	virtual void ADDIN_API SetLocale(const WCHAR_T* loc);

private:
	std::string guid();
	bool removeFile(std::string file);
	void drawImage(char *xml, const char* file);
	long findName(wchar_t* names[], const wchar_t* name, const uint32_t size) const;
	void addError(uint32_t wcode, const wchar_t* source,
		const wchar_t* descriptor, long code);
	// Attributes
	IAddInDefBase      *m_iConnect;
	IMemoryManager     *m_iMemory;

	int					m_height = 640;
	int					m_width = 480;
	int					m_depth = 1;
	int					m_spectrum = 3;
	const char*			m_tempDir;
};

#endif //__DrawingCuttingPlans_H__
