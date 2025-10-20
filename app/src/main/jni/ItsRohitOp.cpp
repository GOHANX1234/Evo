#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <KittyMemory/KittyMemory.h>
#include <KittyMemory/MemoryPatch.h>
#include <KittyMemory/KittyScanner.h>
#include <KittyMemory/KittyUtils.h>
#include "oxorany/oxorany.h"
#include <xdl.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "ItsRohit_Op/gui.hpp"
#include "il2cpp.h"
//#include "fonts/FontAwesome6_solid.h"
#include "ItsRohitOp/Land.hpp"
//#include <ImguiPP.h>
#include "imgui/imgui.h"
#include "imgui/stb_image.h"
#include "mkop.h"
#include "ff.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <Themes.h>
#include "ItsRohitOp/Firewall.h"
#include "ItsRohitOp/exptime.h"
#include "ItsRohitOp/Chams.h"
#include "ItsRohitOp/Land.h"
#include "ItsRohitOp/CN.h"
#include "ItsRohitOp/lundbda.h"
#include "ItsRohitOp/fontch.h"
#include "Icon/OPPOSans-H.h"
#include "Rohit/Icon.h"
#include "Rohit/Iconcpp.h"
#include <fstream>
#include "Icon/Font.h"

#include "GHr_Ryuuka/Tools/Call_Tools.h"
using json = nlohmann::json;
time_t rng = 0;
std::string g_Token, g_Auth;
extern std::string g_ExpiryDate;
extern int g_DaysRemaining;
#include "ItSRohitOpLogin.h"

struct My_Patches {
    MemoryPatch Bypass1;
    MemoryPatch Bypass2;
    MemoryPatch Bypass3;
    MemoryPatch Bypass4;
    MemoryPatch Bypass5;
    MemoryPatch Bypass6;
    MemoryPatch Bypass7;
    MemoryPatch Bypass8;
    MemoryPatch Bypass9;
    MemoryPatch Bypass10;
    MemoryPatch Bypass11;
    MemoryPatch Bypass12;
    MemoryPatch Bypass13;
    MemoryPatch Bypass14;
    MemoryPatch Bypass15;
    
    MemoryPatch Guest;
} hexPatches;
using zygisk::Api;
using zygisk::AppSpecializeArgs;
using zygisk::ServerSpecializeArgs;

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

void HueText(const char* text, ImVec4 color)
{
    static auto start_time = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count() / 1000.0f; 
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.0f)); 
    for (int i = 0; i < strlen(text); i++)
    {
      ImGui::SameLine();
        float t = fmodf(elapsed_seconds + (float)i / (float)strlen(text), 0.65f); 
        ImVec4 currentColor = ImVec4(color.x * t, color.y * t, color.z * t, color.w); 
        ImGui::PushStyleColor(ImGuiCol_Text, currentColor); 
        ImGui::Text("%c", text[i]); 
        ImGui::PopStyleColor(); 
    }
    ImGui::PopStyleColor(); 
}
/*
*/
void hack();
void writeLog(const std::string& logMessage, const std::string& filename = "/storage/emulated/0/Android/data/com.dualspace.multispace.androidx/files/log.txt");


 


class MyModule : public zygisk::ModuleBase {
 public:
  void onLoad(Api *api, JNIEnv *env) override {
    this->api_ = api;
    this->env_ = env;
    genv = env;
   // gEnv = env;

  }

  void preAppSpecialize(AppSpecializeArgs *args) override {
    static constexpr const char *packages[] = {
        "com.dts.freefireth"
    };
    const char *process = env_->GetStringUTFChars(args->nice_name, nullptr);
    for (const auto *package: packages) {
      is_game_ = (strcmp(process, package) == 0);
      if (is_game_) {
        break;
      }
    }
    env_->ReleaseStringUTFChars(args->nice_name, process);
  }

  void postAppSpecialize(const AppSpecializeArgs *args) override {
    if (is_game_) {
       genv->GetJavaVM(&jvm);
     //  genv->GetJavaVM(&gJvm);
      std::thread{hack}.detach();
    }
  }

 private:
  Api *api_ = nullptr;
  JNIEnv *env_ = nullptr;
  bool is_game_ = false;
};


uintptr_t il2cpp_base = 0;
void *getRealAddr(ulong offset) {
    return reinterpret_cast<void*>(il2cpp_base + offset);
};

struct TextureInfo { ImTextureID textureId; int x; int y; int w; int h; };

void DrawImage(int x, int y, int w, int h, ImTextureID Texture) {
ImGui::GetForegroundDrawList()->AddImage(Texture, ImVec2(x, y), ImVec2(x + w, y + h));}


