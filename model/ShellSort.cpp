#include "ShellSort.h"

void ShellSort::visit(const std::string& name, const std::string&) {
    order_ = Song::order(name);
}

void ShellSort::sort(std::vector<Song>& songs) {
    const int total = songs.size();
    for (int interval = total / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < total; i++) {
            Song swapValue = songs[i];
            swapValue.accept(*this);
            const int swapOrder = order_;
            int j;
            for (j = i; j >= interval; j -= interval) {
                songs[j - interval].accept(*this);
                if (order_ <= swapOrder) break;
                songs[j] = songs[j - interval];
            }
            songs[j] = swapValue;
        }
    }
}