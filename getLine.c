#include "shell.h"

/**
 * @info: parameter struct
 * Return: bytes read
 * @buf: address of buffer
 * input_buf - buffers chained commands
 * @len: address of len var
 */

ssize_t readBuffer(info_t *info, char *buffer, size_t *size) {
    ssize_t bytesRead = 0;

    if (*size)
        return 0;

    bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
    if (bytesRead >= 0)
        *size = bytesRead;

    return bytesRead;
}

/*
 * Function to read input from STDIN
 */
int getLine(info_t *info, char **ptr, size_t *length) {
    static char inputBuffer[READ_BUF_SIZE];
    static size_t index = 0, bufferLength = 0;
    size_t k;
    ssize_t bytesRead = 0, totalBytes = 0;
    char *currentPtr = NULL, *newPtr = NULL, *newlinePtr;

    currentPtr = *ptr;

    if (currentPtr && length)
        totalBytes = *length;

    if (index == bufferLength)
        index = bufferLength = 0;

    bytesRead = readBuffer(info, inputBuffer, &bufferLength);
    if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
        return -1;

    newlinePtr = _strchr(inputBuffer + index, '\n');
    k = newlinePtr ? 1 + (unsigned int)(newlinePtr - inputBuffer) : bufferLength;
    newPtr = _realloc(currentPtr, totalBytes, totalBytes ? totalBytes + k : k + 1);

    if (!newPtr)
        return (currentPtr ? free(currentPtr), -1 : -1);

    if (totalBytes)
        _strncat(newPtr, inputBuffer + index, k - index);
    else
        _strncpy(newPtr, inputBuffer + index, k - index + 1);

    totalBytes += k - index;
    index = k;
    currentPtr = newPtr;

    if (length)
        *length = totalBytes;

    *ptr = currentPtr;
    return totalBytes;
}
