#include <dlfcn.h>
#include <stdio.h>
#include <archive.h>


int main(int argc, char **argv) {
  void *mylib = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);
  printf("Attempted to open %s, Return value: %lx\n", argv[1], (long) mylib);

  if(!mylib){
    printf("Errors: %s\n", dlerror());
    printf("Wasn't able to open %s\n", argv[1]);
    return -1;
  }

  struct archive *a;
  struct archive_entry *entry;
  int r;

  struct archive *(*dl_archive_read_new)(void)
    = (struct archive *(*)(void)) dlsym(mylib, "archive_read_new");
  a = dl_archive_read_new();

  int (*dl_archive_read_support_filter_all)(struct archive *)
    = (int (*)(struct archive *)) dlsym(mylib, "archive_read_support_filter_all");
  dl_archive_read_support_filter_all(a);

  int (*dl_archive_read_support_format_all)(struct archive *)
    = (int (*)(struct archive *)) dlsym(mylib, "archive_read_support_format_all");
  dl_archive_read_support_format_all(a);

  int (*dl_archive_read_open_filename)(struct archive *, const char *, size_t)
    = (int (*)(struct archive *, const char*, size_t))dlsym(mylib, "archive_read_open_filename");
  r = dl_archive_read_open_filename(a, "archive.tar", 10240); // Note 1

  if (r != ARCHIVE_OK)
    return -1;

  int (*dl_archive_read_next_header)(struct archive *, struct archive_entry **)
    = (int (*)(struct archive *, struct archive_entry **))dlsym(mylib, "archive_read_next_header");

  const char*(*dl_archive_entry_pathname)(struct archive_entry *)
    = (const char *(*) (struct archive_entry *))dlsym(mylib, "archive_entry_pathname");

  int (*dl_archive_read_data_skip)(struct archive *)
    = (int (*)(struct archive*))dlsym(mylib, "archive_read_data_skip");

  int	(*dl_archive_read_free)(struct archive *)
    = (int (*)(struct archive*))dlsym(mylib, "archive_read_free");

  printf("\ntar contents\n");
  printf("------------\n");
  while (dl_archive_read_next_header(a, &entry) == ARCHIVE_OK)
  {
    printf("%s\n", dl_archive_entry_pathname(entry));
    dl_archive_read_data_skip(a); // Note 2
  }
  r = dl_archive_read_free(a); // Note 3

  if (r != ARCHIVE_OK) {
    return -1;
  }
  if(mylib) {
    int eret = dlclose(mylib);
  }
}

