#include <stdio.h>
#include <xenstore.h>

int mkdir(struct xs_handle *xsd, char *path){
  if(!xs_mkdir(xsd, 0, path)){
    printf("Could not create new directory!\n");
    return 2;
  }
  return 0;
}

int main(int argc, char **argv)
{
  struct xs_handle *xsd = xs_open(0);
  struct xs_permissions perms = {.id = 0, .perms = XS_PERM_READ|XS_PERM_WRITE};
  unsigned int num, i;
  char **list;
  bool res;

  mkdir(xsd, "/rendezvous");
  mkdir(xsd, "/transport");

  res = xs_set_permissions(xsd, 0, "/rendezvous", &perms, 1);
  if(!res) {
    printf("Could not set directory permissions.\n");
    return 3;
  }

  printf("Base directory added. New root directory:\n");
  list = xs_directory(xsd, 0, "/", &num);
  for(i = 0; i < num; i++)
    printf("  /%s\n", list[i]);

  return 0;
}
