#include "model/arrangement/QuickSort.h"
#include <stack>

void QuickSort::visit(const std::string& name, const std::string&) {
    title_ = Song::parse(name);
}

void QuickSort::sort(std::vector<Song>& songs) {
    if (songs.empty()) return;

    std::stack<std::pair<int, int>> stack;
    stack.push({0, static_cast<int>(songs.size()) - 1});

    while (!stack.empty()) {
        const auto bounds = stack.top();
        stack.pop();

        if (bounds.first >= bounds.second) continue;

        const int pivot = divide(songs, bounds);
        if (pivot - 1 > bounds.first) stack.push({bounds.first, pivot - 1});
        if (pivot + 1 < bounds.second) stack.push({pivot + 1, bounds.second});
    }
}

int QuickSort::divide(std::vector<Song>& songs, const std::pair<int, int> &bounds) {
    songs[bounds.second].accept(*this);
    const std::string pivot = title_;
    int i = bounds.first;

    for (int j = bounds.first; j < bounds.second; j++) {
        songs[j].accept(*this);
        if (title_ < pivot) {
            std::swap(songs[i], songs[j]);
            i++;
        }
    }
    std::swap(songs[i], songs[bounds.second]);
    return i;
}