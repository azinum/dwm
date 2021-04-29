// blocks.h
// NOTE: Add +34 to the signal when updating the statusbar commands

// Sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;

// Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/* Icon */	/* Command */		/* Update Interval */	/* Update Signal */
  {"\n", "", 60, 0},

  {"", "keylayout", 60, 2},

	{"mem: ", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},

  {"", "sed 's/down/🌎❌/;s/up/🌎/' /sys/class/net/e*/operstate 2>/dev/null", 20, 0},

  {"", "stat-volume", 30, 1},

	{"", "date '+%a %d %b %Y %H:%M:%S'",					1,		0},
};
