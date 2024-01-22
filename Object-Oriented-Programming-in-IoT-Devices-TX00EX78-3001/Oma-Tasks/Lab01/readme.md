## Simple C++ program
Write a program that defines an empty vector of integers. Then program asks user how many
numbers he/she wants to enter. Then program asks user to enter the numbers one at a time and
adds them to the vector. When all number have been entered the program prints the numbers in the
vector.<br><br>
For example:<br>

```
How many numbers do you want enter? 4
Enter nr[1]: 23
Enter nr[2]: 12
Enter nr[3]: 4
Enter nr[4]: 5
You entered: 23, 12, 4, 5
```
<br>

## Using reference parameter
Write a function that takes a reference to string and a character (by value) as parameters. The
function replaces all occurrences of the character with underscores.
Write a program that ask user to enter a string. Then program asks user to enter character to replace
or “stop” to stop the program. Note that program must read a string after the second question to be
able to test for “stop”. If answer is not “stop” then program passes the first character of second
question’s answer as the character to replace. Then program prints the string and continues. If
answer is “stop” the program ends.
<br>

For example:<br>
```
Enter a string: This is a test
Enter character to replace or “stop”: i
Result: Th_s _s a test
Enter a string: I love C++
Enter character to replace or “stop”: stop
```