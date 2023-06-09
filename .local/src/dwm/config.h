/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"

/* appearance */
static unsigned int borderpx  = 0;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 5;        /* horiz inner gap between windows */
static unsigned int gappiv    = 5;        /* vert inner gap between windows */
static unsigned int gappoh    = 20;        /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 90;        /* vert outer gap between windows and screen edge */
static int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad      = 9;       /* vertical padding of bar */
static const int sidepad      = 90;       /* horizontal padding of bar */
// static char *fonts[]          = { "IosevkaNerdFont:pixelsize=17:antialias=true:autohint=true","IosevkaNerdFont:pixelsize=17:antialias=true:autohint=true" };
static char *fonts[]          = { "SauceCodePro Nerd Font:pixelsize=17:antialias=true:autohint=true" };
static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#00ffff";
static char selfgcolor[]            = "#00ffff";
static char selbordercolor[]        = "#00ffff";
static char selbgcolor[]            = "#303030";
static const unsigned int baralpha = 225;
static const unsigned int borderalpha = 0;
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spblue", "-g", "100x25", "-e", "bluetoothctl", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "splf", "-g", "120x35", "-e", "lfub", NULL };
const char *spcmd3[] = {TERMINAL, "-n", "spterm", "-g", "110x30", NULL };
const char *spcmd4[] = {TERMINAL, "-n", "spcalc", "-g", "100x25", "-e", "bc","-l", NULL };
const char *spcmd5[] = {TERMINAL, "-n", "spvimwiki", "-g", "110x30", "-e", "nvim","-c","VimwikiIndex", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spblue",      spcmd1},
	{"splf",        spcmd2},
	{"spterm",		spcmd3},
	{"spcalc",		spcmd4},
	{"spvimwiki",	spcmd5},
};

/* tagging */
static const char *tags[] = { "", "爵", "切", "", "", "", "7", "8", "9" };
/* static const char *tags[] = { "Home", "Web", "Social", "Teams", "Libre", "Mail", "7", "8", "9" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    			instance   title   tags mask  isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     			NULL,      NULL,   1 << 8,        	0,          0,         	0,     -1 },
	{ "libreoffice",		NULL,	   NULL,   1 << 4,			0,	       	0,	  		0,	    1 },
	{ "TelegramDesktop", 	NULL,	   NULL,   1 << 2,	  		0,	       	0,	  		0,	    0 },
	{ "discord", 			NULL,	   NULL,   1 << 2,	  		0,	       	0,	  		0,	   -1 },
	{ BROWSER,    		NULL,      NULL,   1 << 1,     	  	0,          0,         	0,      0 },
	{ "Lutris",    		NULL,      NULL,   1 << 5,     	  	0,          0,         	0,      0 },
	{ "Microsoft Teams - Preview",NULL,NULL,   1 << 3,     	  	0,          0,         	0,      0 },
	{ TERMCLASS,			NULL,	   NULL,   0,				0,			0,			0,	   -1 },

	{ NULL,					"spblue",  NULL,   SPTAG(0),      	1,          1,         	0,     -1 },
	{ NULL,					"splf",    NULL,   SPTAG(1),      	1,          1,         	0,     -1 },
	{ NULL,      			"spterm",  NULL,   SPTAG(2),      	1,          1,         	0,     -1 },
	{ NULL,      			"spcalc",  NULL,   SPTAG(3),      	1,          1,         	0,     -1 },
	{ NULL,      			"spvimwiki",  NULL,   SPTAG(4),      	1,          1,         	0,     -1 },
};

/* layout(s) */
static float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",		tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */

	{ "",		spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */

	{ "[D]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_c,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color8",		STRING,	 &normbordercolor },
		{ "color12",		STRING,	 &selbordercolor },
		{ "background",		STRING,	 &normbgcolor },
		{ "color4",		STRING,	 &normfgcolor },
		{ "color6",		STRING,	 &selfgcolor },
		{ "background",		STRING,	 &selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	 &mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },

	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_backslash,		view,		{0} },

	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,		XK_a,		defaultgaps,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,		XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.02} },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.02} },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,		XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY,			XK_apostrophe,	togglescratch,	{.ui = 0} },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.ui = 2} },
	{ MODKEY,			XK_s,		togglescratch,	{.ui = 1} },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +4 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -4 } },
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_n,		togglescratch,		{.ui = 4} },

	{ MODKEY,			XK_Down,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Down,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Up,		focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Up,		tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		XK_Page_Up,	shifttag,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = +1 } },
	{ MODKEY|ShiftMask,		XK_Page_Down,	shifttag,	{ .i = +1 } },

	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },


  	{ 0, XF86XK_Calculator,		togglescratch,		 {.ui = 3}},

	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		Button4,	incrgaps,	{.i = +1} },
	{ ClkClientWin,		MODKEY,		Button5,	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
	{ ClkRootWin,		0,		Button2,	togglebar,	{0} },
};

