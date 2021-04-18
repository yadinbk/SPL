from DAO.Activitie import Activitie
import _Repository


def main(args):
    inputFile = open(args)
    fill_activities(inputFile)
    print("bye")


def fill_activities(inputFile):
    for line in inputFile:
        arg = line[:].split(", ")
        a = Activitie(*arg)
        repo.activities.insert(a)



        product_id = a._product_id
        product = repo.products.find(product_id)
        quantity = product._quantity;
        quantityToSet = quantity + ((int)(a._quantity));
        print(quantityToSet)
        if  quantityToSet >= 0:
            repo.products.update(product_id, quantityToSet)



if __name__ == '__main__':
    repo=_Repository._Repository(False)
    main('action.txt')
    repo._conn.commit()
    repo.close()
    # Change before handing out
