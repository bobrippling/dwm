/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int transparentbar     = 0;        /* 1 means transparent bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* ### Programs
 *
 * - fc-list [-f '%{file}\n']
 * - fc-match
 * - xlsfonts
 *
 *
 * ### Fonts
 *
 * (broken)
 *
 * -*-fixed-*-*-*-*-12-*-*-*-*-*-*-*
 * -*-terminus-medium-r-normal-*-14-*-*-*-*-*-*-*
 * -*-terminus-*-*-*-*-*-*-*-*-*-*-*-*
 * -misc-fixed-medium-r-semicondensed--13-100-100-100-c-60-iso8859-1
 * monospace:size=10
 * profont
 * terminus-12
 * xft:ProFont:size=11
 * xft:ProggyTinyTT:size=13
 * NotoSerif
 *
 * (working)
 *
 * monospace:size=10    // boring default
 * ProggyTinyTT:size=14 // wonky at larger sizes
 * ProFont:size=13      // gets a bit ugly above 13
 */

#define FONT "ProFont:size=9"

static const char *fonts[]         = { FONT };
static const char dmenufont[]       = FONT;
static const char normbordercolor[] =  "#2e3436";
static const char normbgcolor[]     =  "#222222";
static const char normfgcolor[]     =  "#bfbfbf";
static const char selbordercolor[]  =  "#6c6a65";
static const char selbgcolor[]      =  "#2e3436";
static const char selfgcolor[]      =  "#b2d169";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor },
};

/* tagging */
static const char *tags[] = {
#define TS(x) #x
	TS(1), TS(2), TS(3), TS(4),
	TS(5), TS(6), TS(7), TS(8),
	TS(9), TS(a), TS(b), TS(c),
	TS(d), TS(e), TS(f),
#undef TS
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     iscentered     isfloating   monitor */
	{ "URxvt",             NULL,       NULL,       0,            1,             1,           -1 },
	{ "xfreerdp",          NULL,       NULL,       0,            1,             1,           -1 },

	{ "Firefox-esr",       NULL,       NULL,       1<<2,         1,             0,           -1 },
	{ "Chromium",          NULL,       NULL,       1<<2,         1,             0,           -1 },
	{ "Brave-browser",     NULL,       NULL,       1<<2,         1,             0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

enum
{
	/* first is default */
	LAYOUT_I_monocle,
	LAYOUT_I_tile,
	LAYOUT_I_bstack,
	LAYOUT_I_col,
	LAYOUT_I_float,
	LAYOUT_I_grid,
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	[LAYOUT_I_tile   ] = { "-|=",   tile    },
	[LAYOUT_I_float  ] = { "###",   NULL    },    /* no layout function means floating behavior */
	[LAYOUT_I_monocle] = { "[M]",   monocle },
	[LAYOUT_I_grid   ] = { "HHH",   grid    },
	[LAYOUT_I_bstack ] = { "-|-",   bstack  },
	[LAYOUT_I_col    ] = { "||=",   col     },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define XF86_KEY(k, cmd) \
	{ 0,   k,    cmd,   {.v = (char *[]){ "dwm_xf86_handler", #k, NULL } } }

#define MOVE_RESIZE_STEP 25

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run_quick", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-f", NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include <X11/XF86keysym.h> /* for XF86* keys */
static Key keys[] = {
	XF86_KEY(XF86XK_Sleep,             spawn),
	XF86_KEY(XF86XK_Launch1,           spawn),
	XF86_KEY(XF86XK_Launch2,           spawn),
	XF86_KEY(XF86XK_Launch3,           spawn),
	XF86_KEY(XF86XK_MonBrightnessUp,   spawn),
	XF86_KEY(XF86XK_MonBrightnessDown, spawn),
	XF86_KEY(XF86XK_Display,           spawn),
	XF86_KEY(XF86XK_Battery,           spawn),
	XF86_KEY(XF86XK_WLAN,              spawn),
	XF86_KEY(XF86XK_AudioNext,         spawn),
	XF86_KEY(XF86XK_AudioPrev,         spawn),
	XF86_KEY(XF86XK_AudioPlay,         spawn),
	XF86_KEY(XF86XK_AudioStop,         spawn),
	XF86_KEY(XF86XK_AudioMute,         spawn),
	XF86_KEY(XF86XK_AudioLowerVolume,  spawn),
	XF86_KEY(XF86XK_AudioRaiseVolume,  spawn),

	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawnq,         {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawnq,         {.v = termcmd } },

	/* move, resize */
	{ MODKEY,                       XK_s,      moveresize,     {.v = (int [4]){ 0, MOVE_RESIZE_STEP, 0, 0 }}},
	{ MODKEY,                       XK_w,      moveresize,     {.v = (int [4]){ 0, -MOVE_RESIZE_STEP, 0, 0 }}},
	{ MODKEY,                       XK_d,      moveresize,     {.v = (int [4]){ MOVE_RESIZE_STEP, 0, 0, 0 }}},
	{ MODKEY,                       XK_a,      moveresize,     {.v = (int [4]){ -MOVE_RESIZE_STEP, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,             XK_s,      moveresize,     {.v = (int [4]){ 0, 0, 0, MOVE_RESIZE_STEP }}},
	{ MODKEY|ShiftMask,             XK_w,      moveresize,     {.v = (int [4]){ 0, 0, 0, -MOVE_RESIZE_STEP }}},
	{ MODKEY|ShiftMask,             XK_d,      moveresize,     {.v = (int [4]){ 0, 0, MOVE_RESIZE_STEP, 0 }}},
	{ MODKEY|ShiftMask,             XK_a,      moveresize,     {.v = (int [4]){ 0, 0, -MOVE_RESIZE_STEP, 0 }}},

	{ MODKEY,                       XK_g,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_g,      togglebartrans, {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_u,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[LAYOUT_I_tile]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[LAYOUT_I_bstack]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[LAYOUT_I_col]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[LAYOUT_I_float]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[LAYOUT_I_monocle]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[LAYOUT_I_grid]} },

	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	/* need to sleep for the latter so scrot can grab the keyboard */
	{ 0,                            XK_Print,  spawnq,         {.v = (char *[]){ "scrot",       "%Y-%m-%d_%H:%M:%S.png", NULL } } },
	{ ShiftMask,                    XK_Print,  spawn ,         {.v = (char *[]){ "sh", "-c", "sleep 1; scrot -s %Y-%m-%d_%H:%M:%S.png", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

