#pragma once
#include "SRGXTypes.h"

typedef enum s3eKey
{
	s3eKeyFirst = 0,        //!< Invalid Key

	s3eKeyEsc = 1,          //!< Esc (cancel).
	s3eKeyTab = 2,          //!< Tab.
	s3eKeyBackspace = 3,    //!< Backspace.
	s3eKeyEnter = 4,        //!< Enter.
	s3eKeyLeftShift = 5,    //!< Left shift key.
	s3eKeyLeftControl = 6,  //!< Left control key.
	s3eKeyReserved = 7,     //!< Reserved, do not use.
	s3eKeySpace = 8,        //!< Key Space.
	s3eKeyLeft = 9,         //!< Key Left.
	s3eKeyUp = 10,          //!< Key Up.
	s3eKeyRight = 11,       //!< Key Right.
	s3eKeyDown = 12,        //!< Key Down.
	s3eKey0 = 13,           //!< Key 0 on device numberpad and on main keyboard.
	s3eKey1 = 14,           //!< Key 1 on device numberpad and on main keyboard.
	s3eKey2 = 15,           //!< Key 2 on device numberpad and on main keyboard.
	s3eKey3 = 16,           //!< Key 3 on device numberpad and on main keyboard.
	s3eKey4 = 17,           //!< Key 4 on device numberpad and on main keyboard.
	s3eKey5 = 18,           //!< Key 5 on device numberpad and on main keyboard.
	s3eKey6 = 19,           //!< Key 6 on device numberpad and on main keyboard.
	s3eKey7 = 20,           //!< Key 7 on device numberpad and on main keyboard.
	s3eKey8 = 21,           //!< Key 8 on device numberpad and on main keyboard.
	s3eKey9 = 22,           //!< Key 9 on device numberpad and on main keyboard.
	s3eKeyA = 23,           //!< Key A.
	s3eKeyB = 24,           //!< Key B.
	s3eKeyC = 25,           //!< Key C.
	s3eKeyD = 26,           //!< Key D.
	s3eKeyE = 27,           //!< Key E.
	s3eKeyF = 28,           //!< Key F.
	s3eKeyG = 29,           //!< Key G.
	s3eKeyH = 30,           //!< Key H.
	s3eKeyI = 31,           //!< Key I.
	s3eKeyJ = 32,           //!< Key J.
	s3eKeyK = 33,           //!< Key K.
	s3eKeyL = 34,           //!< Key L.
	s3eKeyM = 35,           //!< Key M.
	s3eKeyN = 36,           //!< Key N.
	s3eKeyO = 37,           //!< Key O.
	s3eKeyP = 38,           //!< Key P.
	s3eKeyQ = 39,           //!< Key Q.
	s3eKeyR = 40,           //!< Key R.
	s3eKeyS = 41,           //!< Key S.
	s3eKeyT = 42,           //!< Key T.
	s3eKeyU = 43,           //!< Key U.
	s3eKeyV = 44,           //!< Key V.
	s3eKeyW = 45,           //!< Key W.
	s3eKeyX = 46,           //!< Key X.
	s3eKeyY = 47,           //!< Key Y.
	s3eKeyZ = 48,           //!< Key Z.
	s3eKeyF1 = 49,          //!< Key F1.
	s3eKeyF2 = 50,          //!< Key F2.
	s3eKeyF3 = 51,          //!< Key F3.
	s3eKeyF4 = 52,          //!< Key F4.
	s3eKeyF5 = 53,          //!< Key F5.
	s3eKeyF6 = 54,          //!< Key F6.
	s3eKeyF7 = 55,          //!< Key F7.
	s3eKeyF8 = 56,          //!< Key F8.
	s3eKeyF9 = 57,          //!< Key F9.
	s3eKeyF10 = 58,         //!< Key F10.
	s3eKeyNumPad0 = 59,     //!< Key 0 on keyboard numberpad.
	s3eKeyNumPad1 = 60,     //!< Key 1 on keyboard numberpad.
	s3eKeyNumPad2 = 61,     //!< Key 2 on keyboard numberpad.
	s3eKeyNumPad3 = 62,     //!< Key 3 on keyboard numberpad.
	s3eKeyNumPad4 = 63,     //!< Key 4 on keyboard numberpad.
	s3eKeyNumPad5 = 64,     //!< Key 5 on keyboard numberpad.
	s3eKeyNumPad6 = 65,     //!< Key 6 on keyboard numberpad.
	s3eKeyNumPad7 = 66,     //!< Key 7 on keyboard numberpad.
	s3eKeyNumPad8 = 67,     //!< Key 8 on keyboard numberpad.
	s3eKeyNumPad9 = 68,     //!< Key 9 on keyboard numberpad.
	s3eKeyNumPadPlus = 69,  //!< Plus key on keyboard numberpad.
	s3eKeyNumPadMinus = 70, //!< Minus key on keyboard numberpad.
	s3eKeyNumPadEnter = 71, //!< Enter key on keyboard numberpad.
	s3eKeyRSK = 72,         //!< Right soft key.
	s3eKeyLSK = 73,         //!< Left soft key.
	s3eKeyLS = 74,          //!< Left shoulder button.
	s3eKeyRS = 75,          //!< Right shoulder button.
	s3eKeyHash = 76,        //!< Key #.
	s3eKeyStar = 77,        //!< Key * (on keyboard numberpad for normal keyboards).

							// Select/ok button
							s3eKeyOk = 78,          //!< Select key.
							s3eKeyCLR = 79,         //!< CLR key.

													// Volume
													s3eKeyVolUp = 80,       //!< Volume Up key.
													s3eKeyVolDown = 81,     //!< Volume Down key.

																			//Misc.
																			/**
																			* Camera button.
																			*
																			* @platnote{Windows Phone 8, wp8}  On Windows Phone 8 this code is sent on
																			* full button presses only (e.g. autofocus presses not handled)
																			* @endplatnote
																			*
																			* @platnote{Windows Phone 8.1, wp81}  On Windows Phone 8.1 native camera
																			* application is launched on camera button press and s3eKeyboard event is
																			* not sent.
																			* @endplatnote
																			*/
	s3eKeyCamera = 82,

	s3eKeyMic = 83,         //!< Microphone button.
	s3eKeyFn = 84,          //!< Fn button.
	s3eKeySym = 85,         //!< Sym button.

							//Call
							s3eKeyAccept = 86,        //!< call accept (talk).
							s3eKeyEnd = 87,           //!< call end (reject).
							s3eKeyHomePage = 88,      //!< Home key.

							s3eKeyButton1 = 89,       //!< Generic Button1.
							s3eKeyButton2 = 90,       //!< Generic Button2.
							s3eKeyButton3 = 91,       //!< Generic Button3.
							s3eKeyButton4 = 92,       //!< Generic Button4.
							s3eKeyButton5 = 93,       //!< Generic Button5.
							s3eKeyButton6 = 94,       //!< Generic Button6.
							s3eKeyButton7 = 95,       //!< Generic Button7.
							s3eKeyButton8 = 96,       //!< Generic Button8.

							s3eKeyF11 = 97,           //!< Key F11.
							s3eKeyF12 = 98,           //!< Key F12.
							s3eKeyLeftAlt = 99,       //!< Left Alt key.

							s3eKeyRightControl = 100, //!< Right Control Key.
							s3eKeyRightAlt = 101,     //!< Right Alt Key.
							s3eKeyRightShift = 102,   //!< Right Shift Key.
							s3eKeyBacktick = 103,     //!< Backtick '`' Key.
							s3eKeyComma = 104,        //!< Comma ',' Key.
							s3eKeyPeriod = 105,       //!< Period '.' Key.
							s3eKeySlash = 106,        //!< Forward slash '/' Key.
							s3eKeyBackSlash = 107,    //!< Back slash '\' Key.
							s3eKeySemicolon = 108,    //!< Semicolon ';' Key.
							s3eKeyApostrophe = 109,   //!< Apostrophe (') Key.
							s3eKeyLeftBracket = 110,  //!< Left Bracket '[' Key.
							s3eKeyRightBracket = 111, //!< Right Bracket ']' Key.
							s3eKeyEquals = 112,       //!< Equals '=' Key.
							s3eKeyMinus = 113,        //!< Minus '-' key on main keyboard.
							s3eKeyCapsLock = 114,     //!< Caps Lock key

							s3eKeyNumPadPeriod = 115, //!< Period '.' key on numberpad
							s3eKeyNumPadSlash = 116,  //!< Slash '/' key on numberpad
							s3eKeyNumLock = 117,      //!< NumLock key
							s3eKeyInsert = 118,       //!< Insert key
							s3eKeyHome = 119,         //!< Home key
							s3eKeyPageUp = 120,       //!< Page Up key
							s3eKeyPageDown = 121,     //!< Page Down key
							s3eKeyKbEnd = 122,        //!< End key (on keyboard)
							s3eKeyDelete = 123,       //!< Delete key
							s3eKeyPause = 124,        //!< Pause key
							s3eKeyAt = 125,           //!< At '@' key
							s3eKeyBack = 126,         //!< Back key
							s3eKeyMenu = 127,         //!< Menu key
							s3eKeySearch = 128,       //!< Search key
							s3eKey3DMode = 129,       //!< 3D Mode key
							s3eKeyMyApps = 130,       //!< My Apps key
							s3eKeyPrintScreen = 131,  //!< Print screen key
							s3eKeyScrollLock = 132,   //!< Scroll lock key

							s3eKeyAbsGameA = 200,     //!< Abstract Game keyA.
							s3eKeyAbsGameB = 201,     //!< Abstract Game keyB.
							s3eKeyAbsGameC = 202,     //!< Abstract Game keyC.
							s3eKeyAbsGameD = 203,     //!< Abstract Game keyD.
							s3eKeyAbsUp = 204,        //!< Abstract Up.
							s3eKeyAbsDown = 205,      //!< Abstract Down.
							s3eKeyAbsLeft = 206,      //!< Abstract Left.
							s3eKeyAbsRight = 207,     //!< Abstract Right.
							s3eKeyAbsOk = 208,        //!< Abstract Ok.
							s3eKeyAbsASK = 209,       //!< Abstract action softkey.

													  /**
													  * Abstract backwards softkey.
													  *
													  * @platnote{Windows Phone 8, wp8}  On Windows Phone 8 back button press
													  * event is not fired when keyboard is out
													  * @endplatnote
													  *
													  * @platnote{Windows Phone 8.1, wp81}  On Windows Phone 8.1 back button press
													  * event is not fired when keyboard is out
													  * @endplatnote
													  */
	s3eKeyAbsBSK = 210,

	s3eKeyLeftWindows = 211,  //!< The left Windows key.
	s3eKeyRightWindows = 212, //!< The right Windows key.
	s3eKeyLeftBackSlash = 213,//!< The left backslash "\" key.
	s3eKeyL2 = 214,
	s3eKeyR2 = 215,
	s3eKeyMediaRewind = 216,
	s3eKeyMediaFastForward = 217,
	s3eKeyMediaPlayPause = 218,

	s3eKeyCount = 219
} s3eKey;

