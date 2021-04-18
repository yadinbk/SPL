import _Repository

repo=_Repository._Repository(False)


def main():
    repo=_Repository._Repository(False)

    print("Activities")
    for line in repo.activities.getActivities():
        print(line)

    print("Coffee stands")
    for line in repo.coffee_stands.getCoffee_stands():
        print(line)

    print("Employees")
    for line in repo.employees.getEmployees():
        print(line)

    print("Products")
    for line in repo.products.getProducts():
        print(line)

    print("Suppliers")
    for line in repo.suppliers.getSuppliers():
        print(line)



if __name__=='__main__':
    main()
    # Change before handing out
