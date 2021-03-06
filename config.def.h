/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 15;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
/*   Display modes of the tab bar: never shown, always shown, shown only in */
/*   monocle mode in presence of several windows.                           */
/*   Modes after showtab_nmodes are disabled                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_always, showtab_nmodes};
static const int showtab            = showtab_always; /* Default tab bar show mode */
static const int toptab            = True;    /* False means bottom tab bar */

static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char normbordercolor[] = "#ff0000";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#00ee00";
static const char selbordercolor[]  = "#00ff00";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#ff0000";
static const char tabbordercolor[]  = "#000e00";
static const char tabbgcolor[]      = "#222222";
static const char tabfgcolor[]      = "#bbbbbb";
static const char tabselbordercolor[] = "#005522";
static const char tabselbgcolor[]   = "#005577";
static const char tabselfgcolor []  = "#eeeeee";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor  },
	[SchemeTab] = { tabfgcolor, tabbgcolor, tabbordercolor },
        [SchemeTabSel] = { tabselfgcolor, tabselbgcolor, tabselbordercolor },
};

/* tagging */
static const char *tags[] = { "Main", "Web", "Add", "Void", "Media"};
static unsigned int panel[4]={0,0,0,0};//positions: 0-bottom panel, 1-top panel, 2-left panel, 3-right panel

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "conky",     NULL,       NULL,       0,            1,           -1 },
	{ "onboard",     NULL,       NULL,     0,            1,           -1 },
	{ "gnome-mines",     NULL,       NULL,     0,            1,           -1 },
	{ "four-in-a-row",     NULL,       NULL,     0,            1,           -1 },
	{ "iagno",     NULL,       NULL,     0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
        { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[-]",      reading },/* tile border is horizontal, not vertical*/
	{ "HHH",      grid }, /*   grid layout     */
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINDOWMASK XK_Super_L
#define XK_XF86AudioRaiseVolume 0x1008ff13
#define XK_XF86AudioLowerVolume 0x1008ff11
#define XK_XF86MonBrightnessDown 0x1008ff03
#define XK_XF86MonBrightnessUp 0x1008ff02
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ControlMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *desktopmenucmd[] = { "desktop-menu", NULL};
static const char *termcmd[]  = { "tabbed", "-c", "st", "-w", NULL };
static const char *prtscr[]={"screenshot", NULL};
static const char *pcmanfm[]={"pcmanfm",NULL};
static const char *volumeup[]={"amixer", "set", "Master", "5%+", NULL};
static const char *volumedown[]={"amixer", "set", "Master", "5%-", NULL};
static const char *uplight[]={"xbacklight", "+5", NULL};
static const char *downlight[]={"xbacklight", "-5", NULL};
static const char *xkillcmd[] = { "/bin/bash", "-c", "xkill", NULL };

static Key keys[] = {
	// modifier                     key        function        argument
	{ 0,                       WINDOWMASK,      spawn,          {.v = desktopmenucmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { 0,                          XK_Print,     spawn,          {.v=prtscr}},
    { MODKEY,                       XK_e,      spawn,          {.v =pcmanfm} },
	{ MODKEY|ControlMask,              XK_t, spawn,          {.v = termcmd } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	//{ MODKEY,                       XK_b,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom_float,           {.i=+1} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             XK_F4,      killclient,     {0} },
	{ MODKEY,             XK_F5,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,			            XK_y,      setlayout,	   {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ ShiftMask|ControlMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask|ControlMask,                       XK_Left,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask,                       XK_Right, focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,             XK_Left,  tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,             XK_Right, tagmon,         {.i = +1 } },
	{ 0,						XK_XF86AudioRaiseVolume,	spawn,	{ .v=volumeup }	},
	{ 0,						XK_XF86AudioLowerVolume,	spawn,	{ .v=volumedown }	},
	{ 0,						XK_XF86MonBrightnessDown,	spawn,	{ .v=downlight }	},
	{ 0,						XK_XF86MonBrightnessUp,	spawn,	{ .v=uplight }	},
	{ ControlMask|ShiftMask,		XK_r,	   update_configuration, {0} },
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,             XK_BackSpace,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button3,        killclient,           {0} },
	{ ClkWinTitle,          0,              Button1,        focusstack,           {.i=+1} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = volumeup } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = volumedown } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
	{ ClkTabBar,            0,              Button3,        killwin,       {0} },
	{ ClkTabBar,            0,              Button4,        focusstack,     {.i = -1 } },
	{ ClkTabBar,            0,              Button5,        focusstack,     {.i = +1 } },
	{ ClkTabSymbol,         0,              Button1,        killclient,     {0} },
	{ ClkTabSymbol,         0,              Button3,        spawn,     {.v = xkillcmd } },
};
