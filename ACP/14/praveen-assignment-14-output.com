Reading data from input file and inserting data into the tree :
Insert 55
Insert 62
Insert 89
Insert 85
Insert 97
Insert 56
Insert 71
Insert 82
Insert 38
Insert 49
Insert 25
Insert 67
Insert 58
Insert 92
Insert 100
Insert 44
Insert 69
Insert 72
Insert 65
Insert 52
Insert 41
Insert 84
Insert 21
Insert 60
Insert 95
Insert 12
Insert 35
Insert 42
Insert 105
Insert 99
Insert 34
Insert 47
Insert 35
Insert 79
Insert 95
Insert 50
Insert 25
Insert 51
preOrder Traversal :
 55  51  50  52  47  42  41  44  49  34  35  12  21  25  38 105  99 100  95  92  97  84  79  72  82  69  65  67  71  85  89  60  58  56  62 
inOrder Traversal :
 12  21  25  34  35  38  41  42  44  47  49  50  51  52  55  56  58  60  62  65  67  69  71  72  79  82  84  85  89  92  95  97  99 100 105 
postOrder Traversal :
105  99 100  95  92  97  84  79  72  82  69  65  67  71  85  89  60  58  56  62  51  50  52  47  42  41  44  49  34  35  12  21  25  38  55 
Enter number to be deleted :
71
inOrder Traversal after deletion of 71
 12  21  25  34  35  38  41  42  44  47  49  50  51  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
51
inOrder Traversal after deletion of 51
 12  21  25  34  35  38  41  42  44  47  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
38
inOrder Traversal after deletion of 38
 12  21  25  34  35  41  42  44  47  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
5
5, not found in the tree
Enter number to be deleted :
0
0, not found in the tree
Enter number to be deleted :
25
inOrder Traversal after deletion of 25
 12  21  34  35  41  42  44  47  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
42
inOrder Traversal after deletion of 42
 12  21  34  35  41  44  47  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
91
91, not found in the tree
Enter number to be deleted :
35
inOrder Traversal after deletion of 35
 12  21  34  41  44  47  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 
Enter number to be deleted :
47
inOrder Traversal after deletion of 47
 12  21  34  41  44  49  50  52  55  56  58  60  62  65  67  69  72  79  82  84  85  89  92  95  97  99 100 105 

