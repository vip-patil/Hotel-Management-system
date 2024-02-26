
# Hotel management system
---

![Login page](https://github.com/vip-patil/Hotel-Management-system/blob/main/images/Screenshot%202024-02-26%20122427.png)

- This is a C program that aims to meet the needs of a Hotel Management system.
- The program covers essential functionalities for managing customer records, including adding, listing, deleting, searching, and editing records.
- The login feature adds a layer of security, ensuring that only authorized users can access the system.
- The use of console colors enhances the visual appeal and readability of the interface
- The code is logically organized into functions
- Error handling is present in functions like file opening (fopen) and checking for existing room numbers.
- The program reads and writes entire struct CustomerDetails objects directly to and from the file, which is efficient.
## Code description
---
![Menu](https://github.com/vip-patil/Hotel-Management-system/blob/main/images/Screenshot%202024-02-26%20122438.png)

### Header files
- <stdio.h> - provides standard input-output functons like printf() and scanf().
- <conio.h> - provides console input-output functions like getch() and  getche().
- <ctype.h> - provides functions like toupper() and tolower() for character handling and manipulation.
- <stdlib.h> - provides general utilities like malloc(), rand() and exit().
- <time.h> - time() function for working with data.
-  <string.h> - functions like strcpy() and strlen() and for handling charcter array.
- <windows.h> - for setting console text color with the "SetConsoleTextAttribute()" function.

### font color
- void setcolor(int ForgC, int BackC) - The function takes a color code as input and changes the text color in the console window to the specifed color.
   1. Black
  2. Blue
  3. Green
  4. Cyan
  5. Red
  6. Magenta
  7. Yellow (Brown)
  8. Light Gray
  9. Dark Gray
  10. Light Blue
  11. Light Green
  12. Light Cyan
  13. Light Red
  14. Light Magenta
  15. Light Yellow
  16. White

### void add()
![Adding Customer data](https://github.com/vip-patil/Hotel-Management-system/blob/main/images/Screenshot%202024-02-26%20122603.png)

 - The function begins by attempting to open a file in append mode. if file doesn't exsist, it creates by opening in write binary mode.
- checkRoomNumberExists(s.roomnumber) - function checks if room number already exists.
- If the key entered is escape(27), function breaks

### void list() 
- The records are read from file into an array.
- The record is sorted in ascenting order using bubble sort.
-  The sorted sorted record is printed in specifed manner.
![Displaying the customer data](https://github.com/vip-patil/Hotel-Management-system/blob/main/images/Screenshot%202024-02-26%20122620.png)


### void delete1() 
- extra temp.dat file is created in write mode.
- The room number is compared with each record.
- If match found, the "found" flag is set to 1.
- If no record found, removes temporary file and returns.
- If found==1, the original file is removed using remove() and   temporary file is renamed using rename().

### void search() 
![Searching based on room number](https://github.com/vip-patil/Hotel-Management-system/blob/main/images/Screenshot%202024-02-26%20122654.png)

-  allows the user to search for a customer record by entering the room number.

### void edit()
 - function allows the user to edit the detail of a customer record by entering the room number.
