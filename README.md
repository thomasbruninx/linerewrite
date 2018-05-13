# LineReWrite
A simple line by line text editor

## What is it?
LineReWrite is just a simple and small text editor which allows you to edit a text file line by line.
It started out as a fun little coding excercise and it became an actual program.

## Why would you make something like this?
Just for fun and giggles! Isn't coding supposed to be like that?

## How does it work?
It's easy! Just build and install the application and Bob is your uncle.

### Basic usage
```
$>rewrite [FILENAME] [LINE_NR] [OPTIONS]
```
The options you can use are B for Backup, I for Insert, M for Multiline, R for Remove, P for Print, N for No Change. For more information look at the examples bellow. Beware! LINE_NR starts at 0

## Examples
### Editing the first line of a file
```
$>rewrite filename.txt 0
```

### Editing multiple lines starting at line 7
```
$>rewrite filename.txt 7 m
```
If you want to stop editing just press enter on an empty line. (BTW this also works in single line mode in case you changed your mind and you don't want to change the line

### Show the contents (starting at line 4) of the file before editing
```
$>rewrite filename.txt 4 p
```

### Show the contents of my entire file without editing
```
$>rewrite filename.txt 0 pn
```

### Make a backup of my file before I edit it
```
$>rewrite filename.txt 5 b
```

### I don't want to edit, I just want to remove line 14
```
$>rewrite filename.txt 14 r
```

### Insert a new line before line 6
```
$>rewrite filename.txt 6 i
```

### Show the built-in help function
```
$>rewrite
```
Yes, it's that simple!

### And how do I build and install this application?
```
$>build make install
```
Hence the makefile I provided you with, dummy!

## What are your future plans with this?
I don't know yet, you tell me! If you've got ideas or suggestions on what I should do, hit me up. Also if you'd find a bug or any other issue with this let me know. You can do this via Github or send me an e-mail at: thomas-bruninx(at)telenet.be
