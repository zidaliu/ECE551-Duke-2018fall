#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4

char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

/*Declare my functions*/
void printIfo(const char * path,
              int i,
              int len);                   //printout the outputs of all kinds of Infomations
char * permissions(struct stat buff);     //get permission Infomations
void search(char * c, mode_t st, int i);  //search and match permission Infomations
void printfTime(const char * string, struct stat buff);  //get time information
char * getFiletype(mode_t st);                           //get files information

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "No right input Format\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {  //search all the input files
    printIfo(argv[i], i, argc);     //print each files conprehensive infomations
  }
  return 0;
}

void printfTime(const char * string, struct stat buff) {
  char * time;

  switch (string[0]) {
    case 'A':  //means "Access"
      time = time2str(&buff.st_atime, buff.st_atim.tv_nsec);
      break;
    case 'M':  //means "Modify"
      time = time2str(&buff.st_mtime, buff.st_mtim.tv_nsec);
      break;
    case 'C':  //means "Change"
      time = time2str(&buff.st_ctime, buff.st_ctim.tv_nsec);
      break;
  }

  printf("%s: %s\n", string, time);
  free(time);
}

void search(char * c, mode_t st, int i) {
  switch (i) {
    case 1:
      if ((st & S_IRUSR) != 0) {
        *c = 'r';
      }
      else {
        *c = '-';
      }
      break;
    case 2:
      if ((st & S_IWUSR) != 0) {
        *c = 'w';
      }
      else {
        *c = '-';
      }
      break;
    case 3:
      if ((st & S_IXUSR) != 0) {
        *c = 'x';
      }
      else {
        *c = '-';
      }
      break;
    case 4:
      if ((st & S_IRUSR) != 0) {
        *c = 'r';
      }
      else {
        *c = '-';
      }
      break;
    case 5:
      if ((st & S_IWGRP) != 0) {
        *c = 'w';
      }
      else {
        *c = '-';
      }
      break;
    case 6:
      if ((st & S_IXGRP) != 0) {
        *c = 'x';
      }
      else {
        *c = '-';
      }
      break;
    case 7:
      if ((st & S_IROTH) != 0) {
        *c = 'r';
      }
      else {
        *c = '-';
      }
      break;
    case 8:
      if ((st & S_IWOTH) != 0) {
        *c = 'w';
      }
      else {
        *c = '-';
      }
      break;
    case 9:
      if ((st & S_IXOTH) != 0) {
        *c = 'x';
      }
      else {
        *c = '-';
      }
      break;
  }
}

char * permissions(struct stat buff) {
  char * string = NULL;
  char c = {0};
  string = malloc(11 * sizeof(*string));
  switch (buff.st_mode & S_IFMT) {
    case S_IFBLK:
      c = 'b';
      break;
    case S_IFCHR:
      c = 'c';
      break;
    case S_IFDIR:
      c = 'd';
      break;
    case S_IFIFO:
      c = 'p';
      break;
    case S_IFLNK:
      c = 'l';
      break;
    case S_IFREG:
      c = '-';
      break;
    case S_IFSOCK:
      c = 's';
      break;
  }
  string[0] = c;
  /*print string[1]-string[9]*/
  for (int i = 1; i < 10; i++) {
    search(&string[i], buff.st_mode, i);
  }
  string[10] = '\0';
  return string;
}

char * getFiletype(mode_t st) {
  char * filetype;
  switch (st & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "fifo";
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
      break;
  }
  return filetype;
}

void printIfo(const char * path, int i, int len) {
  struct stat buff;
  const char * filetype = NULL;
  char * permission = NULL;
  struct passwd * ownerName;
  struct group * groupName;
  if (lstat(path, &buff) < 0) {
    fprintf(stderr, "stat: cannot stat '%s': No such file or directory\n", path);
    if (i == len - 1) {  //if the illegle input is at the end of the input list, then exit_failure
      exit(EXIT_FAILURE);
    }
    else {
      return;  //if the illegal input is at middle then judge the next file without breakdown
    }
  }

  /*file name output*/
  if (S_ISLNK(buff.st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(path, linktarget, 256);
    if (len > 255) {
      linktarget[255] = '\0';
    }
    else {
      linktarget[len] = '\0';
    }
    printf("  File: %s->> %s\n", path, linktarget);
  }
  else {
    printf("  File: %s\n", path);
  }

  /* getfiletype*/
  filetype = getFiletype(buff.st_mode);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         buff.st_size,
         buff.st_blocks,
         buff.st_blksize,
         filetype);

  /* whether device*/
  if (S_ISCHR(buff.st_mode) || S_ISBLK(buff.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           buff.st_dev,
           buff.st_dev,
           buff.st_ino,
           buff.st_nlink,
           major(buff.st_rdev),
           minor(buff.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           buff.st_dev,
           buff.st_dev,
           buff.st_ino,
           buff.st_nlink);
  }

  /*permission Info*/
  permission = permissions(buff);
  ownerName = getpwuid(buff.st_uid);
  groupName = getgrgid(buff.st_gid);
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         buff.st_mode & ~S_IFMT,
         permission,
         buff.st_uid,
         ownerName->pw_name,
         buff.st_gid,
         groupName->gr_name);

  /*time Info*/
  printfTime("Access", buff);
  printfTime("Modify", buff);
  printfTime("Change", buff);
  printf(" Birth: -\n");
  free(permission);
}