static TextureInfo textureInfo;
TextureInfo createTexture(char *ImagePath) {
int w, h, n;
stbi_uc *data = stbi_load(ImagePath, &w, &h, &n, 0);
GLuint texture;
glGenTextures(1, &texture);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
if (n == 3) {
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
} else {
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}stbi_image_free(data);
textureInfo.textureId = reinterpret_cast<ImTextureID>((GLuint *) texture);
textureInfo.w = w;
textureInfo.h = h;
return textureInfo;
}TextureInfo CreateTexture(const unsigned char* buf, int len) {
TextureInfo image;
unsigned char* image_data = stbi_load_from_memory(buf, len, &image.w, &image.h, NULL, 0);
if (image_data == NULL) perror("文件不存在"); GLuint image_texture;
glGenTextures(1, &image_texture);
glBindTexture(GL_TEXTURE_2D, image_texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //对于非二次方纹理，这在 WebGL 上是必需的
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //相同的
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.w, image.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
stbi_image_free(image_data);
image.textureId = (ImTextureID)image_texture;
return image;
}

//LOGO
TextureInfo mkop;
extern TextureInfo mkop;

TextureInfo ff;
extern TextureInfo ff;



void InitTexture() {
mkop = CreateTexture(mkop_data, sizeof(mkop_data));
ff = CreateTexture(ff_data, sizeof(ff_data));
}

namespace Settings
{
static int Tab = 1;
}

#define ICON_FA_WINDOW_MINIMIZE "\xef\x8a\x96"

void SetupImgui() {
IMGUI_CHECKVERSION();
InitTexture();
ImGui::CreateContext();
ImGui_ImplOpenGL3_Init("#version 300 es");

            ImGuiIO &io = ImGui::GetIO();
            
            
            ImGui::GetStyle().WindowPadding = ImVec2(8, 8);
// ImGui::GetStyle().WindowRounding = 2.0f;
 ImGui::GetStyle().FramePadding = ImVec2(10, 10);
 ImGui::GetStyle().ItemSpacing = ImVec2(10, 10); 
// ImGui::GetStyle().FrameRounding = 0.0f;
// //ImGui::GetStyle().ChildRounding = 4.5f;
 ImGui::GetStyle().FrameBorderSize = 0.0f;
ImGui::GetStyle().WindowBorderSize = 1.0f;
ImGui::GetStyle().TabBorderSize = 1.0f;
ImGui::GetStyle().ScrollbarSize = 20.0f;
// //style->WindowTitleAlign = ImVec2(0.5, 0.5);
// //style->ButtonTextAlign = ImVec2(0.5,0.5);
// style->Colors[ImGuiCol_TitleBg]= ImVec4(0, 0, 0, 0.95f);
// style->Colors[ImGuiCol_TitleBgActive]= ImVec4(0, 0, 0, 0.95f);
// Setup Platform/Renderer backends

    // (This function remains the same as the previous answer)
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

// 🔹 Rounded corners 30% kam
style.WindowRounding   = 5.2f;
style.FrameRounding    = 2.4f;
style.GrabRounding     = 2.4f;
style.PopupRounding    = 2.4f;
style.TabRounding      = 1.8f;
style.ScrollbarRounding= 2.4f;
    



// 🎨 Custom ImGui Style (Green Theme)


colors[ImGuiCol_ChildBg]               = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
colors[ImGuiCol_Border]                = ImColor(0, 200, 0, 200);   // ✅ Green Border
colors[ImGuiCol_Tab]                   = ImColor(0, 255, 0, 100);
colors[ImGuiCol_TabHovered]            = ImColor(0, 255, 0, 200);
colors[ImGuiCol_TabActive]             = ImColor(0, 255, 0, 200);
colors[ImGuiCol_TabUnfocused]          = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);

colors[ImGuiCol_WindowBg]              = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
colors[ImGuiCol_FrameBg]               = ImVec4(0.20f, 0.20f, 0.20f, 0.54f);
colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.30f, 0.30f, 0.30f, 0.78f);
colors[ImGuiCol_FrameBgActive]         = ImVec4(0.40f, 0.40f, 0.40f, 0.67f);

colors[ImGuiCol_TitleBgActive]         = ImColor(0, 255, 0, 255);   // ✅ Title bar Green
colors[ImGuiCol_CheckMark]             = ImColor(0, 255, 0, 255);
colors[ImGuiCol_SliderGrab]            = ImColor(0, 255, 0, 255);
colors[ImGuiCol_SliderGrabActive]      = ImColor(0, 255, 0, 255);

colors[ImGuiCol_Button]                = ImColor(0, 255, 0, 150);
colors[ImGuiCol_ButtonHovered]         = ImColor(0, 255, 0, 250);
colors[ImGuiCol_ButtonActive]          = ImColor(0, 255, 0, 220);

colors[ImGuiCol_Header]                = ImVec4(0.0f, 0.5f, 0.0f, 0.31f);
colors[ImGuiCol_HeaderHovered]         = ImVec4(0.0f, 0.5f, 0.0f, 0.80f);
colors[ImGuiCol_HeaderActive]          = ImColor(0, 255, 0, 255);

