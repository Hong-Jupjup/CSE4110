#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")
#define MAXLINE 1000

const char* host = "localhost";
const char* user = "root";
const char* pw = "1111";
const char* db = "project2";

MYSQL* connection = NULL;
MYSQL conn;
MYSQL_RES* sql_result;
MYSQL_ROW sql_row;

void type1();
void type2();
void type3();
void type4();
void type5();
void type6();
void type7();

int main(void)
{
	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		FILE* fp = fopen("20181702_1.txt", "r");
		char cmd[MAXLINE];
		
		while (1) {
			if (feof(fp))
				break;
			fgets(cmd, MAXLINE, fp);
			mysql_query(connection, cmd);
		}

		if (cmd != NULL)
			mysql_query(connection, cmd);
		fclose(fp);

		int type;
		int flag = 1;
		while (1) {
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf("\tSelect Type: ");
			scanf("%d", &type);

			switch (type) {
				case 1: type1(); break;
				case 2: type2(); break;
				case 3: type3(); break;
				case 4: type4(); break;
				case 5: type5(); break;
				case 6: type6(); break;
				case 7: type7(); break;
				case 0: flag = 0; break;
				default: printf("Invalid Type Number!\n");
			}

			if (flag == 0)
				break;
		}

		fp = fopen("20181702_2.txt", "r");
		while (1) {
			if (feof(fp))
				break;
			fgets(cmd, MAXLINE, fp);
			mysql_query(connection, cmd);
		}
		fclose(fp);
		mysql_close(connection);
	}
	return 0;
}

