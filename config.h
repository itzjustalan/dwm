/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
        "Fira Mono for Powerline:pixelsize=17:antialias=true:autohint=true",
        "NotoColorEmoji:pixelsize=14:antialias=true:autohint=true",
        "Symbola:pixelsize=14:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Fira Mono:size=16";
static const char col_gray1[]       = "#0B2942";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#0B2942";
static const char col_cyan_og[]        = "#005577";
static const char col_cyan_drac[]        = "#0B2942";
static const char col_cyan[]        = "#82AAFF";
//static const char col_border[]        = "#C792EA";
static const char col_border[]        = "#ff6b00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan_drac },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border},
};

/** colors **
#222222
#444444
#bbbbbb
#eeeeee
#005577
#8be9fd
#21222c
#757ab1

#423F68
#C38FE6

#011627
#32374D
#44596B
#567077

#1F385D
#82AAFF
#7FDBCA
#CAECE6
#C792EA
#F78C6C
#4B6479
#0B2942
#C5E478

#15232d
#ff6b00

*/

/* tagging */
// nerd font icons  ﲎ                        爵    ﱘ    ﭮ ﭮ   力   歷   
// telegram -        切
// apps -           隷   黎 
//static const char *tags[] = { " rch", "2", "3", "———|———", "5", "6", "", "8", "力" };
static const char *tags[] = { " rch", "", "1", "2", "3", "4,,", "5", "6", "", "8", "力", "aap", "aau", "acp", "axp", "asp", "#", "黎", "", "", "ooo" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask    isterminal  noswallow  isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,           0,            0,       1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,      0,            -1,      0,           -1 },
	{ "St",       NULL,       NULL,       0,           1,            0,       0,           -1 },
	{ "float",    NULL,       "notes",    0,           0,            0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
#include "horizgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      horizgrid },
};

/* custom constants  */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };


/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

        { MODKEY,                   XK_Down,    moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
        { MODKEY,                   XK_Up,      moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
        { MODKEY,                   XK_Right,   moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
        { MODKEY,                   XK_Left,    moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
        { MODKEY|ShiftMask,         XK_Down,    moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
        { MODKEY|ShiftMask,         XK_Up,      moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
        { MODKEY|ShiftMask,         XK_Right,   moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
        { MODKEY|ShiftMask,         XK_Left,    moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},

    { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
    { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
    { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
    { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
    { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
    { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
    { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
    { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

/*
    { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
    { 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
    { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
*/

    { MODKEY,                       XK_F11, spawn, {.v = downvol } },
    { MODKEY,                       XK_F9,  spawn, {.v = mutevol } },
    { MODKEY,                       XK_F12, spawn, {.v = upvol   } },

  TAGKEYS(                        XK_1,                     0)
  TAGKEYS(                        XK_2,                     1)
	TAGKEYS(                        XK_F1,                      2)
	TAGKEYS(                        XK_F2,                      3)
	TAGKEYS(                        XK_3,                      4)
	TAGKEYS(                        XK_4,                      5)
	TAGKEYS(                        XK_5,                      6)
	TAGKEYS(                        XK_6,                      7)
	TAGKEYS(                        XK_7,                      8)
	TAGKEYS(                        XK_8,                      9)
	TAGKEYS(                        XK_9,                      10)

/* custom work spaces */
  TAGKEYS(                        XK_F5,                     11)
  TAGKEYS(                        XK_F6,                     12)
  TAGKEYS(                        XK_F7,                     13)
  TAGKEYS(                        XK_F8,                     14)
  TAGKEYS(                        XK_F9,                     15)
  TAGKEYS(                        XK_F10,                    16)
  TAGKEYS(                        XK_F11,                    17)
  TAGKEYS(                        XK_F12,                    18)
  TAGKEYS(                        XK_F3,                     19)
  TAGKEYS(                        XK_F4,                     20)


	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