colors[ImGuiCol_Separator]             = ImColor(0, 255, 0, 200);   // ✅ Separator Green
colors[ImGuiCol_Text]                  = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);





    


            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.IniFilename = NULL;

            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
            
          //io.Fonts->AddFontFromMemoryTTF((void *)BaiduZY_data, BaiduZY_size, 30.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
          io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(itsmkop), sizeof(itsmkop), 28.f, &CustomFont);
                  io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 30.0f, &icons_config, icons_ranges);
                  io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 24.f, &CustomFont);
         // memset(&Config, 0, sizeof(sConfig));
//
//

//ImFontConfig CustomFont;
CustomFont.FontDataOwnedByAtlas = false;
//font_cfg.SizePixels = 22.0f;
static const ImWchar vietnamese_chars[] = {
0x0020, 0x00FF, // Basic Latin + Latin Supplement
0x0102, 0x0103, // Â, â
0x0110, 0x0111, // Đ, đ
0x0128, 0x0129, // Ĩ, ĩ
0x0168, 0x0169, // Ũ, ũ
0x01A0, 0x01A1, // Ơ, ơ
0x01AF, 0x01B0, // Ư, ư
0x1EA0, 0x1EF9, // Vietnamese specific characters
0 // null-terminated list
};
}


bool clearMousePos = true;
bool ImGuiOK = false;
bool initImGui = false;

void VerticalTab(const char* label, int tab_index, int* p_selected_tab) {
ImGuiStyle& style = ImGui::GetStyle();
ImVec4* colors = style.Colors;

// Push custom colors for the selected and unselected states
ImVec4 color = ImColor(0, 150, 255, 5);
ImVec4 colorActive = ImColor(0, 150, 255, 5);
ImVec4 colorHovered = ImColor(0, 150, 255, 5);

if (tab_index == *p_selected_tab) {
// This is the selected tab, make it blue like in the image
ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
} else {
// Unselected tabs are dark
ImGui::PushStyleColor(ImGuiCol_Button, color);
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHovered);
ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
}

if (ImGui::Button(label, ImVec2(200, 50))) { // Button size (width, height)
*p_selected_tab = tab_index;
}

if (tab_index == *p_selected_tab) {
ImDrawList* draw_list = ImGui::GetWindowDrawList();
const ImVec2 p_min = ImGui::GetItemRectMin();
const ImVec2 p_max = ImGui::GetItemRectMax();

ImU32 line_color = IM_COL32(50, 150, 255, 255);
float line_thickness = 8.0f;

draw_list->AddLine(
ImVec2(p_min.x, p_min.y), 
ImVec2(p_min.x, p_max.y), 
line_color, 
line_thickness
);
}

ImGui::PopStyleColor(3);
}

static int selected_tab = 0;

inline EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
inline EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    
        eglQuerySurface(dpy, surface, EGL_WIDTH, &g_GlWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &g_GlHeight);
    
    


    if (!g_IsSetup) {
        prevWidth = g_GlWidth;
        prevHeight = g_GlHeight;
        SetupImgui();
        
        g_IsSetup = true;
    }
    
 // Window background = black

    ImGuiIO &io = ImGui::GetIO();
        //Darkness();
        // Thiết lập màu chủ đề
        //ImVec4* colors = ImGui::GetStyle().Colors;


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);
    ImGui::NewFrame();
        if (ImGuiOK) {
            int touchCount = (((int (*)())(Class_Input__get_touchCount))());
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields(*)(int))(Class_Input__GetTouch))(0);
        float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;
        switch (touch.m_Phase) {
            case TouchPhase::Began:
            case TouchPhase::Stationary:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                io.MouseDown[0] = true;
                break;
            case TouchPhase::Ended:
            case TouchPhase::Canceled:
                io.MouseDown[0] = false;
                clearMousePos = true;
                break;
            case TouchPhase::Moved:
                io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
                break;
            default:
                break;
        }
    }
        }
        
        DrawESP(g_GlWidth, g_GlHeight);

ImDrawList* draw = ImGui::GetBackgroundDrawList();

std::string topText = " EVO CHEAT V2.5 ";
ImVec2 textSize = ImGui::CalcTextSize(topText.c_str());

// Box ka padding
float padX = 12.0f;
float padY = 6.0f;

// Box ka position (center screen)
ImVec2 boxMin(g_GlWidth / 2.0f - (textSize.x / 2.0f) - padX, 15);
ImVec2 boxMax(g_GlWidth / 2.0f + (textSize.x / 2.0f) + padX, 15 + textSize.y + padY * 2);

// 🔹 Background (Black Box)
draw->AddRectFilled(
boxMin,
boxMax,
IM_COL32(15, 15, 15, 230),
3.0f
);

// 🔹 Border (Green)
draw->AddRect(
boxMin,
boxMax,
IM_COL32(0, 255, 0, 255),
3.0f
);

// 🔹 Bottom Glow Line
draw->AddRectFilled(
ImVec2(boxMin.x, boxMax.y - 4),
ImVec2(boxMax.x, boxMax.y),
IM_COL32(0, 255, 100, 255),
2.0f
);

// 🔹 White Text (centered inside box)
ImVec2 textPos(
g_GlWidth / 2.0f - textSize.x / 2.0f,
boxMin.y + ( (boxMax.y - boxMin.y) - textSize.y ) / 2.0f
);

