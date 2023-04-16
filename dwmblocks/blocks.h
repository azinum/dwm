// blocks.h
// NOTE: Add +34 to the signal when updating the statusbar commands

// Sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;

#define HAS_BATTERY 0

// Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
  /* Icon */	/* Command */		/* Update Interval */	/* Update Signal */
  {"\n", "", 60, 0},

  {"", "keylayout", 60, 2},

  {"💾 ", "free -m | awk '/^Mem/ { print $3\"/\"$2\" mb\" }' | sed s/i//g", 1, 0},

  {"", "sed 's/down/🌎❌/;s/up/🌎/' /sys/class/net/e*/operstate 2>/dev/null", 10, 0},

#if HAS_BATTERY
  {"", "printf \"🔋 %s%%\" \"$(cat /sys/class/power_supply/BAT0/capacity)\" 2>/dev/null", 30, 0},
#endif

  {"", "stat-volume", 30, 1},

  {"📅 ", "date '+%a %d %b %Y %H:%M:%S'", 1, 0},
};
