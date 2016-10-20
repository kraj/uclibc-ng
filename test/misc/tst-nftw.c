#define _XOPEN_SOURCE 500 
#define _GNU_SOURCE
#include <ftw.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int result = 0;

static int process_one_entry(const char *fpath, const struct stat *sb,
                             int typeflag, struct FTW *ftwbuf)
{
    
    struct stat buf;
    const char *rel_path = fpath+ftwbuf->base;

    printf("Processing %s in working dir %s\n",
	   rel_path, get_current_dir_name());
    if (stat(rel_path, &buf) < 0) {
	perror("Oops...relative path does not exist in current directory");
	result = 1;
    }
}

static int
do_test(void)
{
    char *path = "/tmp/stest_dir";
    char *subpath = "/tmp/stest_dir/d1";
    char *filepath = "/tmp/stest_dir/f1";
    char *filesubpath = "/tmp/stest_dir/d1/f2";
    
    if ((mkdir(path, 0700)) < 0)
	perror("Creating path");
    if ((mkdir(subpath, 0700)) < 0)
	perror("Creating subpath");
    if ((open(filepath, O_CREAT)) < 0)
	perror("Opening filepath");
    if ((open(filesubpath, O_CREAT)) < 0)
	perror("Opening filesubpath");

    if (nftw(path, process_one_entry, 100, (FTW_CHDIR|FTW_DEPTH|FTW_PHYS)) < 0)
        perror("ntfw");

    unlink(filesubpath);
    unlink(filepath);
    rmdir(subpath);
    rmdir(path);

    return result;
}

#define TIMEOUT 5
#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"
