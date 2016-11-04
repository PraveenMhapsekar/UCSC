/**********************************************************
 UCSC Linux System Programming
 Chapter 4 (Thread)
 Assignment #1 (simple find program)
 Author: Hisakazu Ishiguro
 ----------------------------------------------------------
 Description:

   Write a simple program that is a simple version of the
 ‘find’ utility. This program demonstrate pthread and mutual
  exclusive operation using mutex.

 **********************************************************/

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <fnmatch.h>

#define FNAME_LEN 256
#define PATSZ 25

typedef struct dirlst_t {
  char fname[FNAME_LEN];
  int isdir;
  struct dirlst_t *next;
} dirlst_t;

typedef struct find_t {
  char home[FNAME_LEN]; // absolute path of home directory
  char cwd[FNAME_LEN];  // current working dir name
  int nfiles;           // length of linked list
  int ndirs;            // # of links for dir based nodes.
  pthread_t id;         // thread id
  dirlst_t *lst;        // head of linked list
} find_t;

typedef struct cmdArg_t {
  char *cmdname;
  char startdir[FNAME_LEN];
  char searchpat[128];
  int dbg_lvl;
} cmdArg_t;

static cmdArg_t cmdopt;

pthread_mutex_t printmutex = PTHREAD_MUTEX_INITIALIZER;

int _dbg;

typedef enum DBG_LVL {
  DBG_NONE = 0,
  DBG_STATE,
  DBG_DETAIL,
  DBG_DEBUG
} DBG_LVL;

char* strcat_fname(char *cwd, char *fname, int maxlen)
{
  if (cwd == NULL || fname == NULL ||
      ((strlen(cwd) + strlen(fname)) >= maxlen)) {
    printf("append_dir: invalid operation.\n");
    return NULL;
  }

  if (strlen(cwd) > 0)
    strcat(cwd, "/");

  return (strcat(cwd, fname));
}

char *strrm_fname(char *cwd)
{
  int len, i;

  if (cwd == NULL)
    return NULL;

  if ((len = strlen(cwd)) <= 0)
    return cwd;

  for (i = len; i >= 0; i--) {
    if (cwd[i] == '/') {
      cwd[i] = '\0';
      break;
    }
  }

  if (i < 0)
    cwd[0] = '\0';

  return (cwd);
}

dirlst_t *create_lst(char *fname, int isdir)
{
  dirlst_t *lst;

  if ((lst = (dirlst_t *)malloc(sizeof (dirlst_t))) == NULL) {
    printf("create_lst: ERR, malloc failed.\n");
    return NULL;
  }

  if (fname != NULL)
    strcpy(lst->fname, fname);

  lst->isdir = (isdir ? 1 : 0);
  lst->next = NULL;
  return lst;
}

int add_lst(dirlst_t *list, char *fname, int isdir)
{
  int n;
  dirlst_t *lst;

  if (list == NULL || fname == NULL) {
    printf("add_lst: ERR: Invalid param detected.\n");
    return -1;
  }

  for (lst = list, n = 0;
       lst->next != NULL;
       lst = lst->next, n++);

  if ((lst->next = (dirlst_t *)malloc(sizeof (dirlst_t))) == NULL) {
    printf("add_lst: ERR: malloc failed.\n");
    return -1;
  }

  if ((strcpy(lst->next->fname, fname)) == NULL) {
    printf("add_lst: ERR: strcpy failed.\n");
    return -1;
  }

  lst->next->isdir = (isdir ? 1 : 0);
  lst->next->next = NULL;
  n++;

  return n;
}

void fdt_init(find_t *fdt, char *abs_home, char *dir)
{
  fdt->nfiles = 0;
  fdt->ndirs = 0;
  fdt->lst = NULL;
  strcpy(fdt->home, abs_home);
  strcat(fdt->home, "/");
  strcpy(fdt->cwd, dir);
  fdt->id = 0;
}

