#include "filesort.hpp"

std::recursive_mutex tmp_lock, new_lock, _lock;

void file_copy(const std::string& name1, const std::string& name2)
{
    new_lock.lock();
    std::unique_ptr<uint64_t> buf(new uint64_t [MAXSIZE]);
    std::ifstream in(name1, std::ios::binary);
    std::ofstream out(name2, std::ios::binary);
    while (!in.eof()) {
        in.read((char*) buf.get(), MAXSIZE);
        if (in.gcount()) {
            out.write((char*) buf.get(), in.gcount());
        }
    }
    out.close();
    in.close();
    new_lock.unlock();
}

void create_binary_file(std::ofstream &out) 
{
    for (int i = 0; i < 1024 * 1023; ++i) {
        uint64_t rand_num = rand() % 100;
        out.write((char *) &rand_num, sizeof(rand_num));
    }
}

void merge(std::vector<std::string>& f_names)
{
    file_copy(f_names[0], "output");
    std::ifstream in("file_copy", std::ios::binary);
    std::ofstream out("output", std::ios::binary);
    uint64_t c1, c2;
                        
    for (size_t i = 1; i < f_names.size(); ++i) {
        file_copy("output", "file_copy");
        std::ifstream tmp(f_names[i], std::ios::binary);

        in.read((char*) &c1, sizeof(c1));
        tmp.read((char*) &c2, sizeof(c2));

        while (!tmp.eof()) {
            if(!in.gcount()) {
                while (!tmp.eof()) {
                    out.write((char*) &c2, sizeof(c2));
                    tmp.read((char*) &c2, sizeof(c2));
                }
            }
            else if (c2 <=  c1) {
                out.write((char*) &c2, sizeof(c2));
                tmp.read((char*) &c2, sizeof(c2));
            } 
            else {
                out.write((char*) &c1, sizeof(c1));
                in.read((char*) &c1, sizeof(c1));
            }
        }
        if (in.gcount()) {
            out.write((char*) &c1, sizeof(c1));
            std::unique_ptr<uint64_t> buf(new uint64_t [MAXSIZE]);
            while (!in.eof()) {
                in.read((char*) buf.get(), MAXSIZE);
                out.write((char*) buf.get(), in.gcount());
            }
        }
    }
}

void clean_files(std::vector<std::string>& names) 
{
    for (auto &name: names) {
        if (remove(name.c_str())) {
            throw std::runtime_error("Can't remove file");
        }
    }         
    if (remove("file_copy")) {
        throw std::runtime_error("Can't remove file");
    }
}

void thread_function(std::ofstream& out)
{
    std::ifstream in("input", std::ios::binary);            
    if (!in) {
        throw std::runtime_error("Can't open file: input");
    }
    std::vector<std::string> names;                     
    for (int i = 0; !in.eof(); ++i) {
        _lock.lock();
        std::string name = "output" + std::to_string(i) + ".bin";
        names.push_back(name);

        std::unique_ptr<uint64_t> buf(new uint64_t [MAXSIZE]);

        in.read((char*) buf.get(), MAXSIZE);
        size_t cnt = in.gcount();
        if(cnt) {
            size_t read_ = cnt / (2 * sizeof(uint64_t));
            std::sort(buf.get(), buf.get() + 2 * read_);
            out.open(name, std::ios::binary);
            if(!out.is_open()) {
                throw std::runtime_error("Can't open file: " + name);
            }
            out.write((char*) buf.get(), read_ * sizeof(uint64_t));
            out.close();
            ++i;
            name = "output" + std::to_string(i) + ".bin";
            names.push_back(name);
            out.open(name, std::ios::binary);
            if(!out.is_open()) {
                throw std::runtime_error("Can't open file: " + name);
            }
            out.write((char*) (buf.get() + read_), cnt - read_ * sizeof(uint64_t));
            out.close();
        }
        _lock.unlock();
    }

    if (tmp_lock.try_lock())
        return;
    merge(names);
    clean_files(names);
    in.close();
}

void sort_file(std::ofstream& out)
{
    std::thread th1(thread_function, std::ref(out));
    std::thread th2(thread_function, std::ref(out));

    th1.join();
    th2.join();
}