draw->AddText(NULL, 28.0f, textPos, IM_COL32(255, 255, 255, 255), topText.c_str());


        
        
        
static bool itsmk = true;
static bool clickInProgress = false;
static float clickStartTime = 0;
if (itsmk == false) {
if (ImGui::Begin((" MKOP" ), 0,ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground)) {
const auto& pWindowDrawList = ImGui::GetWindowDrawList();
const auto& p = ImGui::GetWindowPos();
ImGui::SetCursorPos(ImVec2(5, 5));
ImVec2 imageSize(120,120);
ImGui::Image(mkop.textureId, imageSize);
if (ImGui::IsItemHovered()) {
if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {clickInProgress = true;
clickStartTime = ImGui::GetTime();}}
if (clickInProgress && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {clickInProgress = false;
float currentTime = ImGui::GetTime();
float clickDuration = currentTime - clickStartTime;
if (clickDuration < 0.2f) {itsmk = true;
}}}}

ImGui::End();

if (itsmk){
ImGui::SetNextWindowSize(ImVec2(780, 400), ImGuiCond_Once);
    if (ImGui::Begin(" ~ EVOCHEAT V2.5", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
    
       static bool isLogin = false;

if (bHasUpdate && isLogin) {
    ImGui::SetNextWindowSize(ImVec2(780, 400), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin(OBFUSCATE(ICON_FA_EXCLAMATION_TRIANGLE " UPDATE REQUIRED"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    
    for (auto& update : g_Updates) {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), ICON_FA_BELL " %s", update.title.c_str());
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::TextWrapped("%s", update.message.c_str());
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        if (ImGui::Button((std::string(ICON_FA_DOWNLOAD " ") + update.buttonText).c_str(), ImVec2(ImGui::GetContentRegionAvailWidth(), 55))) {
            JNIEnv *env;
            jvm->AttachCurrentThread(&env, 0);
            
            jclass uriClass = env->FindClass(OBFUSCATE("android/net/Uri"));
            jmethodID parseMethod = env->GetStaticMethodID(uriClass, OBFUSCATE("parse"), OBFUSCATE("(Ljava/lang/String;)Landroid/net/Uri;"));
            jobject uri = env->CallStaticObjectMethod(uriClass, parseMethod, env->NewStringUTF(update.linkUrl.c_str()));
            
            jclass intentClass = env->FindClass(OBFUSCATE("android/content/Intent"));
            jfieldID actionViewField = env->GetStaticFieldID(intentClass, OBFUSCATE("ACTION_VIEW"), OBFUSCATE("Ljava/lang/String;"));
            jstring actionView = (jstring)env->GetStaticObjectField(intentClass, actionViewField);
            
            jmethodID intentConstructor = env->GetMethodID(intentClass, OBFUSCATE("<init>"), OBFUSCATE("(Ljava/lang/String;Landroid/net/Uri;)V"));
            jobject intent = env->NewObject(intentClass, intentConstructor, actionView, uri);
            
            jmethodID addFlagsMethod = env->GetMethodID(intentClass, OBFUSCATE("addFlags"), OBFUSCATE("(I)Landroid/content/Intent;"));
            env->CallObjectMethod(intent, addFlagsMethod, 0x10000000);
            
            jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
            jmethodID currentApplicationMethod = env->GetStaticMethodID(activityThreadClass, OBFUSCATE("currentApplication"), OBFUSCATE("()Landroid/app/Application;"));
            jobject context = env->CallStaticObjectMethod(activityThreadClass, currentApplicationMethod);
            
            jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
            jmethodID startActivityMethod = env->GetMethodID(contextClass, OBFUSCATE("startActivity"), OBFUSCATE("(Landroid/content/Intent;)V"));
            env->CallVoidMethod(context, startActivityMethod, intent);
            
            jvm->DetachCurrentThread();
        }
        ImGui::Spacing();
    }
    
    ImGui::End();
} else if (!isLogin) {
ImGui::Spacing();
ImGui::Text(OBFUSCATE(ICON_FA_STAR " MOD BY EVOCHEAT  " ICON_FA_CHECK_CIRCLE));
ImGui::Spacing();

ImGui::Text(ICON_FA_PASTE " LOGIN TO CONTINUE");
ImGui::Spacing();
ImGui::PushItemWidth(-1);
static char s[64];
ImGui::InputText("##key", s, sizeof s);
ImGui::PopItemWidth();
if (ImGui::Button(ICON_FA_KEYBOARD " PASTE KEY", ImVec2(ImGui::GetContentRegionAvailWidth(), 55))) {
auto key = getClipboard();
strncpy(s, key.c_str(), sizeof s); }
static std::string err;
if (ImGui::Button(ICON_FA_KEY " LOGIN TO CONTINUE " ICON_FA_CHECK_CIRCLE, ImVec2(ImGui::GetContentRegionAvailWidth(), 55))) {
 err = Login(s);
if (err == "OK") {
isLogin = bValid && g_Auth == g_Token;
} }
if (!err.empty() && err != "OK") {
ImGui::Text(ICON_FA_SERVER "SERVER: %s", err.c_str());
}} else {
 
  std::string title = "EVO CHEAT V2.5";

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 window_pos = ImGui::GetWindowPos();
    float window_width = ImGui::GetWindowWidth();
    float title_bar_height = 45.0f;
    float vertical_offset = 6.0f;

    // Corrected the alpha value to 255 for full opacity.
    draw_list->AddRectFilled(
        window_pos,
        ImVec2(window_pos.x + window_width, window_pos.y + title_bar_height),
        IM_COL32(30, 30, 30, 255) 
    );

    float circle_radius = 13.0f;
    float circle_y_pos = window_pos.y + (title_bar_height / 2.0f) + vertical_offset;
    float initial_x_offset = 25.0f;
    float circle_spacing = 35.0f;

    // Get mouse position and check if the window is being hovered.
    ImVec2 mouse_pos = ImGui::GetMousePos();
    bool is_hovering = ImGui::IsWindowHovered();
    bool is_left_clicked = ImGui::IsMouseClicked(0);

    // Red circle
    ImVec2 red_circle_center = ImVec2(window_pos.x + initial_x_offset, circle_y_pos);
    draw_list->AddCircleFilled(red_circle_center, circle_radius, IM_COL32(255, 95, 86, 255));
    if (is_hovering && is_left_clicked && ImVec2(mouse_pos.x - red_circle_center.x, mouse_pos.y - red_circle_center.y).x * (mouse_pos.x - red_circle_center.x) + (mouse_pos.y - red_circle_center.y) * (mouse_pos.y - red_circle_center.y) < circle_radius * circle_radius) {
        itsmk = false;
    }

    // Yellow circle
    ImVec2 yellow_circle_center = ImVec2(window_pos.x + initial_x_offset + circle_spacing, circle_y_pos);
    draw_list->AddCircleFilled(yellow_circle_center, circle_radius, IM_COL32(254, 189, 47, 255));
    if (is_hovering && is_left_clicked && ImVec2(mouse_pos.x - yellow_circle_center.x, mouse_pos.y - yellow_circle_center.y).x * (mouse_pos.x - yellow_circle_center.x) + (mouse_pos.y - yellow_circle_center.y) * (mouse_pos.y - yellow_circle_center.y) < circle_radius * circle_radius) {
        itsmk = false;
    }

    // Green circle
    ImVec2 green_circle_center = ImVec2(window_pos.x + initial_x_offset + circle_spacing * 2, circle_y_pos);
    draw_list->AddCircleFilled(green_circle_center, circle_radius, IM_COL32(40, 204, 64, 255));
    if (is_hovering && is_left_clicked && ImVec2(mouse_pos.x - green_circle_center.x, mouse_pos.y - green_circle_center.y).x * (mouse_pos.x - green_circle_center.x) + (mouse_pos.y - green_circle_center.y) * (mouse_pos.y - green_circle_center.y) < circle_radius * circle_radius) {
        itsmk = false;
    }

   
 ImVec2 text_size = ImGui::CalcTextSize(title.c_str());
float text_x = window_pos.x + (window_width - text_size.x) / 2.0f;
float text_y = window_pos.y + (title_bar_height - text_size.y) / 2.0f; // ✅ perfect center

draw_list->AddText(ImVec2(text_x, text_y), IM_COL32(0, 255, 0, 255), title.c_str());
        
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + title_bar_height);
    ImGui::Separator();
    
static int selected_tab = 0;
static int last_tab = 0;
static float tab_alpha = 1.0f;   // animation factor
static float anim_speed = 6.0f;  // animation speed

ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));

// === Left Tabs ===
ImGui::BeginChild("LeftTabs", ImVec2(200, 0), true);
{
    VerticalTab("AIM",   0, &selected_tab);
    VerticalTab("ESPS",  1, &selected_tab);
    VerticalTab("CHAMS", 2, &selected_tab);
        VerticalTab("BRUTAL", 3, &selected_tab);
    VerticalTab("INFOS", 4, &selected_tab);
}
ImGui::EndChild();
ImGui::SameLine();

// === Right Side ===
ImGui::BeginChild("mainchild", ImVec2(0, 0), true);
{
    // Tab changed → reset animation
    if (selected_tab != last_tab) {
        tab_alpha = 0.0f;
        last_tab = selected_tab;
    }

    // Animate alpha
    if (tab_alpha < 1.0f)
        tab_alpha += ImGui::GetIO().DeltaTime * anim_speed;

    // Apply fade effect (👇 iske andar apna content daalo)
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha);

    // 🔹 Yaha tumhara tab ka asli content aayega

    
ImGui::EndChild();
ImGui::SameLine();

ImGui::BeginChild("mainchild", ImVec2(0, 0), true);

{
// Display content based on the selected tab
switch (selected_tab) {
//case 0: // SAFE
//ImGui::Text("Safe Settings Content");
//break;
case 0: // AIM
ImGui::Button(" AIM ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0));
ImGui::Checkbox("Headshot", &Headshot);
ImGui::Checkbox("Aim Silent", &jsksksk);
//ImGui::Checkbox("Aimbot Scoping", &AimWhen3);
//ImGui::Checkbox("Aimbot Crouching", &AimWhen1);
//ImGui::Checkbox("SilentAim", &AimSilent);
// // ImGui::SliderFloat फंक्शन एक लेबल, एक float वैरिएबल, min/max रेंज, और एक फॉर्मेट लेता है।
// ImGui::PushItemWidth(200); // स्लाइडर की चौड़ाई सेट करें
//ImGui::SliderFloat("Aimbot FOV", &Fov_Aim, 0.0f, 2000.0f, "%.2f°");
// ImGui::PopItemWidth();
break;
case 1: // ESPS
ImGui::Button(" ESPS ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0));
ImGui::Checkbox("ENABLE ESP", &Enable);
ImGui::Checkbox("ESP LINE", &Config.ESP.Line);
ImGui::Checkbox("ESP BOX", &Config.ESP.Box);
ImGui::Checkbox("ESP HEALTH", &Config.ESP.Target);
//ImGui::Checkbox("ESP DISTANCE", &Config.ESP.Health);
break;


case 2: // CHAMS
ImGui::Button(" CHAMSS ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0));
ImGui::Checkbox("CHAMS FUNCTION", &wireframe);
ImGui::SliderFloat("RED", &r, 0.0f, 255.0f);
ImGui::SliderFloat("GREEN", &g, 0.0f, 255.0f);
ImGui::SliderFloat("BLUE", &b, 0.0f, 255.0f);
break;


case 3: // Brutal
ImGui::Button(" BRUTALS ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0));
ImGui::Checkbox("Speed Run", &speedrun);
ImGui::Checkbox("Reset Geust", &Reset);
break;


case 4: // INFOS
ImGui::Text("Info Section Content");
ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
ImVec2 image_size = ImVec2(78.0f, 78.0f); // Increased size
ImVec2 image_pos = ImVec2(cursor_pos.x + 15.0f, cursor_pos.y + 2.0f); // Adjusted vertical position

ImGui::GetWindowDrawList()->AddImageRounded(ff.textureId, image_pos, ImVec2(image_pos.x + image_size.x, image_pos.y + image_size.y), ImVec2(0, 0), ImVec2(1, 1), ImColor(1.0f,1.0f,1.0f), 5.0f, ImDrawFlags_RoundCornersAll);

// Move cursor and add text next to the image
ImGui::SetCursorScreenPos(ImVec2(image_pos.x + image_size.x + 10.0f, image_pos.y + 19.0f)); // Adjusted text position
        ImGui::Text("FREE FIRE (2019115661)");
    ImGui::Dummy(ImVec2(0.0f, 25.0f));
        ImGui::Separator();    
ImGui::BulletText("Server Status : ");
ImGui::SameLine();
ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Online");
ImGui::Separator();
if (!g_ExpiryDate.empty() && g_DaysRemaining > 0) {
    ImGui::BulletText("Key Validity : ");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", g_ExpiryDate.c_str());
    
    ImGui::Indent(20.0f);
    std::string daysInfo = "Remaining days from today - " + std::to_string(g_DaysRemaining) + " day";
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", daysInfo.c_str());
    ImGui::Unindent(20.0f);
} else {
    ImGui::BulletText("Key Validity : ");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Not Available");
}
break;
}
}
ImGui::EndChild();
}
//
}

    
    }
    
    
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return old_eglSwapBuffers(dpy, surface);
}
//}
typedef unsigned long DWORD;
static uintptr_t libBase;

uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}


inline void hack_injec();
inline void StartGUI() {
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (NULL != ptr_eglSwapBuffer) {
        DobbyHook((void *)ptr_eglSwapBuffer, (void*)hook_eglSwapBuffers, (void**)&old_eglSwapBuffers);
            LOGD("Gui Started");
                        hack_injec();
        }
    }

bool libLoaded = false;

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, OBFUSCATE("/proc/self/maps"));

    fp = fopen(filename, OBFUSCATE("rt"));
    if (fp == NULL) {
        perror(OBFUSCATE("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    libBase = findLibrary(libraryName);
    if (libBase == 0)
        return 0;
    return (reinterpret_cast<DWORD>(libBase + relativeAddr));
}
ProcMap unityMap, anogsMap, il2cppMap;
using KittyScanner::RegisterNativeFn;



    
    
void hack() {
     LOGD("Inject Ok");
    //std::thread thread_hack(hack_thread, getpid());
    //thread_hack.detach();
    
}
uintptr_t get_symbol_addr_in_pid(pid_t pid, const char* libname, uintptr_t offset_in_lib) {
    char maps_path[64];
    snprintf(maps_path, sizeof(maps_path), "/proc/%d/maps", pid);

    FILE* fp = fopen(maps_path, "r");
    if (!fp) return 0;

    char line[512];
    uintptr_t base = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libname)) {
            sscanf(line, "%lx-%*lx", &base);
            break;
        }
    }
    fclose(fp);

    if (base == 0) return 0;
    return base + offset_in_lib;
}