int fdt_addFlist(find_t *fdt, char *fname, int isdir)
{
  if (fdt == NULL || fname == NULL) {
    printf("fdt_addFlist: bad parameter detected.\n");
    return -1;
  }

  if (fdt->lst == NULL) {
    if ((fdt->lst = create_lst(fname, isdir)) == NULL)
      return -2;
  }
  else if ((add_lst(fdt->lst, fname, isdir)) < 0)
    return -3;

  (fdt->nfiles)++;
  if (isdir) (fdt->ndirs)++;
  return 0;
}

char *fdt_fndNextDir(find_t *fdt, int nskip)
{
  int nfnd = 0;
  dirlst_t *lst;

  if (fdt == NULL || nskip < 0) {
    printf("fdt_fndNextDir: bad parameter detected.\n");
    return NULL;
  }

  lst = fdt->lst;

  while (lst) {
    if (lst->isdir)
      if (nfnd++ == nskip)
	return (&(lst->fname[0]));
    lst = lst->next;
  }
  return NULL;
}

void fdt_printLst(find_t *fdt)
{
  int n = 0;
  dirlst_t *lst = fdt->lst;

  if (lst == NULL || fdt->nfiles == 0)
    return;

  while (lst) {
    n++;
    printf("./%s\n",
	   ((lst->fname != NULL) ? lst->fname : "???"));
    lst = lst->next;
  }

  if (_dbg) {
    if (n != fdt->nfiles) {
      printf("\nfile counts(=%d) and list idx(=%d) is not matched.\n",
	     fdt->nfiles, n);
      return;
    }
    printf("Found %d files in \"%s\" dir.\n",
	   fdt->nfiles, fdt->cwd);
  }
}

void fdt_printFileLst(find_t *fdt)
{
  int n = 0;
  int nfile_nodes;
  dirlst_t *lst = fdt->lst;

  if (lst == NULL || fdt->nfiles == 0)
    return;

  while (lst) {
    if (!(lst->isdir)) {
      n++;
      printf("./%s\n",
	     ((lst->fname != NULL) ? lst->fname : "???"));
    }
    lst = lst->next;
  }

  if (_dbg) {
    nfile_nodes = fdt->nfiles - fdt->ndirs;

    if (n != nfile_nodes) {
      printf("\nfile counts(=%d) and num of file lists(=%d) "
	     "are not equal.\n",
	     nfile_nodes, n);
      return;
    }
    printf("Found %d files in \"%s\" dir.\n",
	   nfile_nodes, fdt->cwd);
  }
}

void fdt_rmLst(find_t *fdt)
{
  dirlst_t *lst, *tmp;

  if ((lst = fdt->lst) == NULL)
    return;

  while (lst) {
    tmp = lst->next;
    free(lst);
    fdt->nfiles--;
    if (lst->isdir) fdt->ndirs--;
    lst = tmp;
  }

  fdt->lst = NULL;

  if (_dbg && fdt->nfiles != 0) {
    printf("fdt_rmLst: Invalid file counts detected %d.\n",
	   fdt->nfiles);
  }
}

