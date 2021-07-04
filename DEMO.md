# Example usage

```
Address Book Program
--------------------
Using database at "file:address.db"
db_menu> list
#1:
First name: Vivian
Last name: Mok
Email: vmok@yahoo.com.hk      
Telephone: 29845732
------------------------------
#2:
First name: Peter
Last name: O' Parker
Email: pp@gmail.com
Telephone: 92857292
------------------------------
#3:
First name: Oscar
Last name: Davies
Email: oscard@gmail.com
Telephone: 29847523
------------------------------
3 records in total.
db_menu> add Andy Lau andy@outlook.com 93846572 
db_menu> add Jacky Cheung jcheung@yahoo.com.hk 86592965
db_menu> list
#1:
First name: Vivian
Last name: Mok
Email: vmok@yahoo.com.hk
Telephone: 29845732
------------------------------
#2:
First name: Peter
Last name: O' Parker
Email: pp@gmail.com
Telephone: 92857292
------------------------------
#3:
First name: Oscar
Last name: Davies
Email: oscard@gmail.com
Telephone: 29847523
------------------------------
#4:
First name: Andy
Last name: Lau
Email: andy@outlook.com
Telephone: 93846572
------------------------------
#5:
First name: Jacky
Last name: Cheung
Email: jcheung@yahoo.com.hk
Telephone: 86592965
------------------------------
5 records in total.
db_menu> delete 2 
1 rows affected.
db_menu> list
#1:
First name: Vivian
Last name: Mok
Email: vmok@yahoo.com.hk
Telephone: 29845732
------------------------------
#3:
First name: Oscar
Last name: Davies
Email: oscard@gmail.com
Telephone: 29847523
------------------------------
#4:
First name: Andy
Last name: Lau
Email: andy@outlook.com
Telephone: 93846572
------------------------------
#5:
First name: Jacky
Last name: Cheung
Email: jcheung@yahoo.com.hk
Telephone: 86592965
------------------------------
4 records in total.
db_menu> get Andy Lau
#4:
First name: Andy
Last name: Lau
Email: andy@outlook.com
Telephone: 93846572
db_menu> update 4 Andy Lau andylau@outlook.com 26828593
1 rows affected.
db_menu> list
#1:
First name: Vivian
Last name: Mok
Email: vmok@yahoo.com.hk
Telephone: 29845732
------------------------------
#3:
First name: Oscar
Last name: Davies
Email: oscard@gmail.com
Telephone: 29847523
------------------------------
#4:
First name: Andy
Last name: Lau
Email: andylau@outlook.com
Telephone: 26828593
------------------------------
#5:
First name: Jacky
Last name: Cheung
Email: jcheung@yahoo.com.hk
Telephone: 86592965
------------------------------
4 records in total.
db_menu> exit
```

*All the data used above are used for testing purposes only and have no relations to real life*
