#pragma once
namespace RedSunlight
{
	enum class KeyCode {
		eKeyNone = -1,

		eKeyA,
		eKeyB,
		eKeyC,
		eKeyD,
		eKeyE,
		eKeyF,
		eKeyG,
		eKeyH,
		eKeyI,
		eKeyJ,
		eKeyK,
		eKeyL,
		eKeyM,
		eKeyN,
		eKeyO,
		eKeyQ,
		eKeyP,
		eKeyR,
		eKeyS,
		eKeyT,
		eKeyU,
		eKeyW,
		eKeyV,
		eKeyX,
		eKeyY,
		eKeyZ,

		eKey1,
		eKey2,
		eKey3,
		eKey4,
		eKey5,
		eKey6,
		eKey7,
		eKey8,
		eKey9,
		eKey0,

		eKeyF1,
		eKeyF2,
		eKeyF3,
		eKeyF4,
		eKeyF5,
		eKeyF6,
		eKeyF7,
		eKeyF8,
		eKeyF9,
		eKeyF10,
		eKeyF11,
		eKeyF12,

		eKeyArrowUp,
		eKeyArrowLeft,
		eKeyArrowRight,
		eKeyArrowDown,

		eKeySpace,

		eKeyComma,
		eKeyDot,
		eKeySlash,
		eKeySemicolon,
		eKeyApostrophe,
		eKeyBackslash,
		eLeftBracket,
		eRightBracket,
		eKeyGraveAccent,
		eKeyMinus,
		eKeyEqual,
		eKeyBackspace,
		eKeyEscape,

		eKeyLast
	};

	constexpr int getKeyboardKeysCount()
	{
		return static_cast<int>(KeyCode::eKeyLast);
	}
}