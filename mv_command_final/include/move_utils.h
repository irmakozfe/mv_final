#ifndef MOVE_UTILS_H
#define MOVE_UTILS_H

int mvRenameFile(const char *source_file, const char *new_name);
int mvRenameDir(const char *source_dir, const char *new_name);
int mvMoveFileToDir(const char *source, const char *destination_dir);
int mvMoveDirToDir(const char *source_dir, const char *target_dir);

#endif //MOVE_UTILS_H
