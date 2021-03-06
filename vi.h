/* neatvi main header */

/* helper macros */
#define LEN(a)		(sizeof(a) / sizeof((a)[0]))
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) < (b) ? (b) : (a))
#define p(s, ...)\
	FILE *f = fopen("file", "a");\
	fprintf(f, s, ##__VA_ARGS__);\
	fclose(f);\

int isescape(char ch);
char *substr(const char *s1, const char *s2);
int dstrlen(const char *s, char delim);
void reverse_in_place(char *str, int len);

/* hund file manager */
int hund();
void vi();

/* line buffer, managing a number of lines */
struct lbuf *lbuf_make(void);
void lbuf_free(struct lbuf *lbuf);
int lbuf_rd(struct lbuf *lbuf, int fd, int beg, int end);
int lbuf_wr(struct lbuf *lbuf, int fd, int beg, int end);
void lbuf_edit(struct lbuf *lbuf, char *s, int beg, int end);
char *lbuf_cp(struct lbuf *lbuf, int beg, int end);
char *lbuf_get(struct lbuf *lbuf, int pos);
char **lbuf_buf(struct lbuf *lb);
int lbuf_len(struct lbuf *lbuf);
void lbuf_mark(struct lbuf *lbuf, int mark, int pos, int off);
int lbuf_jump(struct lbuf *lbuf, int mark, int *pos, int *off);
int lbuf_undo(struct lbuf *lbuf);
int lbuf_redo(struct lbuf *lbuf);
int lbuf_modified(struct lbuf *lb);
void lbuf_saved(struct lbuf *lb, int clear);
int lbuf_indents(struct lbuf *lb, int r);
int lbuf_eol(struct lbuf *lb, int r);
void lbuf_globset(struct lbuf *lb, int pos, int dep);
int lbuf_globget(struct lbuf *lb, int pos, int dep);
/* motions */
int lbuf_findchar(struct lbuf *lb, char *cs, int cmd, int n, int *r, int *o);
int lbuf_search(struct lbuf *lb, char *kw, int dir, int *r, int *o, int *len);
int lbuf_paragraphbeg(struct lbuf *lb, int dir, int *row, int *off);
int lbuf_sectionbeg(struct lbuf *lb, int dir, int *row, int *off);
int lbuf_wordbeg(struct lbuf *lb, int big, int dir, int *row, int *off);
int lbuf_wordend(struct lbuf *lb, int big, int dir, int *row, int *off);
int lbuf_pair(struct lbuf *lb, int *row, int *off);

/* string buffer, variable-sized string */
struct sbuf *sbuf_make(void);
void sbuf_free(struct sbuf *sb);
char *sbuf_done(struct sbuf *sb);
char *sbuf_buf(struct sbuf *sb);
void sbuf_chr(struct sbuf *sb, int c);
void sbuf_str(struct sbuf *sb, char *s);
char *sbuf_s(struct sbuf *sb);
void sbuf_mem(struct sbuf *sb, char *s, int len);
void sbuf_printf(struct sbuf *sbuf, char *s, ...);
int sbuf_len(struct sbuf *sb);
void sbuf_cut(struct sbuf *s, int len);

/* regular expression sets */
#define RE_ICASE		1
#define RE_NOTBOL		2
#define RE_NOTEOL		4

struct rset *rset_make(int n, char **pat, int flg);
int rset_find(struct rset *re, char *s, int n, int *grps, int flg);
void rset_free(struct rset *re);
char *re_read(char **src);

/* rendering lines */
void ren_done();
int *ren_position(char *s, char ***c, int *n);
int ren_next(char *s, int p, int dir);
int ren_eol(char *s, int dir);
int ren_pos(char *s, int off);
int ren_cursor(char *s, int pos);
int ren_noeol(char *s, int p);
int ren_off(char *s, int pos);
int ren_region(char *s, int c1, int c2, int *l1, int *l2, int closed);
char *ren_translate(char *s, char *ln);
int ren_cwid(char *s, int pos);

/* text direction */
int dir_context(char *s);
void dir_reorder(char *s, int *ord, char **chrs, int n);
void dir_init(void);
void dir_done(void);

/* string registers */
char *reg_get(int c, int *lnmode);
void reg_put(int c, char *s, int lnmode);
void reg_done(void);

/* utf-8 helper functions */
int uc_len(char *s);
int uc_wid(char *s);
int uc_slen(char *s);
int uc_code(char *s);
char *uc_chr(char *s, int off);
int uc_off(char *s, int off);
char *uc_sub(char *s, int beg, int end);
char *uc_dup(char *s);
int uc_isspace(char *s);
int uc_isprint(char *s);
int uc_isdigit(char *s);
int uc_isalpha(char *s);
int uc_kind(char *c);
int uc_isbell(char *c);
int uc_iscomb(char *c);
char **uc_chop(char *s, int *n);
char *uc_next(char *s);
char *uc_prev(char *beg, char *s);
char *uc_beg(char *beg, char *s);
char *uc_end(char *s);
char *uc_shape(char *beg, char *s);
char *uc_lastline(char *s);

/* managing the terminal */
#define xrows		(term_rows())
#define xcols		(term_cols())

#define CSI_CLEAR_ALL "\x1b[2J", 4
#define CSI_CLEAR_LINE "\x1b[K", 3
#define CSI_CURSOR_TOP_LEFT "\x1b[H", 3
#define CSI_CURSOR_SHOW "\x1b[?25h", 6
#define CSI_CURSOR_HIDE "\x1b[?25l", 6
#define CSI_SCREEN_ALTERNATIVE "\x1b[?47h", 6
#define CSI_SCREEN_NORMAL "\x1b[?47l", 6
#define CSI_CURSOR_HIDE_TOP_LEFT "\x1b[?25l\x1b[H", 9

void term_init(void);
void term_done(void);
void term_clean(void);
void term_suspend(void);
void term_str(char *s);
void term_chr(int ch);
void term_pos(int r, int c);
void term_clear(void);
void term_kill(void);
void term_room(int n);
int term_rows(void);
int term_cols(void);
int term_read(void);
void term_record(void);
void term_commit(void);
char *term_att(int att, int old);
void term_push(char *s, int n);
char *term_cmd(int *n);

#define TK_CTL(x)	((x) & 037)
#define TK_INT(c)	((c) < 0 || (c) == TK_ESC || (c) == TK_CTL('c'))
#define TK_ESC		(TK_CTL('['))

/* line-oriented input and output */
char *led_prompt(char *pref, char *post, char *insert, int *kmap, char *syn);
char *led_input(char *pref, char *post, int *kmap, char *syn);
void led_print(char *msg, int row, char *syn);
void led_printmsg(char *s, int row, char *syn);
char *led_read(int *kmap);
char *led_readchar(int c, int kmap);
int led_pos(char *s, int pos);
void led_done();

/* ex commands */
void hist_set(int i);
void hist_open();
void hist_switch();
void hist_write(char *str);
void hist_done();
char *hist_curstr();
void hist_pos(int row, int off, int top);
void ex(void);
void ex_command(char *cmd);
char *ex_read(char *msg);
void ex_print(char *line);
void ex_show(char *msg);
int ex_init(char **files);
void ex_done(void);
char *ex_path(void);
char *ex_filetype(void);
struct lbuf *ex_lbuf(void);
int ex_kwd(char **kwd, int *dir);
void ex_kwdset(char *kwd, int dir);
int ex_edit(char *path);
void ec_bufferi(int *id);
char* xgetenv(char* q[]);

#define EXLEN	512		/* ex line length */
#define xb 	ex_lbuf()

/* process management */
char *cmd_pipe(char *cmd, char *s, int iproc, int oproc);
int cmd_exec(char *cmd);
char* xgetenv(char* q[]); 

/* syntax highlighting */
#define SYN_BD		0x010000
#define SYN_IT		0x020000
#define SYN_RV		0x040000
#define SYN_FGMK(f)	(0x100000 | (f))
#define SYN_BGMK(b)	(0x200000 | ((b) << 8))

#define SYN_FLG		0xff0000
#define SYN_FGSET(a)	((a) & 0x1000ff)
#define SYN_BGSET(a)	((a) & 0x20ff00)
#define SYN_FG(a)	((a) & 0xff)
#define SYN_BG(a)	(((a) >> 8) & 0xff)

extern struct rset *blockrs;
int *syn_highlight(char *ft, char *s, int n);
char *syn_filetype(char *path);
void syn_context(int att);
int syn_merge(int old, int new);
void syn_init(void);
void syn_done(void);

/* configuration variables */
int conf_dirmark(int idx, char **pat, int *ctx, int *dir, int *grp);
int conf_dircontext(int idx, char **pat, int *ctx);
int conf_placeholder(int idx, char **s, char **d, int *wid);
int conf_highlight(int idx, char **ft, int **att, 
			char **pat, int *end, int *patend);
int conf_filetype(int idx, char **ft, char **pat);
int conf_hlrev(void);
int conf_hlline(void);
int conf_mode(void);
char **conf_kmap(int id);
int conf_kmapfind(char *name);
char *conf_digraph(int c1, int c2);
void conf_changereg(int i, char *reg);

/* file system */
void dir_calc(char *cur_dir);

/* global variables */
extern int xrow;
extern int xoff;
extern int xtop;
extern int xleft;
extern int xvis;
extern int xled;
extern int xquit;
extern int xic;
extern int xai;
extern int xtd;
extern int xshape;
extern int xorder;
extern int xhl;
extern int xhll;
extern int xhww;
extern int xkmap;
extern int xkmap_alt;
extern int xtabspc;
extern int xqexit;
extern int intershell;
extern char* fslink;
extern char fsincl[128];
extern int fstlen;
extern int fspos;
extern int fscount;
extern int vi_lnnum;
extern int vi_hidch;
extern int vi_mod;
