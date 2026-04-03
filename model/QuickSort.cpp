#include "QuickSort.h"
#include <stack>

void QuickSort::visit(const std::string& name, const std::string&) {
    title_ = Song::parse(name);
}

void QuickSort::sort(std::vector<Song>& songs) {
    if (songs.empty()) return;

    std::stack<std::pair<int, int>> stack;
    stack.push({0, static_cast<int>(songs.size()) - 1});

    while (!stack.empty()) {
        auto [startBound, endBound] = stack.top();
        stack.pop();

        if (startBound >= endBound) continue;

        const int pivot = divide(songs, startBound, endBound);
        if (pivot - 1 > startBound) stack.push({startBound, pivot - 1});
        if (pivot + 1 < endBound) stack.push({pivot + 1, endBound});
    }
}

int QuickSort::divide(std::vector<Song>& songs, const int startBound, const int endBound) {
    songs[endBound].accept(*this);
    const std::string pivot = title_;
    int i = startBound;

    for (int j = startBound; j < endBound; j++) {
        songs[j].accept(*this);
        if (title_ < pivot) {
            std::swap(songs[i], songs[j]);
            i++;
        }
    }
    std::swap(songs[i], songs[endBound]);
    return i;
}