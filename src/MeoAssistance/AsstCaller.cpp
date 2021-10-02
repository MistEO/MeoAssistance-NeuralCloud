﻿#include "AsstCaller.h"

#include <string.h>

#include <json_value.h>

#include "Version.h"
#include "AsstAux.h"
#include "Assistance.h"

#if 0
#if _MSC_VER
// Win32平台下Dll的入口
BOOL APIENTRY DllMain(HANDLE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#elif VA_GNUC

#endif
#endif

AsstCallback _callback = nullptr;

void CallbackTrans(asst::AsstMsg msg, const json::value& json, void* custom_arg)
{
    _callback(static_cast<int>(msg), asst::Utf8ToGbk(json.to_string()).c_str(), custom_arg);
}

void* AsstCreate()
{
    return new asst::Assistance();
}

void* AsstCreateEx(AsstCallback callback, void* custom_arg)
{
    // 创建多实例回调会有问题，有空再慢慢整
    _callback = callback;
    return new asst::Assistance(CallbackTrans, custom_arg);
}

void AsstDestory(void* p_asst)
{
    if (p_asst == nullptr) {
        return;
    }

    delete p_asst;
    p_asst = nullptr;
}

bool AsstCatchDefault(void* p_asst)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->catch_default();
}

bool AsstCatchEmulator(void* p_asst)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->catch_emulator();
}

bool AsstCatchUSB(void* p_asst)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->catch_usb();
}

bool AsstCatchRemote(void* p_asst, const char* address)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->catch_remote(address);
}

bool AsstStartProcessTask(void* p_asst, const char* task)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->start_process_task(task, asst::Assistance::ProcessTaskRetryTimesDefault);
}

void AsstStop(void* p_asst)
{
    if (p_asst == nullptr) {
        return;
    }

    ((asst::Assistance*)p_asst)->stop();
}

bool AsstSetParam(void* p_asst, const char* type, const char* param, const char* value)
{
    if (p_asst == nullptr) {
        return false;
    }

    return ((asst::Assistance*)p_asst)->set_param(type, param, value);
}

const char* AsstGetVersion()
{
    return asst::Version;
}

bool AsstStartDebugTask(void* p_asst)
{
    if (p_asst == nullptr) {
        return false;
    }
#if LOG_TRACE
    return ((asst::Assistance*)p_asst)->start_debug_task();
#else
    return false;
#endif // LOG_TRACE
}