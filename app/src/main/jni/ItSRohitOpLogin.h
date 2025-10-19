
// Modified By @ItSMKOP
// Updated to use custom authentication API

#pragma once

bool bValid = false;
bool bHasUpdate = false;

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "GHr_Ryuuka/Tools/curl/json.hpp"
#include "GHr_Ryuuka/Tools/StrEnc.h"


JavaVM *jvm;
JNIEnv *genv;

struct MemoryStruct {
char *memory;
size_t size;
};

struct UpdateInfo {
    std::string title;
    std::string message;
    std::string buttonText;
    std::string linkUrl;
    bool isActive;
};

std::vector<UpdateInfo> g_Updates;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
size_t realsize = size * nmemb;
struct MemoryStruct *mem = (struct MemoryStruct *) userp;

mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
if (mem->memory == NULL) {
return 0;
}
memcpy(&(mem->memory[mem->size]), contents, realsize);
mem->size += realsize;
mem->memory[mem->size] = 0;
return realsize;
}

const char *GetUUID(JNIEnv *env, const char *uuid) {
jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx","\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

auto len = strlen(uuid);

jbyteArray myJByteArray = env->NewByteArray(len);
env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,","\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB","\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW","\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0","\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
return env->GetStringUTFChars(str, 0);
}

const char *GetAndroidID(JNIEnv *env, jobject context) {
jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());
auto obj = env->CallObjectMethod(context, getContentResolverMethod);
auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceModel(JNIEnv *env) {
jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());
auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceBrand(JNIEnv *env) {
jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());
auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
return env->GetStringUTFChars(str, 0);
}
const char *GetPackageName(JNIEnv *env, jobject context) {
jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());
auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
return env->GetStringUTFChars(str, 0);
}
const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());
auto len = strlen(uuid);
jbyteArray myJByteArray = env->NewByteArray(len);
env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);
jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());
auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
return env->GetStringUTFChars(str, 0);
}

std::string CheckForUpdates() {
    g_Updates.clear();
    bHasUpdate = false;
    
    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    std::string errMsg;

    if (!curl) {
        if (chunk.memory) {
            free(chunk.memory);
        }
        return std::string((const char*)OBFUSCATE("Failed to initialize network library for updates"));
    }

    if (curl) {
        std::string api_url = std::string((const char*)OBFUSCATE("https://nikumodsexe.onrender.com/api/updates"));
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, (const char*)OBFUSCATE("Content-Type: application/json"));
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            
            if (http_code == 200) {
                try {
                    json updateArray = json::parse(chunk.memory);
                    if (updateArray.is_array() && !updateArray.empty()) {
                        for (auto& update : updateArray) {
                            if (update["isActive"].get<bool>()) {
                                UpdateInfo info;
                                info.title = update["title"].get<std::string>();
                                info.message = update["message"].get<std::string>();
                                info.buttonText = update["buttonText"].get<std::string>();
                                info.linkUrl = update["linkUrl"].get<std::string>();
                                info.isActive = true;
                                g_Updates.push_back(info);
                                bHasUpdate = true;
                            }
                        }
                    }
                } catch (json::exception &e) {
                    errMsg = std::string((const char*)OBFUSCATE("Update parse failed: ")) + e.what();
                }
            } else if (http_code != 0) {
                errMsg = std::string((const char*)OBFUSCATE("Server returned HTTP ")) + std::to_string(http_code);
            }
        } else {
            errMsg = std::string((const char*)OBFUSCATE("Network error: ")) + curl_easy_strerror(res);
        }
        curl_slist_free_all(headers);
    }
    
    if (chunk.memory) {
        free(chunk.memory);
        chunk.memory = NULL;
        chunk.size = 0;
    }
    curl_easy_cleanup(curl);
    return errMsg;
}

std::string Login(const char *user_key) {
bValid = false;
g_Token = "";
g_Auth = "";

JNIEnv *env;
jvm->AttachCurrentThread(&env, 0);

auto looperClass = env->FindClass((const char*)OBFUSCATE("android/os/Looper"));
auto prepareMethod = env->GetStaticMethodID(looperClass, (const char*)OBFUSCATE("prepare"), (const char*)OBFUSCATE("()V"));
env->CallStaticVoidMethod(looperClass, prepareMethod);

jclass activityThreadClass = env->FindClass((const char*)OBFUSCATE("android/app/ActivityThread"));
jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, (const char*)OBFUSCATE("sCurrentActivityThread"), (const char*)OBFUSCATE("Landroid/app/ActivityThread;"));
jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);

jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, (const char*)OBFUSCATE("mInitialApplication"), (const char*)OBFUSCATE("Landroid/app/Application;"));
jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);

