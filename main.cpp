#include "vmain.inl"
#include "compiler/iall.hpp"
#include "compiler/lua/lua.c"
/*
** 无参数启动（如双击 exe）时：自动运行 exe 同目录下的 main.yok。
** 若不存在则保持 Lua 默认行为（进入交互模式）。
*/
static void default_script (int *argc, char ***argv) {
#ifdef _WIN32
  wchar_t path[MAX_PATH];
  DWORD n = GetModuleFileNameW(NULL, path, MAX_PATH);
  if (n == 0 || n >= MAX_PATH) return;
  wchar_t *slash = wcsrchr(path, L'\\');
  if (slash == NULL) return;
  *(slash + 1) = L'\0';        /* 截到 exe 所在目录 */
  wcscat(path, L"main.yok");   /* 拼上默认脚本名 */
  if (GetFileAttributesW(path) == INVALID_FILE_ATTRIBUTES) return;  /* 没有则不管 */
  /* 宽字符路径转 UTF-8（luaL_loadfile 按 UTF-8 读取） */
  int len = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
  char *utf8 = (char *)malloc((size_t)len);
  WideCharToMultiByte(CP_UTF8, 0, path, -1, utf8, len, NULL, NULL);
  char **new_argv = (char **)malloc(2 * sizeof(char *));
  new_argv[0] = (*argv)[0];
  new_argv[1] = utf8;
  *argc = 2;
  *argv = new_argv;
#endif
}

int main (int argc, char **argv) {
  int status, result;
  if (argc == 1) default_script(&argc, &argv);  /* 无参数：默认运行同目录 main.yok */
  lua_State *L = luaL_newstate();  /* create state */
  if (L == NULL) {
    l_message(argv[0], "cannot create state: not enough memory");
    return EXIT_FAILURE;
  }
  lua_gc(L, LUA_GCSTOP);  /* stop GC while building state */
  lua_pushcfunction(L, &pmain);  /* to call 'pmain' in protected mode */
  lua_pushinteger(L, argc);  /* 1st argument */
  lua_pushlightuserdata(L, argv); /* 2nd argument */
  status = lua_pcall(L, 2, 1, 0);  /* do the call */
  result = lua_toboolean(L, -1);  /* get result */
  report(L, status);
  lua_close(L);
  return (result && status == LUA_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}