from DAO.Activitie import Activitie


class _Activities:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, activitie):
        self._conn.execute("""INSERT INTO Activities (product_id , quantity , activator_id ,date) VALUES (?, ? , ? , 
        ?)""",
        [activitie._product_id , activitie._quantity , activitie._activator_id , activitie._date])

    def find(self, product_id):
        c = self._conn.cursor()
        c.execute("""
            SELECT product_id, quantity, activator_id, date FROM employees WHERE id = ?
        """, [product_id])
        return Activitie(*c.fetchone())

    def getActivities(self):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Activities  ORDER BY Date """)
        Activitie = cursor.fetchall()
        return Activitie