void type1()
{
	/* Type 1 */
	int x;
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 1-------\n");
	printf("** Tracking Number X shipped by USPS has been destroyed in an accident. Find the contact information for the customer. **\n\n");
	printf("   Which X? (0: Exit this query): ");
	scanf("%d", &x);

	if (x == 0) return;
	else {
		char query1[MAXLINE];
		sprintf(query1, "SELECT c.Customer_ID, c.Name, c.Gender, c.Age, c.Address, c.Phone_Number, c.Card_Information FROM Customer AS c JOIN Shipment AS s WHERE s.Shipping_ID = %d and s.Customer_ID = c.Customer_ID and s.Shipping_Company = 'USPS'", x);
		state = 0;
		state = mysql_query(connection, query1);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tGender\tAge\tAddress\tPhone_Number\tCard_Information\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}
	}

	/* Type 1-1 */
	int type;
	printf("---------- Subtypes in TYPE 1 ----------\n");
	printf("\t1. TYPE 1-1\n");
	printf("\tSelect Type (0: Exit this query): ");
	scanf("%d", &type);

	if (type == 0) return;
	else if (type == 1) {
		char query2[MAXLINE];
		printf("------- TYPE 1-1 -------\n");
		printf("** Find the contents of that shipment and create a new shipment of replacement items. **\n\n");
		sprintf(query2, "SELECT s.Shipping_ID, s.Customer_ID, s.Warehouse_ID, s.Purchase_ID, s.Shipping_Company, s.Estimated_Date, s.Delivered_Date FROM Customer AS c JOIN Shipment AS s WHERE s.Shipping_ID = %d and s.Customer_ID = c.Customer_ID and s.Shipping_Company = 'USPS'", x);
		state = 0;
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tShipping_ID\tCustomer_ID\tWarehouse_ID\tPurchase_ID\tShipping_Company\tEstimated_Date\tDelivered_Date\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);

		char query3[MAXLINE];
		sprintf(query3, "UPDATE Shipment AS s JOIN Customer AS c ON s.Customer_ID = c.Customer_ID SET s.Estimated_Date = s.Estimated_Date + 7, s.Delivered_Date = s.Delivered_Date + 7 WHERE s.Shipping_ID = %d and s.Shipping_Company = 'USPS'", x);
		state = 0;
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("New Shipment Information is Updated.\n");
		}
		mysql_free_result(sql_result);
	}
	else {
		printf("Invalid Type Number!\n");
		return;
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type2()
{
	/* Type 2 */
	int state = 0;
	char query1[MAXLINE];

	printf("\n\n");
	printf("------- TYPE 2-------\n");
	printf("** Find the customer who has bought the most (by price) in the past year. **\n\n");
	sprintf(query1, "SELECT * FROM(SELECT c.Customer_ID, c.Name, c.Gender, c.Age, c.Address, c.Phone_Number, c.Card_Information, SUM(p.Purchase_Price) as sum_price FROM Customer as c JOIN (SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline WHERE year(Purchase_Datetime) = '2021') as p ON c.Customer_ID = p.Customer_ID GROUP BY c.Customer_ID) as s ORDER BY sum_price DESC LIMIT 1");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("\tID\tName\tGender\tAge\tAddress\tPhone_Number\tCard_Information\tPrice_Sum\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7]);
		}
	}
	mysql_free_result(sql_result);

	/* Type 2-1 */
	int type;
	printf("---------- Subtypes in TYPE 2 ----------\n");
	printf("\t1. TYPE 2-1\n");
	printf("\tSelect Type (0: Exit this query): ");
	scanf("%d", &type);

	if (type == 0) return;
	else if (type == 1) {
		char query2[MAXLINE];
		printf("------- TYPE 2-1 -------\n");
		printf("** Find the product that the customer bought the most. **\n\n");
		sprintf(query2, "select * from Product as pp JOIN(select product_id, sum(product_number) as num_sum from(select * from(SELECT * FROM purchase_online UNION SELECT * FROM purchase_offline WHERE year(Purchase_Datetime) = '2021') as f where f.customer_id = (SELECT customer_ID FROM(SELECT c.Customer_ID, c.Name, c.Gender, c.Age, c.Address, c.Phone_Number, c.Card_Information, SUM(p.Purchase_Price) as sum_price FROM customer as c JOIN(SELECT * FROM purchase_online UNION SELECT * FROM purchase_offline WHERE year(Purchase_Datetime) = '2021') as p ON c.Customer_ID = p.Customer_ID GROUP BY c.Customer_ID) as s ORDER BY sum_price DESC LIMIT 1)) as g group by g.Product_ID order by num_sum desc limit 1) as h where pp.Product_ID = h.Product_ID");
		state = 0;
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tCategory\tPrice\tManufacturer\tNum_Sum\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	else {
		printf("Invalid Type Number!\n");
		return;
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type3()
{
	/* Type 3 */
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 3-------\n");
	printf("** Find all products sold in the past year. **\n\n");
	
	char query1[MAXLINE];
	sprintf(query1, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Purchase_Price) FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID ORDER BY p.Product_ID");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("\tID\tName\tCategory\tPrice\tManufacturer\tPrice_Sum\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
		}
		printf("\n");
		mysql_free_result(sql_result);
	}

	int type;
	printf("---------- Subtypes in TYPE 3 ----------\n");
	printf("\t1. TYPE 3-1\n");
	printf("\t2. TYPE 3-2\n");
	printf("\tSelect Type (0: Exit this query): ");
	scanf("%d", &type);

	if (type == 0)
		return;
	else if (type == 1) { /* Type 3-1 */
		int k;
		char query2[MAXLINE];
		printf("------- TYPE 3-1 -------\n");
		printf("** Find the top k products by dollar-amount sold. **\n\n");
		printf("   Which K? (0: Exit this query): ");
		scanf("%d", &k);

		sprintf(query2, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Purchase_Price) as sum_price FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID ORDER BY sum_price DESC LIMIT %d", k);
		state = 0;
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tCategory\tPrice\tManufacturer\tPrice_Sum\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	else if (type == 2) { /* Type 3-2 */
		int k;
		char query3[MAXLINE];
		printf("------- TYPE 3-2 -------\n");
		printf("** Find the top 10%% products by dollar-amount sold. **\n\n");

		sprintf(query3, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Purchase_Price) as sum_price, percent_rank() over(order by SUM(Purchase_Price) desc) as percent FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID and p2.percent <= 0.1 ORDER BY sum_price DESC");
		state = 0;
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tCategory\tPrice\tManufacturer\tPrice_Sum\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	else {
		printf("Invalid Type Number!\n");
		return;
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type4()
{
	/* Type 4 */
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 4-------\n");
	printf("** Find all products by unit sales in the past year. **\n\n");

	char query1[MAXLINE];
	sprintf(query1, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Product_Number) FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID ORDER BY p.Product_ID");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("\tID\tName\tCategory\tPrice\tManufacturer\tNum_Sum\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
		}
		printf("\n");
		mysql_free_result(sql_result);
	}

	int type;
	printf("---------- Subtypes in TYPE 4 ----------\n");
	printf("\t1. TYPE 4-1\n");
	printf("\t2. TYPE 4-2\n");
	printf("\tSelect Type (0: Exit this query): ");
	scanf("%d", &type);

	if (type == 0)
		return;
	else if (type == 1) { /* Type 4-1 */
		int k;
		char query2[MAXLINE];
		printf("------- TYPE 4-1 -------\n");
		printf("** Find the top k products by unit sales. **\n\n");
		printf("   Which K? (0: Exit this query): ");
		scanf("%d", &k);

		sprintf(query2, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Product_Number) as sum_price FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID ORDER BY sum_price DESC LIMIT %d", k);
		state = 0;
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tCategory\tPrice\tManufacturer\tNum_Sum\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	else if (type == 2) { /* Type 4-2 */
		int k;
		char query3[MAXLINE];
		printf("------- TYPE 4-2 -------\n");
		printf("** Find the top 10%% products by unit sales. **\n\n");

		sprintf(query3, "SELECT * FROM PRODUCT as p JOIN(SELECT Product_ID, SUM(Product_Number) as sum_price, percent_rank() over(order by SUM(Product_Number) desc) as percent FROM(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE Year(Purchase_Datetime) = '2021' GROUP BY Purchase.Product_ID) as p2 WHERE p.Product_ID = p2.Product_ID and p2.percent <= 0.1 ORDER BY sum_price DESC");
		state = 0;
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("\tID\tName\tCategory\tPrice\tManufacturer\tNum_Sum\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[6]);
			}
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	else {
		printf("Invalid Type Number!\n");
		return;
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type5()
{
	/* Type 5 */
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 5-------\n");
	printf("** Find those products that are out-of-stock at every store in California. **\n\n");
	char query1[MAXLINE];
	sprintf(query1, "SELECT DISTINCT * FROM Product JOIN(SELECT DISTINCT Product_ID FROM(SELECT * FROM Stock_Online as son WHERE son.Product_Stock = '0' UNION SELECT * FROM Stock_Offline as soff WHERE soff.Product_Stock = '0') as a) as b WHERE Product.Product_ID = b.Product_ID");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("\tID\tName\tCategory\tPrice\tManufacturer\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
		}
		printf("\n");
		mysql_free_result(sql_result);
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type6()
{
	/* Type 6 */
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 6-------\n");
	printf("** Find those packages that were not delivered within the promised time. **\n\n");
	char query1[MAXLINE];
	sprintf(query1, "SELECT p.Product_ID, p.Name, p.Category, p.Price, p.Manufacturer FROM Purchase_Online as pon JOIN Product as p WHERE pon.Product_ID = p.Product_ID and pon.Purchase_ID in (SELECT s.Purchase_ID FROM Shipment as s WHERE Estimated_Date < Delivered_Date)");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("\tID\tName\tCategory\tPrice\tManufacturer\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
		}
		printf("\n");
		mysql_free_result(sql_result);
	}

	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}

void type7()
{
	/* Type 7 */
	int state = 0;

	printf("\n\n");
	printf("------- TYPE 7-------\n");
	printf("** Generate the bill for each customer for the past month **\n\n");
	char query1[MAXLINE];
	sprintf(query1, "SELECT * FROM Customer as c JOIN(SELECT * FROM Purchase_Online UNION SELECT * FROM Purchase_Offline) as Purchase WHERE c.Customer_ID = Purchase.Customer_ID and Month(Purchase_Datetime) = '05' and Year(Purchase_Datetime) = '2022' ORDER BY c.Customer_ID, Purchase_Datetime");
	state = 0;
	state = mysql_query(connection, query1);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("If the fisrt letter of Warehouse_ID is 8, the purchase is on offline and if it is 9, it is on online.\n");
		printf("\tCustomer_ID\tCustomer_Name\tCard_Information\tPurchase_ID\tWarehouse_ID\tProduct_ID\tProduct_Number\tPurchase_Price\tPurchase_Datetime\tPurchase_Method\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[6], sql_row[7], sql_row[9], sql_row[10], sql_row[11], sql_row[12], sql_row[13], sql_row[14]);
		}
		printf("\n");
		mysql_free_result(sql_result);
	}
	printf("To go back to select menu, press 0\n");
	int zero;
	while (1) {
		scanf("%d", &zero);
		if (zero == 0)
			break;
	}

	return;
}