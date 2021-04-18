from DAO.Employee import Employee


class _Employees:
    def __init__(self , conn):
        self._conn = conn

    def insert(self, employee):
        self._conn.execute("""INSERT INTO employees (id , name , salary ,coffee_stand) VALUES (?, ? , ? , ?)""",
        [employee._id , employee._name , employee._salary , employee._coffee_stand])

    def find(self, id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, name, salary, coffe_stand FROM employees WHERE id = ?
        """, [id])
        return Employee(*c.fetchone())

    def getEmployees(self):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Employees """)
        _Employee = cursor.fetchall()
        return _Employee