#pragma once

#include <fstream>
#include <ostream>
#include <stdint.h>
#include <string>
#include <vector>

namespace StaffManagement
{
    // Employee class

    class Employee
    {
    public:
        friend std::ostream &operator<<(std::ostream &out, const Employee &employee);
        friend std::istream &operator>>(std::istream &in, Employee &employee);
        friend std::ofstream &operator<<(std::ofstream &out, const Employee &employee);
        friend std::ifstream &operator>>(std::ifstream &in, Employee &employee);

        virtual int salary() const = 0;
        virtual ~Employee() = default;

    protected:
        virtual void printConsole(std::ostream &out) const = 0; // prints the information about the employees
        virtual void readConsole(std::istream &in) = 0;         // reads the information about the employees
        virtual void writeBinary(std::ostream &out) const = 0;  // prints in the binary format
        virtual void readBinary(std::istream &in) = 0;

    protected:
        std::string _name;
        int32_t _base_salary;
    };

    // Developer class

    class Developer : public Employee
    {
    public:
        int salary() const;

    private:
        void printConsole(std::ostream &out) const override;
        void writeBinary(std::ostream &out) const override;
        void readConsole(std::istream &in) override;
        void readBinary(std::istream &in) override;

    private:
        bool _has_bonus;
    };

    // SalesManager class

    class SalesManager : public Employee
    {
    public:
        int salary() const;

    private:
        void printConsole(std::ostream &out) const override;
        void writeBinary(std::ostream &out) const override;
        void readConsole(std::istream &in) override;
        void readBinary(std::istream &in) override;

    private:
        int32_t _sold_nm, _price;
    };

    // EmployeesArray class

    class EmployeesArray
    {
    public:
        friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &arr);
        void add(const Employee *e);
        int total_salary() const;

        const Employee *get_employee(size_t index) const;
        int32_t get_size() const;

        ~EmployeesArray();

    private:
        std::vector<const Employee *> _employees;
    };
}
