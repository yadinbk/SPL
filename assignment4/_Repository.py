import atexit
import sqlite3
import os

from DAO._Activities import _Activities
from DAO._Coffee_stands import _Coffee_stands
from DAO._Employees import _Employees
from DAO._Products import _Products
from DAO._Suppliers import _Suppliers


class _Repository:
    def __init__(self,create):
        if (create):
            if os.path.exists('moncafe.db'):
                os.remove('moncafe.db')
        self._conn = sqlite3.connect('moncafe.db')
        self.employees = _Employees(self._conn)
        self.coffee_stands = _Coffee_stands(self._conn)
        self.products = _Products(self._conn)
        self.suppliers = _Suppliers(self._conn)
        self.activities = _Activities(self._conn)

    def close(self):
        self._conn.commit()
        self._conn.close()

    def create_tables(self):
        self._conn.executescript("""
            CREATE TABLE Coffee_stands    
            (id INTEGER PRIMARY KEY,
            location TEXT NOT NULL,
            number_of_employees INTEGER);
 
            CREATE TABLE Suppliers
            (id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            contact_information TEXT);
        
            CREATE TABLE Products
            (id INTEGER PRIMARY KEY,
            description TEXT NOT NULL,
            price REAL NOT NULL,
            quantity INTEGER NOT NULL);
            
            CREATE TABLE Activities 
            (product_id INTEGER INTEGER REFERENCES Products(id),
            quantity INTEGER NOT NULL,
            activator_id INTEGER NOT NULL,
            date DATE NOT NULL);
            
            CREATE TABLE Employees 
            (id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            salary REAL NOT NULL,
            coffee_stand INTEGER REFERENCES Coffee_stands(id));
            """)
        self._conn.commit()

    def get_grades_with_names(self):
        c = self._conn.cursor()
        all = c.execute("""
             SELECT Employees.name, Employees.salary, Employees.coffee_stand, 
             FROM Employees
             JOIN students ON grades.student_id = students.student_id
         """).fetchall()

        return [EmployeesWithCoffeeStandAndTotal(*row) for row in all]

class EmployeesWithCoffeeStandAndTotal:
    def __init__(self, name, salary, working_location, total_sales_income):
        self._name = name
        self._salary = salary
        self._working_location = working_location
        self._total_sales_income = total_sales_income


class ActivityWithDescriptionAndQuantity :
    def __init__(self, date_of_activity, item_description, quantity, name_of_seller, name_of_the_supplier ):
        self._date_of_activity = date_of_activity
        self._item_description = item_description
        self._quantity = quantity
        self._name_of_seller = name_of_seller
        self._name_of_the_supplier = name_of_the_supplier

