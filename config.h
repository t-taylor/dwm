/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=8" };
static const char col_bg[]          = "#282828";
static const char col_gray1[]        = "#928374";
static const char col_gray2[]        = "#a89984";
static const char col_cyan[]        = "#458588";
static const char col_fg[]          = "#ebdbb2";
static const char *colors[][3]      = {
	/*                   fg         bg          border   */
	[SchemeNorm] =     { col_gray1, col_bg,     col_bg  },
	[SchemeSel]  =     { col_gray1, col_bg,     col_fg  },
	[SchemeStatus] =   { col_gray1, col_bg,     "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel] =  { col_fg,    col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm] = { col_gray1, col_bg,     "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel] =  { col_gray1, col_cyan,   "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm] = { col_gray2, col_bg,     "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "QJackCtl", NULL,       NULL,       0,            1,           -1 },
	{ "amenu",    NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "[M]",      monocle },
	{ "DD",       doubledeck }
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static const char *amenudrun[] = { "amenu", "-r", NULL };
static const char *amenuwind[] = { "amenu", "-w", NULL };
static const char *amenupass[] = { "amenu", "-p", NULL };
static const char *termcmd[]  = { "st", "-e", "tmux", "-2", NULL };
static const char *chromiu[]  = { "chromium", NULL };
static const char *maimshot[]  = { "clipshot", NULL };

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_o,         spawn,          {.v = amenudrun } },
	{ MODKEY,                       XK_i,         spawn,          {.v = amenuwind } }, //window
	{ MODKEY,                       XK_g,         spawn,          {.v = amenupass } }, //gnupass
	{ MODKEY,                       XK_s,         spawn,          {.v = maimshot } }, //scrot
	{ MODKEY,                       XK_m,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,         spawn,          {.v = chromiu } },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,         pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,         pushup,         {0} },
	{ MODKEY,                       XK_a,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_x,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_period,    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_v,         zoom,           {0} }, // view
	{ MODKEY,                       XK_z,         togglefullscr,  {0} }, // view
	{ MODKEY,                       XK_l,         shiftviewclients, { .i = +1 } },
	{ MODKEY,                       XK_h,         shiftviewclients, { .i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,         shiftviewclientsandmove, { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,         shiftviewclientsandmove, { .i = -1 } },
	{ MODKEY,                       XK_semicolon, viewnewtag,     {0} },
	{ MODKEY,                       XK_apostrophe,moveandviewnewtag,{0} },
	{ MODKEY,                       XK_grave,     view,           {0} },
	{ MODKEY,                       XK_BackSpace, killclient,     {0} },
	{ MODKEY,                       XK_y,         cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_p,         togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_n,         focusmon,       {.i = +1 } }, //next monitor
	{ MODKEY|ShiftMask,             XK_n,         tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_n,         newtagallmon,   {.i = +1 } },
	// rhythmbox
	{ MODKEY,                       XK_Insert,    spawn,          SHCMD("rhyctl -p") },
	{ MODKEY,                       XK_Delete,    spawn,          SHCMD("rhyctl -q") },
	{ MODKEY,                       XK_Next,      spawn,          SHCMD("rhythmbox-client --play-pause") },
	{ MODKEY,                       XK_Up,        spawn,          SHCMD("rhyctl -v 0.02") },
	{ MODKEY,                       XK_Down,      spawn,          SHCMD("rhyctl -v -0.02") },
	{ MODKEY,                       XK_Left,      spawn,          SHCMD("rhythmbox-client --previous") },
	{ MODKEY,                       XK_Right,     spawn,          SHCMD("rhythmbox-client --next") },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

