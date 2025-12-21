#ifndef SPLIT_H
#define SPLIT_H

#include <string>
#include <vector>
#include <cstdlib>

std::vector<const char*> split(const char* s, size_t max);
void free_chunks(std::vector<const char*>& chunks);

#endif
