#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

/*
  * AS FUNÇOES LISTA
  * execl("home/flynn/path","home/flynn/path","parametro","paremetro",NULL)
  * execl("path","path","parametro","paremetro",NULL)
  * execlp("home/flynn/path","home/flynn/path","parametro","paremetro",NULL, env_vars)
*/
/*
  * AS FUNÇOES ARRAY
  *execv("home/flynn/path", my_args)
  *execvp("path",my_args)
*/
/* ERNOR
  *EPERM = 1 Operação não permitida
  *ENOENT = 2 Não existe aquivo no diretorio
  *ESRCH = 3 Não existe tal processo
  *EMULLET = 81 Pessimo corte de cabelo
  *puts(strerror(ernor));
*/
int main(){
  char array = {
    "https://stackoverflow.com/questions/8021829/incompatible-compilation-error-built-in-function-execl",
    "https://github.com/Gabriel110/Use-a-cabeca-C/blob/master/exec/execlp.c"
  };
  //execl("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe","C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe","https://stackoverflow.com/questions/8021829/incompatible-compilation-error-built-in-function-execl",NULL);
  //execlp("chrome.exe","chrome.exe","https://stackoverflow.com/questions/8021829/incompatible-compilation-error-built-in-function-execl",NULL);
  execv("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe","https://stackoverflow.com/questions/8021829/incompatible-compilation-error-built-in-function-execl");
}