pid_t get_pid_by_name(const char* process_name) {
    DIR* proc_dir = opendir("/proc");
    if (!proc_dir) return -1;

    struct dirent* entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        if (entry->d_type != DT_DIR) continue;

        pid_t pid = atoi(entry->d_name);
        if (pid <= 0) continue;

        char cmdline_path[256];
        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", pid);

        FILE* fp = fopen(cmdline_path, "r");
        if (!fp) continue;

        char cmdline[256];
        fgets(cmdline, sizeof(cmdline), fp);
        fclose(fp);

        if (strstr(cmdline, process_name)) {
            closedir(proc_dir);
            return pid;
        }
    }

    closedir(proc_dir);
    return -1;
}

void writeLog(const std::string& logMessage, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app); // Mở file ở chế độ append (thêm)
    if (outFile.is_open()) {
        outFile << logMessage << std::endl;
        outFile.close();
    } else {
        std::cerr << "Không thể mở file log: " << filename << std::endl;
    }
}

bool is_current_process(const char* target_name) {
    char cmdline_path[64];
    snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%d/cmdline", getpid());

    FILE* fp = fopen(cmdline_path, "r");
    if (!fp) return false;

    char cmdline[256] = {0};
    fgets(cmdline, sizeof(cmdline), fp);
    fclose(fp);

    return strcmp(cmdline, target_name) == 0;
}




