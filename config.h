/* See LICENSE file for copyright and license details. */
#include "colors.h"
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "noto:size=11" };
static const char dmenufont[]       = "noto:size=11";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
// Imported from colors.h
// static const char col_gray1[]       = "#222222";
// static const char col_gray4[]       = "#eeeeee";
// static const char col_cyan[]       = "#ffcccc";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title           tags mask     isfloating   monitor */
  { "Gimp",           NULL,       NULL,           1,            1,            0 },
  { "Firefox",        NULL,       NULL,           1,            0,            1 },
  { "Brave-browser",  NULL,       NULL,           1,            0,            1 },
  { "discord",        NULL,       NULL,           1,            0,            1 },
  { "ffxiv_dx11.exe", NULL,       NULL,           2,            0,            0 },
  { "Lutris",         NULL,       NULL,           1,            1,            1 },
  { "Steam",          NULL,       NULL,           2,            0,            1 },
  { "PCSX2",          NULL,       NULL,           2,            0,            1 },
  { "Spotify",        NULL,       NULL,           2,            0,            1 },
  { "Spotify",        NULL,       "Steam - News", 2,            0,            1 },
  { "obs",            NULL,       NULL,           2,            0,            1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define Alt_L Mod1Mask
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
static const char *termcmd[]  = { "kitty", "-c", "/home/dawid/.config/kitty/kitty.conf", NULL };
static const char *roficmd[]  = { "rofi", "-show", "run", NULL };

static const char *volume_down[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-10%", NULL };
static const char *volume_up[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+10%", NULL };
static const char *volume_mute[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *media_prev[]  = { "playerctl", "previous", NULL };
static const char *media_next[]  = { "playerctl", "next", NULL };
static const char *media_toggle[]  = { "playerctl", "play-pause", NULL };

static const char *flameshot[]  = { "flameshot", "gui", NULL };

static Key keys[] = {
	/* modifier           key                       function        argument */
	{ 0,         		      XF86XK_AudioMute,         spawn,          {.v = volume_mute} },
	{ 0,         		      XF86XK_AudioLowerVolume,  spawn,          {.v = volume_down} },
	{ 0,         		      XF86XK_AudioRaiseVolume,  spawn,          {.v = volume_up} },
	{ 0,         		      XF86XK_AudioPlay,         spawn,          {.v = media_toggle} },
	{ 0,         		      XF86XK_AudioPrev,         spawn,          {.v = media_prev } },
	{ 0,                  XF86XK_AudioNext,         spawn,          {.v = media_next } },
	{ MODKEY|ShiftMask,   XK_s,                     spawn,          {.v = flameshot } },
	{ Alt_L|ShiftMask,    XK_e,                     spawn,          SHCMD("wpg -z $(wpg -l) && wpg -s $(wpg -c)") },
	{ Alt_L|ShiftMask,    XK_r,                     spawn,          SHCMD("/home/dawid/.scripts/setRandomTheme.sh") },
	{ Alt_L,              XK_d,                     spawn,          {.v = roficmd } },
	{ Alt_L,			        XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,             XK_b,                     togglebar,      {0} },
	{ MODKEY,             XK_Down,                  focusstack,     {.i = +1 } },
	{ MODKEY,             XK_Up,                    focusstack,     {.i = -1 } },
	{ MODKEY,             XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,             XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,             XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,   XK_Return,                zoom,           {0} },
	{ MODKEY,             XK_Tab,                   view,           {0} },
	{ MODKEY,             XK_q,                     killclient,     {0} },
	{ MODKEY,             XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,   XK_space,                 togglefloating, {0} },
	{ MODKEY,             XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,             XK_Left,                  focusmon,       {.i = -1 } },
	{ MODKEY,             XK_Right,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_Left,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_Right,                 tagmon,         {.i = +1 } },
	TAGKEYS(              XK_1,                     0)
	TAGKEYS(              XK_2,                     1)
	TAGKEYS(              XK_3,                     2)
	{ MODKEY|ShiftMask,   XK_q,                     quit,           {0} },
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