#define S3E_KEY_INVALID ((s3eKey)0)
#define    S3E_KEY_STATE_DOWN     (1 << 0)
#define    S3E_KEY_STATE_PRESSED  (1 << 1)
#define    S3E_KEY_STATE_RELEASED (1 << 2)

typedef enum s3eKeyboardNumpadOrientation
{
	S3E_NUMPAD_ORIENT_NORMAL = 0,   ///< First row of numbers across the top
	S3E_NUMPAD_ORIENT_ROT90 = 1,   ///< First row of numbers runs down the right
	S3E_NUMPAD_ORIENT_ROT180 = 2,   ///< First row of numbers runs along the bottom
	S3E_NUMPAD_ORIENT_ROT270 = 3    ///< First row of numbers runs up the left
} s3eKeyboardNumpadOrientation;

typedef enum s3eKeyboardProperty
{
	S3E_KEYBOARD_HAS_NUMPAD = 0,
	S3E_KEYBOARD_HAS_ALPHA = 1,
	S3E_KEYBOARD_HAS_DIRECTION = 2,
	S3E_KEYBOARD_NUMPAD_ORIENTATION = 3,
	S3E_KEYBOARD_GET_CHAR = 4,
	S3E_KEYBOARD_INPUT_TYPE = 5,
	S3E_KEYBOARD_ENABLE_APP_EXIT = 6
} s3eKeyboardProperty;

