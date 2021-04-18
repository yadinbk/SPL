from DAO.Coffee_stand import Coffee_stand


class _Coffee_stands:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, coffee_stand):
        self._conn.execute("""INSERT INTO Coffee_stands (id , location , number_of_employees) VALUES (?, ? , ? )""",
        [coffee_stand._id , coffee_stand._location , coffee_stand._number_of_employees])

    def find(self, id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, location, number_of_employees FROM employees WHERE id = ?
        """, [id])
        return Coffee_stand(*c.fetchone())

    def getCoffee_stands(self):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Coffee_stands """)
        Coffee_stand = cursor.fetchall()
        return Coffee_stand