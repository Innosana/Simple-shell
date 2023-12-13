#include "shell.h"

/**
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 */

int _mycd(info_t *info)
{
    // ... existing code ...

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(s);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);

    // ... remaining code ...

    return (0);
}

int _myhelp(info_t *info)
{
    // ... existing code ...

    if (info->argv[0])
        _puts(*info->argv); /* temp att_unused workaround */

    // ... remaining code ...

    return (0);
}
