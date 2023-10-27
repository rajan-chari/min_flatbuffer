#include <iostream>
#include <fstream>
#include "orange_generated.h"

using namespace MyNamespace;

void serializeRootTable()
{
    // Create an instance of the A struct
    flatbuffers::FlatBufferBuilder builder;
    auto a = CreateADirect(builder, 1, "Alice");

    // Create an instance of the RootTable struct
    auto root_table = CreateRootTable(builder, AorB_A, a.Union());

    // Serialize the RootTable struct to a file
    std::ofstream outfile("root_table.bin", std::ofstream::binary);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file for writing" << std::endl;
        return;
    }
    builder.Finish(root_table);
    outfile.write(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());
    outfile.close();
}

void deserializeRootTable()
{
    // Read the serialized data from the file
    std::ifstream infile("root_table.bin", std::ifstream::binary);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file for reading" << std::endl;
        return;
    }
    infile.seekg(0, infile.end);
    auto size = infile.tellg();
    infile.seekg(0, infile.beg);
    std::vector<char> buffer(size);
    infile.read(buffer.data(), size);
    infile.close();

    // Deserialize the RootTable struct from the buffer
    auto root_table = GetRootTable(buffer.data());

    // Print the values of the fields in the RootTable struct
    std::cout << "RootTable data:" << std::endl;
    if (root_table->data_type() == AorB_A) {
        auto a = static_cast<const A*>(root_table->data());
        std::cout << "  A: id=" << a->id() << ", name=" << a->name()->str() << std::endl;
    } else if (root_table->data_type() == AorB_B) {
        auto b = static_cast<const B*>(root_table->data());
        std::cout << "  B: id=" << b->id() << ", value=" << b->value() << std::endl;
    }
}

int main()
{
    serializeRootTable();
    std::cout << "Serialized RootTable data to root_table.bin" << std::endl;
    std::cout << "Reading root_table.bin" << std::endl;
    deserializeRootTable();
    return 0;
}