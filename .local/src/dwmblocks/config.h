static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"⌨", "sb-kbselect", 0, 30}, */
	{"", "cat /tmp/recordingicon 2>/dev/null",	0,	9},
	{"",	"sb-music",	0,	11},
	{"",	"sb-pacpackages",	0,	8},
	/* {"",	"sb-price lbc \"LBRY Token\" 📚",			9000,	22}, */
	/* {"",	"sb-price bat \"Basic Attention Token\" 🦁",	9000,	20}, */
	/* {"",	"sb-price link \"Chainlink\" 🔗",			300,	25}, */
	/* {"",	"sb-price xmr \"Monero\" 🔒",			9000,	24}, */
	/* {"",	"sb-price eth Ethereum 🍸",	9000,	23}, */
	/* {"",	"sb-price btc Bitcoin 💰",				9000,	21}, */
	{"",	"sb-warp",		0,	7},
	{"",	"sb-cpu",		10,	18},
	/* {"",	"sb-mailbox",	60,	12}, */
	{"",	"sb-memory",	10,	14},
	{"",	"sb-nettraf",	1,	16},
	{"",	"sb-volume",	0,	10},
	{"",	"sb-clock",		1,	1},
	{"",	"sb-battery",	5,	3},
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "  |  ";

