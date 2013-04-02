/* See LICENSE file for copyright and license details. */

#define GREEN  "#b2d169"
#define ORANGE "#f5a400"

/* appearance */
static const char font[]            = "-*-*-profont-*-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] =  "#2e3436";
static const char normbgcolor[]     =  "#222222";
static const char normfgcolor[]     =  "#bfbfbf";
static const char selbordercolor[]  =  "#6c6a65";
static const char selbgcolor[]      =  "#2e3436";
static const char selfgcolor[]      =  GREEN;
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

static const char *tags[] = {
#define TS(x) #x
	TS(1), TS(2), TS(3), TS(4),
	TS(5), TS(6), TS(7), TS(8),
	TS(9), TS(a), TS(b), TS(c),
	TS(d), TS(e), TS(f),
#undef TS
};

#define TAG_ANY   0
#define TAG_ALL   (~0)
#define TAG_MAIN  (1 << 0)
#define TAG_TERM  (1 << 1)
#define TAG_NET   (1 << 2)
#define TAG_IM    (1 << 3)
#define TAG_MISC1 (1 << 4)
#define TAG_MISC2 (1 << 5)
#define TAG_FLOAT (1 << 6)
#define TAG(i)    (1 << ((i)-1))

#define XTERM(n) \
		{ "XTerm"#n          , NULL,             NULL,                   TAG(n),         False,  -1 }, \
		{ "XTerm"#n"f"       , NULL,             NULL,                   TAG(n),         True,   -1 }


/* xprop | awk -F '"' '/^WM_CLASS/ { printf("%s:%s:",$4,$2) }; /^WM_NAME/ { printf("%s\n",$2) }' */
static const Rule rules[] = {
	/* class, instance, title, tags, isfloating, monitor */
	{ "URxvt"            , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	{ "XTerm"            , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	{ "st"               , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	/*
	 * xterm tab spawn mcgraw
	 * XTerm([0-9])(f\?)
	 * \1 = tab, \2 = float
	 */
	XTERM(1),
	XTERM(2),
	XTERM(3),
	XTERM(4),
	XTERM(5),
	XTERM(6),
	XTERM(7),
	{ "Namoroka"         , NULL,             NULL,                   TAG_NET,        True,     -1 },
	{ NULL               , "Browser",        NULL,                   TAG_NET,        True,     -1 },
	{ NULL               , "Navigator",      NULL,                   TAG_NET,        False,    -1 },
	{ "Iron"             , NULL,             NULL,                   TAG_NET,        False,    -1 },
	{ NULL               , "chromium",       NULL,                   TAG_NET,        False,    -1 },
	{ "surf"             , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	{ "Gvim"             , NULL,             NULL,                   TAG_ANY,        True,     -1 },

	{ "Pidgin"           , NULL,             NULL,                   TAG_IM,         False,    -1 },
	{ "Pidgin"           , NULL,             "File Transfers",       TAG_IM,         True,     -1 },
	{ NULL               , "skype",          NULL,                   TAG_IM,         False,    -1 },
	{ NULL               , "skype.real",     NULL,                   TAG_IM,         False,    -1 },

	{ NULL               , NULL,             "Comm v2.0",            TAG_ANY,        True,     -1 },
	{ NULL               , "gft",            NULL,                   TAG_ANY,        True,     -1 },

	{ "vnc"              , NULL,             NULL,                   TAG_ANY,        True,     -1 },

	{ "Xmessage"         , NULL,             NULL,                   TAG_ANY,        True,     -1 },
	{ "Xchm"             , NULL,             NULL,                   TAG_MAIN,       False,    -1 },
	{ "Xpdf"             , NULL,             NULL,                   TAG_MAIN,       False,    -1 },
	{ "Epdfview"         , NULL,             NULL,                   TAG_MAIN,       False,    -1 },
	{ "libreoffice"      , NULL,             NULL,                   TAG_MISC1,      False,    -1 },
	{ NULL               , NULL,             "OpenOffice",           TAG_MISC1,      False,    -1 },
	{ NULL               , NULL,             "LibreOffice",          TAG_MISC1,      False,    -1 },

	{ "Gpicview"         , NULL,             NULL,                   TAG_ANY,        True,     -1 },
	{ "feh"              , NULL,             NULL,                   TAG_ANY,        True,     -1 },
	{ "Gimp"             , NULL,             NULL,                   TAG_FLOAT,      True,     -1 },
	{ "MPlayer"          , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	{ "mplayer2"         , NULL,             NULL,                   TAG_ANY,        False,    -1 },
	{ "ROX-Dialog"       , NULL,             NULL,                   TAG_ANY,        True,     -1 },
	{ "Vnc"              , NULL,             NULL,                   TAG_ANY,        True,     -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

/* funcs in patches/ */
typedef void arrangefunc(Monitor *);
typedef void keyfunc(const Arg *);

extern keyfunc spawnq, shiftview, moveresize, incnmaster, jumpto;

#define INIT_LAYOUT 4
#define INIT_TAG    TAG_TERM

static const Layout layouts[] = {
	/* symbol     arrange function */
/*{ "[]=",      tile },    * first entry is default */
	{ "-|=",   tile    },
	{ "###",   NULL    },    /* no layout function means floating behavior */
	{ "[#]",   monocle },
};

/* key definitions */
#define MODKEY  Mod4Mask
#define AltMask Mod2Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define MOVE_RESIZE_STEP 25

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-f", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include <X11/XF86keysym.h> /* makes XF86* keys work */
static Key keys[] = {
	{ 0,                   XK_Print,                  spawnq,         {.v = (char *[]){ "screenshot", NULL } } },

#define XF86_KEY(k, cmd) \
	{ 0,   k,    cmd,   {.v = (char *[]){ "dwm_xf86_handler", #k, NULL } } }

	XF86_KEY( XF86XK_Sleep,             spawn  ),
	XF86_KEY( XF86XK_Launch1,           spawn  ),
	XF86_KEY( XF86XK_Launch2,           spawn  ),
	XF86_KEY( XF86XK_Launch3,           spawn  ),
	XF86_KEY( XF86XK_MonBrightnessUp,   spawn  ),
	XF86_KEY( XF86XK_MonBrightnessDown, spawn  ),
	XF86_KEY( XF86XK_Display,           spawn  ),
	XF86_KEY( XF86XK_Battery,           spawn  ),
	XF86_KEY( XF86XK_WLAN,              spawn  ),

	XF86_KEY( XF86XK_AudioNext,         spawn  ),
	XF86_KEY( XF86XK_AudioPrev,         spawn  ),
	XF86_KEY( XF86XK_AudioPlay,         spawn  ),
	XF86_KEY( XF86XK_AudioStop,         spawn  ),
	XF86_KEY( XF86XK_AudioMute,         spawn  ),
	XF86_KEY( XF86XK_AudioLowerVolume,  spawn  ),
	XF86_KEY( XF86XK_AudioRaiseVolume,  spawn  ),


	/* modifier            key                        function        argument */
	{ MODKEY,              XK_F3,                     spawnq,         {.v = (char *[]){ "amixer", "set", "Headphone", "toggle", NULL } } },
	{ MODKEY,              XK_F4,                     spawnq,         {.v = (char *[]){ "slock.sh", NULL } } },

	{ MODKEY,              XK_F1,                     spawnq,         {.v = (char *[]){ "setxkbmap", "gb",  "-variant",  "",       NULL } } },
	{ MODKEY,              XK_F2,                     spawnq,         {.v = (char *[]){ "setxkbmap", "gb",  "-variant",  "dvorak", NULL } } },

	{ MODKEY,              XK_p,                      spawnq,         {.v = dmenucmd } },
	{ MODKEY,              XK_Return,                 spawn,          {.v = termcmd  } },

	{ MODKEY|ShiftMask,    XK_q,                      quit,           {0} },
	{ MODKEY,              XK_g,                      togglebar,      {0} },

	/*
	{ MODKEY|ShiftMask,    XK_l,                      pointerlock,    {.i = 1 } },
	{ MODKEY|ShiftMask,    XK_p,                      pointerlock,    {.i = 0 } },
	*/

	{ MODKEY,              XK_j,                      focusstack,     { .i = +1 } },
	{ MODKEY,              XK_k,                      focusstack,     { .i = -1 } },
	{ MODKEY,              XK_u,                      setmfact,       { .f = -0.05 } },
	{ MODKEY,              XK_i,                      setmfact,       { .f = +0.05 } },
	{ MODKEY,              XK_l,                      shiftview,      { .i = +1 } },
	{ MODKEY,              XK_h,                      shiftview,      { .i = -1 } },

	/* move, resize */
	{ MODKEY,              XK_s,                      moveresize,     {.v = (int [4]){ 0, MOVE_RESIZE_STEP, 0, 0 }}},
	{ MODKEY,              XK_w,                      moveresize,     {.v = (int [4]){ 0, -MOVE_RESIZE_STEP, 0, 0 }}},
	{ MODKEY,              XK_d,                      moveresize,     {.v = (int [4]){ MOVE_RESIZE_STEP, 0, 0, 0 }}},
	{ MODKEY,              XK_a,                      moveresize,     {.v = (int [4]){ -MOVE_RESIZE_STEP, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,    XK_s,                      moveresize,     {.v = (int [4]){ 0, 0, 0, MOVE_RESIZE_STEP }}},
	{ MODKEY|ShiftMask,    XK_w,                      moveresize,     {.v = (int [4]){ 0, 0, 0, -MOVE_RESIZE_STEP }}},
	{ MODKEY|ShiftMask,    XK_d,                      moveresize,     {.v = (int [4]){ 0, 0, MOVE_RESIZE_STEP, 0 }}},
	{ MODKEY|ShiftMask,    XK_a,                      moveresize,     {.v = (int [4]){ 0, 0, -MOVE_RESIZE_STEP, 0 }}},

	{ MODKEY|ControlMask,  XK_q,                      jumpto,         {.i = 0}},
	{ MODKEY|ControlMask,  XK_e,                      jumpto,         {.i = 1}},
	{ MODKEY|ControlMask,  XK_a,                      jumpto,         {.i = 2}},
	{ MODKEY|ControlMask,  XK_d,                      jumpto,         {.i = 3}},

	{ MODKEY|ControlMask,  XK_Return,                 zoom,           {0} },
	{ MODKEY,              XK_Tab,                    view,           {0} },
	{ MODKEY,              XK_c,                      killclient,     {0} },

	{ MODKEY,              XK_e,                      setlayout,      {.v = &layouts[0]} }, /* ntile - replaces tile     */
	{ MODKEY,              XK_b,                      setlayout,      {.v = &layouts[1]} }, /* nbstack - replaces bstack */
	{ MODKEY,              XK_n,                      setlayout,      {.v = &layouts[2]} }, /* ncol                      */
	{ MODKEY,              XK_f,                      setlayout,      {.v = &layouts[3]} }, /* float                     */
	{ MODKEY,              XK_m,                      setlayout,      {.v = &layouts[4]} }, /* monocle                   */
	{ MODKEY,              XK_t,                      setlayout,      {.v = &layouts[5]} }, /* grid                      */

	{ MODKEY|ControlMask,  XK_space,                  setlayout,      {0} },
	{ MODKEY,              XK_space,                  togglefloating, {0} },
	{ MODKEY,              XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,              XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period,                 tagmon,         {.i = +1 } },

	{ MODKEY,              XK_y,                      incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_o,                      incnmaster,     {.i = -1 } },

	TAGKEYS(               XK_1,                      0)
	TAGKEYS(               XK_2,                      1)
	TAGKEYS(               XK_3,                      2)
	TAGKEYS(               XK_4,                      3)
	TAGKEYS(               XK_5,                      4)
	TAGKEYS(               XK_6,                      5)
	TAGKEYS(               XK_7,                      6)
	TAGKEYS(               XK_8,                      7)
	TAGKEYS(               XK_9,                      8)
	/* other tags are accessible via left/right */
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,         {0} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,         {.v = &layouts[1]} }, /* 2 = middle button */
	{ ClkLtSymbol,          0,              Button3,        setlayout,         {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,              {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,         {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,       {0} },
	{ ClkTagBar,            0,              Button1,        view,              {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,        {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,         { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,         { .i = +1 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,               {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,         {0} },
};