int rcrsvScan_dir(find_t *fdt, char *dir)
{
  DIR *dp;
  char abs_fname[FNAME_LEN];
  char abs_dir[FNAME_LEN];
  struct dirent *ent;
  struct stat stbuf;
  char fn[1024];

  strcpy(abs_dir, fdt->home);
  strcat(abs_dir, fdt->cwd);

  if (_dbg >= DBG_DEBUG) {
    printf("# <rcrsvScan_dir>------------------"
	   "--------------------------\n"
	   "# threadId=%lu\n"
	   "# home=%s\n# cwd=%s\n# abs_dir=%s\n"
	   "# ---------------------------------"
	   "--------------------------\n",
	   fdt->id, fdt->home, fdt->cwd, abs_dir);
  }

  if ((dp = opendir(abs_dir)) == NULL) {
    printf("rcrsvScan_dir: opendir() failed "
	   "(id=%lu, cwd=%s\n",
	   fdt->id, abs_dir);
    return -1;
  }

  while ((ent = readdir(dp)) != NULL) {
    snprintf(fn, 1024, "%s/%s", abs_dir, ent->d_name);

    if ((stat(fn, &stbuf)) != 0) {
      fprintf(stderr,
	      "stat() is failed with ent->d_name=%s\n",
	      ent->d_name);
      closedir(dp);
      return -1;
    }

    if (!strcmp(ent->d_name, ".") ||
	!strcmp(ent->d_name, ".."))
      continue;

    /* abs_fname:
     * file name includes relative path from the home
     * directory. This string format is used to print out
     * on stdout as the result of find command.
     */
    strcpy(abs_fname, fdt->cwd);
    if ((strlen(abs_fname)) > 0) strcat(abs_fname, "/");
    strcat(abs_fname, ent->d_name);

    if (!(S_ISDIR(stbuf.st_mode))) {
      if (fnmatch(cmdopt.searchpat, ent->d_name, 0) == 0)
	fdt_addFlist(fdt, abs_fname, 0);
    }
    else {
      if (!strcmp(cmdopt.searchpat, "*"))
	fdt_addFlist(fdt, abs_fname, 1);
      strcat(abs_fname, "/");
      strcat(fdt->cwd, "/");
      strcat(fdt->cwd, ent->d_name);
      rcrsvScan_dir(fdt, ent->d_name);

      if ((strrm_fname(fdt->cwd)) == NULL) {
	closedir(dp);
	return -1;
      }
    }
  }

  closedir(dp);
  return 0;

} // rcrsvScan_dir()

void thread_fnc(void *data)
{
  find_t *fdt = (find_t *)data;

  if (_dbg >= DBG_STATE)
    printf("Start thread (id=%lu, subdir=%s) ...\n",
	   (unsigned long)fdt->id, fdt->cwd);

  rcrsvScan_dir(fdt, fdt->cwd);
  pthread_mutex_lock(&printmutex);
  fdt_printLst(fdt);
  pthread_mutex_unlock(&printmutex);
}

void printCmdOpt(cmdArg_t *opt)
{
  printf("cmdName:    %s\n"
	 "startDir:   %s\n"
	 "searchPat: \"%s\"\n"
	 "debugLvl:   %d\n\n",
	 opt->cmdname,
	 opt->startdir,
	 opt->searchpat,
	 opt->dbg_lvl);
}

int parseCmdOpt(int argc, char *argv[], cmdArg_t *opt)
{
  int i;

  opt->cmdname = argv[0];

  if ((getcwd(opt->startdir, FNAME_LEN)) == NULL) {
    fprintf(stderr, "getcwd() failed.\n");
    return -1;
  }

  strcpy(opt->searchpat, "*");
  opt->dbg_lvl = 0;

  for (i = 1; i < argc; i++) {

    if (!strcmp(argv[i], "-name")) {
      if (argc > i)
	strcpy(opt->searchpat, argv[++i]);
      else {
	fprintf(stderr,
		"parseCmdOpt: invalid val of -name "
		"option detected\n");
	return -1;
      }
      continue;
    }

    if (!strcmp(argv[i], "-dbg")) {
      if (argc > i)
	opt->dbg_lvl = atoi(argv[++i]);
      else opt->dbg_lvl = 1;
      continue;
    }

    if (argv[i][0] == '-') {
      fprintf(stderr,
	      "parseCmdOpt: invalid arg %s detected.\n",
	      argv[i]);
      return -1;
    }

    if (i == 1) {
      strcpy(opt->startdir, argv[i]);
      continue;
    }

    fprintf(stderr,
	    "parseCmdOpt: start directory name has to be "
	    "a first argument of the command.\n");
    return -1;
  }

  return 0;

} // parseCmdOpt()

