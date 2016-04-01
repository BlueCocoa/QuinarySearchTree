# Quinary Search Tree
Quinary search tree is an improved data structure of ternary search tree.

This is the basic implementation of quinary search tree. 

For more details, please see [Quinary Search Tree](https://blog.0xbbc.com/2016/04/quinary-search-tree/)

### Installation
```sudo make install```

Install to /usr/local/include by default.

### Demo
```make demo && ./demo```

### Usage

		#include <assert.h>
		#include <QuinarySearchTree.hpp>
		
		int main(int argc, const char * argv[]) {
		    QuinarySearchTree qst;
		    qst.put("key", "value");
		    assert(strcmp(qst.get("key"), "value") == 0);
		    assert(qst.get("not exists") == NULL);
		    return 0;
		}



