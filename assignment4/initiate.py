from DAO.Coffee_stand import Coffee_stand
from DAO.Employee import Employee
from DAO.Product import Product
from DAO.Supplier import Supplier
import _Repository

def main(args):
    inputFile = open(args)
    fill_table(inputFile)
    print("bye")



def fill_table(inputFile):
    for line in inputFile:
        arg = line[:-1].split(", ")
        if arg[0] == 'C':
            repo.coffee_stands.insert(Coffee_stand(*arg[1:]))
        elif arg[0] == 'S':
            repo.suppliers.insert(Supplier(*arg[1:]))
        elif arg[0] == 'E':
            repo.employees.insert(Employee(*arg[1:]))
        elif arg[0] == 'P':
            print(arg)
            repo.products.insert(Product(*arg[1:]))







if __name__=='__main__':
    repo=_Repository._Repository(True)
    repo.create_tables()
    main('config.txt')
    repo.close()
    # Change before handing out