#include<iostream>
#include<windows.h>
#include "Psapi.h"
#include<string>
using namespace std;

#define VK_LBUTTON        0x01    //鼠标左键
#define VK_RBUTTON        0x02    //鼠标右键
#define VK_CANCEL         0x03    //Ctrl + Break
#define VK_MBUTTON        0x04    //鼠标中键/* NOT contiguous with L & RBUTTON */
#define VK_BACK           0x08   //Backspace 键
#define VK_TAB            0x09   //Tab 键
#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D   //回车键
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12   //Alt 键
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14   //Caps Lock 键
#define VK_KANA           0x15
#define VK_HANGEUL        0x15 /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19
#define VK_ESCAPE         0x1B   //Esc 键
#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F
#define VK_SPACE          0x20   //空格
#define VK_PRIOR          0x21   //Page Up 键
#define VK_NEXT           0x22   //Page Down 键
#define VK_END            0x23   //End 键
#define VK_HOME           0x24   //Home 键
#define VK_LEFT           0x25  /*方向键*/
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C   //Print Screen 键
#define VK_INSERT         0x2D  //Insert键
#define VK_DELETE         0x2E  //Delete键
#define VK_HELP           0x2F
#define VK_LWIN           0x5B //左WinKey(104键盘才有)
#define VK_RWIN           0x5C //右WinKey(104键盘才有)
#define VK_APPS           0x5D //AppsKey(104键盘才有)
#define VK_NUMPAD0        0x60 //小键盘0-9
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A //乘
#define VK_ADD                0x6B //加
#define VK_SEPARATOR      0x6C //除
#define VK_SUBTRACT       0x6D //减
#define VK_DECIMAL        0x6E //小数点
#define VK_DIVIDE         0x6F

#define VK_F1             0x70 //功能键F1-F24
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

#define VK_NUMLOCK        0x90 //Num Lock 键

#define VK_SCROLL         0x91 //Scroll Lock 键
#define VK_LSHIFT           0xA0
#define VK_RSHIFT          0xA1
#define VK_LCONTROL        0xA2
#define VK_RCONTROL        0xA3
#define VK_LMENU           0xA4
#define VK_RMENU           0xA5

#if(WINVER >= 0x0400)
#define VK_PROCESSKEY      0xE5
#endif /* WINVER >= 0x0400 */

#define VK_ATTN            0xF6
#define VK_CRSEL           0xF7
#define VK_EXSEL           0xF8
#define VK_EREOF           0xF9
#define VK_PLAY            0xFA
#define VK_ZOOM            0xFB
#define VK_NONAME          0xFC
#define VK_PA1             0xFD
#define VK_OEM_CLEAR       0xFE

// VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39)
// VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)
class KEYBOARD
{
    public:
        void    PressKey(BYTE bVk);
        void    KeyDown(BYTE bVk);
        void    KeyUp(BYTE bVk);
};
//按键（虚拟键值）
void KEYBOARD::PressKey(BYTE bVk)
{
    ::keybd_event(bVk,0,0,0);
    ::keybd_event(bVk,0,KEYEVENTF_KEYUP,0);
}

//按下（虚拟键值）
void KEYBOARD::KeyDown(BYTE bVk)
{
    ::keybd_event(bVk,0,0,0);
}

//抬起（虚拟键值）
void KEYBOARD::KeyUp(BYTE bVk)
{
    ::keybd_event(bVk,0,KEYEVENTF_KEYUP,0);
}

// 遍历窗口
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	// 过滤不可见的窗口
	if(IsWindowVisible(hwnd)){
		// 过滤掉存在标题的窗口
		char szTitle[100] = {0};
		GetWindowText(hwnd, szTitle, 100);
        
        string title = string(szTitle);
        // cout<<title<< " " << endl;
		if(title.find("我的Android手机") > 0){
            cout<<szTitle<< endl;
			// 过滤掉大小不为 650*380 的窗口
			RECT rect;
			GetWindowRect(hwnd, &rect);
			if((rect.right - rect.left) == 658 && (rect.bottom - rect.top) == 757){
				// 过滤掉没有指定文本的窗口
				for(int i = 0; i < 5; i++){
					// 指定位置右键
					PostMessage(hwnd, WM_RBUTTONDOWN, 0,MAKELPARAM(255,674));
					PostMessage(hwnd, WM_RBUTTONUP,0,MAKELPARAM(255,674));
					Sleep(10);
					// 按下 'A'
					PostMessage(hwnd, WM_KEYDOWN, 0x41,0);
					PostMessage(hwnd, WM_KEYUP, 0x41,0);
					Sleep(10);
					// 指定位置右键
					PostMessage(hwnd, WM_RBUTTONDOWN, 0,MAKELPARAM(255,674));
					PostMessage(hwnd, WM_RBUTTONUP, 0,MAKELPARAM(255,674));
					Sleep(10);
					// 按下 'C'
					PostMessage(hwnd, WM_KEYDOWN, 0x43,0);
					PostMessage(hwnd, WM_KEYUP, 0x43,0);
				}
				// 指定位置左键（取消选中）
				PostMessage(hwnd, WM_LBUTTONDOWN, 0,MAKELPARAM(255,674));
				PostMessage(hwnd, WM_LBUTTONUP, 0,MAKELPARAM(255,674));
			}
		}	
	}
    return TRUE;
}
int main() {
    
    // ::SetCursorPos(150,136);
    // mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
    // KEYBOARD keyboard = KEYBOARD();
    // keyboard.PressKey(0x31);
    while (true)
    {
        int flag = 0;
        cin>>flag;
        if(flag != 0) {
            EnumWindows(EnumWindowsProc, 0);
        }
    }
    // PostMessage((HWND)"0000000000150A9A", WM_LBUTTONDOWN, 0,MAKELPARAM(243,697));
    // PostMessage((HWND)"0000000000150A9A", WM_LBUTTONUP, 0,MAKELPARAM(243,697));
    // PostMessage((HWND)"0000000000150A9A", WM_KEYDOWN, 0x31, MAKELPARAM(243,697));
    // HWND hWnd, UINT command, UINT ID, UINT eventType
    return 0;
}
