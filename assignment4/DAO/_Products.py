from DAO.Product import Product


class _Products:
    def __init__(self , conn):
        self._conn = conn

    def insert(self, product):
        self._conn.execute("""INSERT INTO Products (id , description , price ,quantity) VALUES (?, ? , ? , ?)""",
        [product._id , product._description , product._price , product._quantity])

    def find(self, id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, description, price, quantity FROM Products WHERE id = ?
        """, [id])
        return Product(*c.fetchone())


    def update(self,product_id, quantity):
        self._conn.execute("""
               UPDATE Products SET quantity=(?) WHERE id=(?)""",
               [quantity, product_id])

    def getProduct(self , id):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Products WHERE id=(?)""" ,[id])
        product = cursor.fetchone()
        return product

    def getProducts(self):
        cursor = self._conn.cursor()
        cursor.execute("""SELECT * FROM Products """)
        product = cursor.fetchall()
        return product