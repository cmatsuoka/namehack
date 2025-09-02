/*
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <https://unlicense.org/>
 */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <dlfcn.h>

#define TERMINATOR "NAMEHACK_TERMINATOR"

static struct passwd *(*real_getpwuid)(uid_t) = NULL;
static struct group *(*real_getgrgid)(gid_t) = NULL;


static int get_terminator()
{
        static int cached = -1;
        if (cached >= 0) {
                return cached;
        }

        char *t = getenv(TERMINATOR);
        cached = (t && *t) ? *t : '.';

        return cached;
}

struct passwd *getpwuid(uid_t uid)
{
        if (!real_getpwuid) {
                real_getpwuid = dlsym(RTLD_NEXT, "getpwuid");
                if (!real_getpwuid) {
                        return NULL;
                }
        }

        struct passwd *pw = real_getpwuid(uid);
        if (pw) {
                int t = get_terminator();
                char *pos = strchr(pw->pw_name, t);
                if (pos) {
                        *pos = 0;
                }
        }

        return pw;
}

struct group *getgrgid(gid_t gid)
{
        if (!real_getgrgid) {
                real_getgrgid = dlsym(RTLD_NEXT, "getgrgid");
                if (!real_getgrgid) {
                        return NULL;
                }
        }

        struct group *gr = real_getgrgid(gid);
        if (gr) {
                int t = get_terminator();
                char *pos = strchr(gr->gr_name, t);
                if (pos) {
                        *pos = 0;
                }
        }

        return gr;
}