std::string hwid = user_key;
hwid += Tools::GetAndroidID(env, mInitialApplication);
hwid += Tools::GetDeviceModel(env);
hwid += Tools::GetDeviceBrand(env);
std::string UUID = Tools::GetDeviceUniqueIdentifier(env, hwid.c_str());
jvm->DetachCurrentThread();
std::string errMsg;

struct MemoryStruct chunk{};
chunk.memory = (char *) malloc(1);
chunk.size = 0;

CURL *curl;
CURLcode res;
curl = curl_easy_init();

if (!curl) {
    if (chunk.memory) {
        free(chunk.memory);
    }
    return std::string((const char*)OBFUSCATE("Failed to initialize network library"));
}

if (curl) {
std::string api_key = std::string((const char*)OBFUSCATE("https://nikumodsexe.onrender.com/api/verify"));
curl_easy_setopt(curl, CURLOPT_URL, (api_key.c_str()));
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);

struct curl_slist *headers = NULL;
headers = curl_slist_append(headers, (const char*)OBFUSCATE("Content-Type: application/json"));

curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

json postData;
postData["key"] = user_key;
postData["deviceId"] = UUID;
postData["game"] = (const char*)OBFUSCATE("FREE FIRE");

std::string jsonStr = postData.dump();
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

res = curl_easy_perform(curl);
if (res == CURLE_OK) {
long http_code = 0;
curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

if (http_code == 200) {
    try {
    json result = json::parse(chunk.memory);
    if (result[std::string((const char*)OBFUSCATE("valid"))] == true) {
        bValid = true;
        g_Token = (const char*)OBFUSCATE("OK");
        g_Auth = (const char*)OBFUSCATE("OK");
        
        std::string updateErr = CheckForUpdates();
        if (!updateErr.empty()) {
            errMsg = updateErr;
        }
    } else {
        errMsg = result.value(std::string((const char*)OBFUSCATE("message")), std::string((const char*)OBFUSCATE("License verification failed")));
        bValid = false;
    }
    } catch (json::exception &e) {
    errMsg = "{";
    errMsg += e.what();
    errMsg += "}\n{";
    errMsg += chunk.memory;
    errMsg += "}";
    }
} else if (http_code != 0) {
    errMsg = std::string((const char*)OBFUSCATE("Server returned HTTP ")) + std::to_string(http_code);
} else {
    errMsg = std::string((const char*)OBFUSCATE("No response from server"));
}
} else {
errMsg = std::string((const char*)OBFUSCATE("Network error: ")) + curl_easy_strerror(res);
}
curl_slist_free_all(headers);
}

if (chunk.memory) {
    free(chunk.memory);
    chunk.memory = NULL;
    chunk.size = 0;
}
curl_easy_cleanup(curl);
jvm->DetachCurrentThread();
return bValid ? (errMsg.empty() ? "OK" : "OK (Warning: " + errMsg + ")") : errMsg;
}

std::string getClipboard() {
std::string result;
JNIEnv *env;

jvm->AttachCurrentThread(&env, NULL);

auto looperClass = env->FindClass(("android/os/Looper"));
auto prepareMethod = env->GetStaticMethodID(looperClass, ("prepare"), ("()V"));
env->CallStaticVoidMethod(looperClass, prepareMethod);

jclass activityThreadClass = env->FindClass(("android/app/ActivityThread"));
jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, ("sCurrentActivityThread"), ("Landroid/app/ActivityThread;"));
jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);

jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, ("mInitialApplication"), ("Landroid/app/Application;"));
jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);

auto contextClass = env->FindClass(("android/content/Context"));
auto getSystemServiceMethod = env->GetMethodID(contextClass, ("getSystemService"), ("(Ljava/lang/String;)Ljava/lang/Object;"));

auto str = env->NewStringUTF(("clipboard"));
auto clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
env->DeleteLocalRef(str);

jclass ClipboardManagerClass = env->FindClass(("android/content/ClipboardManager"));
auto getText = env->GetMethodID(ClipboardManagerClass, ("getText"), ("()Ljava/lang/CharSequence;"));

jclass CharSequenceClass = env->FindClass(("java/lang/CharSequence"));
auto toStringMethod = env->GetMethodID(CharSequenceClass, ("toString"), ("()Ljava/lang/String;"));

auto text = env->CallObjectMethod(clipboardManager, getText);
if (text) {
str = (jstring) env->CallObjectMethod(text, toStringMethod);
result = env->GetStringUTFChars(str, 0);
env->DeleteLocalRef(str);
env->DeleteLocalRef(text);
}
env->DeleteLocalRef(CharSequenceClass);
env->DeleteLocalRef(ClipboardManagerClass);
env->DeleteLocalRef(clipboardManager);
env->DeleteLocalRef(contextClass);
env->DeleteLocalRef(mInitialApplication);
env->DeleteLocalRef(activityThreadClass); 
jvm->DetachCurrentThread();
return result.c_str();
}
