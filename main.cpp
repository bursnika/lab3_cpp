#include <iostream>
#include <array>
#include <thread>
#include <latch>
#include <syncstream>
#include <chrono>

using namespace std;

std::latch done_a(6);
std::latch done_b(9);
std::latch done_c(7);
std::latch done_d(7);
std::latch done_e(8);
std::latch done_f(6);
std::latch done_g(5);
std::latch done_h(7);
std::latch done_i(9);
std::latch done_j(8);

void f(const char* set_name, int action_index) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::osyncstream(std::cout) << "З набору " << set_name << " виконано дію " << action_index << "." << std::endl;
}

void worker(int id) {
    switch (id) {
    case 0:
        f("a", 1); done_a.count_down();
        f("a", 2); done_a.count_down();
        done_a.wait();

        f("b", 1); done_b.count_down();
        f("b", 2); done_b.count_down();
        f("b", 3); done_b.count_down();
        done_b.wait();
        done_d.wait();

        f("i", 1); done_i.count_down();
        f("i", 2); done_i.count_down();
        f("i", 3); done_i.count_down();
        break;

    case 1:
        f("a", 3); done_a.count_down();
        f("a", 4); done_a.count_down();
        done_a.wait();

        f("b", 4); done_b.count_down();
        f("b", 5); done_b.count_down();
        f("b", 6); done_b.count_down();
        done_b.wait();
        done_d.wait();

        f("i", 4); done_i.count_down();
        f("i", 5); done_i.count_down();
        f("i", 6); done_i.count_down();
        break;

    case 2:
        f("a", 5); done_a.count_down();
        f("a", 6); done_a.count_down();
        done_a.wait();

        f("b", 7); done_b.count_down();
        f("b", 8); done_b.count_down();
        f("b", 9); done_b.count_down();
        done_b.wait();
        done_d.wait();

        f("i", 7); done_i.count_down();
        f("i", 8); done_i.count_down();
        f("i", 9); done_i.count_down();
        break;

    case 3:
        f("c", 1); done_c.count_down();
        f("c", 2); done_c.count_down();
        done_c.wait();

        f("d", 1); done_d.count_down();
        f("d", 2); done_d.count_down();
        f("d", 3); done_d.count_down();
        done_b.wait();
        done_e.wait();

        f("h", 1); done_h.count_down();
        f("h", 2); done_h.count_down();
        f("h", 3); done_h.count_down();
        done_h.wait();
        done_g.wait();

        f("j", 1); done_j.count_down();
        f("j", 2); done_j.count_down();
        break;

    case 4:
        f("c", 3); done_c.count_down();
        f("c", 4); done_c.count_down();
        done_c.wait();

        f("d", 4); done_d.count_down();
        f("d", 5); done_d.count_down();
        f("d", 6); done_d.count_down();
        f("d", 7); done_d.count_down();
        done_b.wait();
        done_e.wait();

        f("h", 4); done_h.count_down();
        f("h", 5); done_h.count_down();
        f("h", 6); done_h.count_down();
        f("h", 7); done_h.count_down();
        done_h.wait();
        done_g.wait();

        f("j", 3); done_j.count_down();
        f("j", 4); done_j.count_down();
        break;

    case 5:
        f("c", 5); done_c.count_down();
        f("c", 6); done_c.count_down();
        done_c.wait();

        f("e", 1); done_e.count_down();
        f("e", 2); done_e.count_down();
        f("e", 3); done_e.count_down();
        f("e", 4); done_e.count_down();

        f("f", 1); done_f.count_down();
        f("f", 2); done_f.count_down();
        done_f.wait();

        f("g", 1); done_g.count_down();
        f("g", 2); done_g.count_down();
        done_h.wait();
        done_g.wait();

        f("j", 5); done_j.count_down();
        f("j", 6); done_j.count_down();
        break;

    case 6:
        f("c", 7); done_c.count_down();
        done_c.wait();

        f("e", 5); done_e.count_down();
        f("e", 6); done_e.count_down();
        f("e", 7); done_e.count_down();
        f("e", 8); done_e.count_down();

        f("f", 3); done_f.count_down();
        f("f", 4); done_f.count_down();
        f("f", 5); done_f.count_down();
        f("f", 6); done_f.count_down();
        done_f.wait();

        f("g", 3); done_g.count_down();
        f("g", 4); done_g.count_down();
        f("g", 5); done_g.count_down();
        done_h.wait();
        done_g.wait();

        f("j", 7); done_j.count_down();
        f("j", 8); done_j.count_down();
        break;
    }
}

int main() {
    std::cout << "Обчислення розпочато." << std::endl;

    {
        std::array<std::jthread, 7> threads {
            std::jthread(worker, 0),
            std::jthread(worker, 1),
            std::jthread(worker, 2),
            std::jthread(worker, 3),
            std::jthread(worker, 4),
            std::jthread(worker, 5),
            std::jthread(worker, 6)
        };
    }

    std::cout << "Обчислення завершено." << std::endl;
    return 0;
}