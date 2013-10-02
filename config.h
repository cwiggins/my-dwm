/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            =
	"-lokaltog-symbols-*-*-*-*-11-*-*-*-*-*-*-*"
    ","
	"-lokaltog-fixed-medium-*-*-*-10-*-*-*-*-*-iso8859-*"
	;
static const char colors[MAXCOLORS][ColLast][8] = {
/*  border     fg         bg       */
	{ "#1a1a1a", "#888888", "#1a1a1a"  },  // normal           light gray / dark gray
	{ "#82ca42", "#ffffff", "#82ca42"  },  // selected tag     white      / light green
	{ "#fd5337", "#ffffff", "#fd5337"  },  // urgent/warning   white      / salmon red
	{ "#fda12b", "#ffffff", "#fda12b"  },  // error            white      / orange
	{ "#000000", "#90d94e", "#1a1a1a"  },  // layout icon      green      / dark gray
	{ "#000000", "#ffffff", "#1a1a1a"  },  // white            white      / dark gray
	{ "#000000", "#fd5337", "#1a1a1a"  },  // red warning fg   red        / dark gray
	{ "#000000", "#daff30", "#1a1a1a"  },  //
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const int marginbottom	    = 15;
static const Bool clicktofocus		= False;
static const Bool viewontag			= False;
static const unsigned int statusmon = 0;

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 4,       False,       -1 },
	{ "Terminator", NULL,	  NULL,	      1 << 1,       False,	     -1 },
	{ "Chromium", NULL,		  NULL,	      1,	        False,	     -1 },
	{ "URxvt",  "ncmpcpp",    NULL,		  1 << 2,	    False,		 -1 },
	{ "URxvt",	"mcabber",    NULL,       1 << 3,	    False,		 -1 },
	{ "URxvt",    "urxvt",	  NULL,		  1 << 1,		False,		 -1 },
	{ "Vimprobable2", NULL,	  NULL,		  1,			False,		 -1 },
	{ "Tabbed",		"tabbed", NULL,       1,			False,		 -1 },
	{ "MPlayer",   "vaapi",   NULL,		  1 << 2,       False,		 -1 },
	{ "URxvt",	"mcabber",	  NULL,		  1 << 3,	    False,		 -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[P]",	  pidgin },
	{ "[B]",	  bstack },
};

/* tagging */
static const Tag tags[] = {
     /* Name	layout	mfact	nmaster */
	{ "Net",	&layouts[2], -1, -1},
	{ "Term",   &layouts[2], -1, -1},
	{ "Media",  &layouts[2], -1, -1},
	{ "Chat",   &layouts[3], 0.5, -1},
	{ "Misc",	&layouts[0], 0.5, -1},
};

// function to restart dwm
void
restart(const Arg *arg) {
	if(arg->v) {
		execvp(((char **)arg->v)[0], (char **)arg->v);
	}
	else{
		execlp("dwm", "dwm", NULL);
	}
}

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
static const char terminal[] = "urxvtc";
static const char scratchpadname[] = "scratchy";
static const char *dmenucmd[] = { "dmenu_run", "-i", "-p", "Run command:", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL  };
static const char *termcmd[]  = { terminal, NULL };
static const char *scratchpadcmd[] = { terminal, "-name", scratchpadname, "-geometry", "40x20", NULL };
static const char *volupcmd[]   = { "pamixer", "--increase", "5", NULL };
static const char *voldocmd[]   = { "pamixer", "--decrease", "5", NULL };
static const char *volmucmd[]   = { "pamixer", "--toggle-mute", NULL };
static const char *musiccmd[]   = { terminal,"-name", "ncmpcpp",  "-e", "ncmpcpp", "-h", "curtanime.hopto.org", NULL };
static const char *screenshotcmd[] = {"scrot", NULL};
static const char *mpdvolupcmd[]	 = {"ncmpcpp", "-h", "curtanime.hopto.org", "volume", "-2", NULL};
static const char *mpdvoldocmd[]	 = {"ncmpcpp", "-h", "curtanime.hopto.org",	"volume", "+2", NULL};
static const char *mpdtogglecmd[]	 = {"ncmpcpp", "-h", "curtanime.hopto.org", "toggle", NULL};
static const char *mpdnextcmd[]		 = {"ncmpcpp", "-h", "curtanime.hopto.org", "next", NULL};
static const char *mpdprevcmd[]		 = {"ncmpcpp", "-h", "curtanime.hopto.org", "prev", NULL};
static const char *mpdstopcmd[]		 = {"ncmpcpp", "-h", "curtanime.hopto.org", "stop", NULL};
static const char *chatcmd[]		 = { terminal, "-name", "mcabber", "-e", "mcabber", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,				XK_c,	   spawn,		   SHCMD("$(tabbed -d >/tmp/tabbed.xid ); vimprobable2 -e $(</tmp/tabbed.xid)") },
	{ MODKEY|ShiftMask,				XK_m,	   spawn,		   {.v = musiccmd } },
	{ MODKEY,						XK_c,	   spawn,	       {.v = chatcmd} },
	{ MODKEY|ShiftMask,				XK_s,	   spawn,	       {.v = screenshotcmd } },
	{ MODKEY,						0x2d,      spawn,		   {.v = mpdvoldocmd } },
	{ MODKEY,						0x3d,      spawn,		   {.v = mpdvolupcmd } },
	{ 0,							0x1008ff14, spawn,		   {.v = mpdtogglecmd } },
	{ 0,							0x1008ff15, spawn,		   {.v = mpdstopcmd } },
	{ 0,							0x1008ff16, spawn,		   {.v = mpdprevcmd } },
	{ 0,							0x1008ff17, spawn,		   {.v = mpdnextcmd } },
	{ MODKEY,						XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_grave,  killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{0,								0x1008ff13, spawn,		   {.v = volupcmd}},
	{0,								0x1008ff11, spawn,		   {.v = voldocmd}},
	{0,								0x1008ff12, spawn,		   {.v = volmucmd}},
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
	{ MODKEY|ShiftMask,				XK_r,	   restart,		   {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

