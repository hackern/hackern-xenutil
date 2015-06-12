#include <stdio.h>
#include <xenstore.h>

struct xs_handle *xsd;

int mkdir(char *path){
  if(!xs_mkdir(xsd, 0, path)){
    printf("Could not create new directory!\n");
    return 2;
  }
  return 0;
}

int setFullPerm(char *path){
  struct xs_permissions perms = {.id = 0, .perms = XS_PERM_READ|XS_PERM_WRITE}; // Full Permissions
  if(!xs_set_permissions(xsd, 0, path, &perms, 1)){
    printf("Could not set directory permissions.\n");
    return 3;
  }
  return 0;
}

int main(int argc, char **argv)
{
  unsigned int num, i;
  char **list;
  bool res;

  xsd = xs_open(0);
  
  mkdir("/rendezvous");
  mkdir("/transport");

  setFullPerm("/rendezvous");
  setFullPerm("/transport");
  setFullPerm("/local/domain");
    
  printf("Base directory added. New root directory:\n");
  list = xs_directory(xsd, 0, "/", &num);
  for(i = 0; i < num; i++)
    printf("  /%s\n", list[i]);

  return 0;
}
