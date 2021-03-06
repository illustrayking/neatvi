/* neatvi configuration file */

/* access mode of new files */
#define MKFILE_MODE		0600

/* map file names to file types */
static struct filetype {
	char *ft;		/* file type */
	char *pat;		/* file name pattern */
} filetypes[] = {
	{"c", "\\.(c|h|cpp|hpp|cc|cs)$"},		/* C */
	{"roff", "\\.(ms|tr|roff|tmac|txt|[1-9])$"},	/* troff */
	{"tex", "\\.tex$"},				/* tex */
	{"msg", "letter$|mbox$|mail$"},			/* email */
	{"mk", "Makefile$|makefile$|\\.mk$"},		/* makefile */
	{"sh", "\\.sh$"},				/* shell script */
	{"py", "\\.py$"},				/* python */
	{"nm", "\\.nm$"},				/* neatmail */
};

/*
colors 0-15 
0 = black | inverse
1 = red3
2 = green3
3 = yellow3
4 = blue2
5 = magenta3
6 = cyan3
7 = gray90
bright colors 
8 = gray50
9 = red
10 = green
11 = yellow
12 = blue
13 = magenta
14 = cyan
15 = white
*/

/* syntax highlighting patterns */
static struct highlight {
	char *ft;		/* the filetype of this pattern */
	int att[16];		/* attributes of the matched groups */
	char *pat;		/* regular expression */
	int end;		/* the group ending this pattern */
	int patend;		/* the ending regex for multi-line patterns */
} highlights[] = {
	{"/", {9}, NULL},
	{"c", {10}, "\\<(signed|unsigned|char|short|int|long|float|double|void|\
		|enum|union|typedef|static|extern|register|struct|f32|u32|s32|u8|\
		|u64|s64|f64|s8|u16|s16|b32|int32_t|uint32_t|bool|const|size_t|\
		|int16_t|uint16_t|uint64_t|int64_t|uint8_t|int8_t)\\>"},
	{"c", {12 | SYN_BD}, "\\<(true|false|asm|__asm|__asm__|memset|memcpy|malloc|\
				|free|realloc|NULL|stdin|stdout|errno)\\>"},
	{"c", {11}, "\\<(return|for|while|if|else|do|sizeof|goto|switch|case|\
			|default|break|continue)\\>"},
	{"c", {4 | SYN_IT}, "//.*$"},
	{"c", {4 | SYN_IT}, "/\\*([^*]|\\*+[^*/])*\\*+/"},
	{"c", {4 | SYN_IT}, "[^\\*/]*\\*/"},
	{"c", {4 | SYN_IT}, "/\\*([^*]|\\*)*", 0, 6},
	{"c", {6}, "^#[ \t]*[a-zA-Z0-9_]+"},
	{"c", {0, SYN_BD}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"c", {5}, "\"([^\"]|\\\\\")*\""},
	{"c", {5}, "'([^\\]|\\\\.)'"},
	{"c", {9}, "[-+]?\\<(0[xX][0-9a-fA-F]+|[0-9]+)\\>"},

	{"roff", {4, 0, 5 | SYN_BD, 4 | SYN_BD, 5 | SYN_BD, 4 | SYN_BD},
		"^[.'][ \t]*((SH.*)|(de) (.*)|([^ \t\\]{2,}))?.*$", 1},
	{"roff", {2 | SYN_IT}, "\\\\\".*$"},
	{"roff", {3}, "\\\\{1,2}[*$fgkmns]([^[(]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\\\([^[(*$fgkmns]|\\(..|\\[[^]]*\\])"},
	{"roff", {3}, "\\$[^$]+\\$"},

	{"tex", {4 | SYN_BD, 0, 3, 0, 5},
		"\\\\[^[{ \t]+(\\[([^]]+)\\])?(\\{([^}]*)\\})?"},
	{"tex", {3}, "\\$[^$]+\\$"},
	{"tex", {2 | SYN_IT}, "%.*$"},

	/* mail */
	{"msg", {6 | SYN_BD}, "^From .*20..$"},
	{"msg", {6 | SYN_BD, 4 | SYN_BD}, "^Subject: (.*)$"},
	{"msg", {6 | SYN_BD, 2 | SYN_BD}, "^From: (.*)$"},
	{"msg", {6 | SYN_BD, 5 | SYN_BD}, "^To: (.*)$"},
	{"msg", {6 | SYN_BD, 5 | SYN_BD}, "^Cc: (.*)$"},
	{"msg", {6 | SYN_BD}, "^[A-Z][-A-Za-z]+: .+$"},
	{"msg", {2 | SYN_IT}, "^> .*$"},

	/* makefile */
	{"mk", {0, 3}, "([A-Za-z_][A-Za-z0-9_]*)[ \t]*="},
	{"mk", {3}, "\\$\\([a-zA-Z0-9_]+\\)"},
	{"mk", {2 | SYN_IT}, "#.*$"},
	{"mk", {0, SYN_BD}, "([A-Za-z_%.]+):"},

	/* shell script */
	{"sh", {5 | SYN_BD}, "\\<(break|case|continue|do|done|elif|else|esac|fi|for|if|in|then|until|while)\\>"},
	{"sh", {2 | SYN_IT}, "#.*$"},
	{"sh", {4}, "\"([^\"\\]|\\\\.)*\""},
	{"sh", {4}, "'[^']*'"},
	{"sh", {4}, "`([^`\\]|\\\\.)*`"},
	{"sh", {1}, "\\$(\\{[^}]+\\}|[a-zA-Z_0-9]+)"},
	{"sh", {0, SYN_BD}, "^([a-zA-Z_][a-zA-Z_0-9]*\\(\\)).*\\{"},

	/* python */
	{"py", {2}, "^#.*$"},
	{"py", {5}, "\\<(and|break|class|continue|def|del|elif|else|except|finally|for|from|global)\\>"},
	{"py", {5}, "\\<(if|import|in|is|lambda|not|or|pass|print|raise|return|try|while)\\>"},
	{"py", {0, 0 | SYN_BD}, "([a-zA-Z][a-zA-Z0-9_]+)\\(", 1},
	{"py", {4}, "[\"']([^\"']|\\\\\")*[\"']"},

	/* neatmail */
	{"nm", {0 | SYN_BGMK(15), 6 | SYN_BD, 12 | SYN_BD, 5, 8 | SYN_BD},
		"^([ROU])([0-9]+)\t([^\t]*)\t([^\t]*)"},
	{"nm", {0 | SYN_BD | SYN_BGMK(6)}, "^[N].*$"},
	{"nm", {0 | SYN_BD | SYN_BGMK(13)}, "^[A-Z][HT].*$"},
	{"nm", {0 | SYN_BD | SYN_BGMK(11)}, "^[A-Z][MI].*$"},
	{"nm", {7 | SYN_BGMK(15)}, "^[A-Z][LJ].*$"},
	{"nm", {0 | SYN_BD | SYN_BGMK(7)}, "^[F].*$"},
	{"nm", {7 | SYN_IT}, "^\t.*$"},
	{"nm", {SYN_BD}, "^:.*$"},

	/* status bar */
	{"---", {8 | SYN_BD, 4, 1}, "^(\".*\").*(\\[[wr]\\]).*$"},
	{"---", {8 | SYN_BD, 4, 4}, "^(\".*\").*(L[0-9]+) +(C[0-9]+).*$"},
	{"---", {8 | SYN_BD}, "^.*$"},
};

