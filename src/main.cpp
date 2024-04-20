#include "employees.h"
#include "bit_manip.h"
#include <iostream>
#include <fstream>
#include <vector>

void readEmployees(std::ifstream &in, int32_t size, StaffManagement::EmployeesArray &arr)
{
    StaffManagement::Employee *employee;

    for (size_t i = 0; i < size; ++i)
    {
        int32_t id;
        in >> manip::read_le_int32(id);

        if (id == 1)
            employee = new StaffManagement::Developer();
        else if (id == 2)
            employee = new StaffManagement::SalesManager();

        in >> *employee;
        arr.add(employee);
    }
}

int main()
{
    std::string cmd;
    StaffManagement::EmployeesArray arr;
    while (true)
    {
        std::cin >> cmd;
        if (cmd == "add")
        {
            int id;
            std::cin >> id;

            StaffManagement::Employee *employee;

            if (id == 1)
                employee = new StaffManagement::Developer();
            else if (id == 2)
                employee = new StaffManagement::SalesManager();

            std::cin >> *employee;
            arr.add(employee);
        }
        else if (cmd == "list")
        {
            std::cout << arr << std::endl;
        }
        else if (cmd == "load")
        {
            std::string path;
            std::cin >> path;

            std::ifstream in(path, std::ios::binary);

            if (!in)
                throw std::runtime_error("Cannot open a file: " + path);

            int32_t size;
            in >> manip::read_le_int32(size);

            readEmployees(in, size, arr);

            in.close();
        }
        else if (cmd == "save")
        {
            std::string path;
            std::cin >> path;

            std::ofstream out(path, std::ios::binary);

            if (!out)
                throw std::runtime_error("Cannot open a file: " + path);

            out << manip::write_le_int32(arr.get_size());

            for (size_t i = 0; i < arr.get_size(); ++i)
                out << *arr.get_employee(i);

            out.close();
        }
        else if (cmd == "exit")
            break;
    }
}
