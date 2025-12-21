#include <vector>
#include <cstring>
#include <cstdlib>

#include "include/split.hpp"

std::vector<const char*> split(const char* s, size_t max_len) {
	std::vector<const char*> result;
	size_t len = std::strlen(s);
	size_t start = 0;

	while (start < len) {
		size_t remaining = len - start;

		// If what's remaining is less than the max_len, split and exit
		if (remaining <= max_len) {
			char* chunk = (char*)malloc(remaining + 1);
			std::memcpy(chunk, s + start, remaining);
			chunk[remaining] = '\0';
			result.push_back(chunk);
			break;
		}

		// Split needed because len(s) > max_len
		size_t end = std::min(start + max_len, len);

		// Look backwards for last space
		size_t split_pos = end;
		while (split_pos > start && s[split_pos] != ' ') {
			--split_pos;
		}

		if (split_pos == start) {
			// No space means we hard split, so we remove a word
			char* chunk = (char*)malloc(max_len + 1);
			std::memcpy(chunk, s + start, max_len);
			chunk[max_len] = '\0';
			result.push_back(chunk);
			start += max_len;
		} else {
			// Else split at space
			size_t chunk_len = split_pos - start;
			char* chunk = (char*)malloc(chunk_len + 1);
			std::memcpy(chunk, s + start, chunk_len);
			chunk[chunk_len] = '\0';
			result.push_back(chunk);
			// Skip space
			start = split_pos + 1;
		}
	}

	return result;
}

// Free all chunks
void free_chunks(std::vector<const char*>& chunks) {
	for (const char* p : chunks) {
		free((void*) p);
	}
	chunks.clear();
}
