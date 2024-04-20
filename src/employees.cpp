#include "employees.h"
#include "bit_manip.h"
#include <fstream>
#include <iostream>
#include <string>

namespace StaffManagement
{
    // Employee base class methods

    void Employee::printConsole(std::ostream &out) const
    {
        out << "Name: " << _name << std::endl;
        out << "Base Salary: " << _base_salary << std::endl;
    }

    void Employee::readConsole(std::istream &in) { in >> _name >> _base_salary; }

    void Employee::writeBinary(std::ostream &out) const
    {
        out << manip::write_c_str(_name.c_str()) << manip::write_le_int32(_base_salary);
    }

    void Employee::readBinary(std::istream &in)
    {
        char name[manip::MAX_NAME_LENGTH];
        in >> manip::read_c_str(name, sizeof(name)) >> manip::read_le_int32(_base_salary);
        _name = name;
    }

    // SalesManager class implementation

    int SalesManager::salary() const
    {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    void SalesManager::printConsole(std::ostream &out) const
    {
        out << "Sales Manager" << std::endl;
        Employee::printConsole(out);
        out << "Sold items: " << _sold_nm << std::endl;
        out << "Item price: " << _price;
    }

    void SalesManager::readConsole(std::istream &in)
    {
        Employee::readConsole(in);
        in >> _sold_nm >> _price;
    }

    void SalesManager::writeBinary(std::ostream &out) const
    {
        out << manip::write_le_int32(2);
        Employee::writeBinary(out);
        out << manip::write_le_int32(_sold_nm) << manip::write_le_int32(_price);
    }

    void SalesManager::readBinary(std::istream &in)
    {
        Employee::readBinary(in);
        in >> manip::read_le_int32(_sold_nm) >> manip::read_le_int32(_price);
    }

    // Developer class implementation

    int Developer::salary() const
    {
        int salary = _base_salary;
        if (_has_bonus)
            salary += 1000;
        return salary;
    }

    void Developer::printConsole(std::ostream &out) const
    {
        out << "Developer" << std::endl;
        Employee::printConsole(out);
        out << "Has bonus: " << (_has_bonus ? "+" : "-");
    }

    void Developer::readConsole(std::istream &in)
    {
        Employee::readConsole(in);
        in >> _has_bonus;
    }

    void Developer::writeBinary(std::ostream &out) const
    {
        out << manip::write_le_int32(1);
        Employee::writeBinary(out);
        out << manip::write_bool(_has_bonus);
    }

    void Developer::readBinary(std::istream &in)
    {
        Employee::readBinary(in);
        in >> manip::read_bool(_has_bonus);
    }

    // Input & output in console implementation

    std::ostream &operator<<(std::ostream &out, const Employee &employee)
    {
        employee.printConsole(out);
        return out;
    }

    std::istream &operator>>(std::istream &in, Employee &employee)
    {
        employee.readConsole(in);
        return in;
    }

    // EmployeesArray implementation

    void EmployeesArray::add(const Employee *e)
    {
        _employees.push_back(e);
    }

    EmployeesArray::~EmployeesArray()
    {
        while (_employees.size())
        {
            delete _employees.back();
            _employees.pop_back();
        }
    }

    int EmployeesArray::total_salary() const
    {
        int salary_sum = 0;
        for (auto &employee : _employees)
            salary_sum += employee->salary();
        return salary_sum;
    }

    int32_t EmployeesArray::get_size() const
    {
        return _employees.size();
    }

    const Employee *EmployeesArray::get_employee(size_t index) const
    {
        return _employees[index];
    }

    // EmployeesArray input & output

    std::ostream &operator<<(std::ostream &out, const EmployeesArray &arr)
    {
        for (int i = 1; i <= arr._employees.size(); ++i)
            std::cout << i << ". " << *arr._employees[i - 1] << std::endl;
        out << "== Total salary: " << arr.total_salary() << std::endl;
        return out;
    }

    // Binary input & output

    std::ofstream &operator<<(std::ofstream &out, const Employee &employee)
    {
        employee.writeBinary(out);
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, Employee &employee)
    {
        employee.readBinary(in);
        return in;
    }
}