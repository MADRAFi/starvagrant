
FREE_TOP = $3000;

GFX_ADDRESS = FREE_TOP;
DISPLAY_LIST_ADDRESS = GFX_ADDRESS + $4B0;
PMG_BASE = DISPLAY_LIST_ADDRESS + $100;

PLAYER_ADDRESS = $5000;
MODULE_ADDRESS = PLAYER_ADDRESS + $800;

CHARSET_ADDRESS1 = $6000;
CHARSET_ADDRESS2 = CHARSET_ADDRESS1 + $400;
CHARSET_ADDRESS3 = CHARSET_ADDRESS2 + $400;

SCREEN_ADDRESS1 = CHARSET_ADDRESS3 + $400;

KEY_OPTION1 = 31; //1
KEY_OPTION2 = 30; //2
KEY_OPTION3 = 26;  //3