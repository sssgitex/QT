function createContactsTable(tx) {
    var sql =
        'CREATE TABLE IF NOT EXISTS contacts (' +
        'id INTEGER PRIMARY KEY AUTOINCREMENT,' +
        'first_name TEXT(30) NOT NULL,' +
        'last_name TEXT(30) NOT NULL,' +
        'age INTEGER NOT NULL,' +
        'email TEXT(30) NOT NULL UNIQUE,' +
        'phone TEXT(20) NOT NULL UNIQUE' +
    ');'
    tx.executeSql(sql)

    sql = "SELECT * FROM contacts";
    if(tx.executeSql(sql).rows.length==0){
        sql =
                'INSERT INTO contacts (first_name,last_name,age,email,phone)' +
                'VALUES'+
                '("Иванов", "Иван", 30, "ivanov@mail.ru", "+7(911)1234567"),'+
                '("Петров", "Петр", 35, "petya@yandex.ru", "+7(095)2333222"),'+
                '("Федоров", "Федор", 25, "fed@inbox.ru", "+7(922)2424567");'
        tx.executeSql(sql);
    }
}

function addContact(tx, first_name, last_name, age, email, phone) {
    const sql =
        'INSERT INTO contacts (first_name, last_name, age, email, phone)' +
        'VALUES("%1", "%2", "%3", "%4","%5");'.arg(first_name).arg(last_name).arg(age).arg(email).arg(phone)
    return tx.executeSql(sql)
}

function updateValue(tx, table_name, idx, column_name, new_value){
    const sql = `UPDATE ${table_name} SET ${column_name} = '${new_value}' where id = ${idx}`;
    return tx.executeSql(sql)
}

function readContacts(tx, model){
    const sql = "SELECT id, first_name, last_name, age, email, phone from contacts";
    var res = tx.executeSql(sql);
    for (let i = 0; i<res.rows.length; i++){
        let item = res.rows[i];
        model.appendRow({id: item.id,
                        first_name: item.first_name,
                        last_name: item.last_name,
                        age: item.age,
                        email: item.email,
                        phone: item.phone});
    }
}


function createCarsTable(tx) {
    var sql =
        'CREATE TABLE IF NOT EXISTS cars (' +
        'id INTEGER PRIMARY KEY AUTOINCREMENT,' +
        'owner_id INTEGER NOT NULL,' +
        'brand TEXT(30) NOT NULL,' +
        'model TEXT(30) NOT NULL,' +
        'color TEXT(30) NOT NULL,' +
        'FOREIGN KEY(owner_id) REFERENCES contacts(id)' +
    ');'
    tx.executeSql(sql);

    sql = "SELECT * FROM cars";
    if(tx.executeSql(sql).rows.length==0){
        sql =
                'INSERT INTO cars (owner_id,brand,model,color)' +
                'VALUES'+
                '(1, "BMW", "i7", "Черный"),'+
                '(1, "Ford", "Focus", "Белый"),'+
                '(2, "Лада", "Веста", "Красный");'
        tx.executeSql(sql);
    }
}

function addCar(tx, owner_id, brand, model, color) {
    const sql =
        'INSERT INTO cars (owner_id, brand, model, color)' +
        'VALUES("%1", "%2", "%3", "%4");'.arg(owner_id).arg(brand).arg(model).arg(color)
    return tx.executeSql(sql)
}

function readCars(tx, model){
    const sql = "SELECT id, owner_id, brand, model, color from cars";
    var res = tx.executeSql(sql);
    for (let i = 0; i<res.rows.length; i++){
        let item = res.rows[i];
        model.appendRow({id: item.id,
                        owner_id: item.owner_id,
                        brand: item.brand,
                        model: item.model,
                        color: item.color});
    }
}
