# problem-solving-server-search-algorithms<br />

In this project, we used [SOLID](https://en.wikipedia.org/wiki/SOLID) principles (such as single responsibility & open/close) and design patterns (such as [Object Adapter](https://en.wikipedia.org/wiki/Adapter_pattern) & [Bridge](https://en.wikipedia.org/wiki/Bridge_pattern) patterns) to create a generic server for problem-solving and to use this server for implementing search algorithms. <br/>

### The project contains the following elements:<br />

* Use of SOLID principles, design patterns and architecture.<br />
* Communication and Client-Server Architecture.<br />
* Use of data structures.<br />
* Data Streaming (files & communication).<br />
* Use of caching.
* Parallel programming using threads.<br />
* Implementation of search algorithms.<br /><br />


### The server functionality
Building a class that implements a server, i.e., a mechanism that listens and waits for clients to connect and then handles their requests, it is a mechanism that will not necessarily be appropriate for each project.
Therefore, we have defined the functionality of the server using an interface, so that each project can have a different class that will implement the same functionality in a different way.
The principle of open/close is maintained here since adding a class that implements the same interface is an extension of the required functionality (open), without the need to change a code we have already written (close) - open for expansions but closed for changes.


#### MySerialServer
Class MySerialServer contains the start method, which has a loop that listens to the client on the port we received.
When the client connects, the server will activate the given ClientHandler to communicate with him.
At the end of the communication, the server returns to the beginning of the loop and listens to the next client.
In that way, the server handles the clients - one by one, serially.<br/>

#### MyParallelServer
Class MyParallelServer handles all clients in parallel, using threads.<br/><br/>


### Communication with clients
We build an interface called ClientHandler that aims to determine the type of conversation with the client. In that way, we can settle for only two classes for server mechanisms (MySerialServer & MyParallelServer), and to each of them, we can inject whatever implementation we want for ClientHandler.
If we want to implement additional protocols in the future, then we will only need to add ClientHandler implementation without changing or
copy the code of the server mechanisms. In that way, we maintained both the principles of single responsibility and open close.


#### MyClientHandler

Class MyClientHandler fits the following communication protocol:

* The client sends line by line until a line with the value "end" is received.

* Each line contains comma-separated integer values, and together they create a matrix of values.

* Then the client sends two additinal lines.
The first line contains two comma-separated values: the row number and the column mumber of the entrace.
The second line contains two comma-separated values: the row number and the column mumber of the exit.

* The server returns a string, with comma-separated values.
The values are from the following types: {Right, Left, Down, Up}. This string indicates the directions to move from the entrance to the exit.<br/><br/>


### Problem solving

To maintain the single responsibility and the open/close principles, we also separated the communication protocol between the client and the server (which is implemented in the classes that inherited ClientHandler) and the algorithm that solves the problem.
Otherwise, we will need one class for each possible combination of the different communication protocol with each algorithm.<br/><br/>


### Saving solutions (caching)

Calculating the solution may take a lot of time. It would be unnecessary to calculate a solution to a problem we have already solved in the past. Instead of that, we can save solutions that have been already calculated on disk. Given a problem, we will be able to check quickly if it was already been solved before, so we will get the solution from the disk instead of calculating it again. 
There may be some different implementations for saving the solutions, for example in files or a database. Therefore, we use an interface to maintain the different principles of SOLID - the CacheManager interface that manages the cache for us.<br/><br/>


### Algorithms implementation

We used the Bridge design pattern to separate the algorithm from the problem it solves.
In particular, we used the Searchable interface to define what the functionality of a search problem is and the Searcher interface for a search algorithm.<br/>

We implemented the following search algorithms:
* [Astar (A*)](https://en.wikipedia.org/wiki/A*_search_algorithm)
* [BestFirstSearch](https://en.wikipedia.org/wiki/Best-first_search)
* [BFS (Breadth-First Search)](https://en.wikipedia.org/wiki/Breadth-first_search)
* [DFS (Depth-first search)](https://en.wikipedia.org/wiki/Depth-first_search)<br/><br/>

### Empirical experiment
We did an empirical experiment to test which algorithm works best. Pseudocode:

* Define a collection of NxN size matrices for an increasing N from 10 to 50.
* Each cell in the matrices contains an integer value that represents the price of passing through that cell.
For example, 0 is free or a plain, the greater the value, the more difficult the ascent is, and infinite it is a wall that cannot be crossed.
* The entrance to the area will be defined in cell 0,0 while the exit in cell 1-N, 1-N.
* Run each of the algorithms 10 times on each of the 10 matrices and check how many vertices each algorithm has developed and whether it has solved the problem - i.e., has found the cheapest route.
* Display the data on the graph where the X axis is the N values and the Y axis is the number of vertices that each algorithm developed in average over the 10 runs.
* By the graph, you can see which algorithm is the most effective.


#### The results:
![Algorithms_Comparison](https://user-images.githubusercontent.com/45918740/98109866-f3493e00-1ea6-11eb-898d-dbe8633ad72f.png)


As you can see, the most efficient algorithm obtained is Astar, and therefore that is the algorithm we embedded on the server-side.<br/><br/><br/>


### Running example (handling multiple clients in parallel):
![running example](https://user-images.githubusercontent.com/45918740/98113257-11fe0380-1eac-11eb-8ae4-58e3cec844ae.JPG)


