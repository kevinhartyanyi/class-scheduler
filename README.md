# Class Scheduler

A simple GUI application for scheduling classes.

## Usage
Create a text file with the following structure:
```
[Subject name],[Day name/number]:[Interval],[Day name/number]:[Interval]...
[Subject2 name],[Day name/number]:[Interval],[Day name/number]:[Interval]...
[Subject3 name],[Day name/number]:[Interval],[Day name/number]:[Interval]...
...
```
[Subject name] Can be anything.

[Day name/number]
You can use numbers or days
```
Subject1,0:8-10,0:10-12,Monday:12-14
Subject2,0:8-10,Tuesday:12-14
Subject3,0:10-12
```
Where
```
0 = Monday
1 = Tuesday
2 = Wednesday
3 = Thursday
4 = Friday
```

[Interval] A time interval. (8-10, 13-18, 12-20...)


## Getting Started

Fastest way is to download a [release](https://github.com/kevinhartyanyi/class-scheduler/releases) for your system.

### Compile on your machine

To compile the code you must have qmake on your machine.
You can install it manually by the instructions in [here](https://doc.qt.io/archives/3.3/qmake-manual-2.html)
Or just download [Qt](https://www.qt.io/) and it will get installed automatically.


Once you have qmake clone this repository and execute the following commands in the repository folder:
```
qmake class_scheduler.pro  
make
```
That's it. 
You will now see an executable in the folder, that you can run.

## Built With

* [Qt](https://www.qt.io/)

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/kevinhartyanyi/class-scheduler/blob/master/LICENSE) file for details