/* how to hightlight current line (hll option) */
#define SYN_LINE		14 | SYN_BD

/* how to hightlight text in the reverse direction */
#define SYN_REVDIR		7

/* right-to-left characters (used only in dircontexts[] and dirmarks[]) */
#define CR2L		"ءآأؤإئابةتثجحخدذرزسشصضطظعغـفقكلمنهوىييپچژکگی‌‍؛،»«؟ًٌٍَُِّْ"
/* neutral characters (used only in dircontexts[] and dirmarks[]) */
#define CNEUT		"-!\"#$%&'()*+,./:;<=>?@^_`{|}~ "

/* direction context patterns; specifies the direction of a whole line */
static struct dircontext {
	int dir;
	char *pat;
} dircontexts[] = {
	{-1, "^[" CR2L "]"},
	{+1, "^[a-zA-Z_0-9]"},
};

/* direction marks; the direction of a few words in a line */
static struct dirmark {
	int ctx;	/* the direction context for this mark; 0 means any */
	int dir;	/* the direction of the matched text */
	int grp;	/* the nested subgroup; 0 means no groups */
	char *pat;
} dirmarks[] = {
	{+0, +1, 1, "\\\\\\*\\[([^]]+)\\]"},
	{+1, -1, 0, "[" CR2L "][" CNEUT CR2L "]*[" CR2L "]"},
	{-1, +1, 0, "[a-zA-Z0-9_][^" CR2L "\\\\`$']*[a-zA-Z0-9_]"},
	{+0, +1, 0, "\\$([^$]+)\\$"},
	{+0, +1, 1, "\\\\[a-zA-Z0-9_]+\\{([^}]+)\\}"},
	{-1, +1, 0, "\\\\[^ \t" CR2L "]+"},
};

/* character placeholders */
static struct placeholder {
	char *s;	/* the source character */
	char *d;	/* the placeholder */
	int wid;	/* the width of the placeholder */
} placeholders[] = {
	{"‌", "-", 1},
	{"‍", "-", 1},
};
