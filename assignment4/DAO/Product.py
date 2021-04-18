class Product:
    def __init__(self, id, description, price, quantity = None):
        self._id = id
        self._description = description
        self._price = price
        if(quantity != None):
            self._quantity = quantity
        else:
            self._quantity = 0;