void hack_injec() {
        while (!unityMap.isValid()) {
        unityMap = KittyMemory::getLibraryBaseMap("libunity.so");
                anogsMap = KittyMemory::getLibraryBaseMap("libanogs.so");
                il2cppMap = KittyMemory::getLibraryBaseMap("libil2cpp.so");
                
        sleep(6);
        }
    
 sleep(5);
    Il2CppAttach();
    
    if (mlovinit()) {
        setShader("_AlphaMask"); //Varies according to game
        LogShaders();
        Wallhack();
    }

         
        
        //aim silent v2
 DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Weapon"), OBFUSCATE("OnCalcDamageOrHealing"), 1), (void *) BLAGCMCGEJG1,(void **) &old_BLAGCMCGEJG1);
        
        
DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateBehavior"), 2), (void *) _LateUpdate, (void **) &LateUpdate);
        //aimsilent
        DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("PlayerNetwork"), OBFUSCATE("TakeDamage"), 9), (void *) &hook_PlayerNetwork_TakeDamage, (void **) &orig_PlayerNetwork_TakeDamage);
        // Speed Run
       // Speed Run
   DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFoldWingGliding"), 0), (void *) _IsFoldWingGliding, (void **)& IsFoldWingGliding);
        DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("message"), OBFUSCATE("ProtoUtil"), OBFUSCATE("MappingFromPhysXState"), 1), (void *) _LEBIPIGPEEP, (void **)& LEBIPIGPEEP);
    // ResetGuest
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameConfig") , OBFUSCATE("get_ResetGuest"), 0), (void *) ResetGuest, (void **) &_ResetGuest);
    
         // Cam Xa
        DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("FollowCamera"), OBFUSCATE("get_OffsetForNormal"), 0),(void *)_GetCameraHeightRateValue, (void **)&GetCameraHeightRateValue);
    
        
        
    // Bypass
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("AndroidJNI"), OBFUSCATE("IsInstanceOf"), 2), (void *) &_Bypass, (void **) &Bypass);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JPPGAJBAAKK"), OBFUSCATE("IsOnlineGame"), 2), (void *) &_Bypass, (void **) &Bypass);
   // DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("AnoSDKNamespace"), OBFUSCATE("IOPOOHPNCKH"), OBFUSCATE("LBABEMNOJAJ"), 8), (void *) &_Bypass, (void **) &Bypass);

    //Fix Game
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("SerializableAttribute"), OBFUSCATE(".ctor"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GarenaMSDK"), OBFUSCATE("GarenaMSDKMgr"), OBFUSCATE("IsPlatformInstalled"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("System.dll"), OBFUSCATE("System.Net"), OBFUSCATE("WebProxy"), OBFUSCATE("IsBypassed"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("System.dll"), OBFUSCATE("System.Net"), OBFUSCATE("IWebProxy"), OBFUSCATE("IsBypassed"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("System.dll"), OBFUSCATE("System.Net"), OBFUSCATE("WebProxy"), OBFUSCATE(".ctor"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("System.dll"), OBFUSCATE("System.Net"), OBFUSCATE("WebProxy"), OBFUSCATE("CheckBypassList"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("EventLogger"), OBFUSCATE("LogReportCheatInHistory"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("EventLogger"), OBFUSCATE("LogReportCheat"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("MobileReplayManager"), OBFUSCATE("GetGameTimeMS"), 0), (void *) &_FixGame, (void **) &FixGame);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("CreditPunishManager"), OBFUSCATE("ShowPunishWindow"), 0), (void *) &_FixGame, (void **) &FixGame);

        
        
    // Bypass Esp
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("SceneGraphicsQuality"), OBFUSCATE("SetGraphicsQuality"), 0), (void *) _BypassESP, (void **) &BypassESP);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("SetResolution"), 0), (void *) _BypassESP, (void **) &BypassESP);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("QualitySettings"), OBFUSCATE("GetQualityLevel"), 0), (void *) _BypassESP, (void **) &BypassESP);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("SceneGraphicsQuality"), OBFUSCATE("SetGraphicsQuality"), 0), (void *) _BypassESP, (void **) &BypassESP);

    // Bypass New
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("PlatformUtility_Android"), OBFUSCATE("IsPackageInstalled"), 0), (void *) _Set_Aim, (void **) &Set_Aim);
    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("PlatformUtility_Android"), OBFUSCATE("CheckFileExists"), 0), (void *) _Set_Aim, (void **) &Set_Aim);
