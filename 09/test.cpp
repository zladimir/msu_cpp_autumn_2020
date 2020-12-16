#include "filesort.hpp"

void check_sorted()
{
    std::ifstream in("output", std::ios::binary);
    if (!in) {
        std::cerr << "Can't open file: output" << std::endl;
        return;
    }
    std::unique_ptr<uint64_t> buf(new uint64_t [MAXSIZE]);
    bool sorted = true;
    while (!in.eof()) {
        in.read((char*) buf.get(), MAXSIZE);
        auto elem = buf.get()[0];
        for (size_t i = 1; buf.get()[i]; i++) {
            if (buf.get()[i] < elem)
                sorted = false;
            else
                elem = buf.get()[i];
        }
    }
    if (sorted)
        std::cout << "Success" << std::endl;
    else
        std::cout << "Fail in sorting" << std::endl;
    return;
}

void test()
{
    std::ofstream bin_file("input", std::ios::binary);
    if (!bin_file) {
        std::cerr << "Can't open file: input" << std::endl;
        return;
    }
    create_binary_file(bin_file);
    bin_file.close();
    try {
        sort_file(bin_file);
    } 
    catch(const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        return;
    }
    check_sorted();
}

int main()
{
    test();
    return 0;
}