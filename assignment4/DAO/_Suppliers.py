from DAO.Supplier import Supplier

class _Suppliers:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, supplier):
        self._conn.execute("""INSERT INTO suppliers (id , name , contact_information) VALUES (? , ? , ?)""",
                           [supplier._id, supplier._name, supplier._contact_information])

    def find(self, id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, name, contact_information FROM suppliers WHERE id = ?
        """, [id])
        return Supplier(*c.fetchone())

    def getSuppliers(self):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Suppliers """)
        _Supplier = cursor.fetchall()
        return _Supplier