// //BLACKLIST FIX BYPASS
// MemoryPatch::createWithHex("libanogs.so", 0x169BC4, "C0 03 5F D6").Modify(); // Bypass sub_169BC4
// MemoryPatch::createWithHex("libanogs.so", 0x175270, "C0 03 5F D6").Modify(); // Disable sub_175270
// MemoryPatch::createWithHex("libanogs.so", 0x3DEBC8, "C0 03 5F D6").Modify(); 
// MemoryPatch::createWithHex("libanogs.so", 0x16ADC8, "C0 03 5F D6").Modify(); 
// MemoryPatch::createWithHex("libanogs.so", 0x423E48, "C0 03 5F D6").Modify(); // Disable sub_423E48
// MemoryPatch::createWithHex("libanogs.so", 0x3C398C, "C0 03 5F D6").Modify(); // Disable sub_3C398C
// MemoryPatch::createWithHex("libanogs.so", 0x3DEDD8, "C0 03 5F D6").Modify(); // ret
// MemoryPatch::createWithHex("libanogs.so", 0x4000E4, "C0 03 5F D6").Modify(); // ret
// MemoryPatch::createWithHex("libanogs.so", 0x3E92D8, "C0 03 5F D6").Modify(); // return 0 immediately
// MemoryPatch::createWithHex("libanogs.so", 0x3FC34C, "C0 03 5F D6").Modify(); // nop
// MemoryPatch::createWithHex("libanogs.so", 0x3FBDA4, "C0 03 5F D6").Modify(); // ret
// MemoryPatch::createWithHex("libanogs.so", 0x3F950C, "C0 03 5F D6").Modify(); // nop
// MemoryPatch::createWithHex("libanogs.so", 0x399978, "C0 03 5F D6").Modify(); // nop



