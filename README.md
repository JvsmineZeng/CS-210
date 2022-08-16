# CS-210

### Summarize the project and what problem it was solving.
> The Corner Grocer application acts as an inventory software for the Corner Grocer store. It initially displays a menu which shows the user 4 options:
> 1. Display an itemized list of the day's sales.
> 2. Allow the user to search for a particular item's amount of sales for the day.
> 3. Display a histogram representation of the day's sales.
> 4. Exit the application.
> <p> The program continues until the user enters option 4. Options 1-3 utilize a text file which contains a list of all products sold for the day. Simultaneously, option 3 writes to a data file which compiles a list similar to that which option 1 displays. I was tasked to build this menu with input validation, and write functions for options 1-3 which obtained (and also sorted in option 3) data by reading/writing a file. </p>

### What did you do particularly well?
> I felt I was proficient in writing complementary Python and C++ functions. I used object-oriented concepts in the Python PythonCode file to create functions organizeItemsSold, findQuantitySold, and buildHistogram which were specific to menu options 1-3, respectively. This allowed me to simply call them with minimal supplementary code in the C++ Source file. Additionally, I remembered to include the "include", "libs", and dll folders/files when setting up the IDE for release.

### Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
> Writing a function for file reading would streamline my Python functions, as all of them require file reading. I think I should also look into text alignment and formatting, if any, in order to write my print statements for the menus and headers more efficiently. In a higher level program, I would read another file listing all "valid items" which Corner Grocer sells, and use this to validate whether or not the item a user is looking up is a product available for sale, before looking for the (valid) item's quantity sold, for option 2.

### Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?
> I had trouble with the print block in Python function organizeItemsSold. Initially, I wrote similar code to the finalized function, but it would print out extra space after the item and its quantity sold despite using strip(). To solve this, I assigned variables item and quantity to functions which would retrieve just the information needed without extra spaces. I then concatenated this into a formatted print statement, which resolved the issue. However, I still do not know exactly what happened that caused the extra space, so I will be looking further into that issue online. I am also going to reference Python dictionaries, and the functions which help to pull data from said dictionaries.

### What skills from this project will be particularly transferable to other projects or course work?
> Corner Grocer has taught me how to code in more than one language for a single program; writing functions in one language and calling them from another will prove to be very useful down the line. I have also learned how to integrate languages and their respective files into the IDE. I have additionally learned how to read and write from multiple files. In whole, I am learning how to write programs with more layers and this is vital for organized, efficient, object-oriented programming.

### How did you make this program maintainable, readable, and adaptable?
>   Using two languages was a main factor in my program's efficiency. I delegated the menu to the C++ Source file, while the functions for options 1-3 of the menu were written in the Python PythonCode file. This allowed me to focus on writing specific functions for each menu option in the "background" and avoided visual and technical clutter in the main Source file. Additionally, creating a separate function for each of the menu options in the Python PythonCode file allowed me to keep each option's code in a single place, calling them in the C++ Source file solely by function name. Whenever I had bugs or issues with any of these components, I could easily locate the function containing the problem and fix it in one place.
