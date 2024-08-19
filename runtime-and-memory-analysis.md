Worst case running time for each LoadCourseDataFromFile function:

Vector: O(n) + O(n) = O(2n) or simply O(n), where n is the number of lines in the file.
Analysis:
Opening the file and checking if it can be opened: O(1)
For the first for loop, it iterates each line, n, and there are operations performed inside of the loop, each of which are O(1), thus the time complexity is O(n).
Rewinding the file is O(1).
The second for loop is similar to the first in that it iterates over each line and performs some O(1) operations, thus the time complexity for this loop is O(n).
Closing the file is O(1).

HashTable: O(n * p * n) or O(n^2 + p), where n is the number of lines in the file and p is the average number of prerequisites per course.
Analysis:
Opening the file and checking if it can be opened: O(1)
For the first for loop, it iterates each line, n, and there are operations performed inside of the loop, each of which are O(1), thus the time complexity is O(n).
Rewinding the file is O(1).
The second for loop iterates over each line in the file, so O(n). Hashing in this loop occurs which at its worst case is O(k), where k represents the length of the course number, which should be insignificant. Finally, the worst case of appending a course to the hash table is O(m) due to collisions, where m is the number of elements in the bucket. The time complexity for this loop is O(n*m).
The third loop iterates over the number of lines, n, an inner loop iterates over each prerequisite in a course, p, and there is also a check to see if a prerequisite exists in courseNumbers, thus the time complexity is O(n*p*n).
Closing the file is O(1).

BinaryTree: O(n * p * n) or O(n^2 + p), where n is the number of lines in the file and p is the average number of prerequisites per course. The worst case for this is actually worse than the HashTable because of the O(n^2) complexity of the second loop of my LoadCourseDataFromFile function for binary trees - the worst case is is when an unbalanced tree is encountered, and the insertion time is O(n).
Analysis:
Opening the file and checking if it can be opened: O(1)
For the first for loop, it iterates each line, n, and there are operations performed inside of the loop, each of which are O(1), thus the time complexity is O(n).
Rewinding the file is O(1).
The second for loop iterates over each line in the file, so O(n). Inserting a course into the binary tree has a worst case runtime of O(n) due to the potential to encounter an unbalanced tree, thus O(n^2).
The third loop iterates over the number of lines, n, an inner loop iterates over each prerequisite in a course, p, and there is also a check to see if a prerequisite exists in courseNumbers, thus the time complexity is O(n*p*n).
Closing the file is O(1).

---

Advantages and Disadvantages:
Vector: Using a vector to store course data provides simplicity and ease of implementation. The vector data structure can dynamically resize, allowing for efficient memory usage as new courses are added. Accessing elements by index is very fast, with a time complexity of O(1). However, searching for a specific course by number requires a linear search, resulting in a time complexity of O(n), which can be inefficient for large datasets. Additionally, inserting elements in a sorted order or maintaining the order requires additional operations, further increasing the complexity. Overall, vectors are beneficial for smaller datasets, but they might not scale well for larger or more complex datasets requiring frequent searches or sorted order maintenance.

HashTable: HashTables offer efficient average-time complexity for insertions, deletions, and lookups, typically O(1), making them a good candidate for large datasets where quick access is important. By using a hash function, courses can be quickly located based on their course number. However, hash tables come with several disadvantages. They require careful handling of collisions, which can degrade performance to O(n) in the worst case. Hash functions also need to be well-designed to minimize collisions. Hash tables do not maintain any order of the elements, so sorting the data for operations like printing in alphanumeric order requires additional handling, making them less suitable when ordered traversal of data is frequently required.

BinaryTree: BinaryTrees, particularly binary search trees, offer a balanced trade-off between search efficiency and order maintenance. Searching, inserting, and deleting nodes typically have a time complexity of O(log⁡n) if the tree is balanced. An in-order traversal of the tree inherently provides the data in sorted order, making it efficient for printing courses in alphanumeric order. However, the performance of binary trees can degrade to O(n) in the worst case if the tree becomes unbalanced, resembling a linked list. Despite these challenges, binary trees are advantageous for applications requiring both efficient search operations and ordered data traversal.

---

Recommendation:
Based on the analysis of the three data structures, I recommend using a BinaryTree for storing and managing course data. The BinaryTree data structure offers a balanced approach, with efficient search, insertion, and deletion operations typically performing at O(log⁡n) when the tree is balanced. This efficiency is important for large datasets. Additionally, the binary tree's ability to perform in-order traversal naturally provides the courses in sorted order, which aligns perfectly with the requirement to print courses alphanumerically. While vectors are simple and hash tables provide fast lookups, they both fall short in maintaining order and handling dynamic data efficiently. Therefore, the binary tree is the best choice for combining search efficiency and maintaining sorted order.