typedef enum s3eKeyboardInputTypes
{
	S3E_KEYBOARD_INPUT_TYPE_DEFAULT = 0,  ///< Default input type for keyboard
	S3E_KEYBOARD_INPUT_TYPE_URL = 1,  ///< Input type for URL
	S3E_KEYBOARD_INPUT_TYPE_EMAIL = 2,  ///< Input type for email
	S3E_KEYBOARD_INPUT_TYPE_NUMBER = 3,  ///< Input type for number pad
	S3E_KEYBOARD_INPUT_TYPE_PHONE = 4,  ///< Input type for phone pad
} s3eKeyboardInputTypes;

typedef enum s3eKeyboardError
{
	S3E_KEYBOARD_ERR_NONE = 0, ///< No Error.
	S3E_KEYBOARD_ERR_PARAM = 1, ///< Invalid parameter.
	S3E_KEYBOARD_ERR_TOO_MANY = 2, ///< Maximum number of callbacks exceeded .
	S3E_KEYBOARD_ERR_ALREADY_REG = 3, ///< The specified callback is already registered.
	S3E_KEYBOARD_ERR_NOT_FOUND = 4, ///< The specified callback was not found for removal.
	S3E_KEYBOARD_ERR_UNAVAIL = 5, ///< The specified callback was not found for removal.

	S3E_KEYBOARD_ERR_DEVICE = 6  ///< The underlying keyboard device failed.
} s3eKeyboardError;

