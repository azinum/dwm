/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx = 3;        /* border pixel of windows */
static unsigned int gappx    = 2;        /* gaps between windows */
static unsigned int snap     = 32;       /* snap pixel */
static int showbar           = 1;        /* 0 means no bar */
static int topbar            = 1;        /* 0 means bottom bar */
static const char* fonts[]   = { "inconsolata:size=11" };
static char dmenufont[]      = "inconsolata:size=11";
static char col_gray2[]      = "#444444";
static char col_gray4[]      = "#eeeeee";

static char selbgcolor[]     = "#086a7e";
static char selbordercolor[] = "#157aae"; // "#086A7E";

static char normbgcolor[] = "#222222";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#222222";
static char normbordercolor[] = "#222222";

static unsigned int baralpha = 0xd0;
static unsigned int borderalpha = OPAQUE;

static const char *colors[][3] = {
  /*               fg         bg         border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, col_gray2 },
  [SchemeSel]  = { col_gray4, selbgcolor,  selbordercolor },

  [SchemeStatus]   = { normfgcolor, normbgcolor,  "#000000" }, // Statusbar right {text, background, not used but cannot be empty}
  [SchemeTagsSel]  = { col_gray4, selbgcolor,  "#000000" }, // Tagbar left selected {text, background,not used but cannot be empty}
  [SchemeTagsNorm] = { normfgcolor, normbgcolor,  "#000000" }, // Tagbar left unselected {text, background, not used but cannot be empty}
  [SchemeInfoSel]  = { col_gray4, selbgcolor,  "#000000" }, // infobar middle  selected {text, background, not used but cannot be empty}
  [SchemeInfoNorm] = { normfgcolor, normbgcolor,  "#000000" }, // infobar middle  unselected {text, background, not used but cannot be empty}
};

static const unsigned int alphas[][3] = {
  /*               fg      bg        border     */
  [SchemeNorm] = { OPAQUE, 0xd0, OPAQUE },
  [SchemeSel]  = { OPAQUE, 0xd0, OPAQUE },

  [SchemeStatus]   = { OPAQUE, OPAQUE, OPAQUE },
  [SchemeTagsSel]  = { OPAQUE, OPAQUE, OPAQUE },
  [SchemeTagsNorm] = { OPAQUE, OPAQUE, OPAQUE },
  [SchemeInfoSel]  = { OPAQUE, OPAQUE, OPAQUE },
  [SchemeInfoNorm] = { OPAQUE, OPAQUE, OPAQUE },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",         NULL,        NULL,           0,            1,           -1 },
};

/* layout(s) */
static float mfact     = 0.55f; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  // { "[M]",      monocle },
};

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char* termcmd[]  = { "st", NULL };
static const char* browser_cmd[] = { "firefox", NULL };
static const char* bookmarks_cmd[] = { "bookmarks", NULL };

ResourcePref resources[] = {
//   { "font",               STRING,  &fonts[0] },
  { "dmenufont",          STRING,  &dmenufont },
  { "normbgcolor",        STRING,  &normbgcolor },
  { "normbordercolor",    STRING,  &normbordercolor },
  { "normfgcolor",        STRING,  &normfgcolor },
  { "selbgcolor",         STRING,  &selbgcolor },
  { "selbordercolor",     STRING,  &selbordercolor },
  { "selfgcolor",         STRING,  &selfgcolor },
  { "borderpx",           INTEGER, &borderpx },
  { "snap",               INTEGER, &snap },
  { "showbar",            INTEGER, &showbar },
  { "topbar",             INTEGER, &topbar },
  { "nmaster",            INTEGER, &nmaster },
  { "resizehints",        INTEGER, &resizehints },
  { "mfact",              FLOAT,   &mfact },
  { "gaps",               INTEGER,   &gappx },
};

static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_p,      spawn,          { .v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          { .v = termcmd } },
  { MODKEY,                       XK_w,      spawn,          { .v = browser_cmd } },
  { MODKEY,                       XK_o,      spawn,          { .v = bookmarks_cmd } },
  { MODKEY,                       XK_b,      togglebar,      { 0 } },
  { MODKEY,                       XK_j,      focusstack,     { .i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     { .i = -1 } },
#if 0
  { MODKEY,                       XK_i,      incnmaster,     { .i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     { .i = -1 } },
#endif
  { MODKEY,                       XK_h,      setmfact,       { .f = -0.05 } },
  { MODKEY,                       XK_l,      setmfact,       { .f = +0.05 } },
  { MODKEY,                       XK_Return, zoom,           { 0 } },
  { MODKEY,                       XK_Tab,    view,           { 0 } },
  { MODKEY|ShiftMask,             XK_c,      killclient,     { 0 } },
  { MODKEY,                       XK_t,      setlayout,      { .v = &layouts[0] } },
  { MODKEY,                       XK_f,      setlayout,      { .v = &layouts[1] } },
  { MODKEY,                       XK_m,      setlayout,      { 0 } },
  { MODKEY,                       XK_space,  setlayout,      { 0 } },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, { 0 } },
  { MODKEY|ShiftMask,             XK_f,      togglefullscr,  { 0 } },
  { MODKEY,                       XK_0,      view,           { .ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            { .ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       { .i = -1 } },
  { MODKEY,                       XK_period, focusmon,       { .i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         { .i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         { .i = +1 } },
  { MODKEY,                       XK_minus,  setgaps,        { .i = -1 } },
  { MODKEY,                       XK_equal,  setgaps,        { .i = +1 } },
  { MODKEY|ShiftMask,             XK_equal,  setgaps,        { .i = 0  } },
  { MODKEY,                       XK_F5,     xrdb,           { .v = NULL } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
  { MODKEY|ShiftMask,             XK_q,      quit,           { 0 } },
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
