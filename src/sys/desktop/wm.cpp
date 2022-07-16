#include <sys/desktop/wm.h>
#include <sys/debug/dbg.h>
#include <sys/lib/string.h>
#include <sys/mem/heap.h>

namespace Wm {
    int index = 0;
    Window wList[10];

    void init() {
        memset(wList, 0, 10);
        Dbg::printf("Wm initialised succesfully.\n");
    }

    int addWindow(Window win) {
        if (index >= 10) {
            Dbg::printf("Wm error: Could not add window '%s'. Too many windows.\n", win.name);
            return;
        }
        index++;
        wList[index] = win;
        Dbg::printf("Wm success: Added window '%s' at position %d.\n", win.name, index);
        return index;
    }

    void removeWindow(int id) {
        Heap::free(&wList[id]);
    }

    void update() {
        for (int i = 1; i <= index; i++) {
            wList[i].update();
        }
    }
}