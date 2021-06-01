/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int gappx              = 30;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 0;        /* 1 means master-area is initially on the right */
static const int firsttime            = 0;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"FontAwesome:pixelsize=35","Caskaydia Cove Nerd Font:pixelsize=35" ,"Hack:pixelsize=28"  };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_orange[]      = "#e0602d";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char col_skyblue[]     = "#589CE7";

static const unsigned int baralpha = 190; // value b/w 0(transparent) & 255 (OPAQUE)
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*                   fg           bg         border   */
	[SchemeEmpty]  = { col_gray2,  col_black,  col_black },
	[SchemeNorm]   = { col_gray3,  col_black,  col_black  },
	[SchemeWarn] =	 { col_black,  col_yellow, col_red },
	[SchemeUrgent]=	 { col_white,  col_red,    col_red },
	[SchemeSel]    = { col_skyblue, col_black,  col_black },
	[SchemeTitle]  = { col_skyblue, col_black,  col_black },
};
static const unsigned int alphas[][3]      = {
	/*                   fg      bg        border     */
	[SchemeEmpty]  = { OPAQUE, baralpha, borderalpha },
	[SchemeNorm]   = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]    = { OPAQUE, baralpha, borderalpha },
	[SchemeTitle]  = { OPAQUE, baralpha, borderalpha },
};
static const char *const autostart[] = {
	"firefox-developer-edition", "https://github.com/trending", NULL,
	"emacs", NULL,
	"fish", "-c", "start &>> /home/sriram/.dwm/log", NULL,
	"workrave", NULL,
	"st", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title                 tags mask             isfloating  canfocus issticky monitor */
	{ NULL,              NULL,      "Picture in picture",  0,                     1,         1,         0,     -1 },
	{ "Gimp",            NULL,      NULL,                  0,                     1,         1,         0,     -1 },
	{ "firefox",         NULL,      NULL,                  1 << 1,                0,         1,         0,     -1 },
	{ "Chromium",        NULL,      NULL,                  1 << 1,                0,         1,         0,     -1 },
	{ "Google-chrome",        NULL,      NULL,                  1 << 1,                0,         1,         0,     -1 },
	{ "Emacs",           NULL,      NULL,                  1 << 2,                0,         1,         0,     -1 },
	{ "jetbrains-idea",  NULL,      NULL,                  1 << 2,                0,         1,         0,     -1 },
	{ "DBeaver",         NULL,      NULL,                  1 << 2,                0,         1,         0,     -1 },
	{ "Slack",           NULL,      NULL,                  1 << 3,                0,         1,         0,     -1 },
	{ "discord",         NULL,      NULL,                  1 << 3,                0,         1,         0,     -1 },
	{ "zoom",            NULL,      NULL,                  1 << 3,                0,         1,         0,     -1 },
	{ "st-256color",     NULL,      "oracle",              1 << 5,                0,         1,         0,     -1 },
	{ NULL,              NULL,      "Prime Video",         1 << 7,                0,         1,         0,     -1 },
	{ NULL,              NULL,      "YouTube",             1 << 8,                0,         1,         0,     -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
#include "gaplessgrid.c"
#include "shiftviewclients.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",	  gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[D]",      deck },
	{ "|||",      col },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};
void swaptags(const Arg *arg);
void copytags(const Arg *arg);

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      combopertagview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,       {.ui = 1 << TAG} }, \
	{ MODKEY|MODKEY2,               KEY,      copytags,        {.ui = 1 << TAG} }, \
	{ MODKEY|MODKEY2|ShiftMask,     KEY,      swaptags,        {.ui = 1 << TAG} },
/* #define TAGKEYS2(KEY,TAG) \ */
/* 	{ MODKEY,                       KEY,      toggleview, {.ui = 1 << TAG} }, \ */
/* 	{ MODKEY|ControlMask,           KEY,      combopertagview,      {.ui = 1 << TAG} }, \ */
/* 	{ MODKEY|ShiftMask,             KEY,      toggletag,       {.ui = 1 << TAG} }, */
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_m,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = -1 } },


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run","-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *chromecmd[]  = { "firefox-developer-edition", NULL };
static const char *emacscmd[]  = { "emacs", NULL };
static const char *personalemacscmd[] = { "emacs", "--with-profile","personal", NULL};
static const char *mpcprev[] = { "mpc","prev", NULL};
static const char *mpctoggle[] = { "mpc","toggle", NULL};
static const char *mpcnext[] = { "mpc","next", NULL};
static const char *amixertoggle[] = {   "amixer", "set", "Master", "toggle", NULL};
static const char *amixerdec[] = {    "amixer", "set", "Master", "5%-" , NULL};
static const char *amixerinc[] = {    "amixer", "set", "Master", "5%+" , NULL};
static const char *bluetoothcmd[]  = { "fish","-c", "soundtouch", NULL };
static const char *wificmd[]  = { "fish", "-c", "batman5G"};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = chromecmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = personalemacscmd } },
	{ 0,                            XK_F5,     spawn,          {.v = mpcprev } }, \
	{ 0,                            XK_F6,     spawn,          {.v = mpctoggle } }, \
	{ 0,                            XK_F7,     spawn,          {.v = mpcnext } },	\
	{ 0,                            XK_F10,    spawn,          {.v = amixertoggle } },	\
	{ 0,                            XK_F11,    spawn,          {.v = amixerdec } },	\
	{ 0,                            XK_F12,    spawn,          {.v = amixerinc } },	\
	/* { MODKEY,                       XK_e,      spawn,          {.v = personalemacscmd } }, */
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      spawn,          {.v = bluetoothcmd} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[7]} },
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ShiftMask,             XK_x,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_r,      togglermaster,  {0} },
	/* { MODKEY|ShiftMask,             XK_r,      applyrules,  {0} }, */
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_l,      shiftview,      { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      shiftview,      { .i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* TAGKEYS(                        XK_w,                      4) */
	/* TAGKEYS(                        XK_p,                      5) */
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
	{ MODKEY,                       XK_Escape, quit,           {1} },

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

void
swaptags(const Arg *arg)
{
	unsigned int newtag = arg->ui & TAGMASK;
	unsigned int curtag = selmon->tagset[selmon->seltags];

	if (newtag == curtag || !curtag || (curtag & (curtag-1)))
		return;

	for (Client *c = selmon->clients; c != NULL; c = c->next) {
		if((c->tags & newtag) || (c->tags & curtag))
			c->tags ^= curtag ^ newtag;

		if(!c->tags) c->tags = newtag;
	}

	selmon->tagset[selmon->seltags] = newtag;

	focus(NULL);
	arrange(selmon);
}

void
copytags(const Arg *arg) {
	unsigned int curtag = selmon->tagset[selmon->seltags];
	unsigned int newtag = arg->ui & TAGMASK;

	if (newtag == curtag || !curtag)
		return;

	/* char command[128]; */
	/* snprintf(command,sizeof(command),"echo current tag:%d > /home/sriram/dwm.log",curtag); */
	/* system(command); */
	for (Client *c = selmon->clients; c != NULL; c = c->next) {
		if(c->tags & curtag) {
			c->tags |= newtag;
		}
	}
	focus(NULL);
	arrange(selmon);
}
