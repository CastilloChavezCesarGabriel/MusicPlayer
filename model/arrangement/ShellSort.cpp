#include "model/arrangement/ShellSort.h"

void ShellSort::sort(std::vector<Song>& songs) {
    const int total = songs.size();
    for (int interval = total / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < total; i++) {
            Song swapValue = songs[i];
            swapValue.accept(*this);
            const long long swapKey = key_;
            int j;
            for (j = i; j >= interval; j -= interval) {
                songs[j - interval].accept(*this);
                if (key_ <= swapKey) break;
                songs[j] = songs[j - interval];
            }
            songs[j] = swapValue;
        }
    }
}