typedef enum s3eKeyboardCallback
{
	S3E_KEYBOARD_KEY_EVENT = 0,
	S3E_KEYBOARD_CHAR_EVENT = 1,

	S3E_KEYBOARD_CALLBACK_MAX
} s3eKeyboardCallback;

typedef struct s3eKeyboardEvent
{
	/** Key that was pressed or released. */
	s3eKey m_Key;
	/** Whether the key was pressed (1) or released (0). */
	uint32_t m_Pressed;
} s3eKeyboardEvent;

#define S3E_KEYBOARD_DISP_LENGTH 16

s3eResult s3eKeyboardGetInt(s3eKeyboardProperty property);

s3eResult s3eKeyboardSetInt(s3eKeyboardProperty property, int32_t value);

void s3eKeyboardClearState();

s3eResult s3eKeyboardUpdate();

int32_t s3eKeyboardGetState(s3eKey key);

s3eWChar s3eKeyboardGetChar();

s3eKey s3eKeyboardAnyKey();

s3eResult s3eKeyboardGetDisplayName(char* dst, s3eKey key, bool terminateString = true);

//Legacy ...

#define s3eKeyShift s3eKeyLeftShift
#define s3eKeyControl s3eKeyLeftControl
#define s3eKeyAlt s3eKeyLeftAlt


#define s3eKeyState int32
#define S3E_KEY_STATE_UP    0
#define s3eKeyStateUp       S3E_KEY_STATE_UP
#define s3eKeyStateDown     S3E_KEY_STATE_DOWN
#define s3eKeyStatePressed  S3E_KEY_STATE_PRESSED
#define s3eKeyStateReleased S3E_KEY_STATE_RELEASED

#define S3E_KEYBOARD_HAS_KEYPAD  S3E_KEYBOARD_HAS_NUMPAD