// //AUTO BAN FIX BYPASS

// MemoryPatch::createWithHex("libanogs.so", 0x3BD164, "C0 03 5F D6").Modify(); // nop
// MemoryPatch::createWithHex("libanogs.so", 0x3C466C, "C0 03 5F D6").Modify(); // ret
// MemoryPatch::createWithHex("libanogs.so", 0x39B91C, "C0 03 5F D6").Modify(); // nop
// MemoryPatch::createWithHex("libanogs.so", 0x3C38E4, "C0 03 5F D6").Modify(); // nop
// MemoryPatch::createWithHex("libanogs.so", 0x17EFD4, "C0 03 5F D6").Modify(); // nop //Shell_Report
// //MemoryPatch::createWithHex("libanogs.so", 0x402380, "C0 03 5F D6").Modify(); // ret


// //Fix Signature AutoBan
// MemoryPatch::createWithHex("libGGP.so", 0x2148CC, "C0 03 5F D6").Modify(); // nop
        
MemoryPatch::createWithHex((uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameConfig"), OBFUSCATE("get_ResetGuest"), 0), OBFUSCATE("20 00 80 D2 C0 03 5F D6")).Modify();
        // DobbyHook((void *) (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("UpdateBehavior"), 2), (void *) hook_LateUpdate, (void **) &orig_LateUpdate);
    hexPatches.Guest = MemoryPatch::createWithHex(getAbsoluteAddress("libil2cpp.so", 0x5ed140c),"20 00 80 D2 C0 03 5F D6");
   
    ImGuiOK = true;
    
}


void hack_thread(pid_t pid) {
        
        StartGUI();
        while(pid == -1){pid = get_pid_by_name("com.dts.freefireth");} 
        remote_inject(pid);
        writeLog(to_string(pid));
    
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved) {
jvm = vm;
JNIEnv *env;
vm->GetEnv((void **) &env, JNI_VERSION_1_6); 
return JNI_VERSION_1_6;
}

__attribute__((constructor))
void lib_main()
{
    std::thread thread_hack(hack_thread, get_pid_by_name("com.dts.freefireth"));
    thread_hack.detach();
}
//REGISTER_ZYGISK_MODULE(MyModule)