int main(int argc, char *argv[])
{
  DIR *dp;
  struct dirent *ent;
  struct stat stbuf;
  find_t top, *fdts = NULL;
  pthread_t *threads;
  char home[FNAME_LEN];
  int subdirs, nfiles, i, status;
  char fn[1024];

  if ((parseCmdOpt(argc, argv, &cmdopt)) != 0)
    return -1;

  _dbg = cmdopt.dbg_lvl;
  strcpy(home, cmdopt.startdir);

  if (_dbg >= DBG_STATE)
    printf("\nStart %s program (cwd:%s) ...\n",
	   argv[0], home);

  if (_dbg >= DBG_DEBUG)
    printCmdOpt(&cmdopt);

  fdt_init(&top, home, "");

  /*
   * Count number of sub directory
   */
  if ((dp = opendir(home)) == NULL) {
    fprintf(stderr, "Cannot open dir: %s\n", home);
    return -1;
  }

  subdirs = 0;
  status = 0;

  while ((ent = readdir(dp)) != NULL) {
    snprintf(fn, 1024, "%s/%s", home, ent->d_name);

    if ((stat(fn, &stbuf)) != 0) {
      fprintf(stderr,
	      "stat() is failed with ent->d_name=%s\n",
	      ent->d_name);
      closedir(dp);
      goto err_exit;
    }

    if (!strcmp(ent->d_name, ".") ||
	!strcmp(ent->d_name, ".."))
      continue;

    if (!(S_ISDIR(stbuf.st_mode))) {
      if ((fnmatch(cmdopt.searchpat, ent->d_name, 0)) == 0) {
	if ((fdt_addFlist(&top, ent->d_name, 0)) < 0) {
	  status = -1;
	  closedir(dp);
	  goto err_exit;
	}
      }
    }
    else {
      subdirs++;
      if ((fdt_addFlist(&top, ent->d_name, 1)) < 0) {
	status = -1;
	closedir(dp);
	goto err_exit;
      }
    }
  }

  closedir(dp);

  /*
   * Print list of files in the top directory.
   */
  if (!strcmp(cmdopt.searchpat, "*"))
    fdt_printLst(&top);
  else fdt_printFileLst(&top);

  /*
   * Prepare thread parameters before launching thread
   * for each sub directories.
   */
  if ((threads =
       (pthread_t *)malloc(sizeof (pthread_t) * subdirs)) == NULL) {
    fprintf(stderr, "malloc failed(1).\n");
    status = -1;
    goto err_exit;
  }

  if ((fdts = (find_t *)malloc(sizeof (find_t) * subdirs)) == NULL) {
    fprintf(stderr, "malloc failed(2).\n");
    status = -1;
    goto err_exit;
  }

  /*
   * Start threads to recursively scaning to each sub
   * directories.
   */
  for (i = 0; i < subdirs; i++) {
    fdt_init(&(fdts[i]), home, fdt_fndNextDir(&top, i));
    fdts[i].id = threads[i];
    pthread_create(&(threads[i]), NULL,
		   (void *)&thread_fnc, &(fdts[i]));
  }

  /*
   * Wait until all threads are done.
   */
  for (i = 0; i < subdirs; i++) {
    if (_dbg >= DBG_STATE)
      printf("Terminating thread (id=%lu, subdr=%s) ...\n",
	     (unsigned long)fdts[i].id, fdts[i].cwd);
    pthread_join(threads[i], NULL);
  }

  if (!strcmp(cmdopt.searchpat, "*"))
    nfiles = top.nfiles;
  else nfiles = top.nfiles - top.ndirs;

  /*
   * Calicualte total number of found files.
   */
  for (i = 0; i < subdirs; i++)
    nfiles += fdts[i].nfiles;

  if (_dbg >= DBG_STATE)
    printf("\nFound %d files.\n", nfiles);

  /*
   * Release allocated memory.
   */
  for (i = 0; i < subdirs; i++)
    fdt_rmLst(&(fdts[i]));

 err_exit:
  fdt_rmLst(&top);

  if (threads)
    free(threads);

  if (fdts)
    free(fdts);

  return status;
}
