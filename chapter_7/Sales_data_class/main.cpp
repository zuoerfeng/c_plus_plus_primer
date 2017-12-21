#include <iostream>
using std::cerr; using std::cin; using std::cout; using std::endl;

#include "Sales_data.h"

int main()
{
    //test1
	Sales_data total;         // variable to hold the running sum
 //   Sales_data a(cin);
	if (read(cin, total))  {  // read the first transaction
		Sales_data trans;     // variable to hold data for the next transaction
		while(read(cin, trans)) {      // read the remaining transactions
			if (total.isbn() == trans.isbn())   // check the isbns
				total.combine(trans);  // update the running total
			else {
				print(cout, total) << endl;  // print the results
				total = trans;               // process the next book
			}
		}
		print(cout, total) << endl;          // print the last transaction
	} else {                                 // there was no input
		cerr << "No data?!" << endl;         // notify the user
	}

    //test2
    Sales_data data1, data2;
	if (read(cin, data1) && read(cin, data2)) {  // read the transactions
		if (data1.isbn() == data2.isbn()) {      // check isbns
			data1.combine(data2);                // add the transactions
			print(cout, data1);                  // print the results
			cout << endl;                        // followed by a newline
		}
	} else
		cerr << "Input failed!" << endl;
	return 0;
}
